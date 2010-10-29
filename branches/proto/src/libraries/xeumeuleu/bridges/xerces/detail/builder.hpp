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

#ifndef xeumeuleu_builder_hpp
#define xeumeuleu_builder_hpp

#include <xeumeuleu/bridges/xerces/detail/xerces.hpp>
#include <xeumeuleu/bridges/xerces/detail/translate.hpp>
#include <xeumeuleu/bridges/xerces/detail/locator.hpp>
#include <xeumeuleu/bridges/xerces/detail/shared_string.hpp>

namespace xml
{
// =============================================================================
/** @class  builder
    @brief  Builder
*/
// Created: MAT 2008-11-23
// =============================================================================
class builder : public XERCES_CPP_NAMESPACE::DOMLSParserImpl
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit builder( const std::string& uri )
        : uri_( uri )
    {}
    virtual ~builder()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void startElement( const XERCES_CPP_NAMESPACE::XMLElementDecl& elemDecl, const unsigned int urlId,
                               const XMLCh* const elemPrefix, const XERCES_CPP_NAMESPACE::RefVectorOf< XERCES_CPP_NAMESPACE::XMLAttr >& attrList,
                               const Count_t attrCount, const bool isEmpty, const bool isRoot )
    {
        static const translate tag( "locator" );
        XERCES_CPP_NAMESPACE::DOMLSParserImpl::startElement( elemDecl, urlId, elemPrefix, attrList, attrCount, isEmpty, isRoot );
        getCurrentNode()->setUserData( tag, new locator( uri_, *getScanner() ), 0 );
    }
    //@}

private:
    //! @name Member data
    //@{
    const shared_string uri_;
    //@}
};

}

#endif // xeumeuleu_builder_hpp
