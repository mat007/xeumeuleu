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

#include "xeumeuleu_test_pch.h"
#include <xeumeuleu/xml.hpp>
#include <turtle/mock.hpp>

namespace
{
    template< typename T > std::string write( const T& value )
    {
        xml::xostringstream xos;
        xos << xml::content( "element", value );
        return xos.str();
    }
    std::string format( const std::string& value )
    {
        return "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
               "<element>" + value + "</element>\n";
    }
}

// -----------------------------------------------------------------------------
// Name: reading_empty_content_throws_proper_exception
// Created: MCO 2007-09-09
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_empty_content_throws_proper_exception )
{
    xml::xistringstream xis( "<element/>" );
    std::string value;
    BOOST_CHECK_THROW_WHAT( xis >> xml::content( "element", value ), "string_input (line 1, column 11) : 'element' does not have a content" );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_writes_text_content_as_it_is
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_content_writes_text_content_as_it_is )
{
    BOOST_CHECK_EQUAL( format( " this is the content  " ), write< const char* >( " this is the content  " ) );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_in_two_parts_concatenates_content
// Created: MCO 2009-11-26
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_content_in_two_parts_concatenates_content )
{
    xml::xostringstream xos;
    xos << xml::start( "element" )
            << "the value "
            << 12;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>the value 12</element>\n", xos.str() );
}

namespace
{
    template< typename T > T read( const std::string& value )
    {
        T result;
        xml::xistringstream xis( "<element> " + value + " </element>" );
        xis >> xml::content( "element", result );
        return result;
    }
    template< typename T > void check_round_trip( T in )
    {
        xml::xobufferstream xos;
        xos << xml::content( "root", in );
        T out;
        xos >> xml::content( "root", out );
        BOOST_CHECK_EQUAL( in, out );
    }
    template< typename T > void check_round_trip_numeric_limits()
    {
        check_round_trip( std::numeric_limits< T >::max() );
        check_round_trip( std::numeric_limits< T >::min() );
    }
    template< typename T > void check_read_special_values()
    {
        BOOST_CHECK_EQUAL( std::numeric_limits< T >::infinity(), read< T >( "INF" ) );
        BOOST_CHECK_EQUAL( -std::numeric_limits< T >::infinity(), read< T >( "-INF" ) );
        {
            const T NaN = read< T >( "NaN" );
            BOOST_CHECK( NaN != NaN );
        }
    }
    template< typename T > void check_round_trip_nan( T t )
    {
        xml::xobufferstream xos;
        xos << xml::content( "root", t );
        T nan;
        xos >> xml::content( "root", nan );
        BOOST_CHECK_NE( nan, nan );
    }
    template< typename T > void check_round_trip_special_values()
    {
        check_round_trip( std::numeric_limits< T >::infinity() );
        check_round_trip( -std::numeric_limits< T >::infinity() );
        check_round_trip_nan( std::numeric_limits< T >::quiet_NaN() );
        check_round_trip_nan( std::numeric_limits< T >::signaling_NaN() );
    }
}

// -----------------------------------------------------------------------------
// Name: streaming_content_writes_node_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_content_round_trips_node_content )
{
    check_round_trip_numeric_limits< short >();
    check_round_trip_numeric_limits< int >();
    check_round_trip_numeric_limits< long >();
    //check_round_trip_numeric_limits< long long >();
    check_round_trip_numeric_limits< float >();
    check_round_trip_numeric_limits< double >();
    check_round_trip_numeric_limits< long double >();
    check_round_trip_numeric_limits< unsigned short >();
    check_round_trip_numeric_limits< unsigned int >();
    check_round_trip_numeric_limits< unsigned long >();
    //check_round_trip_numeric_limits< unsigned long long >();
    check_read_special_values< float >();
    check_read_special_values< double >();
    //check_read_special_values< long double >();
}

namespace
{
    template< typename T >
    void check_special_values()
    {
        BOOST_CHECK_EQUAL( format( "INF" ), write< T >( std::numeric_limits< T >::infinity() ) );
        BOOST_CHECK_EQUAL( format( "-INF" ), write< T >( -std::numeric_limits< T >::infinity() ) );
        BOOST_CHECK_EQUAL( format( "NaN" ), write< T >( std::numeric_limits< T >::quiet_NaN() ) );
        BOOST_CHECK_EQUAL( format( "NaN" ), write< T >( std::numeric_limits< T >::signaling_NaN() ) );
    }
}

BOOST_AUTO_TEST_CASE( streaming_content_writes_node_special_value_content )
{
    check_special_values< float >();
    check_special_values< double >();
    check_special_values< long double >();
}

// -----------------------------------------------------------------------------
// Name: data_conversion_failure_provides_error_context
// Created: MAT 2012-01-27
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( data_conversion_failure_provides_error_context )
{
    short value;
    xml::xistringstream xis( "<element>300000</element>" );
    BOOST_CHECK_THROW_WHAT( xis >> xml::content( "element", value ), "string_input (line 1, column 10) : value of 'element' is not a short" );
}

