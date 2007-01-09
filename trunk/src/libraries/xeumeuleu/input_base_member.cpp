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
#include "xerces_wrapper.h"
#include "encoding.h"
#include "grammar.h"
#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/validators/common/Grammar.hpp>

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

// -----------------------------------------------------------------------------
// Name: input_base_member constructor
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
input_base_member::input_base_member( DOMNode& root )
    : root_( root )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: input_base_member destructor
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
input_base_member::~input_base_member()
{
    root_.release();
}

// -----------------------------------------------------------------------------
// Name: input_base_member::parse
// Created: MAT 2006-01-10
// -----------------------------------------------------------------------------
DOMNode& input_base_member::parse( InputSource& source, const encoding* pEncoding, const grammar* pGrammar )
{
    try
    {
        if( pEncoding )
            source.setEncoding( translate( *pEncoding ) );
        Wrapper4InputSource input( &source, false );
        DOMImplementation* pImpl = DOMImplementationRegistry::getDOMImplementation( translate( "LS" ) );
        xerces_wrapper< DOMBuilder > pParser( ((DOMImplementationLS*)pImpl)->createDOMBuilder( DOMImplementationLS::MODE_SYNCHRONOUS, 0 ) );
        pParser->setFeature( XMLUni::fgXercesUserAdoptsDOMDocument, true );
        pParser->setFeature( XMLUni::fgDOMNamespaces, true );
        pParser->setFeature( XMLUni::fgDOMDatatypeNormalization, true );
        pParser->setFeature( XMLUni::fgXercesSchema, true );
        if( pGrammar )
        {
            const std::string schema = *pGrammar;
            if( ! schema.empty() )
            {
                pParser->setFeature( XMLUni::fgDOMValidation, true );
                pParser->setFeature( XMLUni::fgXercesUseCachedGrammarInParse, true );
                // $$$$ MAT 2006-03-27: use pParser->setProperty( XMLUni::fgXercesSchemaExternalNoNameSpaceSchemaLocation, ... ) ?
                pParser->loadGrammar( translate( schema ), Grammar::SchemaGrammarType, true );
            }
            else
                pParser->setFeature( XMLUni::fgDOMValidateIfSchema, true );
        }
        else
        {
            pParser->setFeature( XMLUni::fgDOMValidateIfSchema, true );
            pParser->setFeature( XMLUni::fgDOMValidation, false );
            pParser->setFeature( XMLUni::fgXercesLoadExternalDTD, false ) ;
        }
        error_handler errorHandler;
        pParser->setErrorHandler( &errorHandler );
        DOMDocument* pDocument = pParser->parse( input );
        if( ! pDocument )
            throw xml::exception( "Could not generate document" );
        return *pDocument;
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
