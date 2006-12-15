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
