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

#include "branch_input.h"
#include "input_context.h"
#include "multi_input.h"

using namespace xml;

// -----------------------------------------------------------------------------
// Name: branch_input constructor
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
branch_input::branch_input( std::auto_ptr< input_base > input1, std::auto_ptr< input_base > input2, input_context& context, bool invert )
    : input1_ ( input1 )
    , input2_ ( input2 )
    , context_( context )
    , invert_ ( invert )
    , level_  ( 0 )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: branch_input destructor
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
branch_input::~branch_input()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: branch_input::start
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::start( const std::string& tag )
{
    input1_->start( tag );
    ++level_;
}

// -----------------------------------------------------------------------------
// Name: branch_input::end
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::end()
{
    input1_->end();
    if( --level_ == 0 )
    {
        if( invert_ ) // $$$$ MAT : crappy bool
            context_.reset( std::auto_ptr< input_base >( new multi_input( input2_, input1_, context_ ) ) );
        else
            context_.reset( std::auto_ptr< input_base >( new multi_input( input1_, input2_, context_ ) ) );
    }
}

#define READ( type ) void branch_input::read( type& value ) const \
                     { \
                         input1_->read( value ); \
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

#define ATTRIBUTE( type ) void branch_input::attribute( const std::string& name, type& value ) const \
                      { \
                         input1_->attribute( name, value ); \
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
// Name: branch_input::has_child
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
bool branch_input::has_child( const std::string& name ) const
{
    return input1_->has_child( name );
}

// -----------------------------------------------------------------------------
// Name: branch_input::has_attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
bool branch_input::has_attribute( const std::string& name ) const
{
    return input1_->has_attribute( name );
}

// -----------------------------------------------------------------------------
// Name: branch_input::has_content
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
bool branch_input::has_content() const
{
    return input1_->has_content();
}

// -----------------------------------------------------------------------------
// Name: branch_input::nodes
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::nodes( const visitor& v ) const
{
    input1_->nodes( v );
}

// -----------------------------------------------------------------------------
// Name: branch_input::attributes
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::attributes( const visitor& v ) const
{
    input1_->attributes( v );
}

// -----------------------------------------------------------------------------
// Name: std::auto_ptr< input_base > branch_input::branch
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
std::auto_ptr< input_base > branch_input::branch( bool clone ) const
{
    return input1_->branch( clone );
}

// -----------------------------------------------------------------------------
// Name: branch_input::copy
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::copy( output& destination ) const
{
    input1_->copy( destination );
}

// -----------------------------------------------------------------------------
// Name: branch_input::error
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::error( const std::string& message ) const
{
    input1_->error( message );
}
