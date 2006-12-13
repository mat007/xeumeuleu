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
        int value;
        xis >> xml::content( "node", value );
    }
}

// -----------------------------------------------------------------------------
// Name: streaming_root_content_makes_a_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_root_content_makes_a_valid_document )
{
    xml::xostringstream xos;
    xos << xml::content( "element", " this is the content  " );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element> this is the content  </element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_child_float_content_makes_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_child_float_content_makes_valid_document )
{
    xml::xostringstream xos;
    const float value = 1.23f;
    xos << xml::start( "element" ) << xml::content( "child", value ) << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <child>1.23</child>\n"
                       "</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_child_double_content_makes_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_child_double_content_makes_valid_document )
{
    xml::xostringstream xos;
    const double value = 1.23;
    xos << xml::start( "element" ) << xml::content( "child", value ) << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <child>1.23</child>\n"
                       "</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_child_integer_content_makes_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_child_integer_content_makes_valid_document )
{
    xml::xostringstream xos;
    const int value = 1242;
    xos << xml::start( "element" ) << xml::content( "child", value ) << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <child>1242</child>\n"
                       "</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_child_short_integer_content_makes_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_child_short_integer_content_makes_valid_document )
{
    xml::xostringstream xos;
    const short value = 1242;
    xos << xml::start( "element" ) << xml::content( "child", value ) << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <child>1242</child>\n"
                       "</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_child_boolean_content_makes_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_child_boolean_content_makes_valid_document )
{
    xml::xostringstream xos;
    const bool value = false;
    xos << xml::start( "element" ) << xml::content( "child", value ) << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <child>false</child>\n"
                       "</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_child_unsigned_integer_content_makes_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_child_unsigned_integer_content_makes_valid_document )
{
    xml::xostringstream xos;
    const unsigned int value = 1242;
    xos << xml::start( "element" ) << xml::content( "child", value ) << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <child>1242</child>\n"
                       "</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_child_long_integer_content_makes_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_child_long_integer_content_makes_valid_document )
{
    xml::xostringstream xos;
    const long value = 1242;
    xos << xml::start( "element" ) << xml::content( "child", value ) << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <child>1242</child>\n"
                       "</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_child_unsigned_long_integer_content_makes_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_child_unsigned_long_integer_content_makes_valid_document )
{
    xml::xostringstream xos;
    const unsigned long value = 1242;
    xos << xml::start( "element" ) << xml::content( "child", value ) << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <child>1242</child>\n"
                       "</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_direct_content_value_makes_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_direct_content_value_makes_valid_document )
{
    xml::xostringstream xos;
    xos << xml::content( "element", 7 );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>7</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_direct_content_non_constant_value_makes_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_direct_content_non_constant_value_makes_valid_document )
{
    xml::xostringstream xos;
    int value = 7;
    xos << xml::content( "element", value );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>7</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_reads_node_string_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_reads_node_string_content )
{
    xml::xistringstream xis( "<element> this is the value </element>");
    std::string value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( " this is the value ", value );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_reads_node_float_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_reads_node_float_content )
{
    xml::xistringstream xis( "<element> 1.23 </element>");
    float value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( 1.23f, value );
}

// -----------------------------------------------------------------------------
// Name: read_node_overflow_double_content_in_float_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( read_node_overflow_double_content_in_float_throws_an_exception )
{
    xml::xistringstream xis( "<element> 1e+99 </element>");
    float value;
    BOOST_CHECK_THROW( xis >> xml::content( "element", value ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_reads_node_double_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_reads_node_double_content )
{
    xml::xistringstream xis( "<element> 1e+99 </element>");
    double value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( 1e+99, value );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_reads_node_integer_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_reads_node_integer_content )
{
    xml::xistringstream xis( "<element> 12 </element>");
    int value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( 12, value );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_reads_node_float_content_in_integer_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_reads_node_float_content_in_integer_throws_an_exception )
{
    xml::xistringstream xis( "<element> 12.3 </element>");
    int value;
    BOOST_CHECK_THROW( xis >> xml::content( "element", value ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_reads_node_boolean_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_reads_node_boolean_content )
{
    xml::xistringstream xis( "<element> true </element>");
    bool value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( true, value );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_reads_node_short_integer_content
// Created: MCO 2006-12-12
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_reads_node_short_integer_content )
{
    xml::xistringstream xis( "<element> 5 </element>");
    short value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( 5, value );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_reads_node_integer_content_in_short_integer_throws_an_exception
// Created: MCO 2006-12-12
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_reads_node_integer_content_in_short_integer_throws_an_exception )
{
    xml::xistringstream xis( "<element> 300000 </element>");
    short value;
    BOOST_CHECK_THROW( xis >> xml::content( "element", value ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_reads_node_unsigned_integer_content
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_reads_node_unsigned_integer_content )
{
    xml::xistringstream xis( "<element> 4294967295 </element>");
    unsigned int value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( 4294967295u, value );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_reads_node_float_content_in_unsigned_integer_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_reads_node_float_content_in_unsigned_integer_throws_an_exception )
{
    xml::xistringstream xis( "<element> 12.3 </element>");
    unsigned int value;
    BOOST_CHECK_THROW( xis >> xml::content( "element", value ), xml::exception );
}
