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

#ifndef _xeumeuleu_locator_h_
#define _xeumeuleu_locator_h_

#include "xerces.h"
#include "translate.h"

namespace xml
{
// =============================================================================
/** @class  locator
    @brief  Locator implementation
*/
// Created: MAT 2007-09-20
// =============================================================================
class locator : public XERCES_CPP_NAMESPACE::DOMLocator
{
public:
    //! @name Constructors/Destructor
    //@{
             locator( const std::string& uri, const XERCES_CPP_NAMESPACE::XMLScanner& scanner );
             locator( const locator& rhs );
             locator( const XERCES_CPP_NAMESPACE::DOMLocator& rhs );
    virtual ~locator();
    //@}

    //! @name Accessors
    //@{
    virtual XMLSSize_t getLineNumber() const;
    virtual XMLSSize_t getColumnNumber() const;
    virtual XMLSSize_t getOffset() const;
    virtual XERCES_CPP_NAMESPACE::DOMNode* getErrorNode() const;
    virtual const XMLCh* getURI() const;
    //@}

    //! @name Modifiers
    //@{
    virtual void setLineNumber( const XMLSSize_t line );
    virtual void setColumnNumber( const XMLSSize_t column );
    virtual void setOffset( const XMLSSize_t offset );
    virtual void setErrorNode( XERCES_CPP_NAMESPACE::DOMNode* const node );
    virtual void setURI( const XMLCh* const uri );
    //@}

    //! @name Operators
    //@{
    operator std::string() const;
    //@}

private:
    //! @name Copy/Assignment
    //@{
    locator& operator=( const locator& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    const translate uri_;
    const XMLSSize_t line_, column_;
    //@}
};

}

#endif // _xeumeuleu_locator_h_
