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
// Name: creating_empty_document_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_empty_document_throws_an_exception )
{
    BOOST_CHECK_THROW( xml::xistringstream( "" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: streaming_document_with_one_element
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_document_with_one_element )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" ) >> xml::end();
}

// -----------------------------------------------------------------------------
// Name: streaming_document_with_prolog_and_one_element
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_document_with_prolog_and_one_element )
{
    xml::xistringstream xis( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
                             "<element/>" );
    xis >> xml::start( "element" ) >> xml::end();
}

// -----------------------------------------------------------------------------
// Name: streaming_document_with_wrong_element_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_document_with_wrong_element_throws_an_exception )
{
    xml::xistringstream xis( "<element/>" );
    BOOST_CHECK_THROW( xis >> xml::start( "not_element" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: leaving_root_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( leaving_root_throws_an_exception )
{
    xml::xistringstream xis( "<element/>" );
    BOOST_CHECK_THROW( xis >> xml::end(), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: not_reading_child_node_is_allowed
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( not_reading_child_node_is_allowed )
{
    xml::xistringstream xis( "<element>"
                               "<sub-node/>"
                             "</element>" );
    xis >> xml::start( "element" ) >> xml::end();
}

// -----------------------------------------------------------------------------
// Name: not_reading_all_child_nodes_is_allowed
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( not_reading_all_child_nodes_is_allowed )
{
    xml::xistringstream xis( "<element>"
                               "<sub-node/>"
                               "<another-sub-node/>"
                             "</element>" );
    xis >> xml::start( "element" )
            >> xml::start( "another-sub-node" ) >> xml::end()
        >> xml::end();
}

// -----------------------------------------------------------------------------
// Name: reading_several_times_in_any_order_is_allowed
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( reading_several_times_in_any_order_is_allowed )
{
    xml::xistringstream xis( "<element>"
                               "<sub-node1/>"
                               "<sub-node2/>"
                             "</element>" );
    xis >> xml::start( "element" )
            >> xml::start( "sub-node2" ) >> xml::end()
            >> xml::start( "sub-node1" ) >> xml::end()
            >> xml::start( "sub-node2" ) >> xml::end()
    >> xml::end();
}

// -----------------------------------------------------------------------------
// Name: streaming_node_string_value
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_node_string_value )
{
    xml::xistringstream xis( "<element>"
                               "\n this is the value \n"
                             "</element>" );
    std::string value;
    xis >> xml::start( "element" ) >> value >> xml::end();
    BOOST_CHECK_EQUAL( "this is the value", value );
}

// -----------------------------------------------------------------------------
// Name: streaming_node_value_fails_when_no_child
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_node_value_fails_when_no_child )
{
    xml::xistringstream xis( "<element/>" );
    std::string value;
    xis >> xml::start( "element" );
    BOOST_CHECK_THROW( xis >> value, xml::exception );
}

// -----------------------------------------------------------------------------
// Name: streaming_node_value_fails_when_no_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_node_value_fails_when_no_content )
{
    xml::xistringstream xis( "<element>"
                               "<sub-node/>"
                             "</element>" );
    std::string value;
    xis >> xml::start( "element" );
    BOOST_CHECK_THROW( xis >> value, xml::exception );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_reads_node_string_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_reads_node_string_content )
{
    xml::xistringstream xis( "<element>"
                               " this is the value "
                             "</element>");
    std::string value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( "this is the value", value );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_reads_node_float_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_reads_node_float_content )
{
    xml::xistringstream xis( "<element>"
                               "1.23"
                             "</element>");
    float value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( 1.23f, value );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_reads_node_double_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_reads_node_double_content )
{
    xml::xistringstream xis( "<element>"
                               "1e+99"
                             "</element>");
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
    xml::xistringstream xis( "<element>"
                               "12"
                             "</element>");
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
    xml::xistringstream xis( "<element>"
                               "12.3"
                             "</element>");
    int value;
    BOOST_CHECK_THROW( xis >> xml::content( "element", value ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: read_node_overflow_double_content_in_float_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( read_node_overflow_double_content_in_float_throws_an_exception )
{
    xml::xistringstream xis( "<element>"
                               "1e+99"
                             "</element>");
    float value;
    BOOST_CHECK_THROW( xis >> xml::content( "element", value ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_reads_node_boolean_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_reads_node_boolean_content )
{
    xml::xistringstream xis( "<element>"
                               "true"
                             "</element>");
    bool value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( true, value );
}

// -----------------------------------------------------------------------------
// Name: creating_an_UTF_8_stream_with_non_UTF_8_characters_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_an_UTF_8_stream_with_non_UTF_8_characters_throws_an_exception )
{
    BOOST_CHECK_THROW( xml::xistringstream( "<?xml version='1.0' encoding='UTF-8' standalone='no' ?>"
                                            "<element>ça c'est sûr !</element>" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_an_utf_16_stream_with_UTF_16_format_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_an_UTF_16_stream_with_extended_characters_does_not_throw_an_exception )
{
    BOOST_CHECK_THROW( xml::xistringstream( "<?xml version='1.0' encoding='UTF-16' standalone='no' ?>"
                                            "<element>ça c'est sûr !</element>" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_an_utf_16_stream_with_ISO_8859_1_format_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_an_ISO_8859_1_stream_with_extended_characters_does_not_throw_an_exception )
{
    xml::xistringstream xis( "<?xml version='1.0' encoding='ISO-8859-1' standalone='no' ?>"
                             "<element>ça c'est sûr !</element>" );
    std::string value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( "ça c'est sûr !", value );
}

// -----------------------------------------------------------------------------
// Name: forcing_encoding_to_ISO_8859_1_allows_to_read_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( forcing_encoding_to_ISO_8859_1_allows_to_read_content )
{
    xml::xistringstream xis( "<element>ça c'est sûr !</element>", xml::encoding( "ISO-8859-1" ) );
    std::string value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( "ça c'est sûr !", value );
}

// -----------------------------------------------------------------------------
// Name: forcing_encoding_to_ISO_8859_1_whereas_UTF_8_is_specified_in_document_allows_to_read_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( forcing_encoding_to_ISO_8859_1_whereas_UTF_8_is_specified_in_document_allows_to_read_content )
{
    xml::xistringstream xis( "<?xml version='1.0' encoding='UTF-8' standalone='no' ?>"
                             "<element>ça c'est sûr !</element>", xml::encoding( "ISO-8859-1" ) );
    std::string value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( "ça c'est sûr !", value );
}

// -----------------------------------------------------------------------------
// Name: creating_stream_with_xml_not_validated_by_schema_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_stream_with_xml_not_validated_by_schema_throws_an_exception )
{
    BOOST_CHECK_THROW( xml::xistringstream( "<wrong-element/>", xml::grammar( "schema.xsd" ) ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_stream_with_xml_validated_by_schema_does_not_throw_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_stream_with_xml_validated_by_schema_does_not_throw_an_exception )
{
    BOOST_CHECK_NO_THROW( xml::xistringstream( "<element/>", xml::grammar( "schema.xsd" ) ) );
}

// -----------------------------------------------------------------------------
// Name: creating_stream_with_xml_not_validated_by_internally_referenced_schema_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_stream_with_xml_not_validated_by_internally_referenced_schema_throws_an_exception )
{
    const std::string xml( "<wrong-element xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='schema.xsd' />" );
    BOOST_CHECK_THROW( xml::xistringstream xis( xml ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_stream_with_xml_validated_by_internally_referenced_schema_does_not_throw_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_stream_with_xml_validated_by_internally_referenced_schema_does_not_throw_an_exception )
{
    const std::string xml( "<element xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='schema.xsd' />" );
    BOOST_CHECK_NO_THROW( xml::xistringstream xis( xml ) );
}
