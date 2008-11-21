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

#ifndef _xsl_file_output_imp_h_
#define _xsl_file_output_imp_h_

#include "output_imp.h"
#include "xeumeuleu/xml.h"
#include <string>
#include <vector>

namespace xsl
{
// =============================================================================
/** @class  file_output_imp
    @brief  File output implementation
*/
// Created: SLI 2007-07-06
// =============================================================================
class file_output_imp : public output_imp
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit file_output_imp( const std::string& stylesheet );
    virtual ~file_output_imp();
    //@}

    //! @name Operations
    //@{
    virtual void parameter( const std::string& key, const std::string& expression );

    virtual const std::string transform( const std::string& input ) const;
    //@}

private:
    //! @name Copy/Assignment
    //@{
    file_output_imp( const file_output_imp& );            //!< Copy constructor
    file_output_imp& operator=( const file_output_imp& ); //!< Assignment operator
    //@}

private:
    //! @name Types
    //@{
    typedef std::vector< std::pair< std::string, std::string > > T_Parameters;
    typedef T_Parameters::const_iterator                       CIT_Parameters;
    //@}

private:
    //! @name Member data
    //@{
    const std::string stylesheet_;
    T_Parameters parameters_;
    //@}
};

}

#endif // _xsl_file_output_imp_h_
