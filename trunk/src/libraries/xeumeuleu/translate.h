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

#include <string>
#include <iostream>
#include <xercesc/util/XMLString.hpp>

#ifndef _xeumeuleu_translate_h_
#define _xeumeuleu_translate_h_

namespace xml
{

// =============================================================================
/** @class  translate
    @brief  String translation helpers
*/
// Created: MAT 2006-01-04
// =============================================================================
class translate
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit translate( const std::string& str );
    explicit translate( const XMLCh* const pCh );
    ~translate();
    //@}

    //! @name Operators
    //@{
    operator const XMLCh* const() const;
    operator std::string() const;

    bool operator==( const XMLCh* const pCh ) const;
    bool operator==( const std::string& str ) const;
    //@}

private:
    //! @name Copy/Assignement
    //@{
    translate( const translate& );            //!< Copy constructor
    translate& operator=( const translate& ); //!< Assignment operator
    //@}

private:
    //! @name Data members
    //@{
    const XMLCh* const pCh_;
    bool isOwner_;
    //@}
};

bool operator==( const XMLCh* const pCh, const translate& tr );
bool operator==( const std::string& str, const translate& tr );

std::ostream& operator<<( std::ostream& stream, const translate& tr );

}

#endif // _xeumeuleu_translate_h_
