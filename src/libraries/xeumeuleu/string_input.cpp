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

#include "string_input.h"
#include "input_imp.h"
#include "grammar.h"
#include "xerces.h"

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

// -----------------------------------------------------------------------------
// Name: string_input constructor
// Created: MAT 2006-03-24
// -----------------------------------------------------------------------------
string_input::string_input( const std::string& data, const grammar& grammar )
    : input_base_member( build( data, 0, grammar ) )
    , input( std::auto_ptr< input_base >( new input_imp( root_ ) ) )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: string_input constructor
// Created: MAT 2006-03-24
// -----------------------------------------------------------------------------
string_input::string_input( const std::string& data, const encoding& encoding, const grammar& grammar )
    : input_base_member( build( data, &encoding, grammar ) )
    , input( std::auto_ptr< input_base >( new input_imp( root_ ) ) )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: string_input destructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
string_input::~string_input()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: string_input::build
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
DOMNode& string_input::build( const std::string& data, const encoding* pEncoding, const grammar& grammar )
{
    MemBufInputSource buffer( reinterpret_cast< const XMLByte* >( data.c_str() ), data.size(), "string_input", false );
    return parse( buffer, pEncoding, grammar );
}
