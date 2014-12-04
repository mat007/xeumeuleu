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

#ifndef xeumeuleu_locator_hpp
#define xeumeuleu_locator_hpp

#include <xeumeuleu/bridges/xerces/detail/xerces.hpp>
#include <xeumeuleu/bridges/xerces/detail/translate.hpp>
#include <xeumeuleu/bridges/xerces/detail/shared_string.hpp>
#include <sstream>

namespace xml
{
// =============================================================================
/** @class  locator
    @brief  Locator implementation
*/
// Created: MAT 2007-09-20
// =============================================================================
class locator
{
public:
    //! @name Constructors/Destructor
    //@{
    locator( const shared_string& uri, const XERCES_CPP_NAMESPACE::XMLScanner& scanner )
        : uri_   ( uri )
        , line_  ( scanner.getLocator()->getLineNumber() )
        , column_( scanner.getLocator()->getColumnNumber() )
    {}
    locator( const shared_string& uri )
        : uri_   ( uri )
        , line_  ( 0 )
        , column_( 0 )
    {}
    locator( const locator& rhs )
        : uri_   ( rhs.uri_ )
        , line_  ( rhs.line_ )
        , column_( rhs.column_ )
    {}
    locator( const XERCES_CPP_NAMESPACE::DOMLocator& rhs )
        : uri_   ( translate( rhs.getURI() ) )
        , line_  ( rhs.getLineNumber() )
        , column_( rhs.getColumnNumber() )
    {}
    //@}

    //! @name Operators
    //@{
    operator std::string() const
    {
        std::stringstream stream;
        stream << uri_ << " (line " << line_ << ", column " << column_ << ") : ";
        return stream.str();
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    locator& operator=( const locator& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    const shared_string uri_;
    const XMLFileLoc line_, column_;
    //@}
};

}

#endif // xeumeuleu_locator_hpp
