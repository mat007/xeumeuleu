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

#ifndef xeumeuleu_xisubstream_hpp
#define xeumeuleu_xisubstream_hpp

#include <xeumeuleu/streams/xistream.hpp>
#include <xeumeuleu/streams/detail/xi_base_member.hpp>

namespace xml
{
// =============================================================================
/** @class  xisubstream
    @brief  Xml input sub-stream
    @par    Using example
    @code
    xml::xistream& xis = ...
    xis >> ...
    xml::xisubstream xiss( xis );
    xiss >> ...
    xis >> ...
    @endcode
    @note the constructor is implicit on purpose.
    @warning the lifetime of the sub-stream must not exceed the lifetime of the underlying wrapped stream.
*/
// Created: MAT 2006-03-18
// =============================================================================
class xisubstream : private xi_base_member, public xistream
{
public:
    //! @name Constructors/Destructor
    //@{
    xisubstream( const xistream& xis )
        : xi_base_member( xis.branch( false ) )
        , xistream( *xi_base_member::input_ )
    {
        if( xis.is_optional() )
            optional();
    }
    xisubstream( const xisubstream& xiss )
        : xi_base_member( xiss.branch( false ) )
        , xistream( *xi_base_member::input_ )
    {
        if( xiss.is_optional() )
            optional();
    }
    virtual ~xisubstream()
    {}
    //@}

    //! @name Operators
    //@{
    operator xistream&() const
    {
        return const_cast< xisubstream& >( *this );
    }
    //@}
};

}

#endif // xeumeuleu_xisubstream_hpp
