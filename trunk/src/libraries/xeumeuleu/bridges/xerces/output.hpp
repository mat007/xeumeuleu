/*
 *   Copyright (c) 2006, Mathieu Champlon
 *   All rights reserved.
 *
 *   Redistribution  and use  in source  and binary  forms, with  or without
 *   modification, are permitted provided  that the following conditions are
 *   met :
 *
 *   . Redistributions  of  source  code  must  retain  the  above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   . Redistributions in  binary form  must reproduce  the above  copyright
 *     notice, this list of conditions  and the following disclaimer in  the
 *     documentation and/or other materials provided with the distribution.
 *
 *   . Neither  the name  of  the  copyright  holders  nor the names  of the
 *     contributors may be used to endorse  or promote products derived from
 *     this software without specific prior written permission.
 *
 *   THIS SOFTWARE  IS  PROVIDED  BY THE  COPYRIGHT HOLDERS  AND CONTRIBUTORS
 *   ``AS IS''  AND ANY  EXPRESS OR  IMPLIED WARRANTIES,  INCLUDING,  BUT NOT
 *   LIMITED TO, THE IMPLIED  WARRANTIES  OF MERCHANTABILITY AND  FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE THE COPYRIGHT
 *   OWNERS OR CONTRIBUTORS  BE LIABLE FOR ANY  DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL,  EXEMPLARY,  OR  CONSEQUENTIAL   DAMAGES  (INCLUDING,  BUT  NOT
 *   LIMITED TO,  PROCUREMENT OF SUBSTITUTE  GOODS OR SERVICES;  LOSS OF USE,
 *   DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED  AND ON  ANY
 *   THEORY  OF  LIABILITY,  WHETHER IN  CONTRACT,  STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY  WAY  OUT OF  THE USE
 *   OF THIS SOFTWARE, EVEN  IF  ADVISED OF  THE POSSIBILITY  OF SUCH DAMAGE.
 */

#ifndef xeumeuleu_output_hpp
#define xeumeuleu_output_hpp

#include <xeumeuleu/streams/exception.hpp>
#include <xeumeuleu/streams/detail/flushable.hpp>
#include <xeumeuleu/bridges/xerces/detail/xerces.hpp>
#include <xeumeuleu/bridges/xerces/detail/trim.hpp>
#include <xeumeuleu/bridges/xerces/detail/chained_exception.hpp>
#include <xeumeuleu/bridges/xerces/detail/translate.hpp>
#include <xeumeuleu/bridges/xerces/detail/import.hpp>
#include <limits>
#include <sstream>
#include <memory>

#define TRY try {
#define CATCH } \
            catch( const XERCES_CPP_NAMESPACE::OutOfMemoryException& ) { throw xml::exception( "Out of memory" ); } \
            catch( const XERCES_CPP_NAMESPACE::XMLException& e ) { throw chained_exception( e ); } \
            catch( const XERCES_CPP_NAMESPACE::DOMException& e ) { throw chained_exception( e ); }

namespace xml
{
// =============================================================================
/** @class  output
    @brief  Output
*/
// Created: MAT 2006-01-04
// =============================================================================
class output
{
public:
    //! @name Constructors/Destructor
    //@{
    output( XERCES_CPP_NAMESPACE::DOMDocument& document, XERCES_CPP_NAMESPACE::DOMNode& root )
        : document_ ( document )
        , root_     ( root )
        , current_  ( &root )
        , flushable_( 0 )
    {}
    output( XERCES_CPP_NAMESPACE::DOMDocument& document, XERCES_CPP_NAMESPACE::DOMNode& root, flushable& flushable )
        : document_ ( document )
        , root_     ( root )
        , current_  ( &root )
        , flushable_( &flushable )
    {}
    virtual ~output()
    {}
    //@}

    //! @name Operations
    //@{
    void start( const std::string& tag )
    {
        TRY
            current_ = current_->appendChild( document_.createElement( translate( trim( tag ) ) ) );
        CATCH
    }
    void end()
    {
        TRY
            if( is_root() )
                throw xml::exception( "Illegal 'end' from root level" );
            current_ = current_->getParentNode();
            if( flushable_ && is_root() )
                flushable_->flush();
        CATCH
    }

