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

#ifndef xeumeuleu_input_imp_h
#define xeumeuleu_input_imp_h

#include "input_base.h"
#include "chained_exception.h"
#include "xerces.h"
#include "translate.h"
#include "trim.h"
#include "exception.h"
#include "visitor.h"
#include "locator.h"
#include "output.h"
#include <limits>
#include <string>

#define TRY try {
#define CATCH } \
            catch( const XERCES_CPP_NAMESPACE::OutOfMemoryException& ) { throw xml::exception( "Out of memory" ); } \
            catch( const XERCES_CPP_NAMESPACE::XMLException& e ) { error( xml::chained_exception( e ).what() ); throw; } \
            catch( const XERCES_CPP_NAMESPACE::DOMException& e ) { error( xml::chained_exception( e ).what() ); throw; }

namespace xml
{
// =============================================================================
/** @class  input_imp
    @brief  Input implementation
*/
// Created: MAT 2006-01-08
// =============================================================================
class input_imp : public input_base
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit input_imp( const XERCES_CPP_NAMESPACE::DOMNode& root )
        : root_   ( root )
        , current_( &root_ )
    {}
    virtual ~input_imp()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string& tag )
    {
        TRY
            const XERCES_CPP_NAMESPACE::DOMNode* child = find_child( tag );
            if( ! child )
                throw xml::exception( location() + context() + " does not have a child named '" + tag + "'" );
            current_ = child;
        CATCH
    }
    virtual void end()
    {
        TRY
            if( current_ == &root_ )
                throw xml::exception( location() + "Cannot move up from " + context() );
            const XERCES_CPP_NAMESPACE::DOMNode* parent = current_->getParentNode();
            if( ! parent )
                throw xml::exception( location() + context() + " has no parent" );
            current_ = parent;
        CATCH
    }

    virtual void read( std::string& value ) const
    {
        TRY
            value = translate( read_value() );
        CATCH
    }
#define READ( type ) virtual void read( type& value ) const { TRY value = convert< type >( read_value() ); CATCH }
    READ( bool )
    READ( short )
    READ( int )
    READ( long )
    READ( long long )
    READ( float )
    READ( double )
    READ( long double )
    READ( unsigned short )
    READ( unsigned int )
    READ( unsigned long )
    READ( unsigned long long )
#undef READ

    virtual std::auto_ptr< input_base > branch( bool clone ) const;

    virtual void copy( output& destination ) const
    {
        TRY
            destination.copy( *current_ );
        CATCH
    }

    virtual void error( const std::string& message ) const
    {
        throw xml::exception( location() + message );
    }
    //@}

    //! @name Accessors
    //@{
    virtual bool has_child( const std::string& name ) const
    {
        TRY
            return find_child( name ) != 0;
        CATCH
    }
    virtual bool has_attribute( const std::string& name ) const
    {
        TRY
            return find_attribute( name ) != 0;
        CATCH
    }
    virtual bool has_content() const
    {
        TRY
            return find_content() != 0;
        CATCH
    }

    virtual void attribute( const std::string& name, std::string& value ) const
    {
        TRY
            value = translate( read_attribute( name ) );
        CATCH
    }
#define ATTRIBUTE( type ) void attribute( const std::string& name, type& value ) const { TRY value = convert< type >( read_attribute( name ) ); CATCH }
    ATTRIBUTE( bool )
    ATTRIBUTE( short )
    ATTRIBUTE( int )
    ATTRIBUTE( long )
    ATTRIBUTE( long long )
    ATTRIBUTE( float )
    ATTRIBUTE( double )
    ATTRIBUTE( long double )
    ATTRIBUTE( unsigned short )
    ATTRIBUTE( unsigned int )
    ATTRIBUTE( unsigned long )
    ATTRIBUTE( unsigned long long )
#undef ATTRIBUTE

    virtual void nodes( const visitor& v ) const;
    virtual void attributes( const visitor& v ) const;
    //@}

