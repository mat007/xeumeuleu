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

#include "input_base_context.h"

using namespace xml;

// -----------------------------------------------------------------------------
// Name: input_base_context constructor
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
input_base_context::input_base_context()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: input_base_context destructor
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
input_base_context::~input_base_context()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: input_base_context::reset
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
input_base& input_base_context::reset( std::auto_ptr< input_base > pInput )
{
    pInput_ = pInput;
    return *pInput_;
}

// -----------------------------------------------------------------------------
// Name: input_base_context::start
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::start( const std::string& tag )
{
    pInput_->start( tag );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::end
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::end()
{
    pInput_->end();
}

// -----------------------------------------------------------------------------
// Name: input_base_context::read
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::read( std::string& value ) const
{
    pInput_->read( value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::read
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::read( float& value ) const
{
    pInput_->read( value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::read
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::read( double& value ) const
{
    pInput_->read( value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::read
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::read( short& value ) const
{
    pInput_->read( value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::read
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::read( int& value ) const
{
    pInput_->read( value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::read
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::read( long& value ) const
{
    pInput_->read( value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::read
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::read( long long& value ) const
{
    pInput_->read( value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::read
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::read( bool& value ) const
{
    pInput_->read( value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::read
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::read( unsigned short& value ) const
{
    pInput_->read( value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::read
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::read( unsigned int& value ) const
{
    pInput_->read( value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::read
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::read( unsigned long& value ) const
{
    pInput_->read( value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::read
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::read( unsigned long long& value ) const
{
    pInput_->read( value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::hasElement
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
bool input_base_context::hasElement( const std::string& tag ) const
{
    return pInput_->hasElement( tag );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::hasAttribute
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
bool input_base_context::hasAttribute( const std::string& name ) const
{
    return pInput_->hasAttribute( name );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::hasContent
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
bool input_base_context::hasContent() const
{
    return pInput_->hasContent();
}

// -----------------------------------------------------------------------------
// Name: input_base_context::attribute
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::attribute( const std::string& name, std::string& value ) const
{
    pInput_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::attribute
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::attribute( const std::string& name, float& value ) const
{
    pInput_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::attribute
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::attribute( const std::string& name, double& value ) const
{
    pInput_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::attribute
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::attribute( const std::string& name, short& value ) const
{
    pInput_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::attribute
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::attribute( const std::string& name, int& value ) const
{
    pInput_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::attribute
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::attribute( const std::string& name, long& value ) const
{
    pInput_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::attribute
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::attribute( const std::string& name, long long& value ) const
{
    pInput_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::attribute
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::attribute( const std::string& name, bool& value ) const
{
    pInput_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::attribute
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::attribute( const std::string& name, unsigned short& value ) const
{
    pInput_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::attribute
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::attribute( const std::string& name, unsigned int& value ) const
{
    pInput_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::attribute
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::attribute( const std::string& name, unsigned long& value ) const
{
    pInput_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::attribute
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::attribute( const std::string& name, unsigned long long& value ) const
{
    pInput_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::nodes
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::nodes( const visitor& v ) const
{
    pInput_->nodes( v );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::attributes
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::attributes( const visitor& v ) const
{
    pInput_->attributes( v );
}

// -----------------------------------------------------------------------------
// Name: std::auto_ptr< input_base > input_base_context::branch
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
std::auto_ptr< input_base > input_base_context::branch( bool clone ) const
{
    return pInput_->branch( clone );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::copy
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::copy( output& destination ) const
{
    pInput_->copy( destination );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::error
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::error( const std::string& message ) const
{
    pInput_->error( message );
}
