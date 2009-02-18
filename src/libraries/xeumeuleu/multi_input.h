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

#ifndef xeumeuleu_multi_input_h
#define xeumeuleu_multi_input_h

#include "input_base.h"
#include "input_context.h"
#include "branch_input.h"
#include <memory>

#ifdef _MSC_VER
#   pragma warning( push )
#   pragma warning( disable: 4355 )
#endif

namespace xml
{
// =============================================================================
/** @class  multi_input
    @brief  Multi input implementation
*/
// Created: MAT 2008-01-07
// =============================================================================
class multi_input : public input_base
{
public:
    //! @name Constructors/Destructor
    //@{
    multi_input( std::auto_ptr< input_base > input1, std::auto_ptr< input_base > input2, input_context& context )
        : input1_ ( input1 )
        , input2_ ( input2 )
        , branch1_( *input1_, *this, context )
        , branch2_( *input2_, *this, context )
        , context_( context )
    {}
    virtual ~multi_input()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string& tag )
    {
        if( input1_->has_child( tag ) && ! input2_->has_child( tag ) )
            context_.reset( branch1_ ).start( tag );
        else if( input2_->has_child( tag ) && ! input1_->has_child( tag ) )
            context_.reset( branch2_ ).start( tag );
        else
        {
            input1_->start( tag );
            input2_->start( tag );
        }
    }
    virtual void end()
    {
        input1_->end();
        input2_->end();
    }

    virtual void read( std::string& value ) const { read_content( value ); }
    virtual void read( bool& value ) const { read_content( value ); }
    virtual void read( short& value ) const { read_content( value ); }
    virtual void read( int& value ) const { read_content( value ); }
    virtual void read( long& value ) const { read_content( value ); }
    virtual void read( long long& value ) const { read_content( value ); }
    virtual void read( float& value ) const { read_content( value ); }
    virtual void read( double& value ) const { read_content( value ); }
    virtual void read( long double& value ) const { read_content( value ); }
    virtual void read( unsigned short& value ) const { read_content( value ); }
    virtual void read( unsigned int& value ) const { read_content( value ); }
    virtual void read( unsigned long& value ) const { read_content( value ); }
    virtual void read( unsigned long long& value ) const { read_content( value ); }

    virtual std::auto_ptr< input_base > branch( bool clone ) const;

    virtual void copy( output& destination ) const
    {
        input1_->copy( destination );
        input2_->copy( destination );
    }

    virtual void error( const std::string& message ) const
    {
        input2_->error( message );
    }
    //@}

    //! @name Accessors
    //@{
    virtual bool has_child( const std::string& name ) const
    {
        return input1_->has_child( name ) || input2_->has_child( name );
    }
    virtual bool has_attribute( const std::string& name ) const
    {
        return input1_->has_attribute( name ) || input2_->has_attribute( name );
    }
    virtual bool has_content() const
    {
        return input1_->has_content() || input2_->has_content();
    }

    virtual void attribute( const std::string& name, std::string& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, bool& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, short& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, int& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, long& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, long long& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, float& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, double& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, long double& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, unsigned short& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, unsigned int& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, unsigned long& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, unsigned long long& value ) const { read_attribute( name, value ); }

    virtual void nodes( const visitor& v ) const
    {
        input1_->nodes( v );
        input2_->nodes( v );
    }
    virtual void attributes( const visitor& v ) const
    {
        input1_->attributes( v );
        input2_->attributes( v );
    }
    //@}

private:
    //! @name Helpers
    //@{
    template< typename T > void read_content( T& value ) const
    {
        if( input1_->has_content() )
            input1_->read( value );
        else
            input2_->read( value );
    }
    template< typename T > void read_attribute( const std::string& name, T& value ) const
    {
        if( input1_->has_attribute( name ) )
            input1_->attribute( name, value );
        else
            input2_->attribute( name, value );
    }
    //@}

private:
    //! @name Member data
    //@{
    std::auto_ptr< input_base > input1_;
    std::auto_ptr< input_base > input2_;
    branch_input branch1_;
    branch_input branch2_;
    input_context& context_;
    //@}
};

}

#ifdef _MSC_VER
#   pragma warning( pop )
#endif

#include "input_base_context.h"

namespace xml
{
    inline std::auto_ptr< input_base > multi_input::branch( bool clone ) const
    {
        return std::auto_ptr< input_base >( new input_base_context( input1_->branch( clone ), input2_->branch( clone ) ) );
    }
}

#endif // xeumeuleu_multi_input_h
