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

#include "xeuseuleu_test_pch.h"
#include <xeuseuleu/xsl.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/detail/utf8_codecvt_facet.hpp> 
#include <fstream>

namespace
{
    const std::string load( const std::string& filename )
    {
        std::ifstream ifs( filename.c_str() );
        if( ! ifs )
            throw std::runtime_error( "File " + filename + " not found" );
        return std::string( std::istreambuf_iterator< char >( ifs ), std::istreambuf_iterator< char >() );
    }
}

// -----------------------------------------------------------------------------
// Name: tranformation_with_a_non_existing_stylesheet_throws
// Created: MCO 2013-03-19
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( tranformation_with_a_non_existing_stylesheet_throws )
{
    BOOST_CHECK_THROW( xsl::xftransform( "non-existing.xsl", "file" ), xsl::exception );
}

// -----------------------------------------------------------------------------
// Name: tranformation_creates_a_file
// Created: SLI 2007-09-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( tranformation_creates_a_file )
{
    const std::string filename = "file";
    {
        xsl::xftransform xf( "stylesheet.xsl", filename );
        xf << xml::start( "root" )
           << xml::end;
    }
    BOOST_REQUIRE_EQUAL(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?><new-root/>",
        load( filename ) );
    std::remove( filename.c_str() );
}

// -----------------------------------------------------------------------------
// Name: tranformation_uses_a_stylesheet_with_unicode_name
// Created: MCO 2013-03-19
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( tranformation_uses_a_stylesheet_with_unicode_name )
{
    std::string stylesheet;
    xml::xifstream( "japanese.xml" )
        >> xml::start( "root" )
            >> xml::attribute( "name", stylesheet );
    stylesheet += ".xsl";
    const boost::filesystem::path path(
        stylesheet.c_str(),
        boost::filesystem::detail::utf8_codecvt_facet() );
    boost::filesystem::copy_file(
        "stylesheet.xsl",
        path,
        boost::filesystem::copy_option::overwrite_if_exists );
    const std::string filename = "file";
    {
        xsl::xftransform xf( stylesheet, filename );
        xf << xml::start( "root" )
           << xml::end;
    }
    BOOST_REQUIRE_EQUAL(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?><new-root/>",
        load( filename ) );
    boost::filesystem::remove( path );
    std::remove( filename.c_str() );
}

// -----------------------------------------------------------------------------
// Name: tranformation_creates_a_file_with_unicode_name
// Created: MCO 2013-03-19
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( tranformation_creates_a_file_with_unicode_name )
{
    std::string filename;
    xml::xifstream( "japanese.xml" )
        >> xml::start( "root" )
            >> xml::attribute( "name", filename );
    const boost::filesystem::path path(
        filename.c_str(),
        boost::filesystem::detail::utf8_codecvt_facet() );
    boost::filesystem::remove( path );
    {
        xsl::xftransform xf( "stylesheet.xsl", filename );
        xf << xml::start( "root" );
    }
    BOOST_CHECK( boost::filesystem::remove( path ) );
}
