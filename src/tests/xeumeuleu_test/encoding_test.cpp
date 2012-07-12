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
#include <boost/assign/list_of.hpp>

// -----------------------------------------------------------------------------
// Name: creating_an_input_stream_with_invalid_encoding_throws
// Created: MCO 2010-09-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_an_input_stream_with_invalid_encoding_throws )
{
    BOOST_CHECK_THROW( xml::xistringstream( "<element/>", xml::encoding( "invalid_encoding" ) ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_an_output_stream_with_invalid_encoding_throws
// Created: MCO 2010-09-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_an_output_stream_with_invalid_encoding_throws )
{
    BOOST_TODO;
    //BOOST_CHECK_THROW( xml::xostringstream( xml::encoding( "invalid_encoding" ) ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: forcing_encoding_upon_read_overrides_prolog_encoding
// Created: MCO 2010-09-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( forcing_encoding_upon_read_overrides_prolog_encoding )
{
    BOOST_CHECK_THROW( xml::xistringstream( "<?xml version='1.0' encoding='UTF-16' standalone='no' ?>"
                                            "<element/>" ), xml::exception );
    BOOST_CHECK_NO_THROW( xml::xistringstream( "<?xml version='1.0' encoding='UTF-16' standalone='no' ?>"
                                               "<element/>", xml::encoding( "UTF-8" ) ) );
}

// -----------------------------------------------------------------------------
// Name: forcing_encoding_upon_write_overrides_prolog_encoding
// Created: MCO 2010-09-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( forcing_encoding_upon_write_overrides_prolog_encoding )
{
    xml::xostringstream xos1( xml::encoding( "UTF-8" ) );
    xos1 << xml::start( "element" );
    xml::xostringstream xos2( xml::encoding( "UTF-16" ) );
    xos2 << xml::start( "element" );
    BOOST_CHECK_NE( xos1.str(), xos2.str() );
}

// -----------------------------------------------------------------------------
// Name: reading_data_in_arabic_preserves_utf_8_characters
// Created: MCO 2012-07-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_data_in_arabic_preserves_utf_8_characters )
{
    xml::xifstream xis( BOOST_RESOLVE( "arabic.xml" ) );
    std::string name;
    xis >> xml::start( "resource" );
    xis >> xml::attribute( "name", name );
    std::vector< char > v = boost::assign::list_of
        ( -40 )( -89 )( -39 )( -124 )( -40 )( -71 )( -40 )
        ( -79 )( -40 )( -88 )( -39 )( -118 )( -40 )( -87 );
    BOOST_CHECK_EQUAL_COLLECTIONS( v.begin(), v.end(), name.begin(), name.end() );
}
