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
// Name: reading_optional_non_existing_element_does_not_throw_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( reading_optional_non_existing_element_does_not_throw_exception )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
            >> xml::optional();
    BOOST_CHECK_NO_THROW( xis >> xml::start( "non-existing-child" ) );
}

// -----------------------------------------------------------------------------
// Name: reading_optional_non_existing_element_sub_node_does_not_throw_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( reading_optional_non_existing_element_sub_node_does_not_throw_exception )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
            >> xml::optional()
            >> xml::start( "non-existing-child" );
    BOOST_CHECK_NO_THROW( xis >> xml::start( "non-existing-sub-child" ) );
}

// -----------------------------------------------------------------------------
// Name: reading_optional_non_existing_element_content_does_not_throw_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( reading_optional_non_existing_element_content_does_not_throw_exception )
{
    xml::xistringstream xis( "<element/>" );
    int value = 0;
    xis >> xml::start( "element" )
            >> xml::optional()
            >> xml::start( "non-existing-child" );
    BOOST_CHECK_NO_THROW( xis >> value );
    BOOST_CHECK_EQUAL( 0, value );
}

// -----------------------------------------------------------------------------
// Name: reading_optional_non_existing_element_attribute_does_not_throw_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( reading_optional_non_existing_element_attribute_does_not_throw_exception )
{
    xml::xistringstream xis( "<element/>" );
    int value = 0;
    xis >> xml::start( "element" )
            >> xml::optional()
            >> xml::start( "non-existing-child" );
    BOOST_CHECK_NO_THROW( xis >> xml::attribute( "attribute", value ) );
    BOOST_CHECK_EQUAL( 0, value ); 
}

// -----------------------------------------------------------------------------
// Name: moving_out_of_optional_non_existing_element_terminates_the_optional_sub_tree
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( moving_out_of_optional_non_existing_element_terminates_the_optional_sub_tree )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
            >> xml::optional()
            >> xml::start( "non-existing-child" )
            >> xml::end();
    BOOST_CHECK_THROW( xis >> xml::start( "non-existing-child" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: reading_existing_element_inside_optional_non_existing_element_is_still_optional
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( reading_existing_element_inside_optional_non_existing_element_is_still_optional )
{
    xml::xistringstream xis( "<element>"
                               "<existing-child/>"
                             "</element>" );
    xis >> xml::start( "element" )
            >> xml::optional()
            >> xml::start( "non-existing-child" )
                >> xml::start( "existing-child" )
                >> xml::end();
    BOOST_CHECK_NO_THROW( xis >> xml::start( "non-existing-sub-child" ) );
}

// -----------------------------------------------------------------------------
// Name: reading_optional_element_inside_optional_non_existing_element
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( reading_optional_element_inside_optional_non_existing_element )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
            >> xml::optional()
            >> xml::start( "non-existing-child" )
                >> xml::optional()
                >> xml::start( "non-existing-sub-child" )
                >> xml::end()
            >> xml::end();
    BOOST_CHECK_THROW( xis >> xml::start( "non-existing-child" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: setting_optional_before_moving_up_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( setting_optional_before_moving_up_throws_an_exception )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
            >> xml::optional();
    BOOST_CHECK_THROW( xis >> xml::end(), xml::exception );
}

namespace
{
    class custom_class
    {
    public:
        void process( xml::xistream& )
        {}
    };
}

// -----------------------------------------------------------------------------
// Name: reading_a_list_resets_the_optional_flag
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( reading_a_list_resets_the_optional_flag )
{
    custom_class custom;
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
            >> xml::optional()
            >> xml::list( "non-existing-child", custom, &custom_class::process );
    BOOST_CHECK_THROW( xis >> xml::start( "non-existing-child" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: reading_an_optional_non_existing_attribute_does_not_throw_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( reading_an_optional_non_existing_attribute_does_not_throw_an_exception )
{
    xml::xistringstream xis( "<element/>" );
    int value = 0;
    xis >> xml::start( "element" )
            >> xml::optional();
    BOOST_CHECK_NO_THROW( xis >> xml::attribute( "non-existinig-attribute", value ) );
    BOOST_CHECK_EQUAL( 0, value );
}

// -----------------------------------------------------------------------------
// Name: reading_an_optional_non_existing_content_does_not_throw_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( reading_an_optional_non_existing_content_does_not_throw_an_exception )
{
    xml::xistringstream xis( "<element/>" );
    int value = 0;
    xis >> xml::start( "element" )
            >> xml::optional();
    BOOST_CHECK_NO_THROW( xis >> value );
    BOOST_CHECK_EQUAL( 0, value );
}
