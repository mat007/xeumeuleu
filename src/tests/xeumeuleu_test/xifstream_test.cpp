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
#include <fstream>

using namespace mockpp;

// -----------------------------------------------------------------------------
// Name: creating_with_non_existing_file_throws_a_verbose_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_with_non_existing_file_throws_a_verbose_exception )
{
    const std::string filename( "directory/non_existing_file" );
    try
    {
        xml::xifstream xis( filename );
    }
    catch( xml::exception& e )
    {
        BOOST_CHECK_EQUAL( "Unable to open file '" + filename + "'", e.what() );
        return;
    }
    BOOST_FAIL( "verbose exception not received" );
}

// -----------------------------------------------------------------------------
// Name: creating_with_existing_empty_file_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_with_existing_empty_file_throws_an_exception )
{
    const std::string filename( "empty_file" );
    std::ofstream( filename.c_str() ).close();
    BOOST_CHECK_THROW( xml::xifstream xis( filename ), xml::exception );
    std::remove( filename.c_str() );
}

// -----------------------------------------------------------------------------
// Name: creating_with_valid_file
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_with_valid_file )
{
    const std::string filename( "valid_file" );
    std::ofstream file( filename.c_str() );
    file << "<element/>";
    file.close();
    xml::xifstream xis( filename );
    xis >> xml::start( "element" ) >> xml::end();
    std::remove( filename.c_str() );
}
