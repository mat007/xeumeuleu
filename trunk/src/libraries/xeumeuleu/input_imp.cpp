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

#include "input_imp.h"
#include "translate.h"
#include "trim.h"
#include "exception.h"
#include "visitor.h"
#include "sub_xistream.h"
#include "buffer_input.h"
#include "locator.h"
#include "output.h"
#include "xerces.h"
#include <limits>

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

// -----------------------------------------------------------------------------
// Name: input_imp constructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
input_imp::input_imp( const DOMNode& root )
    : root_   ( root )
    , current_( &root_ )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: input_imp destructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
input_imp::~input_imp()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: input_imp::context
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
const std::string input_imp::context() const
{
    return "node '" + trim( translate( current_->getNodeName() ) ) + "'";
}

// -----------------------------------------------------------------------------
// Name: input_imp::has_child
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
bool input_imp::has_child( const std::string& name ) const
{
    return find_child( name ) != 0;
}

// -----------------------------------------------------------------------------
// Name: input_imp::has_attribute
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
bool input_imp::has_attribute( const std::string& name ) const
{
    return find_attribute( name ) != 0;
}

// -----------------------------------------------------------------------------
// Name: input_imp::has_content
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
bool input_imp::has_content() const
{
    return find_content() != 0;
}

// -----------------------------------------------------------------------------
// Name: input_imp::find_child
// Created: MAT 2006-01-07
// -----------------------------------------------------------------------------
const DOMNode* input_imp::find_child( const std::string& name ) const
{
    const DOMNode* child = current_->getFirstChild();
    while( child )
    {
        if( trim( name ) == trim( translate( child->getNodeName() ) ) )
            return child;
        child = child->getNextSibling();
    }
    return 0;
}

