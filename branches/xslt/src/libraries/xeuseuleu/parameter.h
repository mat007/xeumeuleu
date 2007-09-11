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

#ifndef _xeuseuleu_parameter_h_
#define _xeuseuleu_parameter_h_

#include "xeumeuleu/xml.h"

namespace xsl
{
    class xtransform;

// =============================================================================
/** @class  parameter
    @brief  parameter
*/
// Created: SLI 2007-09-11
// =============================================================================
class parameter
{
public:
    //! @name Constructors/Destructor
    //@{
             parameter( const std::string& key, const std::string& expression );
    virtual ~parameter();
    //@}

    //! @name Operations
    //@{
    xtransform& operator()( xtransform& lhs ) const;
    //@}

private:
    //! @name Copy/Assignment
    //@{
    parameter( const parameter& );            //!< Copy constructor
    parameter& operator=( const parameter& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    const std::string key_;
    const std::string expression_;
    //@}
};

xtransform& operator<<( xtransform& lhs, const parameter& manipulator );

}

#endif // _xeuseuleu_parameter_h_
