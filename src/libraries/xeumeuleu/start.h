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

#ifndef _xeumeuleu_start_h_
#define _xeumeuleu_start_h_

#include <string>

namespace xml
{
    class xistream;
    class xostream;

// =============================================================================
/** @class  start
    @brief  Start tag manipulator
    @par    Using example
    @code
    xml::xistream& xis = ...;
    xis >> xml::start( "tag_name" );

    xml::xostream& xos = ...;
    xos << xml::start( "tag_name" );
    @endcode
*/
// Created: MAT 2006-01-03
// =============================================================================
class start
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit start( const std::string& tag );
    //@}

    //! @name Operators
    //@{
    xistream& operator()( xistream& xis ) const;
    xostream& operator()( xostream& xos ) const;
    //@}

private:
    //! @name Member data
    //@{
    std::string tag_;
    //@}
};

// -----------------------------------------------------------------------------
// Name: operator>>
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
xistream& operator>>( xistream& xis, const start& manipulator );

// -----------------------------------------------------------------------------
// Name: operator<<
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
xostream& operator<<( xostream& xos, const start& manipulator );

}

#endif // _xeumeuleu_start_h_