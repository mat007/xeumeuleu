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

#include "output.h"
#include "exception.h"
#include "translate.h"
#include "trim.h"
#include "sub_output.h"
#include "xerces.h"
#include <limits>

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

// -----------------------------------------------------------------------------
// Name: output constructor
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
output::output( DOMDocument& document, DOMNode& root )
    : document_( document )
    , root_    ( root )
    , pCurrent_( &root )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: output destructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
output::~output()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: output::context
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
std::string output::context() const
{
    return "node '" + std::string( translate( pCurrent_->getNodeName() ) ) + "'";
}

// -----------------------------------------------------------------------------
// Name: output::start
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
void output::start( const std::string& tag )
{
    pCurrent_ = pCurrent_->appendChild( document_.createElement( translate( trim( tag ) ) ) );
}

// -----------------------------------------------------------------------------
// Name: output::end
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
void output::end()
{
    if( isRoot() )
        throw xml::exception( "Illegal 'end' from root level" );
    pCurrent_ = pCurrent_->getParentNode();
    flush();
}

// -----------------------------------------------------------------------------
// Name: output::cdata
// Created: MCO 2007-03-14
// -----------------------------------------------------------------------------
void output::cdata( const std::string& value )
{
    pCurrent_->appendChild( document_.createCDATASection( translate( value ) ) );
}

// -----------------------------------------------------------------------------
// Name: output::write
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
void output::write( const std::string& value )
{
    pCurrent_->appendChild( document_.createTextNode( translate( value ) ) );
}

// -----------------------------------------------------------------------------
// Name: output::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void output::attribute( const std::string& name, const std::string& value )
{
    DOMNamedNodeMap* pAttributes = pCurrent_->getAttributes();
    if( ! pAttributes )
        throw xml::exception( context() + " cannot have attributes" );
    DOMAttr* pAttribute = document_.createAttribute( translate( trim( name ) ) );
    pAttribute->setValue( translate( value ) );
    pAttributes->setNamedItem( pAttribute );
}

// -----------------------------------------------------------------------------
// Name: output::isEmpty
// Created: MAT 2007-09-06
// -----------------------------------------------------------------------------
bool output::isEmpty( const DOMNode& node ) const
{
    if( node.getNodeType() != DOMNode::TEXT_NODE
     && node.getNodeType() != DOMNode::CDATA_SECTION_NODE )
        return false;
    const XMLCh* const value = node.getNodeValue();
    return XMLChar1_1::isAllSpaces( value, XMLString::stringLen( value ) );
}

// -----------------------------------------------------------------------------
// Name: output::copy
// Created: MAT 2007-09-06
// -----------------------------------------------------------------------------
void output::copy( DOMNode* pNode, DOMNode& to )
{
    if( ! pNode )
        return;
    if( ! isEmpty( *pNode ) )
    {
        DOMNode* pNew = to.appendChild( document_.importNode( pNode, false ) );
        copy( pNode->getFirstChild(), *pNew );
    }
    copy( pNode->getNextSibling(), to );
}

// -----------------------------------------------------------------------------
// Name: output::copy
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
void output::copy( const DOMNode& node )
{
    copy( node.getFirstChild(), *pCurrent_ );
    flush();
}

// -----------------------------------------------------------------------------
// Name: output::branch
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
std::auto_ptr< output > output::branch()
{
    return std::auto_ptr< output >( new sub_output( document_, *pCurrent_, *this ) );
}

// -----------------------------------------------------------------------------
// Name: output::flush
// Created: MAT 2006-05-18
// -----------------------------------------------------------------------------
void output::flush()
{
    if( isRoot() )
        finished();
}

// -----------------------------------------------------------------------------
// Name: output::isRoot
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
bool output::isRoot() const
{
    return pCurrent_ == &root_;
}

namespace
{
    template< typename T > inline std::string convert( T value )
    {
        if( value == std::numeric_limits< T >::infinity() )
            return "INF";
        if( value == - std::numeric_limits< T >::infinity() )
            return "-INF";
        if( value != value )
            return "NaN";
        static char buffer[255];
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
}

// -----------------------------------------------------------------------------
// Name: output::serialize
// Created: MAT 2007-01-29
// -----------------------------------------------------------------------------
std::string output::serialize( float value ) const
{
    return convert( value );
}

// -----------------------------------------------------------------------------
// Name: output::serialize
// Created: MAT 2007-01-29
// -----------------------------------------------------------------------------
std::string output::serialize( double value ) const
{
    return convert( value );
}
