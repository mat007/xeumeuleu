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

namespace
{
    const std::string load( const char* filename )
    {
        std::ifstream ifs( filename );
        if( !ifs )
            throw std::runtime_error( ( std::string( "file " ) + filename + " not found" ).c_str() );
        return std::string( std::istreambuf_iterator< char >( ifs ), std::istreambuf_iterator< char >() );
    }
}

// -----------------------------------------------------------------------------
// Name: empty_tree_does_not_create_any_file
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( empty_tree_does_not_create_any_file )
{
    const std::string filename( "no_file" );
    {
        xml::xofstream xos( filename );
    }
    std::ifstream file( filename.c_str() );
    BOOST_CHECK( !file.is_open() );
}

// -----------------------------------------------------------------------------
// Name: streaming_elements_creates_a_valid_file
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_elements_creates_a_valid_file )
{
    const std::string filename( "valid_file" );
    xml::xofstream xos( filename );
    xos << xml::start( "element" )
            << xml::start( "child" ) << xml::end()
        << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <child/>\n"
                       "</element>\n", load( filename.c_str() ) );
    std::remove( filename.c_str() );
}
