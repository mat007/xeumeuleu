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

#include "input.h"
#include "optional_input.h"
#include "multi_input.h"

using namespace xml;

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
std::auto_ptr< input > input::branch( bool clone ) const
{
    std::auto_ptr< input > pInput( new input( std::auto_ptr< input_base >() ) );
    pInput->pInput_ = pInput_->branch( clone, *pInput );
    return pInput;
}

// -----------------------------------------------------------------------------
// Name: input::copy
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
void input::copy( output& destination ) const
{
    pInput_->copy( destination );
}

// -----------------------------------------------------------------------------
// Name: input::error
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
void input::error( const std::string& message ) const
{
    pInput_->error( message );
}

// -----------------------------------------------------------------------------
// Name: input::hasElement
// Created: MAT 2007-11-04
// -----------------------------------------------------------------------------
bool input::hasElement( const std::string& tag ) const
{
    return pInput_->hasElement( tag );
}

// -----------------------------------------------------------------------------
// Name: input::hasAttribute
// Created: MAT 2007-11-04
// -----------------------------------------------------------------------------
bool input::hasAttribute( const std::string& name ) const
{
    return pInput_->hasAttribute( name );
}

// -----------------------------------------------------------------------------
// Name: input::hasContent
// Created: MAT 2007-11-04
// -----------------------------------------------------------------------------
bool input::hasContent() const
{
    return pInput_->hasContent();
}

// -----------------------------------------------------------------------------
// Name: input::nodes
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void input::nodes( const visitor& v ) const
{
    pInput_->nodes( v );
}

// -----------------------------------------------------------------------------
// Name: input::nodes
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
void input::attributes( const visitor& v ) const
{
    pInput_->attributes( v );
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
// Name: input::attach
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void input::attach( std::auto_ptr< input > pInput )
{
    pInput_.reset( new multi_input( pInput_, pInput->pInput_, *this ) );
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
