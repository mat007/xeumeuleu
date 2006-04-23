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
// Name: empty_sub_stream_does_not_modify_stream
// Created: MCO 2006-03-07
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( empty_sub_stream_does_not_modify_stream )
{
    xml::xobufferstream xobs;
    xml::xostringstream xos;
    xos << xml::start( "element" ) << xobs << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: element_in_sub_stream_is_inserted_in_stream
// Created: MCO 2006-03-07
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( element_in_sub_stream_is_inserted_in_stream )
{
    xml::xobufferstream xobs;
    xobs << xml::start( "sub-node" ) << xml::end();
    xml::xostringstream xos;
    xos << xml::start( "element" ) << xobs << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <sub-node/>\n"
                       "</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: element_in_sub_stream_is_copied_to_an_empty_stream
// Created: MCO 2006-03-07
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( element_in_sub_stream_is_copied_to_an_empty_stream )
{
    xml::xobufferstream xobs;
    xobs << xml::start( "element" ) << xml::end();
    xml::xostringstream xos;
    xos << xobs;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: adding_two_sub_streams_in_an_empty_stream_throws_an_exception
// Created: MCO 2006-03-07
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( adding_two_sub_streams_in_an_empty_stream_throws_an_exception )
{
    xml::xobufferstream xobs;
    xobs << xml::start( "element" ) << xml::end();
    xml::xostringstream xos;
    xos << xobs;
    BOOST_CHECK_THROW( xos << xobs, xml::exception );
}

// -----------------------------------------------------------------------------
// Name: adding_several_times_a_sub_stream_duplicates_the_branch
// Created: MCO 2006-03-07
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( adding_several_times_a_sub_stream_duplicates_the_branch )
{
    xml::xobufferstream xobs;
    xobs << xml::start( "sub-node" ) << xml::end();
    xml::xostringstream xos;
    xos << xml::start( "element" )
          << xobs
          << xobs
          << xobs
        << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <sub-node/>\n"
                       "  <sub-node/>\n"
                       "  <sub-node/>\n"
                       "</element>\n", xos.str() );
}
