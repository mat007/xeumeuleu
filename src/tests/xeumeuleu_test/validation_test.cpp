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
    try
    {
        xml::xistringstream( "<element/>", xml::external_grammar( "non-existing.xsd" ) );
    }
    catch( xml::exception& e )
    {
        BOOST_CHECK_EQUAL( "Failed to load grammar 'non-existing.xsd'", e.what() );
        return;
    }
    BOOST_FAIL( "meaningful exception expected" );
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
