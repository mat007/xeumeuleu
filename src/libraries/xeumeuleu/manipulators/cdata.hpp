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

#ifndef xeumeuleu_cdata_hpp
#define xeumeuleu_cdata_hpp

#include <string>

namespace xml
{
    class xostream;

// =============================================================================
/** @class  cdata_manipulator
    @brief  CDATA manipulator
    @par Using example
    @code
    xml::xostream& xos = ...;
    T value;
    xos << xml::cdata( "node", value );
    xos << xml::content( "node", xml::cdata( value ) );
    @endcode
*/
// Created: MCO 2007-03-14
// =============================================================================
class cdata_manipulator
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit cdata_manipulator( const std::string& content )
        : content_( content )
    {}
    //@}

public:
    //! @name Member data
    //@{
    std::string content_;
    //@}
};

// -----------------------------------------------------------------------------
// Name: start
// Created: MAT 2010-08-19
// -----------------------------------------------------------------------------
inline cdata_manipulator cdata( const std::string& content )
{
    return cdata_manipulator( content );
}

}

#endif // xeumeuleu_cdata_hpp
