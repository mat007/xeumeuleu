/*
 *   Copyright (c) 2009, Mathieu Champlon
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
// Name: xostreamstream_writes_to_stream_when_complete
// Created: MCO 2009-11-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( xostreamstream_writes_to_stream_when_complete )
{
    std::stringstream stream;
    xml::xostreamstream xos( stream );
    xos << xml::start( "element" ) << xml::end;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element/>\n", stream.str() );
}

// -----------------------------------------------------------------------------
// Name: xostreamstream_writes_to_stream_upon_destruction
// Created: MCO 2009-11-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( xostreamstream_writes_to_stream_upon_destruction )
{
    std::stringstream stream;
    {
        xml::xostreamstream xos( stream );
        xos << xml::start( "element" );
    }
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element/>\n", stream.str() );
}

// -----------------------------------------------------------------------------
// Name: xostreamstream_is_not_flushed_upon_destruction_if_already_flushed
// Created: MCO 2009-11-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( xostreamstream_is_not_flushed_upon_destruction_if_already_flushed )
{
    std::stringstream stream;
    {
        xml::xostreamstream xos( stream );
        xos << xml::start( "element" ) << xml::end;
    }
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n"
                       "<element/>\n", stream.str() );
}