// -----------------------------------------------------------------------------
// Name: input_imp::find_attribute
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
const DOMNode* input_imp::find_attribute( const std::string& name ) const
{
    const DOMNamedNodeMap* attributes = current_->getAttributes();
    if( ! attributes )
        return 0;
    return attributes->getNamedItem( translate( trim( name ) ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::find_content
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
const DOMNode* input_imp::find_content() const
{
    const DOMNode* child = current_->getFirstChild();
    while( child )
    {
        if( has_content( *child ) )
            return child;
        child = child->getNextSibling();
    }
    return 0;
}

// -----------------------------------------------------------------------------
// Name: input_imp::has_content
// Created: MAT 2007-07-16
// -----------------------------------------------------------------------------
bool input_imp::has_content( const DOMNode& node ) const
{
    if( node.getNodeType() != DOMNode::TEXT_NODE
     && node.getNodeType() != DOMNode::CDATA_SECTION_NODE )
        return false;
    const XMLCh* const value = node.getNodeValue();
    return ! XMLChar1_1::isAllSpaces( value, XMLString::stringLen( value ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::start
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
void input_imp::start( const std::string& tag )
{
    const DOMNode* child = find_child( tag );
    if( ! child )
        throw xml::exception( location() + context() + " does not have a child named '" + tag + "'" );
    current_ = child;
}

// -----------------------------------------------------------------------------
// Name: input_imp::end
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
void input_imp::end()
{
    if( current_ == &root_ )
        throw xml::exception( location() + "Cannot move up from " + context() );
    const DOMNode* parent = current_->getParentNode();
    if( ! parent )
        throw xml::exception( location() + context() + " has no parent" );
    current_ = parent;
}

// -----------------------------------------------------------------------------
// Name: input_imp::read_value
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
const XMLCh* input_imp::read_value() const
{
    const DOMNode* child = find_content();
    if( ! child )
        throw xml::exception( location() + context() + " does not have a content" );
    return child->getNodeValue();
}

// -----------------------------------------------------------------------------
// Name: input_imp::convert
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
template< typename T >
T input_imp::convert( const XMLCh* from ) const
{
    const double value = XMLDouble( from ).getValue();
    const T result = static_cast< T >( value );
    if( static_cast< double >( result ) != value )
        throw xml::exception( location() + "Value of " + context() + " is not a " + typeid( T ).name() );
    return result;
}

namespace xml
{
// -----------------------------------------------------------------------------
// Name: input_imp::convert
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
template<>
float input_imp::convert< float >( const XMLCh* from ) const
{
    const XMLFloat value( from );
    if( value.isDataOverflowed() )
        throw xml::exception( location() + "Value of " + context() + " overflowed (probably a double instead of a float)" );
    switch( value.getType() )
    {
        case XMLDouble::NegINF :
            return - std::numeric_limits< float >::infinity();
        case XMLDouble::PosINF :
            return std::numeric_limits< float >::infinity();
        case XMLDouble::NaN :
            return std::numeric_limits< float >::quiet_NaN();
        default:
            return static_cast< float >( value.getValue() );
    }
}

// -----------------------------------------------------------------------------
// Name: input_imp::convert
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
template<>
double input_imp::convert< double >( const XMLCh* from ) const
{
    const XMLDouble value( from );
    if( value.isDataOverflowed() )
        throw xml::exception( location() + "Value of " + context() + " overflowed (probably more than a double)" );
    switch( value.getType() )
    {
        case XMLDouble::NegINF :
            return - std::numeric_limits< double >::infinity();
        case XMLDouble::PosINF :
            return std::numeric_limits< double >::infinity();
        case XMLDouble::NaN :
            return std::numeric_limits< double >::quiet_NaN();
        default:
            return value.getValue();
    }
}

// -----------------------------------------------------------------------------
// Name: input_imp::convert
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
template<>
int input_imp::convert< int >( const XMLCh* from ) const
{
    return XMLString::parseInt( from );
}

// -----------------------------------------------------------------------------
// Name: input_imp::convert
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
template<>
bool input_imp::convert< bool >( const XMLCh* from ) const
{
    const std::string value = trim( translate( from ) );
    if( value == "true" || value == "1" )
        return true;
    if( value == "false" || value == "0" )
        return false;
    throw xml::exception( location() + "Value of " + context() + " is not a boolean" );

}
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
void input_imp::read( std::string& value ) const
{
    value = translate( read_value() );
}

#define READ( type ) void input_imp::read( type& value ) const \
                     { \
                         value = convert< type >( read_value() ); \
                     }
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

// -----------------------------------------------------------------------------
// Name: input_imp::read_attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
const XMLCh* input_imp::read_attribute( const std::string& name ) const
{
    const DOMNode* attribute = find_attribute( name );
    if( ! attribute )
        throw xml::exception( location() + context() + " does not have an attribute '" + trim( name ) + "'" );
    return attribute->getNodeValue();
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, std::string& value ) const
{
    value = translate( read_attribute( name ) );
}

#define ATTRIBUTE( type ) void input_imp::attribute( const std::string& name, type& value ) const \
                      { \
                         value = convert< type >( read_attribute( name ) ); \
                      }
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

// -----------------------------------------------------------------------------
// Name: input_imp::nodes
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void input_imp::nodes( const visitor& v ) const
{
    DOMNode* child = current_->getFirstChild();
    while( child )
    {
        if( child->getNodeType() == DOMNode::ELEMENT_NODE )
        {
            sub_xistream xis( *child );
            v.process( trim( translate( child->getNodeName() ) ), xis );
        }
        child = child->getNextSibling();
    }
}

// -----------------------------------------------------------------------------
// Name: input_imp::attributes
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
void input_imp::attributes( const visitor& v ) const
{
    const DOMNamedNodeMap* attributes = current_->getAttributes();
    if( attributes )
    {
        for( XMLSize_t index = 0; index < attributes->getLength(); ++index )
        {
            DOMNode* attribute = attributes->item( index );
            sub_xistream xis( *current_ );
            v.process( trim( translate( attribute->getNodeName() ) ), xis );
        }
    }
}

// -----------------------------------------------------------------------------
// Name: input_imp::branch
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
std::auto_ptr< input_base > input_imp::branch( bool clone ) const
{
    if( clone )
        return std::auto_ptr< input_base >( new buffer_input( *current_ ) );
    return std::auto_ptr< input_base >( new input_imp( *current_ ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::copy
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
void input_imp::copy( output& destination ) const
{
    destination.copy( *current_ );
}

// -----------------------------------------------------------------------------
// Name: input_imp::location
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
const std::string input_imp::location() const
{
    const locator* loc = reinterpret_cast< locator* >( current_->getUserData( translate( "locator" ) ) );
    if( loc )
        return *loc;
    return "";
}

// -----------------------------------------------------------------------------
// Name: input_imp::error
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
void input_imp::error( const std::string& message ) const
{
    throw xml::exception( location() + message );
}
