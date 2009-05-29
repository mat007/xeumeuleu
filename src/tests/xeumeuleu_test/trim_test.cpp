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
#include <xeumeuleu/bridges/xerces/detail/trim.hpp>

// -----------------------------------------------------------------------------
// Name: triming_empty_string_is_no_op
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( triming_empty_string_is_no_op )
{
    BOOST_CHECK_EQUAL( "", xml::trim( "" ) );
}

// -----------------------------------------------------------------------------
// Name: triming_removes_white_spaces_on_both_sides
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( triming_removes_white_spaces_on_both_sides )
{
    BOOST_CHECK_EQUAL( "this is a string", xml::trim( "   this is a string   " ) );
}

// -----------------------------------------------------------------------------
// Name: triming_removes_carriage_returns_and_line_feeds_on_both_sides
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( triming_removes_carriage_returns_and_line_feeds_on_both_sides )
{
    BOOST_CHECK_EQUAL( "this is\r a\n string", xml::trim( "\r\nthis is\r a\n string\r\n" ) );
}

// -----------------------------------------------------------------------------
// Name: triming_removes_tabulations_on_both_sides
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( triming_removes_tabulations_on_both_sides )
{
    BOOST_CHECK_EQUAL( "this is\t a string", xml::trim( "\t\tthis is\t a string\t" ) );
}
