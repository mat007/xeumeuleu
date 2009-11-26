/*
 *   Copyright (c) 2008, Mathieu Champlon
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

// -----------------------------------------------------------------------------
// Name: node_content_can_be_read_with_helper
// Created: MCO 2008-01-19
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( node_content_can_be_read_with_helper )
{
    xml::xistringstream xis( "<element>the content</element>");
    xis >> xml::start( "element" );
    BOOST_CHECK_EQUAL( "the content", xis.value< std::string >() );
}

// -----------------------------------------------------------------------------
// Name: empty_node_content_read_with_helper_throws
// Created: MCO 2008-01-19
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( empty_node_content_read_with_helper_throws )
{
    xml::xistringstream xis( "<element/>");
    xis >> xml::start( "element" );
    BOOST_CHECK_THROW( xis.value< std::string >(), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: empty_node_content_read_with_helper_and_default_value_returns_default_value
// Created: MCO 2008-01-19
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( empty_node_content_read_with_helper_and_default_value_returns_default_value )
{
    xml::xistringstream xis( "<element/>");
    xis >> xml::start( "element" );
    BOOST_CHECK_EQUAL( "the content", xis.value( "the content" ) );
}

namespace
{
    class user_type
    {};
}
namespace xml
{
    xistream& operator>>( xistream& xis, user_type& )
    {
        return xis;
    }
    xostream& operator<<( xostream& xos, const user_type& )
    {
        return xos;
    }
}

// -----------------------------------------------------------------------------
// Name: reading_value_can_be_specialized_for_user_types
// Created: MCO 2009-05-30
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_value_can_be_specialized_for_user_types )
{
    xml::xistringstream xis( "<root/>" );
    user_type u;
    xis >> xml::start( "root" )
            >> u;
}

// -----------------------------------------------------------------------------
// Name: writing_value_can_be_specialized_for_user_types
// Created: MCO 2009-11-26
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_value_can_be_specialized_for_user_types )
{
    xml::xostringstream xos;
    user_type u;
    xos << xml::start( "root" )
            << u;
}

// -----------------------------------------------------------------------------
// Name: writing_value_can_be_specialized_for_const_user_types
// Created: MCO 2009-11-26
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( writing_value_can_be_specialized_for_const_user_types )
{
    xml::xostringstream xos;
    xos << xml::start( "root" )
            << user_type();
}

// -----------------------------------------------------------------------------
// Name: direct_reading_value_can_be_specialized_for_user_types
// Created: MCO 2009-11-25
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( direct_reading_value_can_be_specialized_for_user_types )
{
    xml::xistringstream xis( "<root/>" );
    xis.value< user_type >();
}
