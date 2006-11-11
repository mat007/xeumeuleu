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
#include "input.h"
#include "optional_input.h"
#include "exception.h"

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

// -----------------------------------------------------------------------------
// Name: input constructor
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
input::input( std::auto_ptr< input_base > pInput )
    : pInput_( pInput )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: input destructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
input::~input()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: input::start
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
void input::start( const std::string& tag )
{
    pInput_->start( tag );
}

// -----------------------------------------------------------------------------
// Name: input::end
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
void input::end()
{
    pInput_->end();
}

// -----------------------------------------------------------------------------
// Name: input::branch
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
std::auto_ptr< input > input::branch() const
{
    return std::auto_ptr< input >( new input( pInput_->branch() ) );
}

// -----------------------------------------------------------------------------
// Name: input::visit
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void input::visit( const visitor& v ) const
{
    pInput_->visit( v );
}

// -----------------------------------------------------------------------------
// Name: input::optional
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
void input::optional()
{
    pInput_.reset( new optional_input( pInput_, *this ) );
}

// -----------------------------------------------------------------------------
// Name: input::reset
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
input_base& input::reset( std::auto_ptr< input_base > pInput )
{
    pInput_ = pInput;
    return *pInput_;
}
