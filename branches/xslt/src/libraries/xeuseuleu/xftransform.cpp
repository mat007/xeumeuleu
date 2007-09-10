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

#include "xftransform.h"
#include <xalanc/XalanTransformer/XalanTransformer.hpp>
#include <sstream>

using namespace xsl;

XALAN_USING_XALAN( XalanTransformer )
XALAN_USING_XALAN( XSLTInputSource )
XALAN_USING_XALAN( XSLTResultTarget )
XALAN_USING_XALAN( XalanDOMString )

// -----------------------------------------------------------------------------
// Name: xftransform constructor
// Created: SLI 2007-09-07
// -----------------------------------------------------------------------------
xftransform::xftransform( const std::string& stylesheet, const std::string& filename )
    : stylesheet_( stylesheet )
    , filename_  ( filename )
    , level_     ( 0 )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: xftransform destructor
// Created: SLI 2007-09-07
// -----------------------------------------------------------------------------
xftransform::~xftransform()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: xftransform::operator<<
// Created: SLI 2007-09-07
// -----------------------------------------------------------------------------
xftransform& xftransform::operator<<( const xml::start& start )
{
    stream_ << start;
    ++level_;
    return *this;
}

// -----------------------------------------------------------------------------
// Name: xftransform::operator<<
// Created: SLI 2007-09-07
// -----------------------------------------------------------------------------
xftransform& xftransform::operator<<( const xml::end& end )
{
    stream_ << end;
    --level_;
    transform();
    return *this;
}

// -----------------------------------------------------------------------------
// Name: xftransform::transform
// Created: SLI 2007-09-07
// -----------------------------------------------------------------------------
void xftransform::transform() const
{
    if( level_ == 0 )
    {
        const std::string result = stream_.str();
        std::istringstream is( result );
        XSLTInputSource in( &is );
        XSLTResultTarget out( filename_.c_str() );
        out.setEncoding( XalanDOMString( "ISO-8859-1" ) );
        XSLTInputSource xsl( stylesheet_.c_str() );
        XalanTransformer transformer;
        if( transformer.transform( in, xsl, out ) )
            throw std::runtime_error( transformer.getLastError() );
    }
}
