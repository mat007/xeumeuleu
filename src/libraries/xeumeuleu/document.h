/*
 *   Copyright (c) 2008, Mathieu Champlon
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

#ifndef _xeumeuleu_document_h_
#define _xeumeuleu_document_h_

#include "xerces.h"
#include "xerces_ptr.h"
#include <string>

namespace xml
{
    class encoding;
    class grammar;

// =============================================================================
/** @class  document
    @brief  Document base class
*/
// Created: MAT 2008-02-25
// =============================================================================
class document
{
protected:
    //! @name Constructors/Destructor
    //@{
             document();
             document( const std::string& filename, const encoding* encoding, const grammar& grammar );
             document( const char* data, std::size_t size, const encoding* encoding, const grammar& grammar );
    virtual ~document();
    //@}

protected:
    //! @name Helpers
    //@{
    void fill( const std::string& filename, const std::string& encoding );
    void fill( std::string& data, const std::string& encoding );
    //@}

private:
    //! @name Helpers
    //@{
    static void initialize();

    void write( XERCES_CPP_NAMESPACE::XMLFormatTarget& destination, const std::string& encoding );
    //@}

protected:
    //! @name Member data
    //@{
    xerces_ptr< XERCES_CPP_NAMESPACE::DOMDocument > document_;
    //@}
};

}

#endif // _xeumeuleu_document_h_
