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

// -----------------------------------------------------------------------------
// Name: creating_stream_with_xml_not_validated_by_schema_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_stream_with_xml_not_validated_by_schema_throws_an_exception )
{
    BOOST_CHECK_THROW( xml::xistringstream( "<wrong-element/>", xml::external_grammar( BOOST_RESOLVE( "schema.xsd" ) ) ), xml::exception );
}

namespace
{
    const std::string load( const std::string& filename )
    {
        std::ifstream ifs( filename.c_str() );
        if( ! ifs )
            throw std::runtime_error( "File " + filename + " not found" );
        return std::string( std::istreambuf_iterator< char >( ifs ), std::istreambuf_iterator< char >() );
    }
}

// -----------------------------------------------------------------------------
// Name: creating_stream_with_xml_not_validated_by_in_memory_schema_throws_an_exception
// Created: MCO 2010-11-10
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_stream_with_xml_not_validated_by_in_memory_schema_throws_an_exception )
{
    const std::string grammar = load( BOOST_RESOLVE( "schema.xsd" ) );
    BOOST_CHECK_THROW( xml::xistringstream( "<wrong-element/>", xml::memory_grammar( grammar ) ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_stream_with_non_existing_schema_throws_a_meaningful_exception
// Created: MCO 2008-07-17
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_stream_with_non_existing_schema_throws_a_meaningful_exception )
{
    BOOST_CHECK_THROW_WHAT_SUB( xml::xistringstream( "<element/>", xml::external_grammar( "non-existing.xsd" ) ),
        xml::exception,
        "failed to load grammar 'non-existing.xsd' : unable to open primary document entity" );
}

// -----------------------------------------------------------------------------
// Name: creating_stream_with_invalid_schema_throws_a_meaningful_exception
// Created: MCO 2015-12-14
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_stream_with_invalid_schema_throws_a_meaningful_exception )
{
    BOOST_CHECK_THROW_WHAT_SUB( xml::xistringstream( "<element/>", xml::external_grammar( BOOST_RESOLVE( "invalid.xsd" ) ) ),
        xml::exception,
        "invalid content in 'schema' element" );
}

// -----------------------------------------------------------------------------
// Name: creating_stream_with_xml_validated_by_schema_does_not_throw_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_stream_with_xml_validated_by_schema_does_not_throw_an_exception )
{
    BOOST_CHECK_NO_THROW( xml::xistringstream( "<element/>", xml::external_grammar( BOOST_RESOLVE( "schema.xsd" ) ) ) );
}

// -----------------------------------------------------------------------------
// Name: creating_stream_with_xml_validated_by_internally_referenced_schema_does_not_throw_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_stream_with_xml_validated_by_internally_referenced_schema_does_not_throw_an_exception )
{
    const std::string schema = BOOST_RESOLVE( "schema.xsd" );
    const std::string xml = "<element xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='" + schema + "' />";
    BOOST_CHECK_NO_THROW( xml::xistringstream xis( xml, xml::internal_grammar() ) );
}

// -----------------------------------------------------------------------------
// Name: creating_stream_with_xml_not_validated_by_internally_referenced_schema_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_stream_with_xml_not_validated_by_internally_referenced_schema_throws_an_exception )
{
    const std::string schema = BOOST_RESOLVE( "schema.xsd" );
    const std::string xml = "<wrong-element xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='" + schema + "' />";
    BOOST_CHECK_THROW( xml::xistringstream xis( xml, xml::internal_grammar() ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: internal_schema_is_used_only_if_specified
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( internal_schema_is_used_only_if_specified )
{
    const std::string schema = BOOST_RESOLVE( "schema.xsd" );
    const std::string xml = "<wrong-element xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='" + schema + "' />";
    BOOST_CHECK_NO_THROW( xml::xistringstream xis( xml ) );
}

// -----------------------------------------------------------------------------
// Name: non_existing_internal_schema_is_loaded_only_if_necessary
// Created: MCO 2009-08-13
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( non_existing_internal_schema_is_loaded_only_if_necessary )
{
    const std::string xml = "<element xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='non existing schema.xsd' />";
    BOOST_CHECK_NO_THROW( xml::xistringstream xis( xml ) );
}

// -----------------------------------------------------------------------------
// Name: including_a_non_existing_schema_throws
// Created: MAT 2010-11-17
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( including_a_non_existing_schema_throws )
{
    const std::string schema = "<xs:schema xmlns:xs='http://www.w3.org/2001/XMLSchema'>"
                               "  <xs:include schemaLocation='non-existing.xsd'/>"
                               "  <xs:element name='element'/>"
                               "</xs:schema>";
    BOOST_CHECK_THROW( xml::xistringstream xis( "<element/>", xml::memory_grammar( schema ) ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: several_memory_grammars_can_be_combined
// Created: MAT 2010-11-21
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( several_memory_grammars_can_be_combined )
{
    const std::string schema_1 = load( BOOST_RESOLVE( "schema_1.xsd" ) );
    const std::string schema_2 = load( BOOST_RESOLVE( "schema_2.xsd" ) );
    xml::grammars composite;
    xml::memory_grammar grammar_1( schema_1 );
    xml::memory_grammar grammar_2( schema_2 );
    composite.add( grammar_2 );
    composite.add( grammar_1 );
    BOOST_CHECK_NO_THROW( xml::xistringstream xis( "<element xmlns='http://example.org' attribute='42'/>", composite ) );
}

// -----------------------------------------------------------------------------
// Name: several_external_grammars_can_be_combined
// Created: MAT 2010-11-22
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( several_external_grammars_can_be_combined )
{
    BOOST_CHECK_NO_THROW( xml::xistringstream xis( "<element xmlns='http://example.org' attribute='42'/>",
        xml::external_grammar( BOOST_RESOLVE( "schema_2.xsd" ) ) + xml::external_grammar( BOOST_RESOLVE( "schema_1.xsd" ) ) ) );
}

// -----------------------------------------------------------------------------
// Name: several_memory_and_external_grammars_can_be_combined
// Created: MAT 2010-11-22
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( several_memory_and_external_grammars_can_be_combined )
{
    const std::string schema_2 = load( BOOST_RESOLVE( "schema_2.xsd" ) );
    BOOST_CHECK_NO_THROW( xml::xistringstream xis( "<element xmlns='http://example.org' attribute='42'/>",
        xml::memory_grammar( schema_2 ) + xml::external_grammar( BOOST_RESOLVE( "schema_1.xsd" ) ) ) );
}

// -----------------------------------------------------------------------------
// Name: several_grammars_can_be_combined_using_operator_plus
// Created: MAT 2010-11-17
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( several_grammars_can_be_combined_using_operator_plus )
{
    const std::string schema_1 = load( BOOST_RESOLVE( "schema_1.xsd" ) );
    const std::string schema_2 = load( BOOST_RESOLVE( "schema_2.xsd" ) );
    BOOST_CHECK_THROW( xml::xistringstream xis( "<element xmlns='http://example.org' attribute='42'/>", xml::memory_grammar( schema_1 ) ), xml::exception );
    BOOST_CHECK_THROW( xml::xistringstream xis( "<element xmlns='http://example.org' attribute='42'/>", xml::memory_grammar( schema_1 ) + xml::memory_grammar( schema_2 ) ), xml::exception );
    BOOST_CHECK_NO_THROW( xml::xistringstream xis( "<element xmlns='http://example.org' attribute='42'/>", xml::memory_grammar( schema_2 ) + xml::memory_grammar( schema_1 ) ) );
}

// -----------------------------------------------------------------------------
// Name: several_grammars_with_the_same_target_namespace_can_be_combined
// Created: MAT 2010-11-17
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( several_grammars_with_the_same_target_namespace_can_be_combined )
{
    const std::string schema_1 = "<xs:schema xmlns:xs='http://www.w3.org/2001/XMLSchema'>"
                                 "  <xs:element name='element'>"
                                 "    <xs:complexType>"
                                 "      <xs:attribute name='attribute' type='type'/>"
                                 "    </xs:complexType>"
                                 "  </xs:element>"
                                 "</xs:schema>";
    const std::string schema_2 = "<xs:schema xmlns:xs='http://www.w3.org/2001/XMLSchema'>"
                                 "  <xs:simpleType name='type'>"
                                 "    <xs:restriction base='xs:int'/>"
                                 "  </xs:simpleType>"
                                 "</xs:schema>";
    BOOST_CHECK_THROW( xml::xistringstream xis( "<element attribute='42'/>", xml::memory_grammar( schema_1 ) ), xml::exception );
    BOOST_CHECK_THROW( xml::xistringstream xis( "<element attribute='42'/>", xml::memory_grammar( schema_1 ) + xml::memory_grammar( schema_2 ) ), xml::exception );
    BOOST_CHECK_NO_THROW( xml::xistringstream xis( "<element attribute='42'/>", xml::memory_grammar( schema_2 ) + xml::memory_grammar( schema_1 ) ) );
}

// -----------------------------------------------------------------------------
// Name: creating_stream_with_xml_validated_by_internally_referenced_definition_does_not_throw_an_exception
// Created: MCO 2009-07-04
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_stream_with_xml_validated_by_internally_referenced_definition_does_not_throw_an_exception )
{
    const std::string definition = BOOST_RESOLVE( "document_type.dtd" );
    const std::string xml = "<!DOCTYPE element SYSTEM '" + definition + "'>"
                            "<element/>";
    BOOST_CHECK_NO_THROW( xml::xistringstream xis( xml, xml::internal_grammar() ) );
}

// -----------------------------------------------------------------------------
// Name: creating_stream_with_xml_not_validated_by_internally_referenced_definition_throws_an_exception
// Created: MCO 2009-07-04
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_stream_with_xml_not_validated_by_internally_referenced_definition_throws_an_exception )
{
    const std::string definition = BOOST_RESOLVE( "document_type.dtd" );
    const std::string xml = "<!DOCTYPE element SYSTEM '" + definition + "'>"
                            "<wrong-element/>";
    BOOST_CHECK_THROW( xml::xistringstream xis( xml, xml::internal_grammar() ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: internal_definition_is_used_only_if_specified
// Created: MCO 2009-07-04
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( internal_definition_is_used_only_if_specified )
{
    const std::string definition = BOOST_RESOLVE( "document_type.dtd" );
    const std::string xml = "<!DOCTYPE element SYSTEM '" + definition + "'>"
                            "<wrong-element/>";
    BOOST_CHECK_NO_THROW( xml::xistringstream xis( xml ) );
}

// -----------------------------------------------------------------------------
// Name: non_existing_internal_definition_is_loaded_only_if_necessary
// Created: MCO 2009-08-13
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( non_existing_internal_definition_is_loaded_only_if_necessary )
{
    const std::string xml = "<!DOCTYPE element SYSTEM 'non existing document type.dtd'>"
                            "<element/>";
    BOOST_CHECK_NO_THROW( xml::xistringstream xis( xml ) );
}
