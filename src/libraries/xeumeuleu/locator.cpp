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

#include "locator.h"
#include <sstream>

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

// -----------------------------------------------------------------------------
// Name: locator constructor
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
locator::locator( const std::string& uri, const XMLScanner& scanner )
    : uri_   ( uri )
    , line_  ( scanner.getLocator()->getLineNumber() )
    , column_( scanner.getLocator()->getColumnNumber() )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: locator constructor
// Created: MAT 2008-01-20
// -----------------------------------------------------------------------------
locator::locator( const DOMLocator& rhs )
    : uri_   ( rhs.getURI() )
    , line_  ( rhs.getLineNumber() )
    , column_( rhs.getColumnNumber() )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: locator constructor
// Created: MAT 2008-01-20
// -----------------------------------------------------------------------------
locator::locator( const locator& rhs )
    : uri_   ( std::string( rhs.uri_ ) )
    , line_  ( rhs.line_ )
    , column_( rhs.column_ )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: locator destructor
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
locator::~locator()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: locator::getLineNumber
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
XMLSSize_t locator::getLineNumber() const
{
    return line_;
}

// -----------------------------------------------------------------------------
// Name: locator::getColumnNumber
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
XMLSSize_t locator::getColumnNumber() const
{
    return column_;
}

// -----------------------------------------------------------------------------
// Name: locator::getOffset
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
XMLSSize_t locator::getOffset() const
{
    return -1;
}

// -----------------------------------------------------------------------------
// Name: locator::getErrorNode
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
XERCES_CPP_NAMESPACE::DOMNode* locator::getErrorNode() const
{
    return 0;
}

// -----------------------------------------------------------------------------
// Name: locator::getURI
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
const XMLCh* locator::getURI() const
{
    return uri_;
}

// -----------------------------------------------------------------------------
// Name: locator::setLineNumber
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
void locator::setLineNumber( const XMLSSize_t /*line*/  )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: locator::setColumnNumber
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
void locator::setColumnNumber( const XMLSSize_t /*column*/ )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: locator::setOffset
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
void locator::setOffset( const XMLSSize_t /*offset*/ )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: locator::setErrorNode
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
void locator::setErrorNode( XERCES_CPP_NAMESPACE::DOMNode* const /*node*/ )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: locator::setURI
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
void locator::setURI( const XMLCh* const /*uri*/ )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: locator::operator const std::string
// Created: MAT 2008-11-24
// -----------------------------------------------------------------------------
locator::operator std::string() const
{
    std::stringstream stream;
    stream << " (line " << line_ << ", column " << column_ << ") : ";
    return uri_ + stream.str();
}
