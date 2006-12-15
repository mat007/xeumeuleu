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

namespace
{
    void warning_check()
    {
        xml::xistream& xis = *(xml::xistream*)0;
        int value;
        xis >> xml::content( "node", value );
    }

    template< typename T > std::string write( const T& value )
    {
        xml::xostringstream xos;
        xos << xml::content( "element", value );
        return xos.str();
    }
    template< typename T > T read( const std::string& value )
    {
        T result;
        xml::xistringstream xis( "<element> " + value + " </element>");
        xis >> xml::content( "element", result );
        return result;
    }
    std::string format( const std::string& value )
    {
        return "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
               "<element>" + value + "</element>\n";
    }
}

// -----------------------------------------------------------------------------
// Name: streaming_content_writes_node_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_writes_node_content )
{
    BOOST_CHECK_EQUAL( format(" this is the content  "), write< char* >( " this is the content  " ) );
    BOOST_CHECK_EQUAL( format( "1.23" ), write< float >( 1.23f ) );
    BOOST_CHECK_EQUAL( format( "1.23" ), write< double >( 1.23 ) );
    BOOST_CHECK_EQUAL( format( "1242" ), write< int >( 1242 ) );
    BOOST_CHECK_EQUAL( format( "1242" ), write< short >( 1242 ) );
    BOOST_CHECK_EQUAL( format( "false" ), write< bool >( false ) );
    BOOST_CHECK_EQUAL( format( "1242" ), write< long >( 1242 ) );
    BOOST_CHECK_EQUAL( format( "65535" ), write< unsigned short >( 65535u ) );
    BOOST_CHECK_EQUAL( format( "1242" ), write< unsigned int >( 1242 ) );
    BOOST_CHECK_EQUAL( format( "1242" ), write< unsigned long >( 1242 ) );
}

// -----------------------------------------------------------------------------
// Name: streaming_stack_content_writes_node_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_stack_content_writes_node_content )
{
    xml::xostringstream xos;
    xos << xml::content( "element", 7 );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>7</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_reads_node_content
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_reads_node_content )
{
    BOOST_CHECK_EQUAL( " this is the value ", read< std::string >( "this is the value" ) );
    BOOST_CHECK_EQUAL( 1.23f, read< float >( "1.23" ) );
    BOOST_CHECK_EQUAL( 1e+99, read< double >( "1e+99" ) );
    BOOST_CHECK_EQUAL( 12, read< int >( "12" ) );
    BOOST_CHECK_EQUAL( 32767, read< short >( "32767" ) );
    BOOST_CHECK_EQUAL( true, read< bool >( "true" ) );
    BOOST_CHECK_EQUAL( 5, read< long > ( "5" ) );
    BOOST_CHECK_EQUAL( 4294967295u, read< unsigned int >( "4294967295" ) );
    BOOST_CHECK_EQUAL( 65535u, read< unsigned short >( "65535" ) );
    BOOST_CHECK_EQUAL( 4294967295, read< unsigned long >( "4294967295" ) );
}

// -----------------------------------------------------------------------------
// Name: streaming_content_with_invalid_format_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_content_with_invalid_format_throws_an_exception )
{
    BOOST_CHECK_THROW( read< int >( "12.3" ), xml::exception );
    BOOST_CHECK_THROW( read< short >( "300000" ), xml::exception );
    BOOST_CHECK_THROW( read< unsigned int >( "12.3" ), xml::exception );
    BOOST_CHECK_THROW( read< unsigned int >( "-42" ), xml::exception );
    BOOST_CHECK_THROW( read< float >( "1e+99" ), xml::exception );
}
