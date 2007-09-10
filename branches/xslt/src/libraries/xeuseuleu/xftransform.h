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

#ifndef _xeuseuleu_xftransform_h_
#define _xeuseuleu_xftransform_h_

#include "transform.h"
#include "xeumeuleu/xml.h"
#include <string>
#include <memory>

namespace xsl
{
// =============================================================================
/** @class  xftransform
    @brief  Xsl file transformation
    @par    Using example
    @code
    xsl::xftransform xft( "transform.xsl", "output.file" );
    @endcode
*/
// Created: SLI 2007-09-07
// =============================================================================
class xftransform : private transform
{
public:
    //! @name Constructors/Destructor
    //@{
             xftransform( const std::string& stylesheet, const std::string& filename );
    virtual ~xftransform();
    //@}

    //! @name Operators
    //@{
    xftransform& operator<<( const xml::start& start );
    xftransform& operator<<( const xml::end& end );

    template< typename T > xftransform& operator<<( const T& value )
    {
        stream_ << value;
        transform();
        return *this;
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    xftransform( const xftransform& );            //!< Copy constructor
    xftransform& operator=( const xftransform& ); //!< Assignment operator
    //@}

private:
    //! @name Helpers
    //@{
    void transform() const;
    //@}

private:
    //! @name Member data
    //@{
    const std::string stylesheet_;
    const std::string filename_;
    xml::xostringstream stream_;
    unsigned int level_;
    //@}
};

}

#endif // _xeuseuleu_xftransform_h_
