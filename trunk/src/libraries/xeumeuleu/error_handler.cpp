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

#include "xeumeuleu_pch.h"
#include "error_handler.h"
#include "exception.h"
#include "translate.h"
#include <sstream>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMLocator.hpp>

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

// -----------------------------------------------------------------------------
// Name: error_handler constructor
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
error_handler::error_handler()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: error_handler destructor
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
error_handler::~error_handler()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: error_handler::handleError
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
bool error_handler::handleError( const DOMError& error )
{
    throw xml::exception( interpret( error ) );
}

// -----------------------------------------------------------------------------
// Name: error_handler::interpret
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
std::string error_handler::interpret( const DOMError& error ) const
{
    std::stringstream message;
    const DOMLocator* const pLocation = error.getLocation();
    if( pLocation )
        message << translate( pLocation->getURI() ).operator std::string()
                << " (line " << pLocation->getLineNumber() << ", column " << pLocation->getColumnNumber() << ") : ";
    message << translate( error.getMessage() ).operator std::string();
    return message.str();
}
