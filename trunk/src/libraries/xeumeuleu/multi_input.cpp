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

using namespace xml;

// -----------------------------------------------------------------------------
// Name: multi_input constructor
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
multi_input::multi_input( std::auto_ptr< input_base > pInput1, std::auto_ptr< input_base > pInput2, input_context& context )
    : pInput1_( pInput1 )
    , pInput2_( pInput2 )
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
// Name: multi_input::hasElement
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
bool multi_input::hasElement( const std::string& tag ) const
{
    return pInput1_->hasElement( tag ) || pInput2_->hasElement( tag );
}

// -----------------------------------------------------------------------------
// Name: multi_input::hasAttribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
bool multi_input::hasAttribute( const std::string& name ) const
{
    return pInput1_->hasAttribute( name ) || pInput2_->hasAttribute( name );
}

// -----------------------------------------------------------------------------
// Name: multi_input::hasContent
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
bool multi_input::hasContent() const
{
    return pInput1_->hasContent() || pInput2_->hasContent();
}

// -----------------------------------------------------------------------------
// Name: multi_input::start
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::start( const std::string& tag )
{
    if( pInput1_->hasElement( tag ) && ! pInput2_->hasElement( tag ) )
    {
        pInput1_->start( tag );
        context_.reset( std::auto_ptr< input_base >( new branch_input( pInput1_, pInput2_, context_, false ) ) );
    }
    else if( pInput2_->hasElement( tag ) && ! pInput1_->hasElement( tag ) )
    {
        pInput2_->start( tag );
        context_.reset( std::auto_ptr< input_base >( new branch_input( pInput2_, pInput1_, context_, true ) ) );
    }
    else
    {
        pInput1_->start( tag );
        pInput2_->start( tag );
    }
}

// -----------------------------------------------------------------------------
// Name: multi_input::end
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::end()
{
    pInput1_->end();
    pInput2_->end();
}

// -----------------------------------------------------------------------------
// Name: multi_input::readContent
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
template< typename T > void multi_input::readContent( T& value ) const
{
    if( pInput1_->hasContent() )
        pInput1_->read( value );
    else
        pInput2_->read( value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::readAttribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
template< typename T > void multi_input::readAttribute( const std::string& name, T& value ) const
{
    if( pInput1_->hasAttribute( name ) )
        pInput1_->attribute( name, value );
    else
        pInput2_->attribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::read( std::string& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::read( float& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::read( double& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::read( short& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::read( int& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::read( long& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::read( long long& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::read( bool& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::read( unsigned short& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::read( unsigned int& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::read( unsigned long& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::read
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::read( unsigned long long& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::attribute( const std::string& name, std::string& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::attribute( const std::string& name, float& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::attribute( const std::string& name, double& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::attribute( const std::string& name, short& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::attribute( const std::string& name, int& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::attribute( const std::string& name, long& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::attribute( const std::string& name, long long& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::attribute( const std::string& name, bool& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::attribute( const std::string& name, unsigned short& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::attribute( const std::string& name, unsigned int& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::attribute( const std::string& name, unsigned long& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::attribute
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::attribute( const std::string& name, unsigned long long& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: multi_input::nodes
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::nodes( const visitor& v ) const
{
    pInput1_->nodes( v );
    pInput2_->nodes( v );
}

// -----------------------------------------------------------------------------
// Name: multi_input::attributes
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::attributes( const visitor& v ) const
{
    pInput1_->attributes( v );
    pInput2_->attributes( v );
}

// -----------------------------------------------------------------------------
// Name: multi_input::branch
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
std::auto_ptr< input_base > multi_input::branch( bool clone, input_context& context ) const
{
    return std::auto_ptr< input_base >( new multi_input( pInput1_->branch( clone, context ), pInput2_->branch( clone, context ), context ) );
}

// -----------------------------------------------------------------------------
// Name: multi_input::copy
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::copy( output& destination ) const
{
    pInput1_->copy( destination );
    pInput2_->copy( destination );
}

// -----------------------------------------------------------------------------
// Name: multi_input::error
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
void multi_input::error( const std::string& message ) const
{
    pInput2_->error( message );
}
