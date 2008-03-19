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

#include "file_input.h"
#include "translate.h"
#include "exception.h"
#include "input_imp.h"
#include <fstream>

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

// -----------------------------------------------------------------------------
// Name: file_input constructor
// Created: MAT 2006-03-26
// -----------------------------------------------------------------------------
file_input::file_input( const std::string& filename, const encoding& encoding, const grammar& grammar )
    : input_base_member( build( filename, &encoding, grammar ) )
    , input( std::auto_ptr< input_base >( new input_imp( *pDocument_ ) ) )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: file_input constructor
// Created: MAT 2006-03-26
// -----------------------------------------------------------------------------
file_input::file_input( const std::string& filename, const grammar& grammar )
    : input_base_member( build( filename, 0, grammar ) )
    , input( std::auto_ptr< input_base >( new input_imp( *pDocument_ ) ) )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: file_input destructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
file_input::~file_input()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: file_input::build
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
DOMDocument& file_input::build( const std::string& filename, const encoding* pEncoding, const grammar& grammar )
{
    if( ! std::ifstream( filename.c_str() ) )
        throw xml::exception( "Unable to open file '" + filename + "'" );
    LocalFileInputSource buffer( static_cast< const XMLCh* const >( translate( filename ) ) );
    return parse( buffer, pEncoding, grammar );
}
