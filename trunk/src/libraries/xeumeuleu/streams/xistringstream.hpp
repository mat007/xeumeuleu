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

#ifndef xeumeuleu_xistringstream_hpp
#define xeumeuleu_xistringstream_hpp

#include <xeumeuleu/streams/xistream.hpp>
#include <xeumeuleu/streams/grammar.hpp>
#include <xeumeuleu/bridges/xerces/document.hpp>
#include <xeumeuleu/bridges/xerces/input.hpp>

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
class xistringstream : private document, public xistream
{
public:
    //! @name Constructors/Destructor
    //@{
    xistringstream( const std::string& data, const grammar& grammar = null_grammar() )
        : document( data.c_str(), data.size(), 0, grammar )
        , xistream( input_ )
        , input_( *document_ )
    {}
    xistringstream( const std::string& data, const encoding& encoding, const grammar& grammar = null_grammar() )
        : document( data.c_str(), data.size(), &encoding, grammar )
        , xistream( input_ )
        , input_( *document_ )
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

private:
    //! @name Member data
    //@{
    input input_;
    //@}
};

}

#endif // xeumeuleu_xistringstream_hpp
