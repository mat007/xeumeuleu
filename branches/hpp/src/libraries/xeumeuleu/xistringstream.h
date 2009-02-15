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

#ifndef _xeumeuleu_xistringstream_h_
#define _xeumeuleu_xistringstream_h_

#include "xistream.h"
#include "grammar.h"
#include "string_input.h"

namespace xml
{
    class encoding;

// =============================================================================
/** @class  xistringstream
    @brief  Xml input string stream
    @par    Using example
    @code
    std::string data( ... );
    xml::xistringstream xis( data );
    xml::xistringstream xis( data, xml::encoding( "UTF-8" ) );
    @endcode
*/
// Created: MAT 2006-01-03
// =============================================================================
class xistringstream : public xistream
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit xistringstream( const std::string& data, const grammar& grammar = null_grammar() )
        : xistream( std::auto_ptr< input >( new string_input( data, 0, grammar ) ) )
    {}
    xistringstream( const std::string& data, const encoding& encoding, const grammar& grammar = null_grammar() )
        : xistream( std::auto_ptr< input >( new string_input( data, &encoding, grammar ) ) )
    {}
    virtual ~xistringstream()
    {}
    //@}

private:
    //! @name Copy/Assignment
    //@{
    xistringstream( const xistringstream& );            //!< Copy constructor
    xistringstream& operator=( const xistringstream& ); //!< Assignment operator
    //@}
};

}

#endif // _xeumeuleu_xistringstream_h_
