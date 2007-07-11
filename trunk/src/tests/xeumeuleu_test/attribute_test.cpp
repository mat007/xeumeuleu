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
#include "xeumeuleu/xml.h"

using namespace mockpp;

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
        xos << xml::start( "element" ) << xml::attribute( "attribute", value ) << xml::end();
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
    BOOST_CHECK_EQUAL( format( "12" ), write< unsigned short >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< unsigned int >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< unsigned long >( 12 ) );
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
    BOOST_CHECK_EQUAL( 12u, read< unsigned short >( "12" ) );
    BOOST_CHECK_EQUAL( 12u, read< unsigned int >( "12" ) );
    BOOST_CHECK_EQUAL( 12u, read< unsigned long >( "12" ) );
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
    BOOST_CHECK_EQUAL( "the attribute value", xml::attribute< std::string >( xis, "attribute" ) );
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
    BOOST_CHECK_EQUAL( "the attribute value", xml::attribute( xis, "attribute", value ) );
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
    BOOST_CHECK_EQUAL( value, xml::attribute( xis, "attribute", value ) );
}
