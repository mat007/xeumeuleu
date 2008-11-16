// *****************************************************************************
//
// This file is part of a MASA library or program.
// Refer to the included end-user license agreement for restrictions.
//
// Copyright (c) 2008 Mathématiques Appliquées SA (MASA)
//
// *****************************************************************************

#include "xeumeuleu_test_pch.h"
#include "xeumeuleu/xml.h"

namespace
{
    void read()
    {
        xml::xistringstream xis( "<element>"
                                    "<sub-node/>"
                                    "<another-sub-node/>"
                                 "</element>" );
        xis >> xml::start( "element" )
                >> xml::start( "another-sub-node" ) >> xml::end();
    }
    void write()
    {
        xml::xostringstream xos;
        xos << xml::start( "element" )
                << xml::start( "another-sub-node" ) << xml::end()
            << xml::end();
    }
    void run()
    {
        int count = 1000;
        while( count-- )
        {
            if( std::rand() % 2 != 0 )
                read();
            else
                write();
        }
    }
}

// -----------------------------------------------------------------------------
// Name: creating_a_document_is_thread_safe
// Created: AGE 2008-05-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_a_document_is_thread_safe )
{
    static const int THREADS = 4;
    boost::thread_group group;
    for( int i = 0; i < THREADS; ++i )
        group.create_thread( &run );
    group.join_all();
}
