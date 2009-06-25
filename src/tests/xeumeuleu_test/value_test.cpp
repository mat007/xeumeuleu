/*
 *   Copyright (c) 2008, Mathieu Champlon
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
// Name: node_content_can_be_read_with_helper
// Created: MCO 2008-01-19
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( node_content_can_be_read_with_helper )
{
    xml::xistringstream xis( "<element>the content</element>");
    xis >> xml::start( "element" );
    BOOST_CHECK_EQUAL( "the content", xml::value< std::string >( xis ) );
}

// -----------------------------------------------------------------------------
// Name: empty_node_content_read_with_helper_throws
// Created: MCO 2008-01-19
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( empty_node_content_read_with_helper_throws )
{
    xml::xistringstream xis( "<element/>");
    xis >> xml::start( "element" );
    BOOST_CHECK_THROW( xml::value< std::string >( xis ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: empty_node_content_read_with_helper_throws
// Created: MCO 2008-01-19
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( empty_node_content_read_with_helper_and_default_value_returns_default_value )
{
    xml::xistringstream xis( "<element/>");
    xis >> xml::start( "element" );
    BOOST_CHECK_EQUAL( "the content", xml::value< std::string >( xis, "the content" ) );
}
