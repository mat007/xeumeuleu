/*
 *   Copyright (c) 2010, Mathieu Champlon
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

#include "xeumeuleu_test_pch.h"
#include <xeumeuleu/xml.hpp>
#define MOCK_NO_AUTO_PTR
#include <turtle/mock.hpp>

// -----------------------------------------------------------------------------
// Name: call_allows_to_call_a_read_functor
// Created: MCO 2010-11-26
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( call_allows_to_call_a_read_functor )
{
    MOCK_FUNCTOR( f, void( xml::xistream& ) );
    xml::xistringstream xis( "<element/>" );
    MOCK_EXPECT( f ).once();
    xis >> xml::call( f );
}

// -----------------------------------------------------------------------------
// Name: call_allows_to_call_a_write_functor
// Created: MCO 2010-11-26
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( call_allows_to_call_a_write_functor )
{
    MOCK_FUNCTOR( f, void( xml::xostream& ) );
    xml::xostringstream xos;
    MOCK_EXPECT( f ).once();
    xos << xml::call( f );
}

namespace
{
    template< typename F >
    void call( xml::xistream& xis, F& f )
    {
        xis >> xml::call( f );
    }
}

// -----------------------------------------------------------------------------
// Name: call_allows_to_call_a_functor_by_reference
// Created: MCO 2010-11-26
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( call_allows_to_call_a_functor_by_reference )
{
    MOCK_FUNCTOR( f, void( xml::xistream& ) );
    xml::xistringstream xis( "<element/>" );
    MOCK_EXPECT( f ).once();
    call( xis, f );
}
