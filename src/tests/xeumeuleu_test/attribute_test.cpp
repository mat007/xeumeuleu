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
#define MOCK_NO_AUTO_PTR
#include <turtle/mock.hpp>

// -----------------------------------------------------------------------------
// Name: read_attribute_from_root_level_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_attribute_from_root_level_throws_an_exception )
{
    xml::xistringstream xis( "<element attribute='12'/>" );
    int value;
    BOOST_CHECK_THROW( xis >> xml::attribute( "attribute", value ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: read_unexisting_attribute_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_unexisting_attribute_throws_an_exception )
{
    xml::xistringstream xis( "<element attribute='the attribute value'/>" );
    std::string value;
    xis >> xml::start( "element" );
    BOOST_CHECK_THROW( xis >> xml::attribute( "unexisting_attribute", value ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: read_invalid_type_attribute_throws_an_exception
// Created: MCO MCO 2014-11-13
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_invalid_type_attribute_throws_an_exception )
{
    xml::xistringstream xis( "<element attribute='-1'/>" );
    unsigned int value;
    xis >> xml::start( "element" );
    BOOST_CHECK_THROW_WHAT( xis >> xml::attribute( "attribute", value ), "string_input (line 1, column 26) : value of 'attribute' is not a unsigned int" );
}

// -----------------------------------------------------------------------------
// Name: add_attribute_at_root_level_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( add_attribute_at_root_level_throws_an_exception )
{
    xml::xostringstream xos;
    BOOST_CHECK_THROW( xos << xml::attribute( "attribute", 12 ), xml::exception );
}

namespace
{
    template< typename T > std::string write( const T& value )
    {
        xml::xostringstream xos;
        xos << xml::start( "element" ) << xml::attribute( "attribute", value ) << xml::end;
        return xos.str();
    }
    std::string format( const std::string& value )
    {
        return "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
               "<element attribute=\"" + value + "\"/>\n";
    }
}

// -----------------------------------------------------------------------------
// Name: add_attribute_on_element_makes_a_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( add_attribute_on_element_makes_a_valid_document )
{
    BOOST_CHECK_EQUAL( format( "12" ), write< short >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< int >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< long >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< long long >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< float >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< double >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< long double >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< unsigned short >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< unsigned int >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< unsigned long >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< unsigned long long >( 12 ) );
    BOOST_CHECK_EQUAL( format( "  the attribute value  " ), write< std::string >( "  the attribute value  " ) );
}

namespace
{
    template< typename T > T read( const std::string& value )
    {
        xml::xistringstream xis( "<element attribute=\"" + value + "\"/>" );
        T result;
        xis >> xml::start( "element" ) >> xml::attribute( "attribute", result );
        return result;
    }
}

// -----------------------------------------------------------------------------
// Name: read_attribute_from_element_retrieves_value
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_attribute_from_element_retrieves_value )
{
    BOOST_CHECK_EQUAL( 12, read< short >( "12" ) );
    BOOST_CHECK_EQUAL( 12, read< int >( "12" ) );
    BOOST_CHECK_EQUAL( 12, read< long >( "12" ) );
    BOOST_CHECK_EQUAL( 12, read< long long >( "12" ) );
    BOOST_CHECK_EQUAL( 12.f, read< float >( "12" ) );
    BOOST_CHECK_EQUAL( 12, read< double >( "12" ) );
    BOOST_CHECK_EQUAL( 12, read< long double >( "12" ) );
    BOOST_CHECK_EQUAL( 12u, read< unsigned short >( "12" ) );
    BOOST_CHECK_EQUAL( 12u, read< unsigned int >( "12" ) );
    BOOST_CHECK_EQUAL( 12u, read< unsigned long >( "12" ) );
    BOOST_CHECK_EQUAL( 12u, read< unsigned long long >( "12" ) );
    BOOST_CHECK_EQUAL( "  the attribute value   ", read< std::string >( "  the attribute value   " ) );
}

// -----------------------------------------------------------------------------
// Name: read_attribute_directly_is_valid
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_attribute_directly_is_valid )
{
    xml::xistringstream xis( "<element attribute='the attribute value'/>" );
    xis >> xml::start( "element" );
    BOOST_CHECK_EQUAL( "the attribute value", xis.attribute< std::string >( "attribute" ) );
}

// -----------------------------------------------------------------------------
// Name: read_attribute_directly_with_default_value_is_valid
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_attribute_directly_with_default_value_is_valid )
{
    xml::xistringstream xis( "<element attribute='the attribute value'/>" );
    xis >> xml::start( "element" );
    const std::string value = "the default value";
    BOOST_CHECK_EQUAL( "the attribute value", xis.attribute( "attribute", value ) );
}

// -----------------------------------------------------------------------------
// Name: read_unexisting_attribute_directly_with_default_value_is_valid
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_unexisting_attribute_directly_with_default_value_is_valid )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" );
    const std::string value = "the default value";
    BOOST_CHECK_EQUAL( value, xis.attribute( "attribute", value ) );
}

