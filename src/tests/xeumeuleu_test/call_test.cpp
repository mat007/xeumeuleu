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

namespace
{
    MOCK_CLASS( mock_element )
    {
        MOCK_CONST_METHOD( write, 1, void( xml::xostream& ) )
    };
}

namespace xml
{
    template < typename M1, typename M2 >
    struct sequence_manipulator
    {
        sequence_manipulator( const M1& m1, const M2& m2 )
            : m1_( m1 )
            , m2_( m2 )
        {}

        friend xistream& operator>>( xistream& xis, const sequence_manipulator& m )
        {
            xml::xisubstream xiss( xis );
            xiss >> m.m1_;
            xiss >> m.m2_;
            return xis;
        }
        friend xostream& operator<<( xostream& xos, const sequence_manipulator& m )
        {
            xml::xosubstream xoss( xos );
            xoss << m.m1_;
            xoss << m.m2_;
            return xos;
        }

    private:
        sequence_manipulator& operator=( const sequence_manipulator& );

    private:
        M1 m1_;
        M2 m2_;
    };

    template < typename I, typename T >
    sequence_manipulator<
        start_manipulator,
        call_manipulator< const_caller0< xostream, T > > >
    call( const std::string& name, I& instance, void ( T::*method )( xostream& ) const )
    {
        return sequence_manipulator<
            start_manipulator,
            call_manipulator< const_caller0< xostream, T > > >(
                xml::start( name ),
                call_manipulator< const_caller0< xostream, T > >(
                    const_caller0< xostream, T >( instance, method ) ) );
    }
}

// -----------------------------------------------------------------------------
// Name: call_allows_to_call_member_function
// Created: MCO 2016-11-21
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( call_allows_to_call_member_function )
{
    xml::xostringstream xos;
    mock_element e;
    MOCK_EXPECT( e.write ).once();
    xos << xml::call( "element", e, &mock_element::write );
}
