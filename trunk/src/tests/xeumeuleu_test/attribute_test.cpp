// *****************************************************************************
//
// This file is part of a MASA library or program.
// Refer to the included end-user license agreement for restrictions.
//
// Copyright (c) 2005 Mathématiques Appliquées SA (MASA)
//
// *****************************************************************************

#include "xeumeuleu_test_pch.h"
#include "xeumeuleu/xml.h"

using namespace mockpp;

namespace
{
    void warning_check()
    {
        xml::xistream& xis = *(xml::xistream*)0;
        std::string value;
        xis >> xml::attribute( "attribute", value );
    }

    template< typename T > T read( const std::string& value )
    {
        xml::xistringstream xis( "<element attribute=\"" + value + "\"/>" );
        T result;
        xis >> xml::start( "element" ) >> xml::attribute( "attribute", result );
        return result;
    }
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
// Name: read_attribute_from_root_level_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( read_attribute_from_root_level_throws_an_exception )
{
    xml::xistringstream xis( "<element attribute=\"12\"/>" );
    int value;
    BOOST_CHECK_THROW( xis >> xml::attribute( "attribute", value ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: read_unexisting_attribute_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( read_unexisting_attribute_throws_an_exception )
{
    xml::xistringstream xis( "<element attribute=\"the attribute value\"/>" );
    std::string value;
    xis >> xml::start( "element" );
    BOOST_CHECK_THROW( xis >> xml::attribute( "unexisting_attribute", value ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: read_attribute_from_element_retrieves_value
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( read_attribute_from_element_retrieves_value )
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
// Name: add_attribute_at_root_level_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( add_attribute_at_root_level_throws_an_exception )
{
    xml::xostringstream xos;
    BOOST_CHECK_THROW( xos << xml::attribute( "attribute", 12 ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: add_attribute_on_element_makes_a_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( add_attribute_on_element_makes_a_valid_document )
{
    BOOST_CHECK_EQUAL( format( "12" ), write< short >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< int >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< long >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< unsigned short >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< unsigned int >( 12 ) );
    BOOST_CHECK_EQUAL( format( "12" ), write< unsigned long >( 12 ) );
    BOOST_CHECK_EQUAL( format( "  the attribute value  " ), write< std::string >( "  the attribute value  " ) );
}
