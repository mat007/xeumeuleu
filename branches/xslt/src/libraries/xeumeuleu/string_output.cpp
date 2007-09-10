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

#include "string_output.h"
#include <xercesc/framework/MemBufFormatTarget.hpp>

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

// -----------------------------------------------------------------------------
// Name: string_output constructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
string_output::string_output( const std::string& encoding )
    : output( output_base_member::document_, output_base_member::document_ )
    , encoding_( encoding )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: string_output destructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
string_output::~string_output()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: string_output::str
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
std::string string_output::str() const
{
    return data_;
}

// -----------------------------------------------------------------------------
// Name: string_output::finished
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
void string_output::finished()
{
    MemBufFormatTarget target;
    fill( target, encoding_ );
    data_ = reinterpret_cast< const char* >( target.getRawBuffer() );
}