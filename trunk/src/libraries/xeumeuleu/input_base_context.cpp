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
#include "null_input.h"

using namespace xml;

// -----------------------------------------------------------------------------
// Name: input_base_context constructor
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
input_base_context::input_base_context()
    : input_( new null_input() )
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
input_base& input_base_context::reset( std::auto_ptr< input_base > input )
{
    input_ = input;
    return *input_;
}

// -----------------------------------------------------------------------------
// Name: input_base_context::start
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::start( const std::string& tag )
{
    input_->start( tag );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::end
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::end()
{
    input_->end();
}

#define READ( type ) void input_base_context::read( type& value ) const \
                     { \
                         input_->read( value ); \
                     }
READ( std::string )
READ( bool )
READ( short )
READ( int )
READ( long )
READ( long long )
READ( float )
READ( double )
READ( long double )
READ( unsigned int )
READ( unsigned short )
READ( unsigned long )
READ( unsigned long long )

#define ATTRIBUTE( type ) void input_base_context::attribute( const std::string& name, type& value ) const \
                      { \
                         input_->attribute( name, value ); \
                      }
ATTRIBUTE( std::string )
ATTRIBUTE( bool )
ATTRIBUTE( short )
ATTRIBUTE( int )
ATTRIBUTE( long )
ATTRIBUTE( long long )
ATTRIBUTE( float )
ATTRIBUTE( double )
ATTRIBUTE( long double )
ATTRIBUTE( unsigned short )
ATTRIBUTE( unsigned int )
ATTRIBUTE( unsigned long )
ATTRIBUTE( unsigned long long )

// -----------------------------------------------------------------------------
// Name: input_base_context::has_child
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
bool input_base_context::has_child( const std::string& name ) const
{
    return input_->has_child( name );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::has_attribute
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
bool input_base_context::has_attribute( const std::string& name ) const
{
    return input_->has_attribute( name );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::has_content
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
bool input_base_context::has_content() const
{
    return input_->has_content();
}

// -----------------------------------------------------------------------------
// Name: input_base_context::nodes
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::nodes( const visitor& v ) const
{
    input_->nodes( v );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::attributes
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::attributes( const visitor& v ) const
{
    input_->attributes( v );
}

// -----------------------------------------------------------------------------
// Name: std::auto_ptr< input_base > input_base_context::branch
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
std::auto_ptr< input_base > input_base_context::branch( bool clone ) const
{
    return input_->branch( clone );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::copy
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::copy( output& destination ) const
{
    input_->copy( destination );
}

// -----------------------------------------------------------------------------
// Name: input_base_context::error
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
void input_base_context::error( const std::string& message ) const
{
    input_->error( message );
}
