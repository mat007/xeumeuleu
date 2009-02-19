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

#ifndef xeuseuleu_xftransform_h
#define xeuseuleu_xftransform_h

#include "xtransform.h"

namespace xsl
{
// =============================================================================
/** @class  xftransform
    @brief  Xsl file transform
    @par    Using example
    @code
    xsl::xftransform xft( "transform.xsl", "output.xml" );
    @endcode
*/
// Created: SLI 2007-09-07
// =============================================================================
class xftransform : private transform, public xtransform
{
public:
    //! @name Constructors/Destructor
    //@{
    xftransform( const std::string& stylesheet, const std::string& filename )
        : xtransform( output_ )
        , os_    ( filename.c_str() )
        , output_( os_, stylesheet )
    {}
    xftransform( std::istream& stylesheet, const std::string& filename )
        : xtransform( output_ )
        , os_    ( filename.c_str() )
        , output_( os_, stylesheet )
    {}
    virtual ~xftransform()
    {}
    //@}

private:
    //! @name Member data
    //@{
    std::ofstream os_;
    output output_;
    //@}
};

}

#endif // xeuseuleu_xftransform_h
