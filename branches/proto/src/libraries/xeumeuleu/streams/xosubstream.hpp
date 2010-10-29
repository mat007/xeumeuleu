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

#ifndef xeumeuleu_xosubstream_hpp
#define xeumeuleu_xosubstream_hpp

#include <xeumeuleu/streams/xostream.hpp>
#include <xeumeuleu/streams/detail/xo_base_member.hpp>

namespace xml
{
// =============================================================================
/** @class  xosubstream
    @brief  Xml output sub-stream
    @par    Using example
    @code
    xml::xostream& xos = ...
    xos << ...
    xml::xosubstream xoss( xos );
    xoss << ...
    xos << ...
    @endcode
    @note the constructor is implicit on purpose.
    @warning the life of the sub-stream must not exceed the life of the underlying wrapped stream.
*/
// Created: MAT 2006-03-18
// =============================================================================
class xosubstream : private xo_base_member, public xostream
{
public:
    //! @name Constructors/Destructor
    //@{
    xosubstream( const xostream& xos )
        : xo_base_member( xos.branch() )
        , xostream( *xo_base_member::output_ )
    {}
    xosubstream( const xosubstream& xoss )
        : xo_base_member( xoss.branch() )
        , xostream( *xo_base_member::output_ )
    {}
    virtual ~xosubstream()
    {}
    //@}

    //! @name Operators
    //@{
    operator xostream&() const
    {
        return const_cast< xosubstream& >( *this );
    }
    //@}
};

}

#endif // xeumeuleu_xosubstream_hpp
