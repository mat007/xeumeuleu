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
// Name: empty_tree_does_not_create_any_file
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( empty_tree_does_not_create_any_file )
{
    const std::string filename = "no_file.xml";
    {
        xml::xofstream xos( filename );
    }
    BOOST_CHECK( ! std::ifstream( filename.c_str() ) );
}

// -----------------------------------------------------------------------------
// Name: streaming_elements_creates_a_valid_file_upon_flush
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_elements_creates_a_valid_file_upon_flush )
{
    const std::string filename = "valid_file.xml";
    xml::xofstream xos( filename );
    xos << xml::start( "element" )
            << xml::start( "child" ) << xml::end
        << xml::end;
    xos.flush();
    BOOST_REQUIRE_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                         "<element>\n"
                         "  <child/>\n"
                         "</element>\n", load( filename ) );
    std::remove( filename.c_str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_elements_creates_a_valid_file_upon_destruction
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_elements_creates_a_valid_file_upon_destruction )
{
    const std::string filename = "valid_file.xml";
    {
        xml::xofstream xos( filename );
        xos << xml::start( "element" )
                << xml::start( "child" ) << xml::end
            << xml::end;
    }
    BOOST_REQUIRE_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                         "<element>\n"
                         "  <child/>\n"
                         "</element>\n", load( filename ) );
    std::remove( filename.c_str() );
}

// -----------------------------------------------------------------------------
// Name: utf_16_encoded_file_starts_with_byte_mark_order
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( utf_16_encoded_file_starts_with_byte_mark_order )
{
    const std::string filename = "valid_utf_16_file.xml";
    xml::xofstream xos( filename, xml::encoding( "UTF-16LE" ) );
    xos << xml::content( "element", "this is the content !" );
    xos.flush();
    {
        std::ifstream ifs( filename.c_str() );
        if( ! ifs )
            throw std::runtime_error( "File " + filename + " not found" );
        char actual[2];
        ifs.read( reinterpret_cast< char* >( &actual ), sizeof( actual ) );
        BOOST_REQUIRE_EQUAL( '\xFF', actual[0] );
        BOOST_REQUIRE_EQUAL( '\xFE', actual[1] );
    }
    std::remove( filename.c_str() );
}
