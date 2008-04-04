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

#ifndef _xeuseuleu_output_h_
#define _xeuseuleu_output_h_

#include "xeumeuleu/xml.h"
#include <string>
#include <sstream>
#include <memory>

namespace xsl
{
    class output_imp;

// =============================================================================
/** @class  output
    @brief  Output base class
*/
// Created: SLI 2007-09-10
// =============================================================================
class output
{
public:
    //! @name Constructors/Destructor
    //@{
    virtual ~output();
    //@}

    //! @name Operations
    //@{
    void parameter( const std::string& key, const std::string& expression );

    void transform();

    void apply( const output& output );

    template< typename T > void apply( const T& value )
    {
        xos_ << value;
    }
    //@}

protected:
    //! @name Constructors/Destructor
    //@{
    output( std::ostream& target, const std::string& stylesheet );
    output( std::ostream& target, std::istream& stylesheet );
    //@}

private:
    //! @name Copy/Assignment
    //@{
    output( const output& );            //!< Copy constructor
    output& operator=( const output& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    std::ostream& target_;
    xml::xostringstream xos_;
    std::ostringstream buffer_;
    std::auto_ptr< output_imp > pTransformer_;
    //@}
};

}

#endif // _xeuseuleu_output_h_