// -----------------------------------------------------------------------------
// Name: streaming_stack_content_writes_node_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_stack_content_writes_node_content )
{
    BOOST_CHECK_EQUAL( format( "7" ), write< int >( 7 ) );
    BOOST_CHECK_EQUAL( format( "17.23" ), write< double >( 17.23 ) );
    BOOST_CHECK_EQUAL( format( "1.23" ), write< float >( 1.23f ) );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_reads_node_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_content_reads_node_content )
{
    BOOST_CHECK_EQUAL( " this is the value ", read< std::string >( "this is the value" ) );
    BOOST_CHECK_EQUAL( 1.23f, read< float >( "1.23" ) );
    BOOST_CHECK_EQUAL( 17.23f, read< float >( "17.23" ) );
    BOOST_CHECK_EQUAL( 1e+99, read< double >( "1e+99" ) );
    BOOST_CHECK_EQUAL( 17.23, read< double >( "17.23" ) );
    BOOST_CHECK_EQUAL( 12, read< int >( "12" ) );
    BOOST_CHECK_EQUAL( 32767, read< short >( "32767" ) );
    BOOST_CHECK_EQUAL( true, read< bool >( "true" ) );
    BOOST_CHECK_EQUAL( 5, read< long >( "5" ) );
    BOOST_CHECK_EQUAL( -777, read< long long >( "-777" ) );
    BOOST_CHECK_EQUAL( 4294967295u, read< unsigned int >( "4294967295" ) );
    BOOST_CHECK_EQUAL( 65535u, read< unsigned short >( "65535" ) );
    BOOST_CHECK_EQUAL( 4294967295u, read< unsigned long >( "4294967295" ) );
    BOOST_CHECK_EQUAL( 4294967295u, read< unsigned long long >( "4294967295" ) );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_with_invalid_format_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_content_with_invalid_format_throws_an_exception )
{
    BOOST_CHECK_THROW( read< int >( "12.3" ), xml::exception );
    BOOST_CHECK_THROW( read< unsigned int >( "12.3" ), xml::exception );
    BOOST_CHECK_THROW( read< unsigned int >( "-42" ), xml::exception );
    BOOST_CHECK_THROW( read< float >( "invalid number" ), xml::exception );
}

BOOST_AUTO_TEST_CASE( streaming_content_with_overflow_throws_an_exception )
{
    BOOST_CHECK_THROW( read< short >( "300000" ), xml::exception );
    BOOST_CHECK_THROW( read< float >( "1e+99" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: read_content_directly_is_valid
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_content_directly_is_valid )
{
    xml::xistringstream xis( "<element>the content value</element>" );
    BOOST_CHECK_EQUAL( "the content value", xis.content< std::string >( "element" ) );
}

// -----------------------------------------------------------------------------
// Name: read_content_directly_with_default_value_is_valid
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_content_directly_with_default_value_is_valid )
{
    xml::xistringstream xis( "<element>the content value</element>" );
    const std::string value = "the default value";
    BOOST_CHECK_EQUAL( "the content value", xis.content( "element", value ) );
}

// -----------------------------------------------------------------------------
// Name: read_unexisting_content_directly_with_default_value_is_valid
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_unexisting_content_directly_with_default_value_is_valid )
{
    xml::xistringstream xis( "<element/>" );
    const std::string value = "the default value";
    BOOST_CHECK_EQUAL( value, xis.content( "element", value ) );
}

namespace
{
    class user_type
    {};

    MOCK_FUNCTION( operator>>, 2, xml::xistream&( xml::xistream&, user_type& ), read );

    xml::xostream& operator<<( xml::xostream& xos, const user_type& )
    {
        return xos;
    }
}

// -----------------------------------------------------------------------------
// Name: reading_content_can_be_specialized_for_user_types
// Created: MCO 2009-05-30
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_content_can_be_specialized_for_user_types )
{
    xml::xistringstream xis( "<root/>" );
    user_type u;
    MOCK_EXPECT( read ).once().returns( boost::ref( xis ) );
    xis >> xml::content( "root", u );
}

// -----------------------------------------------------------------------------
// Name: writing_content_can_be_specialized_for_user_types
// Created: MCO 2009-11-26
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_content_can_be_specialized_for_user_types )
{
    xml::xostringstream xos;
    user_type u;
    xos << xml::content( "root", u );
}

// -----------------------------------------------------------------------------
// Name: writing_content_can_be_specialized_for_const_user_types
// Created: MCO 2009-11-26
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_content_can_be_specialized_for_const_user_types )
{
    xml::xostringstream xos;
    xos << xml::content( "root", user_type() );
}

// -----------------------------------------------------------------------------
// Name: direct_reading_content_can_be_specialized_for_user_types
// Created: MCO 2009-05-30
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( direct_reading_content_can_be_specialized_for_user_types )
{
    xml::xistringstream xis( "<root/>" );
    MOCK_EXPECT( read ).once().returns( boost::ref( xis ) );
    xis.content< user_type >( "root" );
}
