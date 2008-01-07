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
#include "xeumeuleu/xml.h"

using namespace mockpp;

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
    BOOST_CHECK_EQUAL( "stream-1", xml::attribute< std::string >( xis, "attribute" ) );
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
    BOOST_CHECK_EQUAL( "stream-2", xml::attribute< std::string >( xis, "attribute" ) );
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
    BOOST_CHECK_EQUAL( "stream-1", xml::attribute< std::string >( xis, "attribute" ) );
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
    BOOST_CHECK_THROW( xml::attribute< std::string >( xis, "attribute" ), xml::exception );
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
    BOOST_CHECK_THROW( xml::attribute< std::string >( xis, "attribute" ), xml::exception );
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
    std::string value1, value2;
    xis >> xml::start( "root-1" )
            >> xml::attribute( "attribute-1", value1 )
        >> xml::end()
        >> xml::start( "root-2" )
            >> xml::attribute( "attribute-2", value2 )
        >> xml::end();
    BOOST_CHECK_EQUAL( "stream-1", value1 );
    BOOST_CHECK_EQUAL( "stream-2", value2 );
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
            >> xml::end();
    BOOST_CHECK_EQUAL( "stream-1", xml::attribute< std::string >( xis, "attribute" ) );
}

// -----------------------------------------------------------------------------
// Name: an_ximultistring_can_be_wrapped_by_an_xisubstream
// Created: MAT 2008-01-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( an_ximultistring_can_be_wrapped_by_an_xisubstream )
{
    xml::xistringstream xis1( "<root-1 attribute='stream-1'/>" );
    xml::xistringstream xis2( "<root-2 attribute='stream-2'/>" );
    xml::ximultistream xis( xis1, xis2 );
    {
        xml::xisubstream xiss( xis );
        xiss >> xml::start( "root-2" );
    }
    xis >> xml::start( "root-1" );
    BOOST_CHECK_EQUAL( "stream-1", xml::attribute< std::string >( xis, "attribute" ) );
}
