/*
 *   Copyright (c) 2008, Mathieu Champlon
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

#ifndef xeumeuleu_hppelpers_hpp
#define xeumeuleu_hppelpers_hpp

#include <xeumeuleu/streams/xisubstream.hpp>
#include <xeumeuleu/manipulators/optional.hpp>
#include <xeumeuleu/manipulators/attribute.hpp>

namespace xml
{
#ifndef XEUMEULEU_NO_DEPRECATED
// -----------------------------------------------------------------------------
// Name: value
// Created: MAT 2008-01-19
// -----------------------------------------------------------------------------
template< typename T >
T value( xisubstream xis ) //<! Deprecated !
{
    T value;
    xis >> value;
    return value;
}

// -----------------------------------------------------------------------------
// Name: value
// Created: MAT 2008-01-19
// -----------------------------------------------------------------------------
template< typename T >
T value( xisubstream xis, const T& fallback ) //<! Deprecated !
{
    T value = fallback;
    xis >> optional >> value;
    return value;
}

// -----------------------------------------------------------------------------
// Name: attribute
// Created: MAT 2007-07-11
// -----------------------------------------------------------------------------
template< typename T >
T attribute( xisubstream xis, const std::string& name ) //<! Deprecated !
{
    T value;
    xis >> attribute( name, value );
    return value;
}

// -----------------------------------------------------------------------------
// Name: attribute
// Created: MAT 2007-07-11
// -----------------------------------------------------------------------------
template< typename T >
T attribute( xisubstream xis, const std::string& name, const T& fallback ) //<! Deprecated !
{
    T value = fallback;
    xis >> optional >> attribute( name, value );
    return value;
}

// -----------------------------------------------------------------------------
// Name: content
// Created: MAT 2007-07-11
// -----------------------------------------------------------------------------
template< typename T >
T content( xisubstream xis, const std::string& tag ) //<! Deprecated !
{
    T value;
    xis >> start( tag ) >> value;
    return value;
}

// -----------------------------------------------------------------------------
// Name: content
// Created: MAT 2007-07-11
// -----------------------------------------------------------------------------
template< typename T >
T content( xisubstream xis, const std::string& tag, const T& fallback ) //<! Deprecated !
{
    T value = fallback;
    xis >> optional >> start( tag ) >> optional >> value;
    return value;
}
#endif // XEUMEULEU_NO_DEPRECATED
}

#endif // xeumeuleu_hppelpers_hpp
