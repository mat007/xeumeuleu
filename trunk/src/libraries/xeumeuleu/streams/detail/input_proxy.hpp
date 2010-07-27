/*
 *   Copyright (c) 2009, Mathieu Champlon
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

#ifndef xeumeuleu_input_proxy_hpp
#define xeumeuleu_input_proxy_hpp

#include <xeumeuleu/streams/detail/input_base.hpp>
#include <xeumeuleu/streams/detail/input_context.hpp>

namespace xml
{
// =============================================================================
/** @class  input_proxy
    @brief  Input proxy to factorize default behaviour
*/
// Created: MAT 2009-02-18
// =============================================================================
class input_proxy : public input_base, protected input_context
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit input_proxy( input_base& input )
        : input_( &input )
    {}
    virtual ~input_proxy()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string* ns, const std::string& tag )
    {
        input_->start( ns, tag );
    }
    virtual void end()
    {
        input_->end();
    }

    virtual data read() const
    {
        return input_->read();
    }

    virtual std::auto_ptr< input_base > attribute( const std::string* ns, const std::string& name ) const
    {
        return input_->attribute( ns, name );
    }

    virtual std::auto_ptr< input_base > branch( bool clone ) const
    {
        return input_->branch( clone );
    }

    virtual void copy( output& destination ) const
    {
        input_->copy( destination );
    }

    virtual input_base& reset( input_base& input )
    {
        input_ = &input;
        return *input_;
    }
    //@}

    //! @name Accessors
    //@{
    virtual bool has_child( const std::string* ns, const std::string& name ) const
    {
        return input_->has_child( ns, name );
    }
    virtual bool has_attribute( const std::string* ns, const std::string& name ) const
    {
        return input_->has_attribute( ns, name );
    }
    virtual bool has_content() const
    {
        return input_->has_content();
    }
    virtual bool has_prefix( const std::string& ns ) const
    {
        return input_->has_prefix( ns );
    }

    virtual void nodes( const std::string* ns, const visitor& v ) const
    {
        input_->nodes( ns, v );
    }
    virtual void attributes( const std::string* ns, const visitor& v ) const
    {
        input_->attributes( ns, v );
    }

    virtual void prefix( const std::string& ns, std::string& prefix ) const
    {
        input_->prefix( ns, prefix );
    }

    virtual std::string context() const
    {
        return input_->context();
    }
    //@}

private:
    //! @name Member data
    //@{
    input_base* input_;
    //@}
};

}

#endif // xeumeuleu_input_proxy_hpp
