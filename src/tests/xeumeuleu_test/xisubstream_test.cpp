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
    const std::string xml = "<element>"
                            "  <sub-node/>"
                            "</element>";
    xml::xistringstream xis( xml );
    xis >> xml::start( "element" );
    xml::xisubstream xiss( xis );
    BOOST_CHECK_NO_THROW( xiss >> xml::start( "sub-node" ) );
}

// -----------------------------------------------------------------------------
// Name: streaming_end_at_sub_root_level_throws_an_exception
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_end_at_sub_root_level_throws_an_exception )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" );
    xml::xisubstream xiss( xis );
    BOOST_CHECK_THROW( xiss >> xml::end(), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_a_sub_stream_does_not_modify_original_stream
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_a_sub_stream_does_not_modify_original_stream )
{
    xml::xistringstream xis( "<element/>" );
    xml::xisubstream xiss( xis );
    xiss >> xml::start( "element" );
    BOOST_CHECK_NO_THROW( xis >> xml::start( "element" ) );
}

// -----------------------------------------------------------------------------
// Name: creating_stream_created_after_optional_does_not_reset_optional
// Created: MCO 2006-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_stream_created_after_optional_does_not_reset_optional )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" ) >> xml::optional();
    xml::xisubstream xiss( xis );
    BOOST_CHECK_NO_THROW( xis >> xml::start( "non-existing" ) );
}

// -----------------------------------------------------------------------------
// Name: sub_stream_created_after_optional_is_not_optional
// Created: MCO 2006-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( sub_stream_created_after_optional_is_not_optional )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" ) >> xml::optional();
    xml::xisubstream xiss( xis );
    BOOST_CHECK_THROW( xiss >> xml::start( "non-existing" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_sub_stream_on_optional_non_existing_branch_is_valid
// Created: MCO 2006-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_sub_stream_on_optional_non_existing_branch_is_valid )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" ) >> xml::optional() >> xml::start( "non-existing" );
    xml::xisubstream xiss( xis );
    BOOST_CHECK_NO_THROW( xis >> xml::start( "another-non-existing" ) );
}
