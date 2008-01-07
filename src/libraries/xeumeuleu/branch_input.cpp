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
branch_input::branch_input( std::auto_ptr< input_base > pInput1, std::auto_ptr< input_base > pInput2, input_context& context, bool invert )
    : pInput1_( pInput1 )
    , pInput2_( pInput2 )
    , context_( context )
    , invert_ ( invert )
    , level_  ( 1 )
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
    pInput1_->start( tag );
    ++level_;
}

// -----------------------------------------------------------------------------
// Name: branch_input::end
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::end()
{
    pInput1_->end();
    if( --level_ == 0 )
    {
        if( invert_ ) // $$$$ MAT : crappy bool
            context_.reset( std::auto_ptr< input_base >( new multi_input( pInput2_, pInput1_, context_ ) ) );
        else
            context_.reset( std::auto_ptr< input_base >( new multi_input( pInput1_, pInput2_, context_ ) ) );
    }
}

// -----------------------------------------------------------------------------
// Name: branch_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::read( std::string& value ) const
{
    pInput1_->read( value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::read( float& value ) const
{
    pInput1_->read( value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::read( double& value ) const
{
    pInput1_->read( value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::read( short& value ) const
{
    pInput1_->read( value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::read( int& value ) const
{
    pInput1_->read( value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::read( long& value ) const
{
    pInput1_->read( value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::read( long long& value ) const
{
    pInput1_->read( value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::read( bool& value ) const
{
    pInput1_->read( value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::read( unsigned short& value ) const
{
    pInput1_->read( value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::read( unsigned int& value ) const
{
    pInput1_->read( value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::read( unsigned long& value ) const
{
    pInput1_->read( value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::read( unsigned long long& value ) const
{
    pInput1_->read( value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::hasElement
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
bool branch_input::hasElement( const std::string& tag ) const
{
    return pInput1_->hasElement( tag );
}

// -----------------------------------------------------------------------------
// Name: branch_input::hasAttribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
bool branch_input::hasAttribute( const std::string& name ) const
{
    return pInput1_->hasAttribute( name );
}

// -----------------------------------------------------------------------------
// Name: branch_input::hasContent
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
bool branch_input::hasContent() const
{
    return pInput1_->hasContent();
}

// -----------------------------------------------------------------------------
// Name: branch_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::attribute( const std::string& name, std::string& value ) const
{
    pInput1_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::attribute( const std::string& name, float& value ) const
{
    pInput1_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::attribute( const std::string& name, double& value ) const
{
    pInput1_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::attribute( const std::string& name, short& value ) const
{
    pInput1_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::attribute( const std::string& name, int& value ) const
{
    pInput1_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::attribute( const std::string& name, long& value ) const
{
    pInput1_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::attribute( const std::string& name, long long& value ) const
{
    pInput1_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::attribute( const std::string& name, bool& value ) const
{
    pInput1_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::attribute( const std::string& name, unsigned short& value ) const
{
    pInput1_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::attribute( const std::string& name, unsigned int& value ) const
{
    pInput1_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::attribute( const std::string& name, unsigned long& value ) const
{
    pInput1_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::attribute( const std::string& name, unsigned long long& value ) const
{
    pInput1_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: branch_input::nodes
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::nodes( const visitor& v ) const
{
    pInput1_->nodes( v );
}

// -----------------------------------------------------------------------------
// Name: branch_input::attributes
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::attributes( const visitor& v ) const
{
    pInput1_->attributes( v );
}

// -----------------------------------------------------------------------------
// Name: std::auto_ptr< input_base > branch_input::branch
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
std::auto_ptr< input_base > branch_input::branch( bool clone, input_context& context ) const
{
    return pInput1_->branch( clone, context );
}

// -----------------------------------------------------------------------------
// Name: branch_input::copy
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::copy( output& destination ) const
{
    pInput1_->copy( destination );
}

// -----------------------------------------------------------------------------
// Name: branch_input::error
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void branch_input::error( const std::string& message ) const
{
    pInput1_->error( message );
}
