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

namespace
{
    template< typename T >
    struct value_or_percentage_manipulator
    {
        value_or_percentage_manipulator( T& value, const T& maximum )
            : value_  ( &value )
            , maximum_( maximum )
        {}
        T* value_;
        T maximum_;
    };

    template< typename T >
    xml::xistream& operator>>( xml::xistream& xis, const value_or_percentage_manipulator< T >& m )
    {
        const std::string s = xis.value< std::string >();
        std::stringstream ss( s );
        ss >> *m.value_;
        if( ! s.empty() && *s.rbegin() == '%' )
            *m.value_ = *m.value_ * m.maximum_ / T( 100 );
        return xis;
    }

    template< typename T >
    value_or_percentage_manipulator< T > value_or_percentage( T& value, const T& maximum )
    {
        return value_or_percentage_manipulator< T >( value, maximum );
    }
}

BOOST_AUTO_TEST_CASE( value_or_percentage_with_percent_sign_computes_percentage )
{
    xml::xistringstream xis( "<element attribute='42%'/>" );
    int result = 0;
    xis >> xml::start( "element" )
            >> xml::attribute( "attribute", value_or_percentage( result, 72 ) );
    BOOST_CHECK_EQUAL( 30, result );
}

BOOST_AUTO_TEST_CASE( value_or_percentage_without_percent_sign_retrieves_value )
{
    xml::xistringstream xis( "<element attribute='42'/>" );
    int result = 0;
    xis >> xml::start( "element" )
            >> xml::attribute( "attribute", value_or_percentage( result, 72 ) );
    BOOST_CHECK_EQUAL( 42, result );
}
