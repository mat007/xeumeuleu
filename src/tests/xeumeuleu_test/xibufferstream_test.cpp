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
// Name: created_buffer_stream_starts_from_current_stream_level
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( created_buffer_stream_starts_from_current_stream_level )
{
    xml::xistringstream xis( "<element>"
                             "  <sub-node/>"
                             "</element>" );
    xis >> xml::start( "element" );
    xml::xibufferstream xiss( xis );
    BOOST_CHECK_NO_THROW( xiss >> xml::start( "sub-node" ) );
}

// -----------------------------------------------------------------------------
// Name: streaming_end_right_after_creating_a_buffer_stream_throws_an_exception
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_end_right_after_creating_a_buffer_stream_throws_an_exception )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" );
    xml::xibufferstream xiss( xis );
    BOOST_CHECK_THROW( xiss >> xml::end, xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_a_buffer_stream_does_not_modify_original_stream
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_a_buffer_stream_does_not_modify_original_stream )
{
    xml::xistringstream xis( "<element/>" );
    xml::xibufferstream xiss( xis );
    xiss >> xml::start( "element" );
    BOOST_CHECK_NO_THROW( xis >> xml::start( "element" ) );
}

// -----------------------------------------------------------------------------
// Name: creating_buffer_stream_created_after_optional_does_not_reset_optional
// Created: MCO 2006-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_buffer_stream_created_after_optional_does_not_reset_optional )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" ) >> xml::optional;
    xml::xibufferstream xiss( xis );
    BOOST_CHECK_NO_THROW( xis >> xml::start( "non-existing" ) );
}

// -----------------------------------------------------------------------------
// Name: buffer_stream_created_after_optional_is_not_optional
// Created: MCO 2006-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( buffer_stream_created_after_optional_is_not_optional )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" ) >> xml::optional;
    xml::xibufferstream xiss( xis );
    BOOST_CHECK_THROW( xiss >> xml::start( "non-existing" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_buffer_stream_on_optional_non_existing_branch_is_valid_and_does_not_reset_optional
// Created: MCO 2006-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_buffer_stream_on_optional_non_existing_branch_is_valid_and_does_not_reset_optional )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" ) >> xml::optional >> xml::start( "non-existing" );
    xml::xibufferstream xiss( xis );
    BOOST_CHECK_NO_THROW( xis >> xml::start( "another-non-existing" ) );
}

// -----------------------------------------------------------------------------
// Name: creating_buffer_stream_on_buffer_stream_is_valid
// Created: MCO 2006-11-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_buffer_stream_on_buffer_stream_is_valid )
{
    xml::xistringstream xis( "<element/>" );
    xml::xibufferstream xiss( xis );
    xml::xibufferstream xisss( xiss );
    BOOST_CHECK_NO_THROW( xisss >> xml::start( "element" ) );
}
