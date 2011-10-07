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

#ifndef xeumeuleu_null_input_hpp
#define xeumeuleu_null_input_hpp

#include <xeumeuleu/streams/exception.hpp>
#include <xeumeuleu/streams/detail/input_base.hpp>
#include <xeumeuleu/streams/detail/input_context.hpp>
#include <xeumeuleu/bridges/xerces/data.hpp>

namespace xml
{
// =============================================================================
/** @class  null_input
    @brief  Null input implementation
*/
// Created: MAT 2006-01-08
// =============================================================================
class null_input : public input_base
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit null_input( const input_base& input )
        : context_( input.context() )
        , level_( 0 )
    {}
    null_input( const null_input& input )
        : input_base()
        , context_( input.context() )
        , level_( 0 )
    {}
    virtual ~null_input()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string* /*ns*/, const std::string& /*tag*/ )
    {
        ++level_;
    }
    virtual void end()
    {
        if( --level_ < 0 )
            throw exception( "Invalid 'end' at root level" );
    }

    virtual data read() const
    {
        return data();
    }

    virtual std::auto_ptr< input_base > attribute( const std::string* /*ns*/, const std::string& /*name*/ ) const
    {
        return std::auto_ptr< input_base >();
    }

    virtual std::auto_ptr< input_base > branch( bool /*clone*/ ) const
    {
        return std::auto_ptr< input_base >( new null_input( *this ) );
    }

    virtual void copy( output& /*destination*/ ) const
    {}
    //@}

    //! @name Accessors
    //@{
    virtual bool has_child( const std::string* /*ns*/, const std::string& /*name*/ ) const
    {
        return false;
    }
    virtual bool has_attribute( const std::string* /*ns*/, const std::string& /*name*/ ) const
    {
        return false;
    }
    virtual bool has_content() const
    {
        return false;
    }
    virtual bool has_prefix( const std::string& /*ns*/ ) const
    {
        return false;
    }

    virtual void nodes( const std::string* /*ns*/, const visitor& /*v*/ ) const
    {}
    virtual void attributes( const std::string* /*ns*/, const visitor& /*v*/ ) const
    {}

    virtual void prefix( const std::string& /*ns*/, std::string& /*prefix*/ ) const
    {}

    virtual std::string context() const
    {
        return context_;
    }
    //@}

private:
    //! @name Member data
    //@{
    const std::string context_;
    int level_;
    //@}
};

}

#endif // xeumeuleu_null_input_hpp
