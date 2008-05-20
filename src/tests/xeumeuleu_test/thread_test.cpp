// *****************************************************************************
//
// This file is part of a MASA library or program.
// Refer to the included end-user license agreement for restrictions.
//
// Copyright (c) 2008 Mathématiques Appliquées SA (MASA)
//
// *****************************************************************************

#include "xeumeuleu_test_pch.h"
#include <boost/thread/thread.hpp>
#include "xeumeuleu/xml.h"

namespace
{
    void Read()
    {
        xml::xistringstream xis( "<element>"
                                    "<sub-node/>"
                                    "<another-sub-node/>"
                                 "</element>" );
        xis >> xml::start( "element" )
                >> xml::start( "another-sub-node" ) >> xml::end()
            >> xml::end();
    }
    void Write()
    {
        xml::xostringstream xos;
        xos << xml::start( "element" )
                << xml::start( "another-sub-node" ) << xml::end()
            << xml::end();
    }
    void UseXeumeuleu()
    {
        unsigned count = 1000;
        while( count-- )
        {
            if( ( rand() % 2 ) != 0 )
                Read();
            else
                Write();
        }
    }
}

// -----------------------------------------------------------------------------
// Name: creating_a_document_is_thread_safe
// Created: AGE 2008-05-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_a_document_is_thread_safe )
{
    const unsigned nThreads = 4;

    boost::thread_group group;
    for( unsigned i = 0; i < nThreads; ++i )
        group.create_thread( &UseXeumeuleu );

    group.join_all();
}