    void write( const std::string& value )
    {
        TRY
            current_->appendChild( document_.createTextNode( translate( value ) ) );
        CATCH
    }
    template< typename T > void write( T value )
    {
        TRY
            write( serialize( value ) );
        CATCH
    }

    void cdata( const std::string& value )
    {
        TRY
            current_->appendChild( document_.createCDATASection( translate( value ) ) );
        CATCH
    }
    void instruction( const std::string& target, const std::string& data )
    {
        TRY
            current_->appendChild( document_.createProcessingInstruction( translate( target ), translate( data ) ) );
        CATCH
    }

    void attribute( const std::string& name, const std::string& value )
    {
        TRY
            XERCES_CPP_NAMESPACE::DOMNamedNodeMap* attributes = current_->getAttributes();
            if( ! attributes )
                throw xml::exception( location() + " cannot have attributes" );
            XERCES_CPP_NAMESPACE::DOMAttr* att = document_.createAttribute( translate( trim( name ) ) );
            att->setValue( translate( value ) );
            attributes->setNamedItem( att );
        CATCH
    }
    template< typename T > void attribute( const std::string& name, T value )
    {
        TRY
            attribute( name, serialize( value ) );
        CATCH
    }

    void copy( const XERCES_CPP_NAMESPACE::DOMNode& node )
    {
        TRY
            import( document_, node.getFirstChild(), *current_ );
            const XERCES_CPP_NAMESPACE::DOMNamedNodeMap* from = node.getAttributes();
            XERCES_CPP_NAMESPACE::DOMNamedNodeMap* to = current_->getAttributes();
            if( from && to )
                for( XMLSize_t index = 0; index < from->getLength(); ++index )
                    to->setNamedItem( document_.importNode( from->item( index ), false ) );
        CATCH
    }

    std::auto_ptr< output > branch() const
    {
        TRY
            return std::auto_ptr< output >( new output( document_, *current_ ) );
        CATCH
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    output( const output& );            //!< Copy constructor
    output& operator=( const output& ); //!< Assignment operator
    //@}

    //! @name Helpers
    //@{
    std::string location() const
    {
        return "node '" + std::string( translate( current_->getNodeName() ) ) + "'";
    }

    std::string serialize( float value ) const
    {
        return convert( value );
    }
    std::string serialize( double value ) const
    {
        return convert( value );
    }
    std::string serialize( long double value ) const
    {
        if( value == std::numeric_limits< long double >::infinity() )
            return "INF";
        if( value == - std::numeric_limits< long double >::infinity() )
            return "-INF";
        if( value != value )
            return "NaN";
        char buffer[255];
#ifdef _MSC_VER
#   pragma warning( push )
#   pragma warning( disable : 4996 )
#endif
        sprintf( buffer, "%Lg", value );
#ifdef _MSC_VER
#   pragma warning( pop )
#endif
        return buffer;
    }
    template< typename T > std::string serialize( T value ) const
    {
        std::stringstream stream;
        stream << std::boolalpha << value;
        return stream.str();
    }

    bool is_root() const
    {
        return current_ == &root_;
    }

    template< typename T > inline std::string convert( T value ) const
    {
        if( value == std::numeric_limits< T >::infinity() )
            return "INF";
        if( value == - std::numeric_limits< T >::infinity() )
            return "-INF";
        if( value != value )
            return "NaN";
        char buffer[255];
#ifdef _MSC_VER
#   pragma warning( push )
#   pragma warning( disable : 4996 )
#endif
        sprintf( buffer, "%g", value );
#ifdef _MSC_VER
#   pragma warning( pop )
#endif
        return buffer;
    }
    //@}

private:
    //! @name Member data
    //@{
    XERCES_CPP_NAMESPACE::DOMDocument& document_;
    XERCES_CPP_NAMESPACE::DOMNode& root_;
    XERCES_CPP_NAMESPACE::DOMNode* current_;
    flushable* flushable_;
    //@}
};

}

#undef TRY
#undef CATCH

#endif // xeumeuleu_output_hpp