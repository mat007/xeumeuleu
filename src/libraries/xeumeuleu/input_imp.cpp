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
#include "chained_exception.h"
#include "visitor.h"
#include "sub_xistream.h"
#include "buffer_input.h"
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
    : root_    ( root )
    , pCurrent_( &root_ )
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
    return "node '" + trim( translate( pCurrent_->getNodeName() ) ) + "'";
}

// -----------------------------------------------------------------------------
// Name: input_imp::hasElement
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
bool input_imp::hasElement( const std::string& tag ) const
{
    return findChild( tag ) != 0;
}

// -----------------------------------------------------------------------------
// Name: input_imp::hasAttribute
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
bool input_imp::hasAttribute( const std::string& name ) const
{
    return findAttribute( name ) != 0;
}

// -----------------------------------------------------------------------------
// Name: input_imp::hasContent
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
bool input_imp::hasContent() const
{
    return findContent() != 0;
}

// -----------------------------------------------------------------------------
// Name: input_imp::findChild
// Created: MAT 2006-01-07
// -----------------------------------------------------------------------------
const DOMNode* input_imp::findChild( const std::string& name ) const
{
    const DOMNode* pChild = pCurrent_->getFirstChild();
    while( pChild )
    {
        if( trim( name ) == trim( translate( pChild->getNodeName() ) ) )
            return pChild;
        pChild = pChild->getNextSibling();
    }
    return 0;
}

// -----------------------------------------------------------------------------
// Name: input_imp::findAttribute
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
const DOMNode* input_imp::findAttribute( const std::string& name ) const
{
    const DOMNamedNodeMap* pAttributes = pCurrent_->getAttributes();
    if( ! pAttributes )
        return 0;
    return pAttributes->getNamedItem( translate( trim( name ) ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::findContent
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
const DOMNode* input_imp::findContent() const
{
    const DOMNode* pChild = pCurrent_->getFirstChild();
    while( pChild )
    {
        if( hasContent( *pChild ) )
            return pChild;
        pChild = pChild->getNextSibling();
    }
    return 0;
}

// -----------------------------------------------------------------------------
// Name: input_imp::hasContent
// Created: MAT 2007-07-16
// -----------------------------------------------------------------------------
bool input_imp::hasContent( const DOMNode& node ) const
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
    const DOMNode* pChild = findChild( tag );
    if( ! pChild )
        throw xml::exception( context() + " does not have a child named '" + tag + "'" );
    pCurrent_ = pChild;
}

// -----------------------------------------------------------------------------
// Name: input_imp::end
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
void input_imp::end()
{
    if( pCurrent_ == &root_ )
        throw xml::exception( "Cannot move up from " + context() );
    const DOMNode* pParent = pCurrent_->getParentNode();
    if( ! pParent )
        throw xml::exception( context() + " has no parent" );
    pCurrent_ = pParent;
}

// -----------------------------------------------------------------------------
// Name: input_imp::readValue
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
const XMLCh* input_imp::readValue() const
{
    const DOMNode* pChild = findContent();
    if( ! pChild )
        throw xml::exception( context() + " does not have a content" );
    return pChild->getNodeValue();
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
        throw xml::exception( "Value of " + context() + " is not a " + typeid( T ).name() );
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
        throw xml::exception( "Value of " + context() + " overflowed (probably a double instead of a float)" );
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
        throw xml::exception( "Value of " + context() + " overflowed (probably more than a double)" );
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
    throw xml::exception( "Value of " + context() + " is not a boolean" );
}
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
void input_imp::read( std::string& value ) const
{
    value = translate( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
void input_imp::read( float& value ) const
{
    value = convert< float >( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
void input_imp::read( double& value ) const
{
    value = convert< double >( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::read( short& value ) const
{
    value = convert< short >( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
void input_imp::read( int& value ) const
{
    value = convert< int >( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::read( long& value ) const
{
    value = convert< long >( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MCO 2007-09-18
// -----------------------------------------------------------------------------
void input_imp::read( long long& value ) const
{
    value = convert< long long >( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
void input_imp::read( bool& value ) const
{
    value = convert< bool >( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::read( unsigned short& value ) const
{
    value = convert< unsigned short >( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::read( unsigned int& value ) const
{
    value = convert< unsigned int >( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::read( unsigned long& value ) const
{
    value = convert< unsigned long >( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MAT 2007-09-18
// -----------------------------------------------------------------------------
void input_imp::read( unsigned long long& value ) const
{
    value = convert< unsigned long >( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::readAttribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
const XMLCh* input_imp::readAttribute( const std::string& name ) const
{
    const DOMNode* pAttribute = findAttribute( name );
    if( ! pAttribute )
        throw xml::exception( context() + " does not have an attribute '" + trim( name ) + "'" );
    return pAttribute->getNodeValue();
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, std::string& value ) const
{
    value = translate( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, float& value ) const
{
    value = convert< float >( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, double& value ) const
{
    value = convert< double >( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, short& value ) const
{
    value = convert< short >( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, int& value ) const
{
    value = convert< int >( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, long& value ) const
{
    value = convert< long >( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MCO 2007-09-18
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, long long& value ) const
{
    value = convert< long long >( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, bool& value ) const
{
    value = convert< bool >( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, unsigned short& value ) const
{
    value = convert< unsigned short >( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, unsigned int& value ) const
{
    value = convert< unsigned int >( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, unsigned long& value ) const
{
    value = convert< unsigned long >( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MAT 2007-09-18
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, unsigned long long& value ) const
{
    value = convert< unsigned long long >( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::nodes
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void input_imp::nodes( const visitor& v ) const
{
    DOMNode* pChild = pCurrent_->getFirstChild();
    while( pChild )
    {
        if( pChild->getNodeType() == DOMNode::ELEMENT_NODE )
        {
            sub_xistream xis( *pChild );
            v.process( trim( translate( pChild->getNodeName() ) ), xis );
        }
        pChild = pChild->getNextSibling();
    }
}

// -----------------------------------------------------------------------------
// Name: input_imp::attributes
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
void input_imp::attributes( const visitor& v ) const
{
    const DOMNamedNodeMap* pAttributes = pCurrent_->getAttributes();
    if( pAttributes )
    {
        for( XMLSize_t index = 0; index < pAttributes->getLength(); ++index )
        {
            DOMNode* pAttribute = pAttributes->item( index );
            sub_xistream xis( *pCurrent_ );
            v.process( trim( translate( pAttribute->getNodeName() ) ), xis );
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
        return std::auto_ptr< input_base >( new buffer_input( *pCurrent_ ) );
    return std::auto_ptr< input_base >( new input_imp( *pCurrent_ ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::copy
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
void input_imp::copy( output& destination ) const
{
    destination.copy( *pCurrent_ );
}

namespace
{
    const std::string interpret( const DOMLocator& locator, const std::string& message )
    {
        std::stringstream stream;
        stream << translate( locator.getURI() ).operator std::string()
               << " (line " << locator.getLineNumber() << ", column " << locator.getColumnNumber() << ") : "
               << translate( message ).operator std::string();
        return stream.str();
    }
}

// -----------------------------------------------------------------------------
// Name: input_imp::error
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
void input_imp::error( const std::string& message ) const
{
    const DOMLocator* pLocator = reinterpret_cast< DOMLocator* >( pCurrent_->getUserData( translate( "locator" ) ) );
    if( ! pLocator )
        throw exception( message );
    throw exception( interpret( *pLocator, message ) );
}