// -----------------------------------------------------------------------------
// Name: read_empty_attribute_is_valid
// Created: MAT 2010-07-27
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_empty_attribute_is_valid )
{
    xml::xistringstream xis( "<element id=' '/>" );
    std::string id;
    xis >> xml::start( "element" )
            >> xml::attribute( "id", id );
    BOOST_CHECK_EQUAL( " ", id );
}

// -----------------------------------------------------------------------------
// Name: read_from_root_attribute_directly_with_default_value_is_valid
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_from_root_attribute_directly_with_default_value_is_valid )
{
    xml::xistringstream xis( "<element/>" );
    const std::string value = "the default value";
    BOOST_CHECK_EQUAL( value, xis.attribute( "attribute", value ) );
}

// -----------------------------------------------------------------------------
// Name: writing_the_same_attribute_twice_yields_the_second_value_overwriting_the_first
// Created: MCO 2008-14-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_the_same_attribute_twice_yields_the_second_value_overwriting_the_first )
{
    xml::xostringstream xos;
    xos << xml::start( "root" )
            << xml::attribute( "attribute", "the first value" )
            << xml::attribute( "attribute", "the second value" )
        << xml::end;
    const std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                                 "<root attribute=\"the second value\"/>\n";
    BOOST_CHECK_EQUAL( expected, xos.str() );
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
// Name: reading_attribute_can_be_specialized_for_user_types
// Created: MCO 2009-05-30
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_attribute_can_be_specialized_for_user_types )
{
    xml::xistringstream xis( "<root attribute=''/>" );
    user_type u;
    MOCK_EXPECT( read ).once().returns( boost::ref( xis ) );
    xis >> xml::start( "root" )
            >> xml::attribute( "attribute", u );
}

// -----------------------------------------------------------------------------
// Name: writing_attribute_can_be_specialized_for_user_types
// Created: MCO 2009-11-14
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_attribute_can_be_specialized_for_user_types )
{
    xml::xostringstream xos;
    user_type u;
    xos << xml::start( "root" )
            << xml::attribute( "attribute", u );
}

// -----------------------------------------------------------------------------
// Name: writing_attribute_can_be_specialized_for_const_user_types
// Created: MCO 2009-11-14
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_attribute_can_be_specialized_for_const_user_types )
{
    xml::xostringstream xos;
    xos << xml::start( "root" )
            << xml::attribute( "attribute", user_type() );
}

// -----------------------------------------------------------------------------
// Name: direct_reading_attribute_can_be_specialized_for_user_types
// Created: MCO 2009-11-25
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( direct_reading_attribute_can_be_specialized_for_user_types )
{
    xml::xistringstream xis( "<root attribute=''/>" );
    xis >> xml::start( "root" );
    MOCK_EXPECT( read ).once().returns( boost::ref( xis ) );
    xis.attribute< user_type >( "attribute" );
}

BOOST_AUTO_TEST_CASE( writing_attribute_value_equal_to_fallback_value_does_not_write_it )
{
    xml::xostringstream xos;
    xos << xml::start( "root" )
            << xml::attribute( "attribute", 42, 42 );
    const std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                                 "<root/>\n";
    BOOST_CHECK_EQUAL( expected, xos.str() );
}

BOOST_AUTO_TEST_CASE( writing_attribute_value_different_from_fallback_value_writes_it )
{
    xml::xostringstream xos;
    xos << xml::start( "root" )
            << xml::attribute( "attribute", 43, 42 );
    const std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                                 "<root attribute=\"43\"/>\n";
    BOOST_CHECK_EQUAL( expected, xos.str() );
}

namespace
{
    xml::xostream& operator<<( xml::xostream& xos, const user_type* )
    {
        return xos << 7;
    }
}

BOOST_AUTO_TEST_CASE( writing_attribute_pointer_equal_to_nullptr_fallback_value_does_not_write_it )
{
    xml::xostringstream xos;
    const user_type* t = 0;
    xos << xml::start( "root" )
            << xml::attribute( "attribute", t, nullptr );
    const std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                                 "<root/>\n";
    BOOST_CHECK_EQUAL( expected, xos.str() );
}

BOOST_AUTO_TEST_CASE( writing_attribute_pointer_different_from_nullptr_fallback_value_writes_it )
{
    xml::xostringstream xos;
    const user_type t;
    xos << xml::start( "root" )
            << xml::attribute( "attribute", &t, nullptr );
    const std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                                 "<root attribute=\"7\"/>\n";
    BOOST_CHECK_EQUAL( expected, xos.str() );
}
