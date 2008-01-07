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

#include "optional_input.h"
#include "input_context.h"
#include "exception.h"
#include "null_input.h"

using namespace xml;

// -----------------------------------------------------------------------------
// Name: optional_input constructor
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
optional_input::optional_input( std::auto_ptr< input_base > pInput, input_context& context )
    : pInput_ ( pInput )
    , context_( context )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: optional_input destructor
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
optional_input::~optional_input()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: optional_input::start
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
void optional_input::start( const std::string& tag )
{
    if( pInput_->hasElement( tag ) )
        context_.reset( pInput_ ).start( tag );
    else
        context_.reset( std::auto_ptr< input_base >( new null_input( pInput_, context_ ) ) ).start( tag );
}

// -----------------------------------------------------------------------------
// Name: optional_input::end
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
void optional_input::end()
{
    context_.reset( pInput_ );
    throw xml::exception( "Invalid 'end' after an 'optional'" );
}

// -----------------------------------------------------------------------------
// Name: optional_input::readContent
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
template< typename T > void optional_input::readContent( T& value ) const
{
    if( pInput_->hasContent() )
        context_.reset( pInput_ ).read( value );
    else
        context_.reset( pInput_ );
}

// -----------------------------------------------------------------------------
// Name: optional_input::read
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
void optional_input::read( std::string& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::read
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
void optional_input::read( float& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::read
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
void optional_input::read( double& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::read
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void optional_input::read( short& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::read
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
void optional_input::read( int& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::read
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void optional_input::read( long& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::read
// Created: MAT 2007-09-18
// -----------------------------------------------------------------------------
void optional_input::read( long long& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::read
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
void optional_input::read( bool& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::read
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void optional_input::read( unsigned short& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::read
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void optional_input::read( unsigned int& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::read
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void optional_input::read( unsigned long& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::read
// Created: MAT 2007-09-18
// -----------------------------------------------------------------------------
void optional_input::read( unsigned long long& value ) const
{
    readContent( value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::hasElement
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
bool optional_input::hasElement( const std::string& tag ) const
{
    return pInput_->hasElement( tag );
}

// -----------------------------------------------------------------------------
// Name: optional_input::hasAttribute
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
bool optional_input::hasAttribute( const std::string& name ) const
{
    return pInput_->hasAttribute( name );
}

// -----------------------------------------------------------------------------
// Name: optional_input::hasContent
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
bool optional_input::hasContent() const
{
    return pInput_->hasContent();
}

// -----------------------------------------------------------------------------
// Name: optional_input::readAttribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
template< typename T > void optional_input::readAttribute( const std::string& name, T& value ) const
{
    if( pInput_->hasAttribute( name ) )
        context_.reset( pInput_ ).attribute( name, value );
    else
        context_.reset( pInput_ );
}

// -----------------------------------------------------------------------------
// Name: optional_input::attribute
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
void optional_input::attribute( const std::string& name, std::string& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::attribute
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
void optional_input::attribute( const std::string& name, float& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::attribute
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
void optional_input::attribute( const std::string& name, double& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void optional_input::attribute( const std::string& name, short& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::attribute
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
void optional_input::attribute( const std::string& name, int& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void optional_input::attribute( const std::string& name, long& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::attribute
// Created: MCO 2007-09-18
// -----------------------------------------------------------------------------
void optional_input::attribute( const std::string& name, long long& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::attribute
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
void optional_input::attribute( const std::string& name, bool& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void optional_input::attribute( const std::string& name, unsigned short& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void optional_input::attribute( const std::string& name, unsigned int& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void optional_input::attribute( const std::string& name, unsigned long& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::attribute
// Created: MCO 2007-09-18
// -----------------------------------------------------------------------------
void optional_input::attribute( const std::string& name, unsigned long long& value ) const
{
    readAttribute( name, value );
}

// -----------------------------------------------------------------------------
// Name: optional_input::nodes
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
void optional_input::nodes( const visitor& v ) const
{
    context_.reset( pInput_ ).nodes( v );
}

// -----------------------------------------------------------------------------
// Name: optional_input::attributes
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
void optional_input::attributes( const visitor& v ) const
{
    context_.reset( pInput_ ).attributes( v );
}

// -----------------------------------------------------------------------------
// Name: std::auto_ptr< input_base > optional_input::branch
// Created: MAT 2006-03-20
// -----------------------------------------------------------------------------
std::auto_ptr< input_base > optional_input::branch( bool clone, input_context& context ) const
{
    return pInput_->branch( clone, context );
}

// -----------------------------------------------------------------------------
// Name: optional_input::copy
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
void optional_input::copy( output& destination ) const
{
    pInput_->copy( destination );
}

// -----------------------------------------------------------------------------
// Name: optional_input::error
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
void optional_input::error( const std::string& message ) const
{
    pInput_->error( message );
}
