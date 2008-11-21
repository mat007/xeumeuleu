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
// Name: error_from_above_root_throws_exception_without_context
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( error_from_above_root_throws_exception_without_context )
{
    const std::string expected = "this is my message";
    xml::xistringstream xis( "<root/>" );
    try
    {
        xis.error( expected );
    }
    catch( std::exception& e )
    {
        BOOST_CHECK_EQUAL( expected, e.what() );
        return;
    }
    BOOST_FAIL( "should have thrown" );
}

// -----------------------------------------------------------------------------
// Name: error_from_root_throws_exception_with_context_after_tag
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( error_from_root_throws_exception_with_context_after_tag )
{
    const std::string message = "this is my message";
    xml::xistringstream xis( "<root/>" );
    xis >> xml::start( "root" );
    try
    {
        xis.error( message );
    }
    catch( std::exception& e )
    {
        BOOST_CHECK_EQUAL( "string_input (line 1, column 8) : " + message, e.what() );
        return;
    }
    BOOST_FAIL( "should have thrown" );
}

// -----------------------------------------------------------------------------
// Name: error_from_root_throws_exception_with_context_between_opening_and_closing_tag
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( error_from_root_throws_exception_with_context_between_opening_and_closing_tag )
{
    const std::string message = "this is my message";
    xml::xistringstream xis( "<root></root>" );
    xis >> xml::start( "root" );
    try
    {
        xis.error( message );
    }
    catch( std::exception& e )
    {
        BOOST_CHECK_EQUAL( "string_input (line 1, column 7) : " + message, e.what() );
        return;
    }
    BOOST_FAIL( "should have thrown" );
}

// -----------------------------------------------------------------------------
// Name: error_context_is_transmitted_from_an_xistream_to_an_xibufferstream
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( error_context_is_transmitted_from_an_xistream_to_an_xibufferstream )
{
    const std::string message = "this is my message";
    xml::xistringstream xis( "<root/>" );
    xml::xibufferstream xibs( xis );
    xibs >> xml::start( "root" );
    try
    {
        xibs.error( message );
    }
    catch( std::exception& e )
    {
        BOOST_CHECK_EQUAL( "string_input (line 1, column 8) : " + message, e.what() );
        return;
    }
    BOOST_FAIL( "should have thrown" );
}
