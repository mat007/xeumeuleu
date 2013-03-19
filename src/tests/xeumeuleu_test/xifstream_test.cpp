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
#include <xeumeuleu/xml.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/detail/utf8_codecvt_facet.hpp> 
#include <fstream>

// -----------------------------------------------------------------------------
// Name: creating_with_non_existing_file_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_with_non_existing_file_throws_an_exception )
{
    BOOST_REQUIRE_THROW( xml::xifstream xis( "directory/non_existing_file.xml" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_with_existing_empty_file_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_with_existing_empty_file_throws_an_exception )
{
    const std::string filename = "empty_file.xml";
    std::ofstream( filename.c_str() ).close();
    BOOST_REQUIRE_THROW( xml::xifstream xis( filename ), xml::exception );
    std::remove( filename.c_str() );
}

// -----------------------------------------------------------------------------
// Name: creating_with_valid_file
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_with_valid_file )
{
    const std::string filename = "valid_file.xml";
    {
        std::ofstream file( filename.c_str() );
        file << "<element/>";
    }
    xml::xifstream xis( filename );
    xis >> xml::start( "element" ) >> xml::end;
    std::remove( filename.c_str() );
}

// -----------------------------------------------------------------------------
// Name: creating_file_with_unicode_name
// Created: MCO 2013-01-31
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_file_with_unicode_name )
{
    std::string filename;
    xml::xifstream( BOOST_RESOLVE( "arabic.xml" ) )
        >> xml::start( "root" )
            >> xml::attribute( "name", filename );
    filename += ".xml";
    const boost::filesystem::path path(
        filename.c_str(),
        boost::filesystem::detail::utf8_codecvt_facet() );
    boost::filesystem::remove( path );
    xml::xofstream( filename ) << xml::start( "root" );
    BOOST_CHECK( boost::filesystem::remove( path ) );
}
