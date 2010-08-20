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
// Name: creating_an_UTF_8_stream_with_non_UTF_8_characters_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_an_UTF_8_stream_with_non_UTF_8_characters_throws_an_exception )
{
    BOOST_CHECK_THROW( xml::xistringstream( "<?xml version='1.0' encoding='UTF-8' standalone='no' ?>"
                                            "<element>ça c'est sûr !</element>" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_an_UTF_16_stream_with_extended_characters_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_an_UTF_16_stream_with_extended_characters_throws_an_exception )
{
    BOOST_CHECK_THROW( xml::xistringstream( "<?xml version='1.0' encoding='UTF-16' standalone='no' ?>"
                                            "<element>ça c'est sûr !</element>" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_an_ISO_8859_1_stream_with_extended_characters_does_not_throw_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_an_ISO_8859_1_stream_with_extended_characters_does_not_throw_an_exception )
{
    xml::xistringstream xis( "<?xml version='1.0' encoding='ISO-8859-1' standalone='no' ?>"
                             "<element>ça c'est sûr !</element>" );
    std::string value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( "ça c'est sûr !", value );
}

// -----------------------------------------------------------------------------
// Name: forcing_encoding_to_ISO_8859_1_allows_to_read_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( forcing_encoding_to_ISO_8859_1_allows_to_read_content )
{
    xml::xistringstream xis( "<element>ça c'est sûr !</element>", xml::encoding( "ISO-8859-1" ) );
    std::string value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( "ça c'est sûr !", value );
}

// -----------------------------------------------------------------------------
// Name: forcing_encoding_to_ISO_8859_1_whereas_UTF_8_is_specified_in_document_allows_to_read_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( forcing_encoding_to_ISO_8859_1_whereas_UTF_8_is_specified_in_document_allows_to_read_content )
{
    xml::xistringstream xis( "<?xml version='1.0' encoding='UTF-8' standalone='no' ?>"
                             "<element>ça c'est sûr !</element>", xml::encoding( "ISO-8859-1" ) );
    std::string value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( "ça c'est sûr !", value );
}

// -----------------------------------------------------------------------------
// Name: creating_a_stream_with_invalid_encoding_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_a_stream_with_invalid_encoding_throws_an_exception )
{
    BOOST_TODO; // $$$$ MAT 2006-01-09: not as easy as it seems
//    BOOST_CHECK_THROW( xml::xostringstream( "invalid_encoding" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: streaming_extended_character_into_ISO_8859_1_makes_a_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_extended_character_into_ISO_8859_1_makes_a_valid_document )
{
    // warning : boost logs by streaming into std::ostream therefore the message can be malformed
    xml::xostringstream xos( xml::encoding( "ISO-8859-1" ) );
    xos << xml::content( "element", "ça c'est sûr !" );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" standalone=\"no\" ?>\n"
                       "<element>ça c'est sûr !</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_extended_character_into_UTF_16_makes_a_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_extended_character_into_UTF_16_makes_a_valid_document )
{
    BOOST_TODO; // $$$$ MAT 2006-04-23: must think about adding support for std::wstring ?
//    xml::xowstringstream xos( xml::encoding( "UTF-16" ) );
//    xos << xml::content( "element", "ça c'est sûr !" );
//    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-16\" standalone=\"no\" ?>\n"
//                       "<element>ça c'est sûr !</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_extended_character_into_UTF_8_makes_a_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_extended_character_into_UTF_8_makes_a_valid_document )
{
    const std::string content( "ça c'est sûr !" );
    xml::xostringstream xos( xml::encoding( "UTF-8" ) );
    xos << xml::content( "element", content );
    xml::xistringstream xis( xos.str() );
    std::string value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( content, value );
}
