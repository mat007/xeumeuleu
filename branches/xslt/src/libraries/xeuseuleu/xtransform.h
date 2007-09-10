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

#ifndef _xeuseuleu_xtransform_h_
#define _xeuseuleu_xtransform_h_

#include "xeumeuleu/xml.h"
#include <string>

namespace xsl
{
    class output;

// =============================================================================
/** @class  xtransform
    @brief  xtransform
*/
// Created: SLI 2007-09-10
// =============================================================================
class xtransform
{
public:
    //! @name Constructors/Destructor
    //@{
    virtual ~xtransform();
    //@}

    //! @name Operations
    //@{
    xtransform& operator<<( const xml::start& start );
    xtransform& operator<<( const xml::end& end );
    template< typename T > xtransform& operator<<( const T& value );
    //@}

protected:
    //! @name Constructors/Destructor
    //@{
    explicit xtransform( const std::string& stylesheet, output& output );
    //@}

private:
    //! @name Copy/Assignment
    //@{
    xtransform( const xtransform& );            //!< Copy constructor
    xtransform& operator=( const xtransform& ); //!< Assignment operator
    //@}

    //! @name Helpers
    //@{
    void transform() const;
    //@}

private:
    //! @name Member data
    //@{
    unsigned int level_;
    const std::string stylesheet_;
    xml::xostringstream stream_;
    output& output_;
    //@}
};

// -----------------------------------------------------------------------------
// Name: xtransform::operator<<
// Created: SLI 2007-09-10
// -----------------------------------------------------------------------------
template< typename T > xtransform& xtransform::operator<<( const T& value )
{
    stream_ << value;
    transform();
    return *this;
}

}

#endif // _xeuseuleu_xtransform_h_
