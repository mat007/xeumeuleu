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

#ifndef xeumeuleu_ximultistream_hpp
#define xeumeuleu_ximultistream_hpp

#include <xeumeuleu/streams/xistream.hpp>
#include <xeumeuleu/streams/detail/multi_input.hpp>

#ifdef _MSC_VER
#   pragma warning( push )
#   pragma warning( disable: 4355 )
#endif

namespace xml
{
// =============================================================================
/** @class  ximultistream
    @brief  Xml input multi-stream
    @par    Using example
    @code
    xml::xistream& xis1 = ...
    xml::xistream& xis2 = ...
    xml::ximultistream xims( xis1, xis2 );
    xims >> ...
    @endcode
    @warning the life of the multi-stream must not exceed the life of the underlying wrapped stream.
*/
// Created: MAT 2008-01-07
// =============================================================================
class ximultistream : public xistream
{
public:
    //! @name Constructors/Destructor
    //@{
    ximultistream( const xistream& xis1, const xistream& xis2 )
        : xistream( input_ )
        , input_( xis1.branch( false ), xis2.branch( false ), *this )
    {}
    virtual ~ximultistream()
    {}
    //@}

private:
    //! @name Member data
    //@{
    multi_input input_;
    //@}
};

}

#ifdef _MSC_VER
#   pragma warning( pop )
#endif

#endif // xeumeuleu_ximultistream_hpp
