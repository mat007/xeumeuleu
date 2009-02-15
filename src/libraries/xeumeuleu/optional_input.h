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

#ifndef _xeumeuleu_optional_input_h_
#define _xeumeuleu_optional_input_h_

#include "input_base.h"
#include "input_context.h"
#include "exception.h"
#include "null_input.h"

namespace xml
{
    class input_context;

// =============================================================================
/** @class  optional_input
    @brief  Input state to handle optional manipulation
*/
// Created: MAT 2006-03-20
// =============================================================================
class optional_input : public input_base
{
public:
    //! @name Constructors/Destructor
    //@{
    optional_input( std::auto_ptr< input_base > input, input_context& context )
        : input_  ( input )
        , context_( context )
    {}
    virtual ~optional_input()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string& tag )
    {
        if( input_->has_child( tag ) )
            context_.reset( input_ ).start( tag );
        else
            context_.reset( std::auto_ptr< input_base >( new null_input( input_, context_ ) ) ).start( tag );
    }
    virtual void end()
    {
        context_.reset( input_ );
        throw xml::exception( "Invalid 'end' after an 'optional'" );
    }

#define READ( type ) void read( type& value ) const { read_content( value ); }
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
#undef READ

    virtual std::auto_ptr< input_base > branch( bool clone ) const
    {
        return input_->branch( clone );
    }

    virtual void copy( output& destination ) const
    {
        input_->copy( destination );
    }

    virtual void error( const std::string& message ) const
    {
        input_->error( message );
    }
    //@}

    //! @name Accessors
    //@{
    virtual bool has_child( const std::string& name ) const
    {
        return input_->has_child( name );
    }
    virtual bool has_attribute( const std::string& name ) const
    {
        return input_->has_attribute( name );
    }
    virtual bool has_content() const
    {
        return input_->has_content();
    }

#define ATTRIBUTE( type ) void attribute( const std::string& name, type& value ) const { read_attribute( name, value ); }
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
#undef ATTRIBUTE

    virtual void nodes( const visitor& v ) const
    {
        context_.reset( input_ ).nodes( v );
    }
    virtual void attributes( const visitor& v ) const
    {
        context_.reset( input_ ).attributes( v );
    }
    //@}

private:
    //! @name Helpers
    //@{
    template< typename T > void read_content( T& value ) const
    {
        if( input_->has_content() )
            context_.reset( input_ ).read( value );
        else
            context_.reset( input_ );
    }
    template< typename T > void read_attribute( const std::string& name, T& value ) const
    {
        if( input_->has_attribute( name ) )
            context_.reset( input_ ).attribute( name, value );
        else
            context_.reset( input_ );
    }
    //@}

private:
    //! @name Member data
    //@{
    mutable std::auto_ptr< input_base > input_;
    input_context& context_;
    //@}
};

}

#endif // _xeumeuleu_optional_input_h_
