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
// Name: root_has_context
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( root_has_context )
{
    xml::xistringstream xis( "<root/>" );
    BOOST_CHECK_EQUAL( "string_input (line 0, column 0) : ", xis.context() );
}

// -----------------------------------------------------------------------------
// Name: root_child_node_has_context
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( root_child_node_has_context )
{
    xml::xistringstream xis( "<root/>" );
    xis >> xml::start( "root" );
    BOOST_CHECK_EQUAL( "string_input (line 1, column 8) : ", xis.context() );
}

// -----------------------------------------------------------------------------
// Name: root_child_node_has_context_between_opening_and_closing_tag
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( root_child_node_has_context_between_opening_and_closing_tag )
{
    xml::xistringstream xis( "<root></root>" );
    xis >> xml::start( "root" );
    BOOST_CHECK_EQUAL( "string_input (line 1, column 7) : ", xis.context() );
}

// -----------------------------------------------------------------------------
// Name: context_is_transmitted_from_an_xistream_to_an_xisubstream_created_on_optional_non_existing_branch
// Created: MCO 2008-05-25
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( context_is_transmitted_from_an_xistream_to_an_xisubstream_created_on_optional_non_existing_branch )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" ) >> xml::optional >> xml::start( "non-existing" );
    xml::xisubstream xiss( xis );
    BOOST_CHECK_EQUAL( xiss.context(), "string_input (line 1, column 11) : " );
}

// -----------------------------------------------------------------------------
// Name: context_is_transmitted_from_an_xistream_to_an_xibufferstream
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( context_is_transmitted_from_an_xistream_to_an_xibufferstream )
{
    xml::xistringstream xis( "<root/>" );
    xml::xibufferstream xibs( xis );
    xibs >> xml::start( "root" );
    BOOST_CHECK_EQUAL( "string_input (line 1, column 8) : ", xibs.context() );
}

// -----------------------------------------------------------------------------
// Name: context_is_transmitted_from_an_xistream_to_an_xobufferstream
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( context_is_transmitted_from_an_xistream_to_an_xobufferstream )
{
    const std::string message = "this is my message";
    xml::xistringstream xis( "<root/>" );
    xml::xobufferstream xobs;
    xobs << xis;
    xobs >> xml::start( "root" );
    BOOST_CHECK_EQUAL( "string_input (line 1, column 8) : ", xobs.context() );
}

// -----------------------------------------------------------------------------
// Name: context_is_transmitted_from_an_xistream_to_an_xobufferstream_created_on_optional_non_existing_branch
// Created: MCO 2009-11-16
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( context_is_transmitted_from_an_xistream_to_an_xobufferstream_created_on_optional_non_existing_branch )
{
    std::auto_ptr< xml::xibufferstream > xibs;
    {
        xml::xistringstream xis( "<root/>" );
        xis >> xml::start( "root" ) >> xml::optional >> xml::start( "non-existing" );
        xibs.reset( new xml::xibufferstream( xis ) );
    }
    BOOST_CHECK_EQUAL( "string_input (line 1, column 8) : ", xibs->context() );
}

// -----------------------------------------------------------------------------
// Name: the_context_of_an_ximultistream_refers_to_contexts_of_both_streams
// Created: MAT 2009-06-27
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( the_context_of_an_ximultistream_refers_to_contexts_of_both_streams )
{
    xml::xistringstream xis1( "<root/>" );
    xml::xistringstream xis2( "<root/>" );
    xml::ximultistream xis( xis1, xis2 );
    xis >> xml::start( "root" );
    BOOST_CHECK_EQUAL( "string_input (line 1, column 8) : string_input (line 1, column 8) : ", xis.context() );
}

// -----------------------------------------------------------------------------
// Name: the_context_of_an_xistringstream_can_be_customized
// Created: MAT 2014-12-04
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( the_context_of_an_xistringstream_can_be_customized )
{
    xml::xistringstream xis( "<root/>", xml::null_grammar(), xml::id( "custom id" ) );
    xis >> xml::start( "root" );
    BOOST_CHECK_EQUAL( "custom id (line 1, column 8) : ", xis.context() );
}
