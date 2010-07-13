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

#ifndef xeumeuleu_import_hpp
#define xeumeuleu_import_hpp

#include <xeumeuleu/bridges/xerces/detail/xerces.hpp>
#include <xeumeuleu/bridges/xerces/detail/locator.hpp>

namespace xml
{
namespace detail
{
    inline bool is_empty( const XERCES_CPP_NAMESPACE::DOMNode& node )
    {
        if( node.getNodeType() != XERCES_CPP_NAMESPACE::DOMNode::TEXT_NODE
         && node.getNodeType() != XERCES_CPP_NAMESPACE::DOMNode::CDATA_SECTION_NODE )
            return false;
        const XMLCh* const value = node.getNodeValue();
        return XERCES_CPP_NAMESPACE::XMLChar1_1::isAllSpaces( value, XERCES_CPP_NAMESPACE::XMLString::stringLen( value ) );
    }

    inline XERCES_CPP_NAMESPACE::DOMNode& clone( XERCES_CPP_NAMESPACE::DOMDocument& document,
                                                 const XERCES_CPP_NAMESPACE::DOMNode& from,
                                                 XERCES_CPP_NAMESPACE::DOMNode& to )
    {
        static const translate tag( "locator" );
        XERCES_CPP_NAMESPACE::DOMNode& added = *to.appendChild( document.importNode( const_cast< XERCES_CPP_NAMESPACE::DOMNode* >( &from ), false ) );
        const locator* loc = reinterpret_cast< locator* >( from.getUserData( tag ) );
        if( loc )
            added.setUserData( tag, new locator( *loc ), 0 );
        return added;
    }
}

    inline void import( XERCES_CPP_NAMESPACE::DOMDocument& document,
                        const XERCES_CPP_NAMESPACE::DOMNode* from,
                        XERCES_CPP_NAMESPACE::DOMNode& to )
    {
        while( from )
        {
            if( ! detail::is_empty( *from ) )
                import( document, from->getFirstChild(), detail::clone( document, *from, to ) );
            from = from->getNextSibling();
        }
    }

    inline XERCES_CPP_NAMESPACE::DOMNode& import( XERCES_CPP_NAMESPACE::DOMDocument& document,
                                                  const XERCES_CPP_NAMESPACE::DOMNode& from,
                                                  XERCES_CPP_NAMESPACE::DOMNode& to )
    {
        if( from.getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::DOCUMENT_NODE )
        {
            if( from.getFirstChild() )
                import( document, *from.getFirstChild(), to );
            return document;
        }
        XERCES_CPP_NAMESPACE::DOMNode& added = detail::clone( document, from, to );
        import( document, from.getFirstChild(), added );
        return added;
    }
}

#endif // xeumeuleu_import_hpp
