// *****************************************************************************
//
// This file is part of a MASA library or program.
// Refer to the included end-user license agreement for restrictions.
//
// Copyright (c) 2005 Mathématiques Appliquées SA (MASA)
//
// *****************************************************************************

#include "xeumeuleu_test_pch.h"
#include "xeumeuleu/trim.h"

using namespace mockpp;

// -----------------------------------------------------------------------------
// Name: triming_removes_white_spaces_on_both_sides
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( triming_removes_white_spaces_on_both_sides )
{
    BOOST_CHECK_EQUAL( "this is a string", xml::trim( "   this is a string   " ) );
}

// -----------------------------------------------------------------------------
// Name: triming_empty_string_is_no_op
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( triming_empty_string_is_no_op )
{
    BOOST_CHECK_EQUAL( "", xml::trim( "" ) );
}
