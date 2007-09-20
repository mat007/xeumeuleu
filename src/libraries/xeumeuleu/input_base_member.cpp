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

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

// -----------------------------------------------------------------------------
// Name: input_base_member constructor
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
input_base_member::input_base_member( DOMDocument& document )
    : pDocument_( document )
{
    // NOTHING
}

namespace
{
    void clean( const DOMNode* const pNode )
    {
        if( ! pNode )
            return;
        delete reinterpret_cast< DOMLocator* >( pNode->getUserData( translate( "locator" ) ) );
        clean( pNode->getNextSibling() );
        clean( pNode->getFirstChild() );
    }
}

// -----------------------------------------------------------------------------
// Name: input_base_member destructor
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
input_base_member::~input_base_member()
{
    clean( pDocument_.get() );
}

namespace
{
    class locator : public DOMLocator
    {
    public:
        locator( const std::string& uri, const XMLScanner& scanner, DOMNode& node )
            : uri_   ( uri )
            , line_  ( scanner.getLocator()->getLineNumber() )
            , column_( scanner.getLocator()->getColumnNumber() )
            , node_  ( node )
        {}
        virtual XMLSSize_t getLineNumber() const { return line_; }
        virtual XMLSSize_t getColumnNumber() const { return column_; }
        virtual XMLSSize_t getOffset() const { return -1; }
        virtual DOMNode* getErrorNode() const { return &node_; }
        virtual const XMLCh* getURI() const { return uri_; }
        virtual void setLineNumber( const XMLSSize_t /*line*/ ) {}
        virtual void setColumnNumber( const XMLSSize_t /*column*/ ) {}
        virtual void setOffset( const XMLSSize_t /*offset*/ ) {}
        virtual void setErrorNode( DOMNode* const /*pNode*/ ) {}
        virtual void setURI( const XMLCh* const /*uri*/ ) {}
    private:
        const translate uri_;
        const XMLSSize_t line_, column_;
        DOMNode& node_;
    };

    class builder : public DOMBuilderImpl
    {
    public:
        explicit builder( const std::string& uri )
            : uri_( uri )
        {}
    private:
        void startElement( const XMLElementDecl& elemDecl, const unsigned int urlId, const XMLCh* const elemPrefix, const RefVectorOf< XMLAttr >& attrList,
                           const unsigned int attrCount, const bool isEmpty, const bool isRoot )
        {
            DOMBuilderImpl::startElement( elemDecl, urlId, elemPrefix, attrList, attrCount, isEmpty, isRoot );
            DOMNode* pNode = getCurrentNode();
            pNode->setUserData( translate( "locator" ), new locator( uri_, *getScanner(), *pNode ), 0 );
        }
        const std::string uri_;
    };
}

 // -----------------------------------------------------------------------------
// Name: input_base_member::parse
// Created: MAT 2006-01-10
// -----------------------------------------------------------------------------
DOMDocument& input_base_member::parse( InputSource& source, const encoding* pEncoding, const grammar& grammar )
{
    try
    {
        builder builder( translate( source.getSystemId() ) );
        parser parser( builder );
        grammar.configure( parser );
        if( pEncoding )
            source.setEncoding( translate( *pEncoding ) );
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
