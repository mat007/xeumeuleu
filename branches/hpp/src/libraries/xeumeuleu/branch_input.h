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

#ifndef xeumeuleu_branch_input_h
#define xeumeuleu_branch_input_h

#include "input_base.h"
#include "input_context.h"
#include "multi_input.h"

namespace xml
{
// =============================================================================
/** @class  branch_input
    @brief  Input state to handle branch manipulation
*/
// Created: MAT 2008-01-07
// =============================================================================
class branch_input : public input_base
{
public:
    //! @name Constructors/Destructor
    //@{
    branch_input( std::auto_ptr< input_base > input1, std::auto_ptr< input_base > input2, input_context& context, bool invert )
        : input1_ ( input1 )
        , input2_ ( input2 )
        , context_( context )
        , invert_ ( invert )
        , level_  ( 0 )
    {}
    virtual ~branch_input()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string& tag )
    {
        input1_->start( tag );
        ++level_;
    }
    virtual void end()
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

    virtual void read( std::string& value ) const { input1_->read( value ); }
    virtual void read( bool& value ) const { input1_->read( value ); }
    virtual void read( short& value ) const { input1_->read( value ); }
    virtual void read( int& value ) const { input1_->read( value ); }
    virtual void read( long& value ) const { input1_->read( value ); }
    virtual void read( long long& value ) const { input1_->read( value ); }
    virtual void read( float& value ) const { input1_->read( value ); }
    virtual void read( double& value ) const { input1_->read( value ); }
    virtual void read( long double& value ) const { input1_->read( value ); }
    virtual void read( unsigned short& value ) const { input1_->read( value ); }
    virtual void read( unsigned int& value ) const { input1_->read( value ); }
    virtual void read( unsigned long& value ) const { input1_->read( value ); }
    virtual void read( unsigned long long& value ) const { input1_->read( value ); }

    virtual std::auto_ptr< input_base > branch( bool clone ) const
    {
        return input1_->branch( clone );
    }

    virtual void copy( output& destination ) const
    {
        input1_->copy( destination );
    }

    virtual void error( const std::string& message ) const
    {
        input1_->error( message );
    }
    //@}

    //! @name Accessors
    //@{
    virtual bool has_child( const std::string& name ) const
    {
        return input1_->has_child( name );
    }
    virtual bool has_attribute( const std::string& name ) const
    {
        return input1_->has_attribute( name );
    }
    virtual bool has_content() const
    {
        return input1_->has_content();
    }

    virtual void attribute( const std::string& name, std::string& value ) const { input1_->attribute( name, value ); }
    virtual void attribute( const std::string& name, bool& value ) const { input1_->attribute( name, value ); }
    virtual void attribute( const std::string& name, short& value ) const { input1_->attribute( name, value ); }
    virtual void attribute( const std::string& name, int& value ) const { input1_->attribute( name, value ); }
    virtual void attribute( const std::string& name, long& value ) const { input1_->attribute( name, value ); }
    virtual void attribute( const std::string& name, long long& value ) const { input1_->attribute( name, value ); }
    virtual void attribute( const std::string& name, float& value ) const { input1_->attribute( name, value ); }
    virtual void attribute( const std::string& name, double& value ) const { input1_->attribute( name, value ); }
    virtual void attribute( const std::string& name, long double& value ) const { input1_->attribute( name, value ); }
    virtual void attribute( const std::string& name, unsigned short& value ) const { input1_->attribute( name, value ); }
    virtual void attribute( const std::string& name, unsigned int& value ) const { input1_->attribute( name, value ); }
    virtual void attribute( const std::string& name, unsigned long& value ) const { input1_->attribute( name, value ); }
    virtual void attribute( const std::string& name, unsigned long long& value ) const { input1_->attribute( name, value ); }

    virtual void nodes( const visitor& v ) const
    {
        input1_->nodes( v );
    }
    virtual void attributes( const visitor& v ) const
    {
        input1_->attributes( v );
    }
    //@}

private:
    //! @name Member data
    //@{
    std::auto_ptr< input_base > input1_;
    std::auto_ptr< input_base > input2_;
    input_context& context_;
    bool invert_;
    unsigned int level_;
    //@}
};

}

#endif // xeumeuleu_branch_input_h
