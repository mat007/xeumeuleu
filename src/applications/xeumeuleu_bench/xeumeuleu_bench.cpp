/*
 *   Copyright (c) 2007, Mathieu Champlon
 *   All rights reserved.
 *
 *   Redistribution  and use  in source  and binary  forms, with  or without
 *   modification, are permitted provided  that the following conditions are
 *   met :
 *
 *   . Redistributions  of  source  code  must  retain  the  above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   . Redistributions in  binary form  must reproduce  the above  copyright
 *     notice, this list of conditions  and the following disclaimer in  the
 *     documentation and/or other materials provided with the distribution.
 *
 *   . Neither  the name  of  the  copyright  holders  nor the names  of the
 *     contributors may be used to endorse  or promote products derived from
 *     this software without specific prior written permission.
 *
 *   THIS SOFTWARE  IS  PROVIDED  BY THE  COPYRIGHT HOLDERS  AND CONTRIBUTORS
 *   ``AS IS''  AND ANY  EXPRESS OR  IMPLIED WARRANTIES,  INCLUDING,  BUT NOT
 *   LIMITED TO, THE IMPLIED  WARRANTIES  OF MERCHANTABILITY AND  FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE THE COPYRIGHT
 *   OWNERS OR CONTRIBUTORS  BE LIABLE FOR ANY  DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL,  EXEMPLARY,  OR  CONSEQUENTIAL   DAMAGES  (INCLUDING,  BUT  NOT
 *   LIMITED TO,  PROCUREMENT OF SUBSTITUTE  GOODS OR SERVICES;  LOSS OF USE,
 *   DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED  AND ON  ANY
 *   THEORY  OF  LIABILITY,  WHETHER IN  CONTRACT,  STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY  WAY  OUT OF  THE USE
 *   OF THIS SOFTWARE, EVEN  IF  ADVISED OF  THE POSSIBILITY  OF SUCH DAMAGE.
 */

#include <xeumeuleu/xml.hpp>
#ifdef _MSC_VER
#   pragma warning( push, 0 )
#endif
#include <boost/date_time/posix_time/posix_time.hpp>
#ifdef _MSC_VER
#   pragma warning( pop )
#endif
#include <iostream>

using namespace boost::posix_time;

namespace
{
//    const int FILES = 100000;
//    const int NODES = 1;
    const int FILES = 1;
    const int NODES = 1000000;
}

int main()
{
    const ptime start = microsec_clock::local_time();
    for( int file = 0; file < FILES; ++file )
    {
        xml::xofstream xos( "bench.xml" );
        xos << xml::start( "root" );
        for( int node = 0; node < NODES; ++node )
            xos << xml::start( "element" )
                    << 12.f
                    << xml::attribute( "id", 27.f )
                << xml::end;
    }
    const time_duration duration = microsec_clock::local_time() - start;
    std::cout << "duration : " << duration << std::endl;
    return EXIT_SUCCESS;
}
