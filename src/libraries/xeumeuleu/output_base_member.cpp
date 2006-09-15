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

#include "xeumeuleu_pch.h"
#include "output_base_member.h"
#include "translate.h"
#include "error_handler.h"
#include "chained_exception.h"
#include "beautifier.h"
#include "xerces_wrapper.h"
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

// -----------------------------------------------------------------------------
// Name: output_base_member constructor
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
output_base_member::output_base_member()
    : document_( build() )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: output_base_member destructor
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
output_base_member::~output_base_member()
{
    document_.release();
}

// -----------------------------------------------------------------------------
// Name: output_base_member::build
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
DOMDocument& output_base_member::build()
{
    try
    {
        DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation( translate( "LS" ) );
        DOMDocument* pDocument = impl->createDocument();
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

// -----------------------------------------------------------------------------
// Name: output_base_member::fill
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
void output_base_member::fill( XMLFormatTarget& destination, const std::string& encoding ) const
{
    const DOMImplementation* pImpl = DOMImplementationRegistry::getDOMImplementation( translate( "LS" ) );
    xerces_wrapper< DOMWriter > pWriter( ((DOMImplementationLS*)pImpl)->createDOMWriter() );
    error_handler errorHandler;
    pWriter->setErrorHandler( &errorHandler );
    pWriter->setEncoding( translate( encoding ) );
    pWriter->setFeature( XMLUni::fgDOMWRTFormatPrettyPrint, true );
    beautifier target( destination, pWriter->getNewLine() );
    pWriter->writeNode( &target, *&document_ );
}
