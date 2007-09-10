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

#include "translate.h"

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

// -----------------------------------------------------------------------------
// Name: translate constructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
translate::translate( const std::string& str )
    : pCh_    ( XMLString::transcode( str.c_str() ) )
    , isOwner_( true )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: translate constructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
translate::translate( const XMLCh* const pCh )
    : pCh_    ( pCh )
    , isOwner_( false )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: translate destructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
translate::~translate()
{
    if( isOwner_ )
        XMLString::release( const_cast< XMLCh** >( &pCh_ ) ); // $$$$ MAT 2006-01-04: not the cleanest class on earth...
}

// -----------------------------------------------------------------------------
// Name: translate::operator const XMLCh* const
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
translate::operator const XMLCh* const() const
{
    return pCh_;
}

// -----------------------------------------------------------------------------
// Name: translate::operator std::string
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
translate::operator std::string() const
{
    if( ! pCh_ )
        return std::string();
    char* pStr = XMLString::transcode( pCh_ );
    if( ! pStr )
        return std::string();
    const std::string str( pStr );
    XMLString::release( &pStr );
    return str;
}

// -----------------------------------------------------------------------------
// Name: translate::operator==
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
bool translate::operator==( const XMLCh* const pCh ) const
{
    return XMLString::equals( pCh, pCh_ );
}

// -----------------------------------------------------------------------------
// Name: translate::operator==
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
bool translate::operator==( const std::string& str ) const
{
    return translate( str ) == pCh_;
}

// -----------------------------------------------------------------------------
// Name: xml::operator==
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
bool xml::operator==( const XMLCh* const pCh, const translate& tr )
{
    return tr.operator ==( pCh );
}

// -----------------------------------------------------------------------------
// Name: xml::operator==
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
bool xml::operator==( const std::string& str, const translate& tr )
{
    return tr.operator ==( str );
}

// -----------------------------------------------------------------------------
// Name: xml::operator<<
// Created: MAT 2006-03-26
// -----------------------------------------------------------------------------
std::ostream& xml::operator<<( std::ostream& stream, const translate& tr )
{
    return stream << tr.operator std::string();
}