private:
    //! @name Helpers
    //@{
    const std::string location() const
    {
        const locator* loc = reinterpret_cast< locator* >( current_->getUserData( translate( "locator" ) ) );
        if( loc )
            return *loc;
        return "";
    }
    const std::string context() const
    {
        return "node '" + trim( translate( current_->getNodeName() ) ) + "'";
    }

    const XERCES_CPP_NAMESPACE::DOMNode* find_child( const std::string& name ) const
    {
        const XERCES_CPP_NAMESPACE::DOMNode* child = current_->getFirstChild();
        while( child )
        {
            if( trim( name ) == trim( translate( child->getNodeName() ) ) )
                return child;
            child = child->getNextSibling();
        }
        return 0;
    }
    const XERCES_CPP_NAMESPACE::DOMNode* find_attribute( const std::string& name ) const
    {
        const XERCES_CPP_NAMESPACE::DOMNamedNodeMap* attributes = current_->getAttributes();
        if( ! attributes )
            return 0;
        return attributes->getNamedItem( translate( trim( name ) ) );
    }
    const XERCES_CPP_NAMESPACE::DOMNode* find_content() const
    {
        const XERCES_CPP_NAMESPACE::DOMNode* child = current_->getFirstChild();
        while( child )
        {
            if( has_content( *child ) )
                return child;
            child = child->getNextSibling();
        }
        return 0;
    }

    bool has_content( const XERCES_CPP_NAMESPACE::DOMNode& node ) const
    {
        if( node.getNodeType() != XERCES_CPP_NAMESPACE::DOMNode::TEXT_NODE
         && node.getNodeType() != XERCES_CPP_NAMESPACE::DOMNode::CDATA_SECTION_NODE )
            return false;
        const XMLCh* const value = node.getNodeValue();
        return ! XERCES_CPP_NAMESPACE::XMLChar1_1::isAllSpaces( value, XERCES_CPP_NAMESPACE::XMLString::stringLen( value ) );
    }

    const XMLCh* read_value() const
    {
        const XERCES_CPP_NAMESPACE::DOMNode* child = find_content();
        if( ! child )
            throw xml::exception( location() + context() + " does not have a content" );
        return child->getNodeValue();
    }
    const XMLCh* read_attribute( const std::string& name ) const
    {
        const XERCES_CPP_NAMESPACE::DOMNode* attribute = find_attribute( name );
        if( ! attribute )
            throw xml::exception( location() + context() + " does not have an attribute '" + trim( name ) + "'" );
        return attribute->getNodeValue();
    }

    template< typename T > T convert( const XMLCh* from ) const
    {
        const double value = XERCES_CPP_NAMESPACE::XMLDouble( from ).getValue();
        const T result = static_cast< T >( value );
        if( static_cast< double >( result ) != value )
            throw xml::exception( location() + "Value of " + context() + " is not a " + typeid( T ).name() );
        return result;
    }
    template<>
    float convert< float >( const XMLCh* from ) const
    {
        const XERCES_CPP_NAMESPACE::XMLFloat value( from );
        if( value.isDataOverflowed() )
            throw xml::exception( location() + "Value of " + context() + " overflowed (probably a double instead of a float)" );
        switch( value.getType() )
        {
            case XERCES_CPP_NAMESPACE::XMLDouble::NegINF :
                return - std::numeric_limits< float >::infinity();
            case XERCES_CPP_NAMESPACE::XMLDouble::PosINF :
                return std::numeric_limits< float >::infinity();
            case XERCES_CPP_NAMESPACE::XMLDouble::NaN :
                return std::numeric_limits< float >::quiet_NaN();
            default:
                return static_cast< float >( value.getValue() );
        }
    }
    template<>
    double convert< double >( const XMLCh* from ) const
    {
        const XERCES_CPP_NAMESPACE::XMLDouble value( from );
        if( value.isDataOverflowed() )
            throw xml::exception( location() + "Value of " + context() + " overflowed (probably more than a double)" );
        switch( value.getType() )
        {
            case XERCES_CPP_NAMESPACE::XMLDouble::NegINF :
                return - std::numeric_limits< double >::infinity();
            case XERCES_CPP_NAMESPACE::XMLDouble::PosINF :
                return std::numeric_limits< double >::infinity();
            case XERCES_CPP_NAMESPACE::XMLDouble::NaN :
                return std::numeric_limits< double >::quiet_NaN();
            default:
                return value.getValue();
        }
    }
    template<>
    int convert< int >( const XMLCh* from ) const
    {
        return XERCES_CPP_NAMESPACE::XMLString::parseInt( from );
    }
    template<>
    bool convert< bool >( const XMLCh* from ) const
    {
        const std::string value = trim( translate( from ) );
        if( value == "true" || value == "1" )
            return true;
        if( value == "false" || value == "0" )
            return false;
        throw xml::exception( location() + "Value of " + context() + " is not a boolean" );
    }
    //@}

private:
    //! @name Member data
    //@{
    const XERCES_CPP_NAMESPACE::DOMNode& root_;
    const XERCES_CPP_NAMESPACE::DOMNode* current_;
    //@}
};

}

#include "sub_xistream.h"
#include "buffer_input.h"

namespace xml
{
    inline std::auto_ptr< input_base > input_imp::branch( bool clone ) const
    {
        TRY
            if( clone )
                return std::auto_ptr< input_base >( new buffer_input( *current_ ) );
            return std::auto_ptr< input_base >( new input_imp( *current_ ) );
        CATCH
    }
    inline void input_imp::nodes( const visitor& v ) const
    {
        TRY
            XERCES_CPP_NAMESPACE::DOMNode* child = current_->getFirstChild();
            while( child )
            {
                if( child->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE )
                {
                    sub_xistream xis( *child );
                    v.process( trim( translate( child->getNodeName() ) ), xis );
                }
                child = child->getNextSibling();
            }
        CATCH
    }
    inline void input_imp::attributes( const visitor& v ) const
    {
        TRY
            const XERCES_CPP_NAMESPACE::DOMNamedNodeMap* attributes = current_->getAttributes();
            if( attributes )
            {
                for( XMLSize_t index = 0; index < attributes->getLength(); ++index )
                {
                    XERCES_CPP_NAMESPACE::DOMNode* attribute = attributes->item( index );
                    sub_xistream xis( *current_ );
                    v.process( trim( translate( attribute->getNodeName() ) ), xis );
                }
            }
        CATCH
    }
}

#undef TRY
#undef CATCH

#endif // xeumeuleu_input_imp_h
