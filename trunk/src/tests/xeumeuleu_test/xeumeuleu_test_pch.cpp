/*
 *   Copyright (c) 2006, Mathieu Champlon
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

#include "xeumeuleu_test_pch.h"
#include <string>
#include <boost/test/unit_test_log_formatter.hpp>
#include <boost/test/detail/supplied_log_formatters.hpp>

using namespace boost::unit_test;
using namespace boost::unit_test::ut_detail;

namespace
{
    static std::string data_directory;

    void set_data_directory( int argc, char* argv[] )
    {
        while( argc-- )
        {
            const std::string argument( argv[argc] );
            const std::string::size_type n = argument.find( '=' );
            if( n != std::string::npos )
            {
                const std::string option = argument.substr( 0, n );
                if( option == "--data_directory" )
                    data_directory = argument.substr( n+1 );
            }
        }
    }

    class msvc_log_formatter : public msvc65_like_log_formatter
    {
    public:
        msvc_log_formatter()
            : msvc65_like_log_formatter( unit_test_log::instance() )
        {}

        virtual void log_exception( std::ostream& output, const_string test_case_name, const_string explanation )
        {
            output << "Exception in '" << test_case_name << "': error: " << explanation;
        }
    };

}

test_suite* init_unit_test_suite( int argc, char* argv [] )
{
    unit_test_log::instance().set_log_formatter( new msvc_log_formatter() );
    set_data_directory( argc, argv );
    return ut_detail::auto_unit_test_suite();
}

std::string BOOST_RESOLVE( const std::string& filename )
{
    if( data_directory.empty() )
        return filename;
    return data_directory + '/' + filename;
}
