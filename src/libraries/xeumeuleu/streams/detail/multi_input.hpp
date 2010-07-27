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

#ifndef xeumeuleu_multi_input_hpp
#define xeumeuleu_multi_input_hpp

#include <xeumeuleu/streams/detail/input_base.hpp>
#include <xeumeuleu/streams/detail/input_context.hpp>
#include <xeumeuleu/streams/detail/branch_input.hpp>
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
    virtual void start( const std::string* ns, const std::string& tag )
    {
        if( input1_->has_child( ns, tag ) && ! input2_->has_child( ns, tag ) )
            context_.reset( branch1_ ).start( ns, tag );
        else if( input2_->has_child( ns, tag ) && ! input1_->has_child( ns, tag ) )
            context_.reset( branch2_ ).start( ns, tag );
        else
        {
            input1_->start( ns, tag );
            input2_->start( ns, tag );
        }
    }
    virtual void end()
    {
        input1_->end();
        input2_->end();
    }

    virtual data read() const
    {
        if( input1_->has_content() )
            return input1_->read();
        return input2_->read();
    }

    virtual std::auto_ptr< input_base > attribute( const std::string* ns, const std::string& name ) const
    {
        if( input1_->has_attribute( ns, name ) )
            return input1_->attribute( ns, name );
        return input2_->attribute( ns, name );
    }

    virtual std::auto_ptr< input_base > branch( bool clone ) const;

    virtual void copy( output& destination ) const
    {
        input1_->copy( destination );
        input2_->copy( destination );
    }
    //@}

    //! @name Accessors
    //@{
    virtual bool has_child( const std::string* ns, const std::string& name ) const
    {
        return input1_->has_child( ns, name ) || input2_->has_child( ns, name );
    }
    virtual bool has_attribute( const std::string* ns, const std::string& name ) const
    {
        return input1_->has_attribute( ns, name ) || input2_->has_attribute( ns, name );
    }
    virtual bool has_content() const
    {
        return input1_->has_content() || input2_->has_content();
    }
    virtual bool has_prefix( const std::string& ns ) const
    {
        return input1_->has_prefix( ns ) || input2_->has_prefix( ns );
    }

    virtual void nodes( const std::string* ns, const visitor& v ) const
    {
        input1_->nodes( ns, v );
        input2_->nodes( ns, v );
    }
    virtual void attributes( const std::string* ns, const visitor& v ) const
    {
        input1_->attributes( ns, v );
        input2_->attributes( ns, v );
    }

    virtual void prefix( const std::string& ns, std::string& prefix ) const
    {
        if( input1_->has_prefix( ns ) )
            input1_->prefix( ns, prefix );
        else
            input2_->prefix( ns, prefix );
    }

    virtual std::string context() const
    {
        return input1_->context() + input2_->context();
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

#include <xeumeuleu/streams/detail/input_base_context.hpp>

namespace xml
{
    inline std::auto_ptr< input_base > multi_input::branch( bool clone ) const
    {
        return std::auto_ptr< input_base >( new input_base_context( input1_->branch( clone ), input2_->branch( clone ) ) );
    }
}

#endif // xeumeuleu_multi_input_hpp
