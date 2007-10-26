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
#include <fstream>

using namespace mockpp;

namespace
{
    void BOOST_CHECK_FILE_EXISTS( const std::string& filename )
    {
        std::ifstream file( filename.c_str() );
        BOOST_CHECK( file.is_open() );
        file.close();
        std::remove( filename.c_str() );
    }
}

// -----------------------------------------------------------------------------
// Name: tranformation_creates_a_file
// Created: SLI 2007-09-07
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( tranformation_creates_a_file )
{
    const std::string output = "output.xml";
    xsl::xftransform xf( BOOST_RESOLVE( "stylesheet.xsl" ), output );
    xf << xml::start( "root" )
       << xml::end();
    BOOST_CHECK_FILE_EXISTS( output );
}

// -----------------------------------------------------------------------------
// Name: file_to_file_transformation_in_one_line
// Created: MCO 2007-10-26
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( file_to_file_transformation_in_one_line )
{
    const std::string output = "output.xml";
    xsl::xftransform( BOOST_RESOLVE( "stylesheet.xsl" ), output ) << xml::xifstream( BOOST_RESOLVE( "input.xml" ) );
    BOOST_CHECK_FILE_EXISTS( output );
}
