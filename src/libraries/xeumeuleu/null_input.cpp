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

#include "null_input.h"
#include "input_context.h"
#include "exception.h"

using namespace xml;

// -----------------------------------------------------------------------------
// Name: null_input constructor
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
null_input::null_input( std::auto_ptr< input_base > input, input_context& context )
    : input_  ( input )
    , context_( &context )
    , level_  ( 0 )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: null_input constructor
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
null_input::null_input()
    : context_( 0 )
    , level_  ( 0 )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: null_input destructor
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
null_input::~null_input()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: null_input::start
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
void null_input::start( const std::string& /*tag*/ )
{
    ++level_;
}

// -----------------------------------------------------------------------------
// Name: null_input::end
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
void null_input::end()
{
    if( --level_ == 0 && context_ )
        context_->reset( input_ );
    else if( level_ < 0 )
        throw xml::exception( "Cannot move up from root" );
}

#define READ( type ) void null_input::read( type& /*value*/ ) const \
                     { \
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
READ( unsigned short )
READ( unsigned int )
READ( unsigned long )
READ( unsigned long long )

#define ATTRIBUTE( type ) void null_input::attribute( const std::string& /*name*/, type& /*value*/ ) const \
                          { \
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
// Name: null_input::has_element
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
bool null_input::has_element( const std::string& /*tag*/ ) const
{
    return false;
}

// -----------------------------------------------------------------------------
// Name: null_input::has_attribute
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
bool null_input::has_attribute( const std::string& /*name*/ ) const
{
    return false;
}

// -----------------------------------------------------------------------------
// Name: null_input::has_content
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
bool null_input::has_content() const
{
    return false;
}

// -----------------------------------------------------------------------------
// Name: null_input::nodes
// Created: MAT 2006-01-08
// -----------------------------------------------------------------------------
void null_input::nodes( const visitor& /*v*/ ) const
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: null_input::attributes
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
void null_input::attributes( const visitor& /*v*/ ) const
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: null_input::branch
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
std::auto_ptr< input_base > null_input::branch( bool /*clone*/ ) const
{
    return std::auto_ptr< input_base >( new null_input() );
}

// -----------------------------------------------------------------------------
// Name: null_input::copy
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
void null_input::copy( output& /*destination*/ ) const
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: null_input::error
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
void null_input::error( const std::string& message ) const
{
    if( ! input_.get() )
        throw xml::exception( message );
    input_->error( message );
}
