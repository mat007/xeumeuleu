/*
 *   Copyright (c) 2010, Mathieu Champlon
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
#include <turtle/mock.hpp>

// -----------------------------------------------------------------------------
// Name: reading_start_ignores_namespace_by_default
// Created: MAT 2010-06-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_start_ignores_namespace_by_default )
{
    xml::xistringstream xis( "<ns:element xmlns:ns='http://www.example.org'/>" );
    xis >> xml::start( "element" );
}

// -----------------------------------------------------------------------------
// Name: reading_start_in_empty_namespace_is_valid
// Created: MAT 2010-07-13
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_start_in_empty_namespace_is_valid )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::ns( "" ) >> xml::start( "element" );
}

// -----------------------------------------------------------------------------
// Name: reading_prefixed_start_is_valid
// Created: MAT 2010-06-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_prefixed_start_is_valid )
{
    xml::xistringstream xis( "<ns:element xmlns:ns='http://www.example.org'/>" );
    xis >> xml::start( "ns:element" );
}

// -----------------------------------------------------------------------------
// Name: reading_start_filtered_on_invalid_namespace_throws
// Created: MAT 2010-06-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_start_filtered_on_invalid_namespace_throws )
{
    xml::xistringstream xis( "<ns:element xmlns:ns='http://www.example.org'/>" );
    xis >> xml::ns( "invalid namespace" );
    BOOST_CHECK_THROW( xis >> xml::start( "element" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: reading_start_filtered_on_correct_namespace_does_not_throw
// Created: MAT 2010-06-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_start_filtered_on_correct_namespace_does_not_throw )
{
    xml::xistringstream xis( "<ns:element xmlns:ns='http://www.example.org'/>" );
    xis >> xml::ns( "http://www.example.org" ) >> xml::start( "element" );
}

// -----------------------------------------------------------------------------
// Name: reading_start_filtered_on_correct_default_namespace_does_not_throw
// Created: MAT 2010-06-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_start_filtered_on_correct_default_namespace_does_not_throw )
{
    xml::xistringstream xis( "<element xmlns='http://www.example.org'/>" );
    xis >> xml::ns( "http://www.example.org" ) >> xml::start( "element" );
}

// -----------------------------------------------------------------------------
// Name: reading_end_resets_namespace
// Created: MAT 2010-07-19
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_end_resets_namespace )
{
    xml::xistringstream xis( "<element xmlns:ns='http://www.example.org'/>" );
    xis >> xml::start( "element" )
            >> xml::ns( "http://www.example.org" )
        >> xml::end
        >> xml::start( "element" );
}

// -----------------------------------------------------------------------------
// Name: namespace_overwrites_any_previous_specification
// Created: MAT 2010-07-19
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( namespace_overwrites_any_previous_specification )
{
    xml::xistringstream xis( "<element xmlns='http://www.example.org'/>" );
    xis >> xml::ns( "invalid namespace" )
        >> xml::ns( "http://www.example.org" ) >> xml::start( "element" );
}

// -----------------------------------------------------------------------------
// Name: reading_attribute_ignores_namespace_by_default
// Created: MAT 2010-06-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_attribute_ignores_namespace_by_default )
{
    xml::xistringstream xis( "<element ns:attribute='12' xmlns:ns='http://www.example.org'/>" );
    int value = 0;
    xis >> xml::start( "element" )
            >> xml::attribute( "attribute", value );
    BOOST_CHECK_EQUAL( 12, value );
}

// -----------------------------------------------------------------------------
// Name: reading_attribute_in_empty_namespace_does_not_throw
// Created: MAT 2010-07-13
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_attribute_in_empty_namespace_does_not_throw )
{
    xml::xistringstream xis( "<element attribute='12'/>" );
    int value = 0;
    xis >> xml::start( "element" )
            >> xml::ns( "" ) >> xml::attribute( "attribute", value );
    BOOST_CHECK_EQUAL( 12, value );
}

// -----------------------------------------------------------------------------
// Name: reading_prefixed_attribute_does_not_throw
// Created: MAT 2010-06-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_prefixed_attribute_does_not_throw )
{
    xml::xistringstream xis( "<element ns:attribute='12' xmlns:ns='http://www.example.org'/>" );
    int value;
    xis >> xml::start( "element" )
            >> xml::attribute( "ns:attribute", value );
    BOOST_CHECK_EQUAL( 12, value );
}

// -----------------------------------------------------------------------------
// Name: reading_attribute_filtered_on_correct_namespace_does_not_throw
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_attribute_filtered_on_correct_namespace_does_not_throw )
{
    xml::xistringstream xis( "<element ns:attribute='12' xmlns:ns='http://www.example.org'/>" );
    int value = 0;
    xis >> xml::start( "element" )
            >> xml::ns( "http://www.example.org" ) >> xml::attribute( "attribute", value );
    BOOST_CHECK_EQUAL( 12, value );
}

// -----------------------------------------------------------------------------
// Name: reading_attribute_filtered_on_invalid_namespace_throws
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_attribute_filtered_on_invalid_namespace_throws )
{
    xml::xistringstream xis( "<element ns:attribute='12' xmlns:ns='http://www.example.org'/>" );
    int value = 0;
    xis >> xml::start( "element" )
            >> xml::ns( "invalid namespace" );
    BOOST_CHECK_THROW( xis >> xml::attribute( "attribute", value ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: namespace_declarations_are_regular_attributes
// Created: MAT 2010-07-13
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( namespace_declarations_are_regular_attributes )
{
    xml::xistringstream xis( "<element xmlns:ns='http://www.example.org'/>" );
    xis >> xml::start( "element" );
    std::string actual;
    xis >> xml::ns( "http://www.w3.org/2000/xmlns/" ) >> xml::attribute( "ns", actual );
    BOOST_CHECK_EQUAL( "http://www.example.org", actual );
}

// -----------------------------------------------------------------------------
// Name: default_namespace_declaration_is_a_regular_attribute
// Created: MAT 2010-07-13
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( default_namespace_declaration_is_a_regular_attribute )
{
    xml::xistringstream xis( "<element xmlns='http://www.example.org'/>" );
    std::string actual;
    xis >> xml::start( "element" )
            >> xml::ns( "http://www.w3.org/2000/xmlns/" ) >> xml::attribute( "xmlns", actual );
    BOOST_CHECK_EQUAL( "http://www.example.org", actual );
}

namespace
{
    MOCK_CLASS( mock_custom_class_list )
    {
        void process( xml::xistream& xis )
        {
            std::string content;
            xis >> content;
            forward( content );
        }
        MOCK_METHOD_EXT( forward, 1, void( std::string ), forward );
    };
}

// -----------------------------------------------------------------------------
// Name: reading_list_with_namespace_elements
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_list_with_namespace_elements )
{
    xml::xistringstream xis( "<element xmlns='http://www.example.org' xmlns:ns2='http://www.example2.org' xmlns:ns3='http://www.example.org'>"
                             "  <sub-node>content number one</sub-node>"
                             "  <ns2:sub-node>content number two</ns2:sub-node>"
                             "  <ns3:sub-node>content number three</ns3:sub-node>"
                             "</element>" );
    mock_custom_class_list mock_custom;
    MOCK_EXPECT( mock_custom, forward ).once().with( "content number one" );
    MOCK_EXPECT( mock_custom, forward ).once().with( "content number two" );
    MOCK_EXPECT( mock_custom, forward ).once().with( "content number three" );
    xis >> xml::start( "element" )
            >> xml::list( "sub-node", mock_custom, &mock_custom_class_list::process );
}

// -----------------------------------------------------------------------------
// Name: reading_list_filtered_on_correct_namespace_filters_elements
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_list_filtered_on_correct_namespace_filters_elements )
{
    xml::xistringstream xis( "<element xmlns='http://www.example.org' xmlns:ns2='http://www.example2.org' xmlns:ns3='http://www.example.org'>"
                             "  <sub-node>content number one</sub-node>"
                             "  <ns2:sub-node>content number two</ns2:sub-node>"
                             "  <ns3:sub-node>content number three</ns3:sub-node>"
                             "</element>" );
    mock_custom_class_list mock_custom;
    MOCK_EXPECT( mock_custom, forward ).once().with( "content number one" );
    MOCK_EXPECT( mock_custom, forward ).once().with( "content number three" );
    xis >> xml::start( "element" )
            >> xml::ns( "http://www.example.org" ) >> xml::list( "sub-node", mock_custom, &mock_custom_class_list::process );
}

// -----------------------------------------------------------------------------
// Name: reading_list_filtered_on_no_namespace_filters_elements
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_list_filtered_on_no_namespace_filters_elements )
{
    xml::xistringstream xis( "<element xmlns='http://www.example.org' xmlns:ns2='http://www.example2.org' xmlns:ns3='http://www.example.org'>"
                             "  <sub-node xmlns=''>content number one</sub-node>"
                             "  <sub-node>content number two</sub-node>"
                             "  <ns2:sub-node>content number three</ns2:sub-node>"
                             "  <ns3:sub-node>content number four</ns3:sub-node>"
                             "</element>" );
    mock_custom_class_list mock_custom;
    MOCK_EXPECT( mock_custom, forward ).once().with( "content number one" );
    xis >> xml::start( "element" )
            >> xml::ns( "" ) >> xml::list( "sub-node", mock_custom, &mock_custom_class_list::process );
}

namespace
{
    MOCK_CLASS( mock_custom_class_name_list )
    {
        void process( const std::string& ns, const std::string& name, xml::xistream& xis )
        {
            std::string content;
            xis >> content;
            forward( ns, name, content );
        }
        MOCK_METHOD_EXT( forward, 3, void( std::string, std::string, std::string ), forward )
    };
}

// -----------------------------------------------------------------------------
// Name: reading_name_list_with_namespace_elements
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_name_list_with_namespace_elements )
{
    xml::xistringstream xis( "<element xmlns='http://www.example.org' xmlns:ns='http://www.example.org' xmlns:ns2='http://www.example2.org'>"
                             "  <sub-node1>content number one</sub-node1>"
                             "  <ns:sub-node2>content number two</ns:sub-node2>"
                             "  <ns2:sub-node3>content number three</ns2:sub-node3>"
                             "</element>" );
    mock_custom_class_name_list mock_custom;
    MOCK_EXPECT( mock_custom, forward ).once().with( "http://www.example.org", "sub-node1", "content number one" );
    MOCK_EXPECT( mock_custom, forward ).once().with( "http://www.example.org", "sub-node2", "content number two" );
    MOCK_EXPECT( mock_custom, forward ).once().with( "http://www.example2.org", "sub-node3", "content number three" );
    xis >> xml::start( "element" )
            >> xml::list( mock_custom, &mock_custom_class_name_list::process );
}

// -----------------------------------------------------------------------------
// Name: reading_name_list_filtered_on_namespace_filters_elements
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_name_list_filtered_on_namespace_filters_elements )
{
    xml::xistringstream xis( "<element xmlns='http://www.example.org' xmlns:ns='http://www.example.org' xmlns:ns2='http://www.example2.org'>"
                             "  <sub-node1>content number one</sub-node1>"
                             "  <ns:sub-node2>content number two</ns:sub-node2>"
                             "  <ns2:sub-node3>content number three</ns2:sub-node3>"
                             "</element>" );
    mock_custom_class_name_list mock_custom;
    MOCK_EXPECT( mock_custom, forward ).once().with( "http://www.example.org", "sub-node1", "content number one" );
    MOCK_EXPECT( mock_custom, forward ).once().with( "http://www.example.org", "sub-node2", "content number two" );
    xis >> xml::start( "element" )
            >> xml::ns( "http://www.example.org" ) >> xml::list( mock_custom, &mock_custom_class_name_list::process );
}

// -----------------------------------------------------------------------------
// Name: reading_name_list_filtered_on_no_namespace_filters_elements
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_name_list_filtered_on_no_namespace_filters_elements )
{
    xml::xistringstream xis( "<element xmlns='http://www.example.org' xmlns:ns='http://www.example.org' xmlns:ns2='http://www.example2.org'>"
                             "  <sub-node1 xmlns=''>content number one</sub-node1>"
                             "  <sub-node2>content number two</sub-node2>"
                             "  <ns:sub-node3>content number three</ns:sub-node3>"
                             "  <ns2:sub-node4>content number four</ns2:sub-node4>"
                             "</element>" );
    mock_custom_class_name_list mock_custom;
    MOCK_EXPECT( mock_custom, forward ).once().with( "", "sub-node1", "content number one" );
    xis >> xml::start( "element" )
            >> xml::ns( "" ) >> xml::list( mock_custom, &mock_custom_class_name_list::process );
}

namespace
{
    MOCK_CLASS( mock_custom_class )
    {
    public:
        void process( const std::string& ns, const std::string& name, xml::xistream& xis )
        {
            std::string content;
            xis >> content;
            forward( ns, name, content );
        }
        MOCK_METHOD_EXT( forward, 3, void( std::string, std::string, std::string ), forward )
    };
}

// -----------------------------------------------------------------------------
// Name: reading_attributes_with_namespace_from_element_filters_attributes
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_attributes_with_namespace_from_element_filters_attributes )
{
    xml::xistringstream xis( "<root xmlns='http://www.example.org' xmlns:ns='http://www.example.org' xmlns:ns2='http://www.example2.org'>"
                             "  <element attribute='attribute 1' ns:attribute='attribute 2' ns2:attribute='attribute 3'/>"
                             "</root>" );
    mock_custom_class mock_custom;
    MOCK_EXPECT( mock_custom, forward ).once().with( "", "attribute", "attribute 1" );
    MOCK_EXPECT( mock_custom, forward ).once().with( "http://www.example.org", "attribute", "attribute 2" );
    MOCK_EXPECT( mock_custom, forward ).once().with( "http://www.example2.org", "attribute", "attribute 3" );
    xis >> xml::start( "root" )
            >> xml::start( "element" )
                >> xml::attributes( mock_custom, &mock_custom_class::process );
}

// -----------------------------------------------------------------------------
// Name: reading_attributes_with_namespace_filtered_on_namespace_from_element_filters_attributes
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_attributes_with_namespace_filtered_on_namespace_from_element_filters_attributes )
{
    xml::xistringstream xis( "<root xmlns='http://www.example.org' xmlns:ns='http://www.example.org' xmlns:ns2='http://www.example2.org'>"
                             "  <element attribute='attribute 1' ns:attribute='attribute 2' ns2:attribute='attribute 3'/>"
                             "</root>" );
    mock_custom_class mock_custom;
    MOCK_EXPECT( mock_custom, forward ).once().with( "http://www.example.org", "attribute", "attribute 2" );
    xis >> xml::start( "root" )
            >> xml::start( "element" )
                >> xml::ns( "http://www.example.org" ) >> xml::attributes( mock_custom, &mock_custom_class::process );
}

// -----------------------------------------------------------------------------
// Name: reading_attributes_with_namespace_filtered_on_no_namespace_from_element_filters_attributes
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_attributes_with_namespace_filtered_on_no_namespace_from_element_filters_attributes )
{
    xml::xistringstream xis( "<root xmlns='http://www.example.org' xmlns:ns='http://www.example.org' xmlns:ns2='http://www.example2.org'>"
                             "  <element attribute='attribute 1' ns:attribute='attribute 2' ns2:attribute='attribute 3'/>"
                             "</root>" );
    mock_custom_class mock_custom;
    MOCK_EXPECT( mock_custom, forward ).once().with( "", "attribute", "attribute 1" );
    xis >> xml::start( "root" )
            >> xml::start( "element" )
                >> xml::ns( "" ) >> xml::attributes( mock_custom, &mock_custom_class::process );
}

// -----------------------------------------------------------------------------
// Name: reading_prefix_retrieves_namespace_prefix
// Created: MAT 2010-07-19
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_prefix_retrieves_namespace_prefix )
{
    std::string prefix;
    xml::xistringstream xis( "<element xmlns:ns='http://www.example.org'/>" );
    xis >> xml::start( "element" )
            >> xml::prefix( "http://www.example.org", prefix );
    BOOST_CHECK_EQUAL( "ns", prefix );
}

// -----------------------------------------------------------------------------
// Name: reading_prefix_for_no_namespace_retrieves_an_empty_prefix
// Created: MAT 2010-07-27
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_prefix_for_no_namespace_retrieves_an_empty_prefix )
{
    std::string prefix = "?";
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
            >> xml::prefix( "", prefix );
    BOOST_CHECK( prefix.empty() );
}

// -----------------------------------------------------------------------------
// Name: reading_prefix_of_invalid_namespace_throws
// Created: MAT 2010-07-19
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_prefix_of_invalid_namespace_throws )
{
    std::string prefix;
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" );
    BOOST_CHECK_THROW( xis >> xml::prefix( "invalid namespace", prefix ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: reading_prefix_of_default_namespace_retrieves_empty_prefix
// Created: MAT 2010-07-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_prefix_of_default_namespace_retrieves_empty_prefix )
{
    std::string prefix;
    xml::xistringstream xis( "<element xmlns='http://www.example.org'/>" );
    xis >> xml::start( "element" )
            >> xml::prefix( "http://www.example.org", prefix );
    BOOST_CHECK( prefix.empty() );
}

// -----------------------------------------------------------------------------
// Name: reading_prefix_in_multi_stream_retrieves_the_first_available
// Created: MAT 2010-07-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_prefix_in_multi_stream_retrieves_the_first_available )
{
    std::string prefix;
    xml::xistringstream xis1( "<element xmlns:ns1='http://www.example.org'/>" );
    xml::xistringstream xis2( "<element xmlns:ns2='http://www.example.org'/>" );
    xml::ximultistream xis( xis1, xis2 );
    xis >> xml::start( "element" )
            >> xml::prefix( "http://www.example.org", prefix );
    BOOST_CHECK_EQUAL( "ns1", prefix );
}

// -----------------------------------------------------------------------------
// Name: reading_default_prefix_in_multi_stream_retrieves_the_first_available
// Created: MAT 2010-07-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_default_prefix_in_multi_stream_retrieves_the_first_available )
{
    std::string prefix;
    xml::xistringstream xis1( "<element xmlns='http://www.example.org'/>" );
    xml::xistringstream xis2( "<element xmlns:ns='http://www.example.org'/>" );
    xml::ximultistream xis( xis1, xis2 );
    xis >> xml::start( "element" )
            >> xml::prefix( "http://www.example.org", prefix );
    BOOST_CHECK( prefix.empty() );
}

// -----------------------------------------------------------------------------
// Name: reading_writing_namespace_declaration
// Created: MAT 2010-07-22
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_writing_namespace_declaration )
{
    xml::xistringstream xis( "<element xmlns:ns='http://www.example.org'/>" );
    xml::xostringstream xos;
    xos << xis;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element xmlns:ns=\"http://www.example.org\"/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: reading_writing_default_namespace_declaration
// Created: MAT 2010-07-22
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_writing_default_namespace_declaration )
{
    xml::xistringstream xis( "<element xmlns='http://www.example.org'/>" );
    xml::xostringstream xos;
    xos << xis;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element xmlns=\"http://www.example.org\"/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: reading_writing_namespace_declaration_and_usage
// Created: MAT 2010-07-22
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_writing_namespace_declaration_and_usage )
{
    xml::xistringstream xis( "<ns:element xmlns:ns='http://www.example.org'/>" );
    xml::xostringstream xos;
    xos << xis;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<ns:element xmlns:ns=\"http://www.example.org\"/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: writing_prefixed_start_is_valid
// Created: MAT 2010-07-28
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_prefixed_start_is_valid )
{
    xml::xostringstream xos;
    xos << xml::start( "ns:element" );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<ns:element/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: writing_start_filtered_on_namespace_prefixes_it
// Created: MAT 2010-06-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_start_filtered_on_namespace_prefixes_it )
{
    xml::xostringstream xos;
    xos << xml::ns( "http://www.example.org" ) << xml::start( "element" ) << xml::prefix( "http://www.example.org", "ns" );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<ns:element xmlns:ns=\"http://www.example.org\"/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: writing_start_filtered_on_default_namespace_does_not_prefix_it
// Created: MAT 2010-06-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_start_filtered_on_default_namespace_does_not_prefix_it )
{
    xml::xostringstream xos;
    xos << xml::ns( "http://www.example.org" ) << xml::start( "element" );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element xmlns=\"http://www.example.org\"/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: writing_start_filtered_on_no_namespace_does_not_prefix_it
// Created: MAT 2010-07-27
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_start_filtered_on_no_namespace_does_not_prefix_it )
{
    xml::xostringstream xos;
    xos << xml::ns( "" ) << xml::start( "element" );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: writing_prefix_for_non_existing_namespace_adds_prefix_declaration
// Created: MAT 2010-07-27
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_prefix_for_non_existing_namespace_adds_prefix_declaration )
{
    xml::xostringstream xos;
    xos << xml::start( "element" ) << xml::prefix( "http://www.example.org", "ns" );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
        "<element xmlns:ns=\"http://www.example.org\"/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: writing_prefix_for_no_namespace_throws
// Created: MAT 2010-07-27
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_prefix_for_no_namespace_throws )
{
    xml::xostringstream xos;
    xos << xml::start( "element" );
    BOOST_CHECK_THROW( xos << xml::prefix( "", "ns" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: writing_default_prefix_for_no_namespace_throws
// Created: MAT 2010-07-27
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_default_prefix_for_no_namespace_throws )
{
    xml::xostringstream xos;
    xos << xml::start( "element" );
    BOOST_CHECK_THROW( xos << xml::prefix( "", "" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: writing_prefix_for_default_namespace_adds_prefix_declaration
// Created: MAT 2010-07-27
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_prefix_for_default_namespace_adds_prefix_declaration )
{
    xml::xostringstream xos;
    xos << xml::start( "element" )
            << xml::prefix( "http://www.example.org", "" );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element xmlns=\"http://www.example.org\"/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: namespace_is_only_declared_the_first_time_needed
// Created: MAT 2010-06-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( namespace_is_only_declared_the_first_time_needed )
{
    xml::xostringstream xos;
    xos << xml::ns( "http://www.example.org" ) << xml::start( "element" ) << xml::prefix( "http://www.example.org", "ns" )
            << xml::ns( "http://www.example.org" ) << xml::start( "sub-element" )
                << xml::ns( "http://www.example.org" ) << xml::attribute( "attribute", 42 );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<ns:element xmlns:ns=\"http://www.example.org\">\n"
                       "  <ns:sub-element ns:attribute=\"42\"/>\n"
                       "</ns:element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: writing_schemas
// Created: MAT 2010-07-28
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_schemas )
{
    xml::xostringstream xos;
    xos << xml::ns( "http://www.example.org" ) << xml::start( "element" )
            << xml::prefix( "http://www.w3.org/2001/XMLSchema-instance", "xsi" )
            << xml::ns( "http://www.w3.org/2001/XMLSchema-instance" )
                << xml::attribute( "noNamespaceSchemaLocation", "my-schema.xsd" );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element xmlns=\"http://www.example.org\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"my-schema.xsd\"/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: writing_schemas_with_attributes
// Created: MAT 2010-07-28
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_schemas_with_attributes )
{
    xml::xostringstream xos;
    xos << xml::start( "element" )
        << xml::attribute( "xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance" )
            << xml::attribute( "xsi:noNamespaceSchemaLocation", "my-schema.xsd" );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"my-schema.xsd\"/>\n", xos.str() );
}
