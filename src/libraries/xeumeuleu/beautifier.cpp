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

#include "beautifier.h"
#include "translate.h"

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

namespace
{
    static const XMLCh defaultNewLine[] = { chLF, chNull };
}

// -----------------------------------------------------------------------------
// Name: beautifier constructor
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
beautifier::beautifier( XMLFormatTarget& target, const XMLCh* newLine )
    : target_        ( target )
    , newLine_       ( translate( newLine == chNull ? defaultNewLine : newLine ) )
    , discardNewLine_( false )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: beautifier destructor
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
beautifier::~beautifier()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: beautifier::writeChars
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void beautifier::writeChars( const XMLByte* const toWrite, const unsigned int count, XMLFormatter* const formatter )
{
    if( isNewLine( toWrite, count ) )
    {
        if( ! discardNewLine_ )
            target_.writeChars( toWrite, count, formatter );
        discardNewLine_ = ! discardNewLine_;
    }
    else
    {
        target_.writeChars( toWrite, count, formatter );
        discardNewLine_ = false;
    }
}

// -----------------------------------------------------------------------------
// Name: beautifier::isNewLine
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
inline
bool beautifier::isNewLine( const XMLByte* const toWrite, const unsigned int count ) const
{
    return count == newLine_.size() && 0 == strncmp( reinterpret_cast< const char* const >( toWrite ), newLine_.c_str(), count );
}
