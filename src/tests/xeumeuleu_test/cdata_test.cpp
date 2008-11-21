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
#include "xeumeuleu/xml.h"

using namespace mockpp;

// -----------------------------------------------------------------------------
// Name: streaming_cdata_creates_output_with_cdata_content
// Created: MCO 2007-03-14
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_cdata_creates_output_with_cdata_section )
{
    xml::xostringstream xos;
    xos << xml::start( "element" )
            << xml::cdata( "<<<" )
        << xml::end;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <![CDATA[<<<]]>\n"
                       "</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_cdata_creates_output_with_cdata_content
// Created: MCO 2007-03-14
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_cdata_content_creates_output_with_cdata_section )
{
    xml::xostringstream xos;
    xos << xml::content( "element", xml::cdata( "<<<" ) );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <![CDATA[<<<]]>\n"
                       "</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_cdata_creates_output_with_cdata_content_on_level_two
// Created: MCO 2007-03-16
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_cdata_creates_output_with_cdata_content_on_level_two )
{
    xml::xostringstream xos;
    xos << xml::start( "root" )
            << xml::content( "element", xml::cdata( "<<<" ) )
        << xml::end;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<root>\n"
                       "  <element>\n"
                       "    <![CDATA[<<<]]>\n"
                       "  </element>\n"
                       "</root>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: reading_cdata_provides_valid_content
// Created: MCO 2007-03-14
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_cdata_provides_valid_text )
{
    std::string content;
    xml::xistringstream xis( "<element><![CDATA[<<<]]></element>");
    xis >> xml::start( "element" )
            >> content;
    BOOST_CHECK_EQUAL( "<<<", content );
}

// -----------------------------------------------------------------------------
// Name: reading_formatted_cdata_provides_valid_text
// Created: MCO 2007-03-14
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_formatted_cdata_provides_valid_text )
{
    std::string content;
    xml::xistringstream xis( "<element>\n"
                             "  <![CDATA[<<<]]>"
                             "</element>");
    xis >> xml::start( "element" )
            >> content;
    BOOST_CHECK_EQUAL( "<<<", content );
}
