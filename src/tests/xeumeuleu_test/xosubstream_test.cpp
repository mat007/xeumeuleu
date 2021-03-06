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

// -----------------------------------------------------------------------------
// Name: created_output_sub_stream_starts_from_current_stream_level
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( created_output_sub_stream_starts_from_current_stream_level )
{
    xml::xostringstream xos;
    xos << xml::start( "element" );
    xml::xosubstream xoss( xos );
    xoss << xml::start( "sub-node" ) << xml::end;
    xos << xml::end;
    const std::string xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                            "<element>\n"
                            "  <sub-node/>\n"
                            "</element>\n";
    BOOST_CHECK_EQUAL( xml, xos.str() );
}

// -----------------------------------------------------------------------------
// Name: streaming_end_to_an_output_sub_stream_at_root_level_throws_an_exception
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( streaming_end_to_an_output_sub_stream_at_root_level_throws_an_exception )
{
    xml::xostringstream xos;
    xos << xml::start( "element" );
    xml::xosubstream xoss( xos );
    BOOST_CHECK_THROW( xoss << xml::end, xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_root_element_after_it_has_been_created_in_sub_stream_throws_an_exception
// Created: MCO 2006-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_root_element_after_it_has_been_created_in_sub_stream_throws_an_exception )
{
    xml::xostringstream xos;
    xml::xosubstream xoss( xos );
    xoss << xml::start( "element" );
    BOOST_CHECK_THROW( xos << xml::start( "element" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: creating_a_sub_stream_does_not_modify_original_output_stream
// Created: MCO 2006-03-18
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_a_sub_stream_does_not_modify_original_output_stream )
{
    xml::xostringstream xos;
    xos << xml::start( "element" );
    xml::xosubstream xoss( xos );
    xoss << xml::start( "sub-node" );
    BOOST_CHECK_NO_THROW( xos << xml::end );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <sub-node/>\n"
                       "</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: creating_a_sub_stream_remaining_empty_does_not_add_a_prolog_to_the_output
// Created: MCO 2008-05-08
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_a_sub_stream_remaining_empty_does_not_add_a_prolog_to_the_output )
{
    xml::xostringstream xos;
    {
        xml::xosubstream xoss( xos );
    }
    BOOST_CHECK_EQUAL( "", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: creating_sub_stream_of_sub_stream_is_valid
// Created: MCO 2006-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( creating_sub_stream_of_sub_stream_is_valid )
{
    xml::xostringstream xos;
    xml::xosubstream xoss( xos );
    xml::xosubstream xosss( xoss );
}

// -----------------------------------------------------------------------------
// Name: sub_output_stream_creates_a_mutable_temporary
// Created: MCO 2009-06-17
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( sub_output_stream_creates_a_mutable_temporary )
{
    xml::xostringstream xos;
    xml::xosubstream( xos ) << xml::start( "element" );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element/>\n",
                       xos.str() );
}

BOOST_AUTO_TEST_CASE( optional_after_creating_sub_stream_is_no_op )
{
    xml::xostringstream xos;
    {
        xml::xosubstream xoss( xos );
        xoss << xml::optional;
    }
    xos << xml::start( "element" );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element/>\n",
                       xos.str() );
}

BOOST_AUTO_TEST_CASE( creating_sub_stream_after_optional_throws )
{
    xml::xostringstream xos;
    xos << xml::optional;
    BOOST_CHECK_THROW( xml::xosubstream xoss( xos ), xml::exception );
}

BOOST_AUTO_TEST_CASE( creating_sub_stream_after_optional_element_is_no_op )
{
    xml::xostringstream xos;
    xos << xml::optional << xml::start( "root" );
    {
        xml::xosubstream xoss( xos );
    }
    xos << xml::start( "element" );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<root>\n"
                       "  <element/>\n"
                       "</root>\n",
                       xos.str() );
}

BOOST_AUTO_TEST_CASE( creating_sub_stream_after_optional_element_and_writing_elements_writes_them_all )
{
    xml::xostringstream xos;
    xos << xml::optional << xml::start( "root" );
    {
        xml::xosubstream xoss( xos );
        xoss << xml::start( "element-1" )
                << xml::start( "element-2" );
    }
    xos << xml::start( "element-3" );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<root>\n"
                       "  <element-1>\n"
                       "    <element-2/>\n"
                       "  </element-1>\n"
                       "  <element-3/>\n"
                       "</root>\n",
                       xos.str() );
}

BOOST_AUTO_TEST_CASE( creating_sub_stream_after_optional_element_and_writing_interleaved_elements_writes_them_all )
{
    xml::xostringstream xos;
    xos << xml::optional << xml::start( "root" );
    xml::xosubstream xoss( xos );
    xos << xml::start( "element-1" );
    xoss << xml::start( "element-2" );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<root>\n"
                       "  <element-1/>\n"
                       "  <element-2/>\n"
                       "</root>\n",
                       xos.str() );
}

BOOST_AUTO_TEST_CASE( creating_sub_streams_after_optional_element_and_writing_another_element_writes_them_all )
{
    xml::xostringstream xos;
    xos << xml::optional << xml::start( "root" );
    {
        xml::xosubstream xoss( xos );
        {
            xml::xosubstream xoss2( xos );
            xoss2 << xml::start( "element-1" );
        }
        xoss << xml::start( "element-2" );
    }
    xos << xml::start( "element-3" );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<root>\n"
                       "  <element-1/>\n"
                       "  <element-2/>\n"
                       "  <element-3/>\n"
                       "</root>\n",
                       xos.str() );
}

BOOST_AUTO_TEST_CASE( optional_element_after_creating_sub_stream_is_no_op )
{
    xml::xostringstream xos;
    {
        xml::xosubstream xoss( xos );
        xoss << xml::optional << xml::start( "non-existing-element" );
    }
    xos << xml::start( "element" );
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element/>\n",
                       xos.str() );
}

BOOST_AUTO_TEST_CASE( optional_both_before_and_after_substream_writes_them_all )
{
    xml::xostringstream xos;
    xos << xml::optional << xml::start( "root" );
    {
        xml::xosubstream xoss( xos );
        xoss << xml::optional << xml::start( "element" )
                 << xml::start( "sub-element" )
                 << xml::end
            << xml::end;
    }
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<root>\n"
                       "  <element>\n"
                       "    <sub-element/>\n"
                       "  </element>\n"
                       "</root>\n",
                       xos.str() );
}
