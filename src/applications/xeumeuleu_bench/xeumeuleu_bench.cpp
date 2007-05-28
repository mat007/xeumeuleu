// *****************************************************************************
//
// This file is part of a MASA library or program.
// Refer to the included end-user license agreement for restrictions.
//
// Copyright (c) 2007 Mathématiques Appliquées SA (MASA)
//
// *****************************************************************************

#include "xeumeuleu_bench_pch.h"
#include "xeumeuleu/xml.h"

using namespace boost::posix_time;

int main( int /*argc*/, char* /*argv[]*/ )
{
    const ptime start = microsec_clock::local_time();
    for( int i = 0; i < 100000; ++i )
    {
        xml::xofstream xos( "bench.xml" );
        xos << xml::start( "root" )
                << xml::content( "element", 12.f )
                << xml::start( "another" )
                    << xml::attribute( "id", 27.f )
                << xml::end()
            << xml::end();
    }
    const time_duration duration = microsec_clock::local_time() - start;
    xml::xostringstream xos;
    std::cout << "duration : " << duration << std::endl;
    return 0;
}
