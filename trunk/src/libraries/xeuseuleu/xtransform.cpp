/*
 *   Copyright (c) 2007, Mathieu Champlon
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

#include "xtransform.h"
#include "string_output.h"
#include "buffer.h"
#include "xbuffertransform.h"

using namespace xsl;

// -----------------------------------------------------------------------------
// Name: xtransform constructor
// Created: SLI 2007-09-10
// -----------------------------------------------------------------------------
xtransform::xtransform( output& output )
    : pBuffer_( new buffer( output ) )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: xtransform destructor
// Created: SLI 2007-09-10
// -----------------------------------------------------------------------------
xtransform::~xtransform()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: xtransform::write
// Created: SLI 2007-09-25
// -----------------------------------------------------------------------------
void xtransform::write( const xsl::xbuffertransform& buffer )
{
    buffer.apply( *this );
}

// -----------------------------------------------------------------------------
// Name: xtransform::add
// Created: SLI 2007-09-26
// -----------------------------------------------------------------------------
void xtransform::add( const std::string& stylesheet )
{
    pBuffer_.reset( new buffer( *new string_output( stylesheet ), pBuffer_ ) );
}

// -----------------------------------------------------------------------------
// Name: xtransform::add
// Created: SLI 2008-04-04
// -----------------------------------------------------------------------------
void xtransform::add( std::istream& stylesheet )
{
    pBuffer_.reset( new buffer( *new string_output( stylesheet ), pBuffer_ ) );
}

// -----------------------------------------------------------------------------
// Name: xtransform::parameter
// Created: SLI 2007-09-11
// -----------------------------------------------------------------------------
void xtransform::parameter( const std::string& key, const std::string& expression )
{
    pBuffer_->parameter( key, expression );
}