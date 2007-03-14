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
#include <xercesc/util/XMLFloat.hpp>
#include <xercesc/util/XMLDouble.hpp>
#include <xercesc/util/XMLInteger.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
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
std::string input_imp::context() const
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
    if( ! pChild || pChild->getNodeType() != DOMNode::TEXT_NODE
                 && pChild->getNodeType() != DOMNode::CDATA_SECTION_NODE )
        return 0;
    return pChild;
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
// Name: input_imp::toFloat
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
float input_imp::toFloat( const XMLCh* from ) const
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
// Name: input_imp::toDouble
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
double input_imp::toDouble( const XMLCh* from ) const
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
// Name: input_imp::toShort
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
short input_imp::toShort( const XMLCh* from ) const
{
    const double value = XMLDouble( from ).getValue();
    const short result = static_cast< short >( value );
    if( static_cast< double >( result ) != value )
        throw xml::exception( "Value of " + context() + " is not a short integer" );
    return result;
}

// -----------------------------------------------------------------------------
// Name: input_imp::toInteger
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
int input_imp::toInteger( const XMLCh* from ) const
{
    return XMLString::parseInt( from );
}

// -----------------------------------------------------------------------------
// Name: input_imp::toLong
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
long input_imp::toLong( const XMLCh* from ) const
{
    const double value = XMLDouble( from ).getValue();
    const long result = static_cast< long >( value );
    if( static_cast< double >( result ) != value )
        throw xml::exception( "Value of " + context() + " is not a long integer" );
    return result;
}

// -----------------------------------------------------------------------------
// Name: input_imp::toBoolean
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
bool input_imp::toBoolean( const XMLCh* from ) const
{
    const std::string value = trim( translate( from ) );
    if ( value == "true" || value == "1" )
        return true;
    if ( value == "false" || value == "0" )
        return false;
    throw xml::exception( "Value of " + context() + " is not a boolean" );
}

// -----------------------------------------------------------------------------
// Name: input_imp::toUnsignedShort
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
unsigned short input_imp::toUnsignedShort( const XMLCh* from ) const
{
    const double value = XMLDouble( from ).getValue();
    const unsigned short result = static_cast< unsigned short >( value );
    if( static_cast< double >( result ) != value )
        throw xml::exception( "Value of " + context() + " is not an unsigned short integer" );
    return result;
}

// -----------------------------------------------------------------------------
// Name: input_imp::toUnsignedInteger
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
unsigned int input_imp::toUnsignedInteger( const XMLCh* from ) const
{
    const double value = XMLDouble( from ).getValue();
    const unsigned int result = static_cast< unsigned int >( value );
    if( static_cast< double >( result ) != value )
        throw xml::exception( "Value of " + context() + " is not an unsigned integer" );
    return result;
}

// -----------------------------------------------------------------------------
// Name: input_imp::toUnsignedLong
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
unsigned long input_imp::toUnsignedLong( const XMLCh* from ) const
{
    const double value = XMLDouble( from ).getValue();
    const unsigned long result = static_cast< unsigned long >( value );
    if( static_cast< double >( result ) != value )
        throw xml::exception( "Value of " + context() + " is not an unsigned short integer" );
    return result;
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
    value = toFloat( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
void input_imp::read( double& value ) const
{
    value = toDouble( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::read( short& value ) const
{
    value = toShort( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
void input_imp::read( int& value ) const
{
    value = toInteger( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::read( long& value ) const
{
    value = toLong( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
void input_imp::read( bool& value ) const
{
    value = toBoolean( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::read( unsigned short& value ) const
{
    value = toUnsignedShort( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::read( unsigned int& value ) const
{
    value = toUnsignedInteger( readValue() );
}

// -----------------------------------------------------------------------------
// Name: input_imp::read
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::read( unsigned long& value ) const
{
    value = toUnsignedLong( readValue() );
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
    value = toFloat( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, double& value ) const
{
    value = toDouble( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, short& value ) const
{
    value = toShort( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, int& value ) const
{
    value = toInteger( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, long& value ) const
{
    value = toLong( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, bool& value ) const
{
    value = toBoolean( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, unsigned short& value ) const
{
    value = toUnsignedShort( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, unsigned int& value ) const
{
    value = toUnsignedInteger( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void input_imp::attribute( const std::string& name, unsigned long& value ) const
{
    value = toUnsignedLong( readAttribute( name ) );
}

// -----------------------------------------------------------------------------
// Name: input_imp::visit
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void input_imp::visit( const visitor& v ) const
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
// Name: input_imp::branch
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
std::auto_ptr< input_base > input_imp::branch() const
{
    return std::auto_ptr< input_base >( new input_imp( *pCurrent_ ) );
}
