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
    BOOST_CHECK_EQUAL( "\n this is the value \n", value );
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
// Name: streaming_node_value_mixed_with_sub_node
// Created: MCO 2006-10-16
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_node_value_mixed_with_sub_node )
{
    xml::xistringstream xis( "<element>"
                             " \n text node content "
                               "<sub-node/>"
                             "</element>" );
    std::string value;
    xis >> xml::start( "element" ) >> value >> xml::start( "sub-node" ) >> xml::end() >> xml::end();
    BOOST_CHECK_EQUAL( " \n text node content ", value );
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
// Name: creating_an_UTF_16_stream_with_extended_characters_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_an_UTF_16_stream_with_extended_characters_throws_an_exception )
{
    BOOST_CHECK_THROW( xml::xistringstream( "<?xml version='1.0' encoding='UTF-16' standalone='no' ?>"
                                            "<element>ça c'est sûr !</element>" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_an_ISO_8859_1_stream_with_extended_characters_does_not_throw_an_exception
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
    BOOST_CHECK_THROW( xml::xistringstream( "<wrong-element/>", xml::external_grammar( BOOST_RESOLVE( "schema.xsd" ) ) ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_stream_with_xml_validated_by_schema_does_not_throw_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_stream_with_xml_validated_by_schema_does_not_throw_an_exception )
{
    BOOST_CHECK_NO_THROW( xml::xistringstream( "<element/>", xml::external_grammar( BOOST_RESOLVE( "schema.xsd" ) ) ) );
}

// -----------------------------------------------------------------------------
// Name: creating_stream_with_xml_validated_by_internally_referenced_schema_does_not_throw_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_stream_with_xml_validated_by_internally_referenced_schema_does_not_throw_an_exception )
{
    const std::string schema = BOOST_RESOLVE( "schema.xsd" );
    const std::string xml( "<element xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='" + schema + "' />" );
    BOOST_CHECK_NO_THROW( xml::xistringstream xis( xml, xml::internal_grammar() ) );
}

// -----------------------------------------------------------------------------
// Name: creating_stream_with_xml_not_validated_by_internally_referenced_schema_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_stream_with_xml_not_validated_by_internally_referenced_schema_throws_an_exception )
{
    const std::string schema = BOOST_RESOLVE( "schema.xsd" );
    const std::string xml( "<wrong-element xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='" + schema + "' />" );
    BOOST_CHECK_THROW( xml::xistringstream xis( xml, xml::internal_grammar() ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: internal_schema_is_used_only_if_specified
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( internal_schema_is_used_only_if_specified )
{
    const std::string schema = BOOST_RESOLVE( "schema.xsd" );
    const std::string xml( "<wrong-element xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='" + schema + "' />" );
    BOOST_CHECK_NO_THROW( xml::xistringstream xis( xml ) );
}
