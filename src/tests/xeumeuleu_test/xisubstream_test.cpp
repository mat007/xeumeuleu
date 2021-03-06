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
// Name: created_input_sub_stream_starts_from_current_stream_level
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( created_input_sub_stream_starts_from_current_stream_level )
{
    const std::string xml = "<element>"
                            "  <sub-node/>"
                            "</element>";
    xml::xistringstream xis( xml );
    xis >> xml::start( "element" );
    xml::xisubstream xiss( xis );
    BOOST_CHECK_NO_THROW( xiss >> xml::start( "sub-node" ) );
}

// -----------------------------------------------------------------------------
// Name: streaming_end_right_after_creating_a_sub_stream_throws_an_exception
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_end_right_after_creating_a_sub_stream_throws_an_exception )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" );
    xml::xisubstream xiss( xis );
    BOOST_CHECK_THROW( xiss >> xml::end, xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_a_sub_stream_does_not_modify_original_input_stream
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_a_sub_stream_does_not_modify_original_input_stream )
{
    xml::xistringstream xis( "<element/>" );
    xml::xisubstream xiss( xis );
    xiss >> xml::start( "element" );
    BOOST_CHECK_NO_THROW( xis >> xml::start( "element" ) );
}

// -----------------------------------------------------------------------------
// Name: sub_stream_created_after_optional_does_not_reset_optional
// Created: MCO 2006-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( sub_stream_created_after_optional_does_not_reset_optional )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" ) >> xml::optional;
    xml::xisubstream xiss( xis );
    BOOST_CHECK_NO_THROW( xis >> xml::start( "non-existing" ) );
}

// -----------------------------------------------------------------------------
// Name: sub_stream_created_after_optional_is_still_optional
// Created: MCO 2006-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( sub_stream_created_after_optional_is_still_optional )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" ) >> xml::optional;
    xml::xisubstream xiss( xis );
    BOOST_CHECK_NO_THROW( xiss >> xml::start( "non-existing" ) );
}

// -----------------------------------------------------------------------------
// Name: sub_stream_created_after_non_existing_optional_element_is_still_optional
// Created: MCO 2009-10-11
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( sub_stream_created_after_non_existing_optional_element_is_still_optional )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" ) >> xml::optional >> xml::start( "non-existing" );
    xml::xisubstream xiss( xis );
    BOOST_CHECK_NO_THROW( xiss >> xml::start( "another-non-existing" ) );
}

// -----------------------------------------------------------------------------
// Name: sub_stream_created_on_optional_non_existing_branch_does_not_reset_optional
// Created: MCO 2006-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( sub_stream_created_on_optional_non_existing_branch_does_not_reset_optional )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" ) >> xml::optional >> xml::start( "non-existing" );
    xml::xisubstream xiss( xis );
    BOOST_CHECK_NO_THROW( xis >> xml::start( "another-non-existing" ) );
}

// -----------------------------------------------------------------------------
// Name: sub_stream_created_after_optional_throws_when_moving_up_from_root
// Created: MCO 2008-05-25
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( sub_stream_created_after_optional_throws_when_moving_up_from_root )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" ) >> xml::optional >> xml::start( "non-existing" );
    xml::xisubstream xiss( xis );
    BOOST_CHECK_THROW( xiss >> xml::end, xml::exception );
}

// -----------------------------------------------------------------------------
// Name: sub_stream_created_after_optional_does_not_modify_original_stream
// Created: MCO 2009-10-26
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( sub_stream_created_after_optional_does_not_modify_original_stream )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::optional >> xml::start( "non-existing" );
    xml::xisubstream xiss( xis );
    xiss >> xml::start( "non-existing" ) >> xml::end;
    BOOST_CHECK_NO_THROW( xis >> xml::end );
}

// -----------------------------------------------------------------------------
// Name: creating_sub_stream_on_sub_stream_is_valid
// Created: MCO 2006-11-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_sub_stream_on_sub_stream_is_valid )
{
    xml::xistringstream xis( "<element/>" );
    xml::xisubstream xiss( xis );
    xml::xisubstream xisss( xiss );
    BOOST_CHECK_NO_THROW( xisss >> xml::start( "element" ) );
}

// -----------------------------------------------------------------------------
// Name: sub_input_stream_creates_a_mutable_temporary
// Created: MCO 2009-06-18
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( sub_input_stream_creates_a_mutable_temporary )
{
    xml::xistringstream xis( "<element attribute='my-attribute'/>" );
    std::string value;
    xml::xisubstream( xis ) >> xml::start( "element" ) >> xml::attribute( "attribute", value );
    BOOST_CHECK_EQUAL( "my-attribute", value );
}
