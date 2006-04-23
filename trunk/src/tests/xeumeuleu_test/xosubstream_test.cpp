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
// Name: created_sub_stream_starts_from_current_stream_level
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( created_sub_stream_starts_from_current_stream_level )
{
    xml::xostringstream xos;
    xos << xml::start( "element" );
    xml::xosubstream xoss( xos );
    xoss << xml::start( "sub-node" ) << xml::end();
    xos << xml::end();
    const std::string xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                            "<element>\n"
                            "  <sub-node/>\n"
                            "</element>\n";
    BOOST_CHECK_EQUAL( xml, xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_end_at_root_level_throws_an_exception
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_end_at_root_level_throws_an_exception )
{
    xml::xostringstream xos;
    xos << xml::start( "element" );
    xml::xosubstream xoss( xos );
    BOOST_CHECK_THROW( xoss << xml::end(), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_root_element_after_it_has_been_created_in_sub_stream_throws_an_exception
// Created: MCO 2006-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_root_element_after_it_has_been_created_in_sub_stream_throws_an_exception )
{
    xml::xostringstream xos;
    xml::xosubstream xoss( xos );
    xoss << xml::start( "element" );
    BOOST_CHECK_THROW( xos << xml::start( "element" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_a_sub_stream_does_not_modify_original_stream
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_a_sub_stream_does_not_modify_original_stream )
{
    xml::xostringstream xos;
    xos << xml::start( "element" );
    xml::xosubstream xoss( xos );
    xoss << xml::start( "sub-node" );
    BOOST_CHECK_NO_THROW( xos << xml::end() );
    const std::string xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                            "<element>\n"
                            "  <sub-node/>\n"
                            "</element>\n";
    BOOST_CHECK_EQUAL( xml, xos.str() );
}

// -----------------------------------------------------------------------------
// Name: creating_root_element_in_sub_stream_completes_the_stream
// Created: MCO 2006-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_root_element_in_sub_stream_completes_the_stream )
{
    xml::xostringstream xos;
    xml::xosubstream xoss( xos );
    xoss << xml::start( "element" ) << xml::end();
    const std::string xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                            "<element/>\n";
    BOOST_CHECK_EQUAL( xml, xos.str() );
}
