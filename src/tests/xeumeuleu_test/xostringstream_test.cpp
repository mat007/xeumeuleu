// *****************************************************************************
//
// This file is part of a MASA library or program.
// Refer to the included end-user license agreement for restrictions.
//
// Copyright (c) 2005 Mathématiques Appliquées SA (MASA)
//
// *****************************************************************************

#include "xeumeuleu_test_pch.h"
#include "xeumeuleu/xml.h"

using namespace mockpp;

// -----------------------------------------------------------------------------
// Name: creating_empty_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_empty_document )
{
    xml::xostringstream xos;
    BOOST_CHECK_EQUAL( "", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_root_element_makes_a_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_root_element_makes_a_valid_document )
{
    xml::xostringstream xos;
    xos << xml::start( "element" ) << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_root_element_twice_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_root_element_twice_throws_an_exception )
{
    xml::xostringstream xos;
    xos << xml::start( "element" ) << xml::end();
    BOOST_CHECK_THROW( xos << xml::start( "another_element" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: streaming_child_element_makes_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_child_element_makes_a_valid_document )
{
    xml::xostringstream xos;
    xos << xml::start( "element" ) << xml::start( "child" ) << xml::end() << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <child/>\n"
                       "</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_end_at_root_level_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_end_at_root_level_throws_an_exception )
{
    xml::xostringstream xos;
    BOOST_CHECK_THROW( xos << xml::end(), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: streaming_value_at_root_level_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_value_at_root_level_throws_an_exception )
{
    xml::xostringstream xos;
    BOOST_CHECK_THROW( xos << " this is the content ", xml::exception );
}

// -----------------------------------------------------------------------------
// Name: streaming_text_node_value_mixed_with_sub_node
// Created: MCO 2006-10-16
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_text_node_value_mixed_with_sub_node )
{
    BOOST_TODO; // $$$$ MAT 2006-10-16: of course this test fails as we format the output : should it be considered a bug or a feature ?
//    xml::xostringstream xos;
//    xos << xml::start( "element" ) << " \n text node content " << xml::start( "child" ) << xml::end() << xml::end();
//    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
//                       "<element> \n text node content "
//                       "<child/>\n"
//                       "</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: creating_a_stream_with_invalid_encoding_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_a_stream_with_invalid_encoding_throws_an_exception )
{
    BOOST_TODO; // $$$$ MAT 2006-01-09: not as easy as it seems
//    BOOST_CHECK_THROW( xml::xostringstream( "invalid_encoding" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: streaming_extended_character_into_ISO_8859_1_makes_a_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_extended_character_into_ISO_8859_1_makes_a_valid_document )
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
BOOST_AUTO_UNIT_TEST( streaming_extended_character_into_UTF_16_makes_a_valid_document )
{
    BOOST_TODO; // $$$$ MAT 2006-04-23: must think about adding support for std::wstring ?
//    xml::xowstringstream xos( "UTF-16" );
//    xos << xml::content( "element", "ça c'est sûr !" );
//    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-16\" standalone=\"no\" ?>\n"
//                       "<element>ça c'est sûr !</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_extended_character_into_UTF_8_makes_a_valid_document
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_extended_character_into_UTF_8_makes_a_valid_document )
{
    xml::xostringstream xos( xml::encoding( "UTF-8" ) );
    xos << xml::content( "element", "ça c'est sûr !" );
    const std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                                 "<element>ça c'est sûr !</element>\n";
    xml::xistringstream xis( xos.str() );
    std::string value;
    xis >> xml::content( "element", value );
    BOOST_CHECK_EQUAL( "ça c'est sûr !", value );
}
