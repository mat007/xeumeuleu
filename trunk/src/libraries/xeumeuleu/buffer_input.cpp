/*
 *   Copyright (c) 2007, Mathieu Champlon
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

#include "buffer_input.h"
#include "translate.h"
#include "exception.h"
#include "locator.h"

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

namespace
{
    DOMDocument& build()
    {
        DOMImplementation* pImpl = DOMImplementationRegistry::getDOMImplementation( translate( "LS" ) );
        if( ! pImpl )
            throw xml::exception( "Internal error in 'buffer_input::build' : DOMImplementation 'LS' not found" );
        return *pImpl->createDocument();
    }
    void copy( DOMNode* pFrom, DOMNode* pTo )
    {
        while( pFrom && pTo )
        {
            const locator* pLocator = reinterpret_cast< locator* >( pFrom->getUserData( translate( "locator" ) ) );
            if( pLocator )
                pTo->setUserData( translate( "locator" ), new locator( *pLocator, *pTo ), 0 );
            copy( pFrom->getFirstChild(), pTo->getFirstChild() );
            pFrom = pFrom->getNextSibling();
            pTo = pTo->getNextSibling();
        }
    }
    DOMNode& import( DOMDocument& document, DOMNode& node )
    {
        if( node.getNodeType() == DOMNode::DOCUMENT_NODE )
        {
            import( document, *node.getFirstChild() );
            return document;
        }
        DOMNode& added = *document.appendChild( document.importNode( &node, true ) );
        copy( &node, &added );
        return added;
    }
}

// -----------------------------------------------------------------------------
// Name: buffer_input constructor
// Created: MCO 2007-04-27
// -----------------------------------------------------------------------------
buffer_input::buffer_input( const DOMNode& root )
    : input_base_member( build() )
    , input_imp( import( *pDocument_, const_cast< DOMNode& >( root ) ) )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: buffer_input destructor
// Created: MCO 2007-04-27
// -----------------------------------------------------------------------------
buffer_input::~buffer_input()
{
    // NOTHING
}
