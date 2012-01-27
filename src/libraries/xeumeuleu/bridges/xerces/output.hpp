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
#include <xeumeuleu/streams/detail/output_base.hpp>
#include <xeumeuleu/bridges/xerces/detail/xerces.hpp>
#include <xeumeuleu/bridges/xerces/detail/chained_exception.hpp>
#include <xeumeuleu/bridges/xerces/detail/translate.hpp>
#include <xeumeuleu/bridges/xerces/detail/import.hpp>
#include <sstream>
#include <limits>
#include <memory>

#define XEUMEULEU_TRY try {
#define XEUMEULEU_CATCH } \
            catch( const XERCES_CPP_NAMESPACE::OutOfMemoryException& ) { throw exception( "Out of memory" ); } \
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
class output : public output_base
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
    virtual void start( const std::string* ns, const std::string& tag )
    {
        XEUMEULEU_TRY
            if( ns )
            {
                current_ = current_->appendChild( document_.createElementNS( translate( *ns ), translate( tag ) ) );
                const XMLCh* prefix = lookupPrefix( *current_, translate( *ns ) );
                if( prefix )
                    current_->setPrefix( prefix );
            }
            else
            {
                const XMLCh* defaultNs =
                    current_->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::DOCUMENT_NODE ? 0 : current_->lookupNamespaceURI( 0 );
                if( defaultNs )
                    current_ = current_->appendChild( document_.createElementNS( defaultNs, translate( tag ) ) );
                else
                    current_ = current_->appendChild( document_.createElement( translate( tag ) ) );
            }
        XEUMEULEU_CATCH
    }
    virtual void end()
    {
        XEUMEULEU_TRY
            if( is_root() )
                throw exception( "Illegal 'end' from root level" );
            current_ = current_->getParentNode();
            if( flushable_ && is_root() )
                flushable_->flush();
        XEUMEULEU_CATCH
    }

    virtual void write( const std::string& value )
    {
        XEUMEULEU_TRY
            current_->appendChild( document_.createTextNode( translate( value ) ) );
        XEUMEULEU_CATCH
    }
    virtual void write( bool value )
    {
        XEUMEULEU_TRY
            write( serialize( value ) );
        XEUMEULEU_CATCH
    }
    virtual void write( int value )
    {
        XEUMEULEU_TRY
            write( serialize( value ) );
        XEUMEULEU_CATCH
    }
    virtual void write( long value )
    {
        XEUMEULEU_TRY
            write( serialize( value ) );
        XEUMEULEU_CATCH
    }
    virtual void write( long long value )
    {
        XEUMEULEU_TRY
            write( serialize( value ) );
        XEUMEULEU_CATCH
    }
    virtual void write( float value )
    {
        XEUMEULEU_TRY
            write( serialize( value ) );
        XEUMEULEU_CATCH
    }
    virtual void write( double value )
    {
        XEUMEULEU_TRY
            write( serialize( value ) );
        XEUMEULEU_CATCH
    }
    virtual void write( long double value )
    {
        XEUMEULEU_TRY
            write( serialize( value ) );
        XEUMEULEU_CATCH
    }
    virtual void write( unsigned int value )
    {
        XEUMEULEU_TRY
            write( serialize( value ) );
        XEUMEULEU_CATCH
    }
    virtual void write( unsigned long value )
    {
        XEUMEULEU_TRY
            write( serialize( value ) );
        XEUMEULEU_CATCH
    }
    virtual void write( unsigned long long value )
    {
        XEUMEULEU_TRY
            write( serialize( value ) );
        XEUMEULEU_CATCH
    }

    virtual void cdata( const std::string& value )
    {
        XEUMEULEU_TRY
            current_->appendChild( document_.createCDATASection( translate( value ) ) );
        XEUMEULEU_CATCH
    }
    virtual void instruction( const std::string& target, const std::string& data )
    {
        XEUMEULEU_TRY
            current_->appendChild( document_.createProcessingInstruction( translate( target ), translate( data ) ) );
        XEUMEULEU_CATCH
    }
    virtual void prefix( const std::string& ns, const std::string& prefix )
    {
        XEUMEULEU_TRY
            XERCES_CPP_NAMESPACE::DOMNamedNodeMap* attributes = current_->getAttributes();
            if( ! attributes )
                throw exception( location() + " cannot have attributes" );
            const std::string p = prefix.empty() ? "xmlns" : "xmlns:" + prefix;
            XERCES_CPP_NAMESPACE::DOMAttr* att = document_.createAttributeNS( XERCES_CPP_NAMESPACE::XMLUni::fgXMLNSURIName, translate( p ) );
            att->setValue( translate( ns ) );
            attributes->setNamedItemNS( att );
            if( ! current_->getPrefix() && current_->getNamespaceURI() == translate( ns ) )
                current_->setPrefix( translate( prefix ) );
        XEUMEULEU_CATCH
    }

    virtual std::auto_ptr< output_base > attribute( const std::string* ns, const std::string& name )
    {
        XEUMEULEU_TRY
            XERCES_CPP_NAMESPACE::DOMNamedNodeMap* attributes = current_->getAttributes();
            if( ! attributes )
                throw exception( location() + " cannot have attributes" );
            XERCES_CPP_NAMESPACE::DOMAttr* att = ns ? create_attribute( *attributes, *ns, name ) : create_attribute( *attributes, name );
            return std::auto_ptr< output_base >( new output( document_, *att ) );
        XEUMEULEU_CATCH
    }

    virtual void copy( const input_base& input )
    {
        input.copy( *this );
    }

    void copy( const XERCES_CPP_NAMESPACE::DOMNode& node )
    {
        XEUMEULEU_TRY
            import( document_, node.getFirstChild(), *current_ );
            const XERCES_CPP_NAMESPACE::DOMNamedNodeMap* from = node.getAttributes();
            XERCES_CPP_NAMESPACE::DOMNamedNodeMap* to = current_->getAttributes();
            if( from && to )
                for( XMLSize_t index = 0; index < from->getLength(); ++index )
                    to->setNamedItem( document_.importNode( from->item( index ), false ) );
        XEUMEULEU_CATCH
    }

    virtual std::auto_ptr< output_base > branch() const
    {
        XEUMEULEU_TRY
            return std::auto_ptr< output_base >( new output( document_, *current_ ) );
        XEUMEULEU_CATCH
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
        return "Node '" + translate( current_->getNodeName() ) + "'";
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

    XERCES_CPP_NAMESPACE::DOMAttr* create_attribute( XERCES_CPP_NAMESPACE::DOMNamedNodeMap& attributes, const std::string& ns, const std::string& name )
    {
        XERCES_CPP_NAMESPACE::DOMAttr* att = document_.createAttributeNS( translate( ns ), translate( name ) );
        attributes.setNamedItemNS( att );
        const XMLCh* prefix = lookupPrefix( *current_, translate( ns ) );
        if( prefix )
            att->setPrefix( prefix );
        return att;
    }
    XERCES_CPP_NAMESPACE::DOMAttr* create_attribute( XERCES_CPP_NAMESPACE::DOMNamedNodeMap& attributes, const std::string& name )
    {
        XERCES_CPP_NAMESPACE::DOMAttr* att = document_.createAttribute( translate( name ) );
        attributes.setNamedItem( att );
        return att;
    }

    bool is_root() const
    {
        return current_ == &root_;
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

#undef XEUMEULEU_TRY
#undef XEUMEULEU_CATCH

#endif // xeumeuleu_output_hpp
