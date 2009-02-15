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

#ifndef xeumeuleu_input_h
#define xeumeuleu_input_h

#include "input_context.h"
#include "input_base.h"
#include "optional_input.h"
#include "multi_input.h"
#include <string>
#include <memory>

namespace xml
{
// =============================================================================
/** @class  input
    @brief  Input
*/
// Created: MAT 2006-01-04
// =============================================================================
class input : private input_context
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit input( std::auto_ptr< input_base > input )
        : input_( input )
    {}
    virtual ~input()
    {}
    //@}

    //! @name Operations
    //@{
    void start( const std::string& tag )
    {
        input_->start( tag );
    }
    void end()
    {
        input_->end();
    }

    template< typename T > void read( T& value ) const
    {
        input_->read( value );
    }

    std::auto_ptr< input > branch( bool clone ) const
    {
        return std::auto_ptr< input >( new input( input_->branch( clone ) ) );
    }

    void copy( output& destination ) const
    {
        input_->copy( destination );
    }

    void error( const std::string& message ) const
    {
        input_->error( message );
    }
    //@}

    //! @name Accessors
    //@{
    bool has_child( const std::string& name ) const
    {
        return input_->has_child( name );
    }
    bool has_attribute( const std::string& name ) const
    {
        return input_->has_attribute( name );
    }
    bool has_content() const
    {
        return input_->has_content();
    }

    template< typename T > void attribute( const std::string& name, T& value ) const
    {
        input_->attribute( name, value );
    }

    void nodes( const visitor& v ) const
    {
        input_->nodes( v );
    }
    void attributes( const visitor& v ) const
    {
        input_->attributes( v );
    }
    //@}

    //! @name Modifiers
    //@{
    void optional()
    {
        input_.reset( new optional_input( input_, *this ) );
    }

    void attach( std::auto_ptr< input > input )
    {
        input_.reset( new multi_input( input_, input->input_, *this ) );
    }
    //@}

private:
    //! @name Operations
    //@{
    virtual input_base& reset( std::auto_ptr< input_base > input )
    {
        input_ = input;
        return *input_;
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    input( const input& );            //!< Copy constructor
    input& operator=( const input& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    std::auto_ptr< input_base > input_;
    //@}
};

}

#endif // xeumeuleu_input_h
