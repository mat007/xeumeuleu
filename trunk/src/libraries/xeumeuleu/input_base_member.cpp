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

#include "input_base_member.h"
#include "translate.h"
#include "error_handler.h"
#include "chained_exception.h"
#include "encoding.h"
#include "grammar.h"
#include "parser.h"
#include "locator.h"

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

// -----------------------------------------------------------------------------
// Name: input_base_member constructor
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
input_base_member::input_base_member( DOMDocument& document )
    : document_( document )
{
    // NOTHING
}

namespace
{
    void clean( const DOMNode* node )
    {
        while( node )
        {
            delete reinterpret_cast< locator* >( node->getUserData( translate( "locator" ) ) );
            clean( node->getFirstChild() );
            node = node->getNextSibling();
        }
    }
}

// -----------------------------------------------------------------------------
// Name: input_base_member destructor
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
input_base_member::~input_base_member()
{
    clean( document_.get() );
}

namespace
{
    class builder : public DOMBuilderImpl
    {
    public:
        explicit builder( const std::string& uri )
            : uri_( uri )
        {}
    private:
        void startElement( const XMLElementDecl& elemDecl, const unsigned int urlId, const XMLCh* const elemPrefix, const RefVectorOf< XMLAttr >& attrList,
                           const unsigned int attrCount, const bool is_empty, const bool is_root )
        {
            DOMBuilderImpl::startElement( elemDecl, urlId, elemPrefix, attrList, attrCount, is_empty, is_root );
            DOMNode* node = getCurrentNode();
            node->setUserData( translate( "locator" ), new locator( uri_, *getScanner(), *node ), 0 );
        }
        const std::string uri_;
    };
}

 // -----------------------------------------------------------------------------
// Name: input_base_member::parse
// Created: MAT 2006-01-10
// -----------------------------------------------------------------------------
DOMDocument& input_base_member::parse( InputSource& source, const encoding* encoding, const grammar& grammar )
{
    try
    {
        builder builder( translate( source.getSystemId() ) );
        parser parser( builder );
        grammar.configure( parser );
        if( encoding )
            source.setEncoding( translate( *encoding ) );
        return parser.parse( source );
    }
    catch( const OutOfMemoryException& )
    {
        throw xml::exception( "Out of memory" );
    }
    catch( const XMLException& e )
    {
        throw chained_exception( e );
    }
    catch( const DOMException& e )
    {
        throw chained_exception( e );
    }
}
