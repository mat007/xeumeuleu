/*
*   Copyright (c) 2007, Mathieu Champlon
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

#ifndef _xeuseuleu_fileoutput_h_
#define _xeuseuleu_fileoutput_h_

#include "transform.h"
#include "output.h"
#include <string>

namespace xsl
{
// =============================================================================
/** @class  file_output
    @brief  File output implementation
*/
// Created: SLI 2007-09-10
// =============================================================================
class file_output : private transform, public output
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit file_output( const std::string& stylesheet, const std::string& filename );
    virtual ~file_output();
    //@}

private:
    //! @name Copy/Assignment
    //@{
    file_output( const file_output& );            //!< Copy constructor
    file_output& operator=( const file_output& ); //!< Assignment operator
    //@}
};

}

#endif // _xeuseuleu_fileoutput_h_
