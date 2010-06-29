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

#ifndef xeumeuleu_attribute_input_hpp
#define xeumeuleu_attribute_input_hpp

#include <xeumeuleu/streams/detail/input_base.hpp>

namespace xml
{
// =============================================================================
/** @class  attribute_input
    @brief  Attribute input implementation
*/
// Created: MAT 2009-11-25
// =============================================================================
class attribute_input : public input_base
{
public:
    //! @name Constructors/Destructor
    //@{
    attribute_input( input_base& input, const std::string& attribute )
        : input_    ( input )
        , attribute_( attribute )
    {}
    virtual ~attribute_input()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string& /*tag*/ )
    {
        throw xml::exception( context() + "Invalid 'start' while reading attribute" );
    }
    virtual void end()
    {
        throw xml::exception( context() + "Invalid 'end' while reading attribute" );
    }

    virtual data read() const
    {
        return input_.attribute( attribute_ );
    }
    virtual data attribute( const std::string& /*name*/ ) const
    {
        throw xml::exception( context() + "Invalid 'attribute' while reading attribute" );
    }

    virtual std::auto_ptr< input_base > branch( bool /*clone*/ ) const
    {
        throw xml::exception( context() + "Invalid 'branch' while reading attribute" );
    }

    virtual void copy( output& /*destination*/ ) const
    {
        throw xml::exception( context() + "Invalid 'copy' while reading attribute" );
    }
    //@}

    //! @name Accessors
    //@{
    virtual bool has_child( const std::string& /*name*/ ) const
    {
        return false;
    }
    virtual bool has_attribute( const std::string& /*name*/ ) const
    {
        return false;
    }
    virtual bool has_content() const
    {
        return true;
    }

    virtual void nodes( const visitor& /*v*/ ) const
    {
        throw xml::exception( context() + "Invalid 'nodes' while reading attribute" );
    }
    virtual void attributes( const visitor& /*v*/ ) const
    {
        throw xml::exception( context() + "Invalid 'attributes' while reading attribute" );
    }

    virtual std::string context() const
    {
        return input_.context();
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    attribute_input( const attribute_input& );            //!< Copy constructor
    attribute_input& operator=( const attribute_input& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    input_base& input_;
    const std::string& attribute_;
    //@}
};

}

#endif // xeumeuleu_attribute_input_hpp
