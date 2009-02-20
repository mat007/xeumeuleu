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

using namespace mockpp;

// -----------------------------------------------------------------------------
// Name: copy_xistream_from_root_to_empty_xostream
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( copy_xistream_from_root_to_empty_xostream )
{
    xml::xistringstream xis( "<root/>" );
    xml::xostringstream xos;
    xos << xis;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<root/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: copy_xistream_with_prolog_from_root_to_empty_xostream
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( copy_xistream_with_prolog_from_root_to_empty_xostream )
{
    xml::xistringstream xis( "<?xml version='1.0' encoding='UTF-8' standalone='no' ?><root/>" );
    xml::xostringstream xos;
    xos << xis;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<root/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: copy_xistream_from_root_to_xostream
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( copy_xistream_from_root_to_xostream )
{
    xml::xistringstream xis( "<element/>" );
    xml::xostringstream xos;
    xos << xml::content( "root", xis );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<root>\n"
                       "  <element/>\n"
                       "</root>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: copy_xistream_from_sub_element_to_xostream
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( copy_xistream_from_sub_element_to_xostream )
{
    xml::xistringstream xis( "<element>"
                               "<sub-element/>"
                             "</element>" );
    xis >> xml::start( "element" );
    xml::xostringstream xos;
    xos << xml::content( "root", xis );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<root>\n"
                       "  <sub-element/>\n"
                       "</root>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: copy_xistream_from_sub_elements_to_xostream_root_throws
// Created: MCO 2008-11-22
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( copy_xistream_from_sub_elements_to_xostream_root_throws )
{
    xml::xistringstream xis( "<element>"
                               "<sub-element/>"
                               "<sub-element/>"
                             "</element>" );
    xis >> xml::start( "element" );
    xml::xostringstream xos;
    BOOST_CHECK_THROW( xos << xis, xml::exception );
}

// -----------------------------------------------------------------------------
// Name: copy_xistream_from_optional_non_existing_element_to_xostream
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( copy_xistream_from_optional_non_existing_element_to_xostream )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
        >> xml::optional >> xml::start( "non existing element" );
    xml::xostringstream xos;
    xos << xml::content( "root", xis );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<root/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: copy_xistream_from_optional_to_xostream
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( copy_xistream_from_optional_to_xostream )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
        >> xml::optional;
    xml::xostringstream xos;
    xos << xml::content( "root", xis );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<root/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: copy_xistream_from_sub_element_to_xostream_removes_meaningless_empty_text_node
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( copy_xistream_from_sub_element_to_xostream_removes_meaningless_empty_text_node )
{
    xml::xistringstream xis( "<root>  <sub-element/></root>" );
    xis >> xml::start( "root" );
    xml::xostringstream xos;
    xos << xml::start( "root" ) << xis << xml::end;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<root>\n"
                       "  <sub-element/>\n"
                       "</root>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: copy_xistream_from_sub_element_to_xostream_removes_meaningless_empty_text_sub_node
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( copy_xistream_from_sub_element_to_xostream_removes_meaningless_empty_text_sub_node )
{
    xml::xistringstream xis( "<root>"
                             "  <element>"
                             "  </element>"
                             "</root>" );
    xml::xostringstream xos;
    xos << xis ;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<root>\n"
                       "  <element/>\n"
                       "</root>\n", xos.str() );
}
