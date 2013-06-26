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
#include <boost/assign/list_of.hpp>

// -----------------------------------------------------------------------------
// Name: parameters_are_sent_to_the_stylesheet
// Created: SLI 2007-09-11
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( parameters_are_sent_to_the_stylesheet )
{
    xsl::xstringtransform xf( BOOST_RESOLVE( "parameters.xsl" ) );
    xml::xistringstream xis( "<root/>" );
    xf << xsl::parameter( "key1", "expression1" )
       << xsl::parameter( "key2", "expression2" )
       << xis;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root key1=\"expression1\" key2=\"expression2\"/>", xf.str() );
}

// -----------------------------------------------------------------------------
// Name: unicode_parameters_are_sent_to_the_stylesheet
// Created: MCO 2013-06-26
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( unicode_parameters_are_sent_to_the_stylesheet )
{
    std::string name;
    xml::xifstream( BOOST_RESOLVE( "japanese.xml" ) )
        >> xml::start( "root" )
            >> xml::attribute( "name", name );
    xsl::xstringtransform xf( BOOST_RESOLVE( "parameter.xsl" ) );
    xf << xsl::parameter( "key", name )
       << xml::xistringstream( "<root/>" );
    std::string attribute;
    xml::xistringstream xis( xf.str() );
    xis >> xml::start( "root" )
            >> xml::attribute( "key", attribute );
    std::vector< char > v = boost::assign::list_of
        ( -29 )( -127 )( -78 )( -29 )( -126 )( -119 )( -29 )
        ( -127 )( -116 )( -29 )( -127 )( -86 )( -29 )( -127 )
        ( -78 )( -29 )( -126 )( -119 )( -29 )( -127 )( -116 )
        ( -29 )( -127 )( -86 );
    BOOST_CHECK_EQUAL_COLLECTIONS( v.begin(), v.end(), attribute.begin(), attribute.end() );
}
