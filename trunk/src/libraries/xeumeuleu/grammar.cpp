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

#include "grammar.h"
#include "translate.h"
#include "parser.h"
#include "xerces.h"
#include "exception.h"

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

// -----------------------------------------------------------------------------
// Name: external_grammar constructor
// Created: MAT 2006-03-24
// -----------------------------------------------------------------------------
external_grammar::external_grammar( const std::string& uri )
    : uri_( uri )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: external_grammar destructor
// Created: MAT 2006-03-24
// -----------------------------------------------------------------------------
external_grammar::~external_grammar()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: external_grammar::configure
// Created: MCO 2007-01-16
// -----------------------------------------------------------------------------
void external_grammar::configure( parser& parser ) const
{
    parser->setFeature( XMLUni::fgDOMValidation, true );
    parser->setFeature( XMLUni::fgXercesUseCachedGrammarInParse, true );
    // $$$$ MAT 2006-03-27: use parser->setProperty( XMLUni::fgXercesSchemaExternalNoNameSpaceSchemaLocation, ... ) ?
    if( ! parser->loadGrammar( translate( uri_ ), Grammar::SchemaGrammarType, true ) )
        throw xml::exception( "Failed to load grammar '" + uri_ + "'" );
}

// -----------------------------------------------------------------------------
// Name: internal_grammar constructor
// Created: ZEBRE 2006-08-30
// -----------------------------------------------------------------------------
internal_grammar::internal_grammar()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: internal_grammar destructor
// Created: ZEBRE 2006-08-30
// -----------------------------------------------------------------------------
internal_grammar::~internal_grammar()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: internal_grammar::configure
// Created: MCO 2007-01-16
// -----------------------------------------------------------------------------
void internal_grammar::configure( parser& parser ) const
{
    parser->setFeature( XMLUni::fgDOMValidateIfSchema, true );
}

// -----------------------------------------------------------------------------
// Name: null_grammar::null_grammar
// Created: MCO 2007-01-16
// -----------------------------------------------------------------------------
null_grammar::null_grammar()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: null_grammar::~null_grammar
// Created: MCO 2007-01-16
// -----------------------------------------------------------------------------
null_grammar::~null_grammar()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: null_grammar::configure
// Created: MCO 2007-01-16
// -----------------------------------------------------------------------------
void null_grammar::configure( parser& parser ) const
{
    parser->setFeature( XMLUni::fgDOMValidation, false );
    parser->setFeature( XMLUni::fgXercesLoadExternalDTD, false ) ;
}
