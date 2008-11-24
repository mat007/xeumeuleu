/*
 *   Copyright (c) 2008, Mathieu Champlon
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

#include "import.h"
#include "locator.h"

using namespace XERCES_CPP_NAMESPACE;

namespace xml
{
    bool is_empty( const DOMNode& node )
    {
        if( node.getNodeType() != DOMNode::TEXT_NODE
         && node.getNodeType() != DOMNode::CDATA_SECTION_NODE )
            return false;
        const XMLCh* const value = node.getNodeValue();
        return XMLChar1_1::isAllSpaces( value, XMLString::stringLen( value ) );
    }
    DOMNode& clone( DOMDocument& document, const DOMNode& from, DOMNode& to )
    {
        DOMNode& added = *to.appendChild( document.importNode( const_cast< DOMNode* >( &from ), false ) );
        const locator* loc = reinterpret_cast< locator* >( from.getUserData( translate( "locator" ) ) );
        if( loc )
            added.setUserData( translate( "locator" ), new locator( *loc ), 0 );
        return added;
    }
    void import( DOMDocument& document, const DOMNode* from, DOMNode& to )
    {
        while( from )
        {
            if( ! is_empty( *from ) )
                import( document, from->getFirstChild(), clone( document, *from, to ) );
            from = from->getNextSibling();
        }
    }
    DOMNode& import( DOMDocument& document, const DOMNode& from, DOMNode& to )
    {
        if( from.getNodeType() == DOMNode::DOCUMENT_NODE )
        {
            import( document, *from.getFirstChild(), to );
            return document;
        }
        DOMNode& added = clone( document, from, to );
        import( document, from.getFirstChild(), added );
        return added;
    }
}
