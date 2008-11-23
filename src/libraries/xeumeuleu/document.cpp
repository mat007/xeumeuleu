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

#include "document.h"
#include "chained_exception.h"
#include "error_handler.h"
#include "beautifier.h"
#include "translate.h"
#include "builder.h"
#include "grammar.h"
#include "encoding.h"
#include "parser.h"
#include "xerces.h"
#include "import.h"
#include <fstream>

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

namespace
{
    void initialize()
    {
        try
        {
            static const struct Initializer
            {
                Initializer()
                {
                    XMLPlatformUtils::Initialize();
                }
                ~Initializer()
                {
                    XMLPlatformUtils::Terminate();
                }
            } initializer;
        }
        catch( const XMLException& e )
        {
            throw chained_exception( e );
        }
    }
    DOMDocument& build()
    {
        initialize();
        try
        {
            DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation( translate( "LS" ) );
            if( ! impl )
                throw xml::exception( "Internal error in 'document::build' : DOMImplementation 'LS' not found" );
            return *impl->createDocument();
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
    DOMDocument& parse( InputSource& source, const encoding* encoding, const grammar& grammar )
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
    DOMDocument& build( const std::string& filename, const encoding* encoding, const grammar& grammar )
    {
        initialize();
        if( ! std::ifstream( filename.c_str() ) )
            throw xml::exception( "Unable to open file '" + filename + "'" );
        LocalFileInputSource source( static_cast< const XMLCh* const >( translate( filename ) ) );
        return parse( source, encoding, grammar );
    }
    DOMDocument& build( const char* data, std::size_t size, const encoding* encoding, const grammar& grammar )
    {
        initialize();
        MemBufInputSource source( reinterpret_cast< const XMLByte* >( data ), size, "string_input", false );
        return parse( source, encoding, grammar );
    }
}

// -----------------------------------------------------------------------------
// Name: document constructor
// Created: MAT 2008-02-25
// -----------------------------------------------------------------------------
document::document()
    : document_( build() )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: document constructor
// Created: MAT 2008-11-23
// -----------------------------------------------------------------------------
document::document( const std::string& filename, const encoding* encoding, const grammar& grammar )
    : document_( build( filename, encoding, grammar ) )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: document constructor
// Created: MAT 2008-11-23
// -----------------------------------------------------------------------------
document::document( const char* data, std::size_t size, const encoding* encoding, const grammar& grammar )
    : document_( build( data, size, encoding, grammar ) )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: document destructor
// Created: MAT 2008-02-25
// -----------------------------------------------------------------------------
document::~document()
{
    clean( document_.get() );
}

// -----------------------------------------------------------------------------
// Name: document::write
// Created: MAT 2008-11-23
// -----------------------------------------------------------------------------
void document::write( XMLFormatTarget& destination, const std::string& encoding )
{
    DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation( translate( "LS" ) );
    if( ! impl )
        throw xml::exception( "Internal error in 'document::fill' : DOMImplementation 'LS' not found" );
    xerces_ptr< DOMWriter > writer( *dynamic_cast< DOMImplementationLS* >( impl )->createDOMWriter() );
    error_handler handler;
    writer->setErrorHandler( &handler );
    writer->setEncoding( translate( encoding ) );
    writer->setFeature( XMLUni::fgDOMWRTFormatPrettyPrint, true );
    writer->setFeature( XMLUni:: fgDOMWRTBOM, true );
    beautifier target( destination, writer->getNewLine() );
    writer->writeNode( &target, *document_ );
}

// -----------------------------------------------------------------------------
// Name: document::fill
// Created: MAT 2008-11-23
// -----------------------------------------------------------------------------
void document::fill( const std::string& filename, const std::string& encoding )
{
    LocalFileFormatTarget target( filename.c_str() );
    write( target, encoding );
}

// -----------------------------------------------------------------------------
// Name: document::fill
// Created: MAT 2008-11-23
// -----------------------------------------------------------------------------
void document::fill( std::string& data, const std::string& encoding )
{
    MemBufFormatTarget target;
    write( target, encoding );
    data = reinterpret_cast< const char* >( target.getRawBuffer() );
}
