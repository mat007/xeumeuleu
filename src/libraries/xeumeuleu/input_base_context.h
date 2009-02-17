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

#ifndef xeumeuleu_input_base_context_h
#define xeumeuleu_input_base_context_h

#include "input_base.h"
#include "input_context.h"
#include "null_input.h"

namespace xml
{
// =============================================================================
/** @class  input_base_context
    @brief  Input base context adapter implementation
*/
// Created: MAT 2008-04-25
// =============================================================================
class input_base_context : public input_base, public input_context
{
public:
    //! @name Constructors/Destructor
    //@{
    input_base_context()
        : input_( new null_input() )
    {}
    virtual ~input_base_context()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string& tag )
    {
        input_->start( tag );
    }
    virtual void end()
    {
        input_->end();
    }

    virtual void read( std::string& value ) const { input_->read( value ); }
    virtual void read( bool& value ) const { input_->read( value ); }
    virtual void read( short& value ) const { input_->read( value ); }
    virtual void read( int& value ) const { input_->read( value ); }
    virtual void read( long& value ) const { input_->read( value ); }
    virtual void read( long long& value ) const { input_->read( value ); }
    virtual void read( float& value ) const { input_->read( value ); }
    virtual void read( double& value ) const { input_->read( value ); }
    virtual void read( long double& value ) const { input_->read( value ); }
    virtual void read( unsigned int& value ) const { input_->read( value ); }
    virtual void read( unsigned short& value ) const { input_->read( value ); }
    virtual void read( unsigned long& value ) const { input_->read( value ); }
    virtual void read( unsigned long long& value ) const { input_->read( value ); }

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

    virtual input_base& reset( std::auto_ptr< input_base > input )
    {
        input_ = input;
        return *input_;
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

    virtual void attribute( const std::string& name, std::string& value ) const { input_->attribute( name, value ); }
    virtual void attribute( const std::string& name, bool& value ) const { input_->attribute( name, value ); }
    virtual void attribute( const std::string& name, short& value ) const { input_->attribute( name, value ); }
    virtual void attribute( const std::string& name, int& value ) const { input_->attribute( name, value ); }
    virtual void attribute( const std::string& name, long& value ) const { input_->attribute( name, value ); }
    virtual void attribute( const std::string& name, long long& value ) const { input_->attribute( name, value ); }
    virtual void attribute( const std::string& name, float& value ) const { input_->attribute( name, value ); }
    virtual void attribute( const std::string& name, double& value ) const { input_->attribute( name, value ); }
    virtual void attribute( const std::string& name, long double& value ) const { input_->attribute( name, value ); }
    virtual void attribute( const std::string& name, unsigned short& value ) const { input_->attribute( name, value ); }
    virtual void attribute( const std::string& name, unsigned int& value ) const { input_->attribute( name, value ); }
    virtual void attribute( const std::string& name, unsigned long& value ) const { input_->attribute( name, value ); }
    virtual void attribute( const std::string& name, unsigned long long& value ) const { input_->attribute( name, value ); }

    virtual void nodes( const visitor& v ) const
    {
        input_->nodes( v );
    }
    virtual void attributes( const visitor& v ) const
    {
        input_->attributes( v );
    }
    //@}

private:
    //! @name Member data
    //@{
    std::auto_ptr< input_base > input_;
    //@}
};

}

#endif // xeumeuleu_input_base_context_h
