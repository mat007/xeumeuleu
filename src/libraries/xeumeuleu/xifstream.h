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

#ifndef xeumeuleu_xifstream_h
#define xeumeuleu_xifstream_h

#include "document.h"
#include "input_imp.h"
#include "grammar.h"

namespace xml
{
// =============================================================================
/** @class  xifstream
    @brief  Xml input file stream
    @par    Using example
    @code
    xml::xifstream xis( "filename" );
    xml::xifstream xis( "filename", xml::encoding( "UTF-16" ) );
    @endcode
*/
// Created: MAT 2006-01-04
// =============================================================================
class xifstream : private document, public xistream
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit xifstream( const std::string& filename, const grammar& grammar = null_grammar() )
        : document( filename, 0, grammar )
        , xistream( std::auto_ptr< input_base >( new input_imp( *document_ ) ) )
    {}
    xifstream( const std::string& filename, const encoding& encoding, const grammar& grammar = null_grammar() )
        : document( filename, &encoding, grammar )
        , xistream( std::auto_ptr< input_base >( new input_imp( *document_ ) ) )
    {}
    virtual ~xifstream()
    {}
    //@}
};

}

#endif // xeumeuleu_xifstream_h
