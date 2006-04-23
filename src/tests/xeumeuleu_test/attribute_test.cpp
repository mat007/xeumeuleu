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
// Name: read_integer_attribute_from_element_retrieves_value
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( read_integer_attribute_from_element_retrieves_value )
{
    xml::xistringstream xis( "<element attribute=\"12\"/>" );
    int value;
    xis >> xml::start( "element" ) >> xml::attribute( "attribute", value ) >> xml::end();
    BOOST_CHECK_EQUAL( 12, value );
}

// -----------------------------------------------------------------------------
// Name: read_string_attribute_from_element_retrieves_value
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( read_string_attribute_from_element_retrieves_value )
{
    xml::xistringstream xis( "<element attribute=\"the attribute value\"/>" );
    std::string value;
    xis >> xml::start( "element" ) >> xml::attribute( "attribute", value ) >> xml::end();
    BOOST_CHECK_EQUAL( "the attribute value", value );
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
// Name: add_attribute_at_root_level_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( add_attribute_at_root_level_throws_an_exception )
{
    xml::xostringstream xos;
    const int value = 12;
    BOOST_CHECK_THROW( xos << xml::attribute( "attribute", value ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: add_integer_attribute_on_element_makes_a_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( add_integer_attribute_on_element_makes_a_valid_document )
{
    xml::xostringstream xos;
    const int value = 12;
    xos << xml::start( "element" ) << xml::attribute( "attribute", value ) << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element attribute=\"12\"/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: add_string_attribute_on_element_makes_a_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( add_string_attribute_on_element_makes_a_valid_document )
{
    xml::xostringstream xos;
    const std::string value = "  the attribute value  ";
    xos << xml::start( "element" ) << xml::attribute( "attribute", value ) << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element attribute=\"the attribute value\"/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: add_stack_integer_attribute_on_element_makes_a_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( add_stack_integer_attribute_on_element_makes_a_valid_document )
{
    xml::xostringstream xos;
    xos << xml::start( "element" ) << xml::attribute( "attribute", 12 ) << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element attribute=\"12\"/>\n", xos.str() );
}
