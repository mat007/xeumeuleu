/*
 *   Copyright (c) 2007, Mathieu Champlon
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
// Name: reading_from_an_ximultistream_reads_from_first_stream
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_from_an_ximultistream_reads_from_first_stream )
{
    xml::xistringstream xis1( "<root-1/>" );
    xml::xistringstream xis2( "<root-2/>" );
    xml::ximultistream xis( xis1, xis2 );
    BOOST_CHECK_NO_THROW( xis >> xml::start( "root-1" ) );
}

// -----------------------------------------------------------------------------
// Name: reading_from_an_ximultistream_reads_from_second_stream
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_from_an_ximultistream_reads_from_second_stream )
{
    xml::xistringstream xis1( "<root-1/>" );
    xml::xistringstream xis2( "<root-2/>" );
    xml::ximultistream xis( xis1, xis2 );
    BOOST_CHECK_NO_THROW( xis >> xml::start( "root-2" ) );
}

// -----------------------------------------------------------------------------
// Name: reading_from_an_ximultistream_a_non_existing_node_throws
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_from_an_ximultistream_a_non_existing_node_throws )
{
    xml::xistringstream xis1( "<root-1/>" );
    xml::xistringstream xis2( "<root-2/>" );
    xml::ximultistream xis( xis1, xis2 );
    BOOST_CHECK_THROW( xis >> xml::start( "non-existing-node" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: reading_from_an_ximultistream_reads_attribute_from_first_stream
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_from_an_ximultistream_reads_attribute_from_first_stream )
{
    xml::xistringstream xis1( "<root attribute='stream-1'/>" );
    xml::xistringstream xis2( "<root/>" );
    xml::ximultistream xis( xis1, xis2 );
    xis >> xml::start( "root" );
    BOOST_CHECK_EQUAL( "stream-1", xis.attribute< std::string >( "attribute" ) );
}

// -----------------------------------------------------------------------------
// Name: reading_from_an_ximultistream_reads_attribute_from_second_stream
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_from_an_ximultistream_reads_attribute_from_second_stream )
{
    xml::xistringstream xis1( "<root/>" );
    xml::xistringstream xis2( "<root attribute='stream-2'/>" );
    xml::ximultistream xis( xis1, xis2 );
    xis >> xml::start( "root" );
    BOOST_CHECK_EQUAL( "stream-2", xis.attribute< std::string >( "attribute" ) );
}

// -----------------------------------------------------------------------------
// Name: reading_from_an_ximultistream_reads_attribute_with_first_stream_precedence
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_from_an_ximultistream_reads_attribute_with_first_stream_precedence )
{
    xml::xistringstream xis1( "<root attribute='stream-1'/>" );
    xml::xistringstream xis2( "<root attribute='stream-2'/>" );
    xml::ximultistream xis( xis1, xis2 );
    xis >> xml::start( "root" );
    BOOST_CHECK_EQUAL( "stream-1", xis.attribute< std::string >( "attribute" ) );
}

// -----------------------------------------------------------------------------
// Name: reading_from_an_ximultistream_a_non_existing_attribute_throws
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_from_an_ximultistream_a_non_existing_attribute_throws )
{
    xml::xistringstream xis1( "<root/>" );
    xml::xistringstream xis2( "<root/>" );
    xml::ximultistream xis( xis1, xis2 );
    xis >> xml::start( "root" );
    BOOST_CHECK_THROW( xis.attribute< std::string >( "attribute" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: reading_from_an_ximultistream_a_non_existing_attribute_from_existing_branch_throws
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_from_an_ximultistream_a_non_existing_attribute_from_existing_branch_throws )
{
    xml::xistringstream xis1( "<root-1/>" );
    xml::xistringstream xis2( "<root-2/>" );
    xml::ximultistream xis( xis1, xis2 );
    xis >> xml::start( "root-1" );
    BOOST_CHECK_THROW( xis.attribute< std::string >( "attribute" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: reading_from_an_ximultistream_from_first_branch_then_second_branch_is_transparent
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_from_an_ximultistream_from_first_branch_then_second_branch_is_transparent )
{
    xml::xistringstream xis1( "<root-1 attribute-1='stream-1'/>" );
    xml::xistringstream xis2( "<root-2 attribute-2='stream-2'/>" );
    xml::ximultistream xis( xis1, xis2 );
    std::string actual1, actual2;
    xis >> xml::start( "root-1" )
            >> xml::attribute( "attribute-1", actual1 )
        >> xml::end
        >> xml::start( "root-2" )
            >> xml::attribute( "attribute-2", actual2 );
    BOOST_CHECK_EQUAL( "stream-1", actual1 );
    BOOST_CHECK_EQUAL( "stream-2", actual2 );
}

// -----------------------------------------------------------------------------
// Name: reading_from_an_ximultistream_from_second_branch_does_not_change_stream_precedence
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_from_an_ximultistream_from_second_branch_does_not_change_stream_precedence )
{
    xml::xistringstream xis1( "<root attribute='stream-1'/>" );
    xml::xistringstream xis2( "<root attribute='stream-2'><element/></root>" );
    xml::ximultistream xis( xis1, xis2 );
    xis >> xml::start( "root" )
            >> xml::start( "element" )
            >> xml::end;
    BOOST_CHECK_EQUAL( "stream-1", xis.attribute< std::string >( "attribute" ) );
}

// -----------------------------------------------------------------------------
// Name: an_ximultistream_can_be_wrapped_by_an_xisubstream
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( an_ximultistream_can_be_wrapped_by_an_xisubstream )
{
    xml::xistringstream xis1( "<root-1 attribute='stream-1'/>" );
    xml::xistringstream xis2( "<root-2 attribute='stream-2'/>" );
    xml::ximultistream xis( xis1, xis2 );
    {
        xml::xisubstream xiss( xis );
        xiss >> xml::start( "root-2" );
    }
    xis >> xml::start( "root-1" );
    BOOST_CHECK_EQUAL( "stream-1", xis.attribute< std::string >( "attribute" ) );
}

// -----------------------------------------------------------------------------
// Name: an_ximultistream_can_be_wrapped_by_another_ximultistream
// Created: MAT 2008-04-25
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( an_ximultistream_can_be_wrapped_by_another_ximultistream )
{
    xml::xistringstream xis1( "<root-1 attribute='stream-1'/>" );
    xml::xistringstream xis2( "<root-2 attribute='stream-2'/>" );
    xml::xistringstream xis3( "<root-3 attribute='stream-3'/>" );
    xml::ximultistream xims( xis1, xis2 );
    xml::ximultistream xis( xims, xis3 );
    std::string actual1, actual2, actual3;
    xis >> xml::start( "root-1" )
            >> xml::attribute( "attribute", actual1 )
        >> xml::end
        >> xml::start( "root-2" )
            >> xml::attribute( "attribute", actual2 )
        >> xml::end
        >> xml::start( "root-3" )
            >> xml::attribute( "attribute", actual3 );
    BOOST_CHECK_EQUAL( "stream-1", actual1 );
    BOOST_CHECK_EQUAL( "stream-2", actual2 );
    BOOST_CHECK_EQUAL( "stream-3", actual3 );
}

// -----------------------------------------------------------------------------
// Name: serializing_an_ximultistream_into_an_xostream_at_root_level_throws
// Created: MAT 2008-11-22
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( serializing_an_ximultistream_into_an_xostream_at_root_level_merges_attributes )
{
    xml::xistringstream xis1( "<root/>" );
    xml::xistringstream xis2( "<root/>" );
    xml::ximultistream xims( xis1, xis2 );
    xml::xostringstream xos;
    BOOST_CHECK_THROW( xos << xims, xml::exception );
}

// -----------------------------------------------------------------------------
// Name: serializing_an_ximultistream_into_an_xostream_adds_both_stream_contents
// Created: MAT 2008-11-22
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( serializing_an_ximultistream_into_an_xostream_adds_both_stream_contents )
{
    xml::xistringstream xis1( "<root-1/>" );
    xml::xistringstream xis2( "<root-2/>" );
    xml::ximultistream xims( xis1, xis2 );
    xml::xostringstream xos;
    xos << xml::start( "root" )
            << xims
        << xml::end;
    xml::xistringstream xis( xos.str() );
    xis >> xml::start( "root" )
            >> xml::start( "root-1" )
            >> xml::end
            >> xml::start( "root-2" );
}

// -----------------------------------------------------------------------------
// Name: an_ximultistream_can_be_buffered_by_an_xibufferstream
// Created: MAT 2008-05-17
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( an_ximultistream_can_be_buffered_by_an_xibufferstream )
{
    xml::xistringstream xis1( "<root-1 attribute='stream-1'/>" );
    xml::xistringstream xis2( "<root-2 attribute='stream-2'/>" );
    xml::ximultistream xis( xis1, xis2 );
    xml::xibufferstream xibs( xis );
    std::string actual1, actual2;
    xibs >> xml::start( "root-1" )
             >> xml::attribute( "attribute", actual1 )
         >> xml::end
         >> xml::start( "root-2" )
             >> xml::attribute( "attribute", actual2 );
    BOOST_CHECK_EQUAL( "stream-1", actual1 );
    BOOST_CHECK_EQUAL( "stream-2", actual2 );
}

// -----------------------------------------------------------------------------
// Name: an_optional_attribute_not_found_in_first_stream_falls_back_to_the_second_stream
// Created: MAT 2008-05-17
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( an_optional_attribute_not_found_in_first_stream_falls_back_to_the_second_stream )
{
    xml::xistringstream xis1( "<root/>" );
    xml::xistringstream xis2( "<root attribute='stream-2'/>" );
    xml::ximultistream xis( xis1, xis2 );
    xml::xibufferstream xibs( xis );
    std::string actual = "stream-1";
    xibs >> xml::start( "root" )
            >> xml::optional >>xml::attribute( "attribute", actual );
    BOOST_CHECK_EQUAL( "stream-2", actual );
}

// -----------------------------------------------------------------------------
// Name: an_optional_attribute_not_found_in_either_stream_is_valid
// Created: MAT 2008-05-17
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( an_optional_attribute_not_found_in_either_stream_is_valid )
{
    xml::xistringstream xis1( "<root/>" );
    xml::xistringstream xis2( "<root/>" );
    xml::ximultistream xis( xis1, xis2 );
    xml::xibufferstream xibs( xis );
    std::string actual = "no attribute";
    xibs >> xml::start( "root" )
            >> xml::optional >>xml::attribute( "attribute", actual );
    BOOST_CHECK_EQUAL( "no attribute", actual );
}

// -----------------------------------------------------------------------------
// Name: an_optional_attribute_not_found_in_an_optional_sub_node_of_either_stream_is_valid
// Created: MCO 2009-05-31
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( an_optional_attribute_not_found_in_an_optional_sub_node_of_either_stream_is_valid )
{
    xml::xistringstream xis1( "<root>"
                              "  <sub-node/>"
                              "</root>" );
    xml::xistringstream xis2( "<root/>" );
    xml::ximultistream xis( xis1, xis2 );
    std::string attribute;
    xis >> xml::start( "root" )
            >> xml::optional >> xml::start( "sub-node" )
                >> xml::optional >> xml::attribute( "non-existing-attribute", attribute );
}
