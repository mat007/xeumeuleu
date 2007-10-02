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
#include "xeuseuleu/xsl.h"

using namespace mockpp;

// -----------------------------------------------------------------------------
// Name: xbuffertransform_can_be_serialized
// Created: SLI 2007-09-25
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( xbuffertransform_can_be_serialized )
{
    xsl::xbuffertransform xbt( BOOST_RESOLVE( "stylesheet.xsl" ) );
    xsl::xstringtransform xst( BOOST_RESOLVE( "buffer_test.xsl" ) );
    xml::xistringstream xis( "<root/>" );
    xst << xbt << xis;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\"?><buffer-root/>", xst.str() );
}

// -----------------------------------------------------------------------------
// Name: xbuffertransform_can_be_inserted_in_the_serialization_flow
// Created: SLI 2007-09-28
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( xbuffertransform_can_be_inserted_in_the_serialization_flow )
{
    xsl::xbuffertransform xbt( BOOST_RESOLVE( "stylesheet.xsl" ) );
    xsl::xstringtransform xst( BOOST_RESOLVE( "flow_test.xsl" ) );
    xml::xistringstream xis( "<root/>" );
    xst << xml::start( "root" )
            << xbt << xis
            << xbt << xis
        << xml::end();
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\"?><flow-root><element/><element/></flow-root>", xst.str() );
}

// -----------------------------------------------------------------------------
// Name: xbuffertransform_can_have_parameters
// Created: SLI 2007-09-28
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( xbuffertransform_can_have_parameters )
{
    xsl::xstringtransform xst( BOOST_RESOLVE( "stylesheet.xsl" ) );
    xsl::xbuffertransform xbt( BOOST_RESOLVE( "parameter_test.xsl" ) );
    xml::xistringstream xis( "<root/>" );
    xst << xbt << xsl::parameter( "key1", "expression1" )
               << xsl::parameter( "key2", "expression2" )
               << xis;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\"?><new-root key1=\"expression1\" key2=\"expression2\"/>", xst.str() );
}
