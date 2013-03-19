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

namespace
{
    std::istringstream stylesheet( "<?xml version='1.0' encoding='ISO-8859-1'?>" );
    const xsl::xstringtransform static_transform_is_valid( stylesheet );
}

// -----------------------------------------------------------------------------
// Name: non_existing_stylesheet_file_throws
// Created: MAT 2007-09-10
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( non_existing_stylesheet_file_throws )
{
    BOOST_CHECK_THROW( xsl::xstringtransform( "non-existing.xsl" ), xsl::exception );
}

// -----------------------------------------------------------------------------
// Name: stylesheet_can_be_a_stream
// Created: SLI 2008-04-04
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( stylesheet_can_be_a_stream )
{
    std::istringstream stylesheet(
        "<?xml version='1.0' encoding='ISO-8859-1'?>"
        "<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>"
            "<xsl:template match='/root'>"
                "<new-root>"
                    "<xsl:copy-of select='@*'/>"
                    "<xsl:apply-templates select='element'/>"
                "</new-root>"
            "</xsl:template>"
            "<xsl:template match='element'>"
                "<transformed/>"
            "</xsl:template>"
        "</xsl:stylesheet>"
    );
    xsl::xstringtransform xst( stylesheet );
    xml::xistringstream xis(
        "<root>"
            "<element/>"
            "<element/>"
        "</root>"
    );
    xst << xis;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\"?><new-root><transformed/><transformed/></new-root>", xst.str() );
}

// -----------------------------------------------------------------------------
// Name: tranformation_is_applied_at_end_root_level
// Created: SLI 2007-09-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( tranformation_is_applied_at_end_root_level )
{
    xsl::xstringtransform xst( BOOST_RESOLVE( "stylesheet.xsl" ) );
    xst << xml::start( "root" )
            << xml::start( "element" )
            << xml::end
            << xml::start( "element" )
            << xml::end;
    BOOST_CHECK( xst.str().empty() );
    xst << xml::end;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\"?><new-root><transformed/><transformed/></new-root>", xst.str() );
}

// -----------------------------------------------------------------------------
// Name: tranformation_from_an_xistream_is_valid
// Created: SLI 2007-09-10
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( tranformation_from_an_xistream_is_valid )
{
    xsl::xstringtransform xst( BOOST_RESOLVE( "stylesheet.xsl" ) );
    xml::xistringstream xis(
        "<root>"
            "<element/>"
            "<element/>"
        "</root>"
    );
    xst << xis;
    BOOST_CHECK_EQUAL( "<?xml version=\"1.0\" encoding=\"UTF-8\"?><new-root><transformed/><transformed/></new-root>", xst.str() );
}
