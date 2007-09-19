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

#ifndef _xeumeuleu_input_base_member_h_
#define _xeumeuleu_input_base_member_h_

#include "xerces.h"

namespace xml
{
    class encoding;
    class grammar;

// =============================================================================
/** @class  input_base_member
    @brief  Base from member idiom base class
*/
// Created: MAT 2006-03-19
// =============================================================================
class input_base_member
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit input_base_member( XERCES_CPP_NAMESPACE::DOMNode& root );
    virtual ~input_base_member();
    //@}

private:
    //! @name Copy/Assignment
    //@{
    input_base_member( const input_base_member& );            //!< Copy constructor
    input_base_member& operator=( const input_base_member& ); //!< Assignment operator
    //@}

protected:
    //! @name Helpers
    //@{
    static XERCES_CPP_NAMESPACE::DOMNode& parse( XERCES_CPP_NAMESPACE::InputSource& source, const encoding* pEncoding, const grammar& grammar );
    //@}

protected:
    //! @name Member data
    //@{
    XERCES_CPP_NAMESPACE::DOMNode& root_;
    //@}
};

}

#endif // _xeumeuleu_input_base_member_h_
