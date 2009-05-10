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
// Name: a_buffer_stream_can_be_used_for_writing_and_reading
// Created: MCO 2008-04-26
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( a_buffer_stream_can_be_used_for_writing_and_reading )
{
    xml::xobufferstream xbs;
    xbs << xml::start( "root" );
    xbs >> xml::start( "root" );
}

// -----------------------------------------------------------------------------
// Name: empty_buffer_stream_does_not_modify_stream
// Created: MCO 2006-03-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( empty_buffer_stream_does_not_modify_stream )
{
    xml::xobufferstream xobs;
    xml::xostringstream xos;
    xos << xml::start( "element" ) << xobs << xml::end;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: element_in_buffer_stream_is_inserted_in_stream
// Created: MCO 2006-03-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( element_in_buffer_stream_is_inserted_in_stream )
{
    xml::xobufferstream xobs;
    xobs << xml::start( "sub-node" ) << xml::end;
    xml::xostringstream xos;
    xos << xml::start( "element" ) << xobs << xml::end;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <sub-node/>\n"
                       "</element>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: element_in_buffer_stream_is_copied_to_an_empty_stream
// Created: MCO 2006-03-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( element_in_buffer_stream_is_copied_to_an_empty_stream )
{
    xml::xobufferstream xobs;
    xobs << xml::start( "element" ) << xml::end;
    xml::xostringstream xos;
    xos << xobs;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element/>\n", xos.str() );
}

// -----------------------------------------------------------------------------
// Name: adding_two_buffer_streams_in_an_empty_stream_throws_an_exception
// Created: MCO 2006-03-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( adding_two_buffer_streams_in_an_empty_stream_throws_an_exception )
{
    xml::xobufferstream xobs;
    xobs << xml::start( "element" ) << xml::end;
    xml::xostringstream xos;
    xos << xobs;
    BOOST_CHECK_THROW( xos << xobs, xml::exception );
}

// -----------------------------------------------------------------------------
// Name: adding_several_times_a_buffer_stream_duplicates_the_branch
// Created: MCO 2006-03-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( adding_several_times_a_buffer_stream_duplicates_the_branch )
{
    xml::xobufferstream xobs;
    xobs << xml::start( "sub-node" ) << xml::end;
    xml::xostringstream xos;
    xos << xml::start( "element" )
          << xobs
          << xobs
          << xobs
        << xml::end;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element>\n"
                       "  <sub-node/>\n"
                       "  <sub-node/>\n"
                       "  <sub-node/>\n"
                       "</element>\n", xos.str() );
}
