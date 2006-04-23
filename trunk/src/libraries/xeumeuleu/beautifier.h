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

#ifndef _xeumeuleu_beautifier_h_
#define _xeumeuleu_beautifier_h_

#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <string>

namespace xml
{

// =============================================================================
/** @class  beautifier
    @brief  Xerces target wrapper
    
    Intercepts written data to remove double new lines (xerces pretty print 'bug')
*/
// Created: MAT 2006-01-05
// =============================================================================
class beautifier : public XERCES_CPP_NAMESPACE::XMLFormatTarget
{

public:
    //! @name Constructors/Destructor
    //@{
             beautifier( XERCES_CPP_NAMESPACE::XMLFormatTarget& target, const XMLCh* newLine );
    virtual ~beautifier();
    //@}

    //! @name Operations
    //@{
    virtual void writeChars( const XMLByte* const toWrite, const unsigned int count, XERCES_CPP_NAMESPACE::XMLFormatter* const formatter );
    //@}

private:
    //! @name Copy/Assignement
    //@{
    beautifier( const beautifier& );            //!< Copy constructor
    beautifier& operator=( const beautifier& ); //!< Assignment operator
    //@}

    //! @name Helpers
    //@{
    bool isNewLine( const XMLByte* const toWrite, const unsigned int count ) const;
    //@}

private:
    //! @name Member data
    //@{
    XERCES_CPP_NAMESPACE::XMLFormatTarget& target_;
    const std::string newLine_;
    bool discardNewLine_;
    //@}
};

}

#endif // _xeumeuleu_beautifier_h_
