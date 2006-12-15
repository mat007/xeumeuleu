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

// -----------------------------------------------------------------------------
// Name: created_sub_stream_starts_from_current_stream_level
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( created_sub_stream_starts_from_current_stream_level )
{
    xml::xostringstream xos;
    xos << xml::start( "element" );
    xml::xosubstream xoss( xos );
    xoss << xml::start( "sub-node" ) << xml::end();
    xos << xml::end();
    const std::string xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                            "<element>\n"
                            "  <sub-node/>\n"
                            "</element>\n";
    BOOST_CHECK_EQUAL( xml, xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_end_at_root_level_throws_an_exception
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( streaming_end_at_root_level_throws_an_exception )
{
    xml::xostringstream xos;
    xos << xml::start( "element" );
    xml::xosubstream xoss( xos );
    BOOST_CHECK_THROW( xoss << xml::end(), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_root_element_after_it_has_been_created_in_sub_stream_throws_an_exception
// Created: MCO 2006-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_root_element_after_it_has_been_created_in_sub_stream_throws_an_exception )
{
    xml::xostringstream xos;
    xml::xosubstream xoss( xos );
    xoss << xml::start( "element" );
    BOOST_CHECK_THROW( xos << xml::start( "element" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_a_sub_stream_does_not_modify_original_stream
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_a_sub_stream_does_not_modify_original_stream )
{
    xml::xostringstream xos;
    xos << xml::start( "element" );
    xml::xosubstream xoss( xos );
    xoss << xml::start( "sub-node" );
    BOOST_CHECK_NO_THROW( xos << xml::end() );
    const std::string xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                            "<element>\n"
                            "  <sub-node/>\n"
                            "</element>\n";
    BOOST_CHECK_EQUAL( xml, xos.str() );
}

// -----------------------------------------------------------------------------
// Name: creating_root_element_in_sub_stream_completes_the_stream
// Created: MCO 2006-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_root_element_in_sub_stream_completes_the_stream )
{
    xml::xostringstream xos;
    xml::xosubstream xoss( xos );
    xoss << xml::start( "element" ) << xml::end();
    const std::string xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                            "<element/>\n";
    BOOST_CHECK_EQUAL( xml, xos.str() );
}

// -----------------------------------------------------------------------------
// Name: creating_sub_stream_in_sub_stream_is_valid
// Created: MCO 2006-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( creating_sub_stream_in_sub_stream_is_valid )
{
    xml::xostringstream xos;
    xml::xosubstream xoss( xos );
    xml::xosubstream xosss( xoss );
}
