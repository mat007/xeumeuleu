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

#include "xbuffertransform.h"
#include "xtransform.h"

using namespace xsl;

// -----------------------------------------------------------------------------
// Name: xbuffertransform constructor
// Created: SLI 2007-09-26
// -----------------------------------------------------------------------------
xbuffertransform::xbuffertransform( const std::string& stylesheet )
    : stylesheet_( stylesheet )
    , pStream_   ( 0 )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: xbuffertransform constructor
// Created: SLI 2008-04-04
// -----------------------------------------------------------------------------
xbuffertransform::xbuffertransform( std::istream& stylesheet )
    : pStream_( &stylesheet )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: xbuffertransform destructor
// Created: SLI 2007-09-26
// -----------------------------------------------------------------------------
xbuffertransform::~xbuffertransform()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: xbuffertransform::apply
// Created: SLI 2007-09-26
// -----------------------------------------------------------------------------
void xbuffertransform::apply( xtransform& xst ) const
{
    if( pStream_ == 0 )
        xst.add( stylesheet_ );
    else
        xst.add( *pStream_ );
}
