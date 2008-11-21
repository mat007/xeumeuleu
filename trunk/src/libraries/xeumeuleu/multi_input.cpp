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

#include "multi_input.h"
#include "input_context.h"
#include "branch_input.h"
#include "input_base_context.h"

using namespace xml;

// -----------------------------------------------------------------------------
// Name: multi_input constructor
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
multi_input::multi_input( std::auto_ptr< input_base > input1, std::auto_ptr< input_base > input2, input_context& context )
    : input1_ ( input1 )
    , input2_ ( input2 )
    , context_( context )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: multi_input destructor
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
multi_input::~multi_input()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: multi_input::start
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::start( const std::string& tag )
{
    if( input1_->has_element( tag ) && ! input2_->has_element( tag ) )
        context_.reset( std::auto_ptr< input_base >( new branch_input( input1_, input2_, context_, false ) ) ).start( tag );
    else if( input2_->has_element( tag ) && ! input1_->has_element( tag ) )
        context_.reset( std::auto_ptr< input_base >( new branch_input( input2_, input1_, context_, true ) ) ).start( tag );
    else
    {
        input1_->start( tag );
        input2_->start( tag );
    }
}

// -----------------------------------------------------------------------------
// Name: multi_input::end
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::end()
{
    input1_->end();
    input2_->end();
}

// -----------------------------------------------------------------------------
// Name: multi_input::read_content
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
template< typename T > void multi_input::read_content( T& value ) const
{
    if( input1_->has_content() )
        input1_->read( value );
    else
        input2_->read( value );
}

#define READ( type ) void multi_input::read( type& value ) const \
                     { \
                         read_content( value ); \
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

// -----------------------------------------------------------------------------
// Name: multi_input::read_attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
template< typename T > void multi_input::read_attribute( const std::string& name, T& value ) const
{
    if( input1_->has_attribute( name ) )
        input1_->attribute( name, value );
    else
        input2_->attribute( name, value );
}

#define ATTRIBUTE( type ) void multi_input::attribute( const std::string& name, type& value ) const \
                      { \
                         read_attribute( name, value ); \
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
// Name: multi_input::has_element
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
bool multi_input::has_element( const std::string& tag ) const
{
    return input1_->has_element( tag ) || input2_->has_element( tag );
}

// -----------------------------------------------------------------------------
// Name: multi_input::has_attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
bool multi_input::has_attribute( const std::string& name ) const
{
    return input1_->has_attribute( name ) || input2_->has_attribute( name );
}

// -----------------------------------------------------------------------------
// Name: multi_input::has_content
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
bool multi_input::has_content() const
{
    return input1_->has_content() || input2_->has_content();
}

// -----------------------------------------------------------------------------
// Name: multi_input::nodes
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::nodes( const visitor& v ) const
{
    input1_->nodes( v );
    input2_->nodes( v );
}

// -----------------------------------------------------------------------------
// Name: multi_input::attributes
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::attributes( const visitor& v ) const
{
    input1_->attributes( v );
    input2_->attributes( v );
}

// -----------------------------------------------------------------------------
// Name: multi_input::branch
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
std::auto_ptr< input_base > multi_input::branch( bool clone ) const
{
    std::auto_ptr< input_base_context > context( new input_base_context() );
    std::auto_ptr< input_base > input( new multi_input( input1_->branch( clone ), input2_->branch( clone ), *context ) );
    context->reset( input );
    return std::auto_ptr< input_base >( context );
}

// -----------------------------------------------------------------------------
// Name: multi_input::copy
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::copy( output& destination ) const
{
    input1_->copy( destination );
    input2_->copy( destination );
}

// -----------------------------------------------------------------------------
// Name: multi_input::error
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::error( const std::string& message ) const
{
    input2_->error( message );
}
