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

#ifndef xeumeuleu_optional_input_hpp
#define xeumeuleu_optional_input_hpp

#include <xeumeuleu/streams/exception.hpp>
#include <xeumeuleu/streams/detail/input_proxy.hpp>
#include <xeumeuleu/streams/detail/input_context.hpp>

namespace xml
{
// =============================================================================
/** @class  optional_input
    @brief  Input state to handle optional manipulation
*/
// Created: MAT 2006-03-20
// =============================================================================
class optional_input : public input_proxy
{
public:
    //! @name Constructors/Destructor
    //@{
    optional_input( input_base& input1, input_base& input2, input_context& context )
        : input_proxy( input1 )
        , input1_ ( input1 )
        , input2_ ( input2 )
        , context_( context )
    {}
    virtual ~optional_input()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string* ns, const std::string& tag )
    {
        if( input1_.has_child( ns, tag ) )
            context_.reset( input1_ ).start( ns, tag );
        else
            context_.reset( input2_ ).start( ns, tag );
    }
    virtual void end()
    {
        context_.reset( input1_ ).end();
    }

    virtual data read() const
    {
        if( input1_.has_content() )
            return context_.reset( input1_ ).read();
        return context_.reset( input2_ ).read();
    }

    virtual std::auto_ptr< input_base > attribute( const std::string* ns, const std::string& name ) const
    {
        if( input1_.has_attribute( ns, name ) )
            return context_.reset( input1_ ).attribute( ns, name );
        return context_.reset( input2_ ).attribute( ns, name );
    }
    //@}

    //! @name Accessors
    //@{
    virtual void nodes( const std::string* ns, const visitor& v ) const
    {
        context_.reset( input1_ ).nodes( ns, v );
    }
    virtual void attributes( const std::string* ns, const visitor& v ) const
    {
        context_.reset( input1_ ).attributes( ns, v );
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    optional_input( const optional_input& );            //!< Copy constructor
    optional_input& operator=( const optional_input& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    input_base& input1_;
    input_base& input2_;
    input_context& context_;
    //@}
};

}

#endif // xeumeuleu_optional_input_hpp
