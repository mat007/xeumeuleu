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

namespace
{
    const xml::xistringstream global( "<static-stream-is-valid/>" );
}

// -----------------------------------------------------------------------------
// Name: creating_empty_document_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_empty_document_throws_an_exception )
{
    BOOST_CHECK_THROW( xml::xistringstream( "" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: streaming_document_with_one_element
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_document_with_one_element )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" ) >> xml::end;
}

// -----------------------------------------------------------------------------
// Name: streaming_document_with_one_element_with_temporary
// Created: MCO 2010-08-19
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_document_with_one_element_with_temporary )
{
    xml::xistringstream( "<element/>" ) >> xml::start( "element" );
}

// -----------------------------------------------------------------------------
// Name: streaming_document_with_prolog_and_one_element
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_document_with_prolog_and_one_element )
{
    xml::xistringstream xis( "<?xml version='1.0' encoding='UTF-8' standalone='no'?>"
                             "<element/>" );
    xis >> xml::start( "element" ) >> xml::end;
}

// -----------------------------------------------------------------------------
// Name: streaming_document_with_wrong_element_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_document_with_wrong_element_throws_an_exception )
{
    xml::xistringstream xis( "<element/>" );
    BOOST_CHECK_THROW( xis >> xml::start( "not_element" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: leaving_root_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( leaving_root_throws_an_exception )
{
    xml::xistringstream xis( "<element/>" );
    BOOST_CHECK_THROW_WHAT( xis >> xml::end,
        xml::exception,
        "string_input : cannot move up from document" );
}

// -----------------------------------------------------------------------------
// Name: not_reading_child_node_is_allowed
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( not_reading_child_node_is_allowed )
{
    xml::xistringstream xis( "<element>"
                               "<sub-node/>"
                             "</element>" );
    xis >> xml::start( "element" ) >> xml::end;
}

// -----------------------------------------------------------------------------
// Name: not_reading_all_child_nodes_is_allowed
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( not_reading_all_child_nodes_is_allowed )
{
    xml::xistringstream xis( "<element>"
                               "<sub-node/>"
                               "<another-sub-node/>"
                             "</element>" );
    xis >> xml::start( "element" )
            >> xml::start( "another-sub-node" ) >> xml::end
        >> xml::end;
}

// -----------------------------------------------------------------------------
// Name: reading_several_times_in_any_order_is_allowed
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_several_times_in_any_order_is_allowed )
{
    xml::xistringstream xis( "<element>"
                               "<sub-node1/>"
                               "<sub-node2/>"
                             "</element>" );
    xis >> xml::start( "element" )
            >> xml::start( "sub-node2" ) >> xml::end
            >> xml::start( "sub-node1" ) >> xml::end
            >> xml::start( "sub-node2" ) >> xml::end
    >> xml::end;
}

// -----------------------------------------------------------------------------
// Name: streaming_node_string_value
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_node_string_value )
{
    xml::xistringstream xis( "<element>"
                               "\n this is the value \n"
                             "</element>" );
    std::string value;
    xis >> xml::start( "element" ) >> value >> xml::end;
    BOOST_CHECK_EQUAL( "\n this is the value \n", value );
}

// -----------------------------------------------------------------------------
// Name: streaming_node_value_fails_when_no_child
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_node_value_fails_when_no_child )
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
BOOST_AUTO_TEST_CASE( streaming_node_value_fails_when_no_content )
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
BOOST_AUTO_TEST_CASE( streaming_node_value_mixed_with_sub_node )
{
    xml::xistringstream xis( "<element>"
                             " \n text node content "
                               "<sub-node/>"
                             "</element>" );
    std::string value;
    xis >> xml::start( "element" ) >> value >> xml::start( "sub-node" ) >> xml::end >> xml::end;
    BOOST_CHECK_EQUAL( " \n text node content ", value );
}

namespace
{
    class my_class
    {
    public:
        void read( xml::xistream& xis )
        {
            xis.attribute< std::string >( "a" );
        }
    };
    std::string create()
    {
        std::stringstream str;
        str << "<root>" << std::endl;
        for( unsigned int i = 0; i < 100000; ++i )
            str << "  <element a='dummy'/>" << std::endl;
        str << "</root>" << std::endl;
        return str.str();
    }
}

// -----------------------------------------------------------------------------
// Name: reading_huge_xml_is_valid
// Created: AGE 2007-10-22
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_huge_xml_is_valid )
{
    my_class reader;
    {
        xml::xistringstream xis( create() );
        xis >> xml::start( "root" )
                >> xml::list( "element", reader, &my_class::read )
            >> xml::end;
    }
}
