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

#ifndef xeumeuleu_error_handler_hpp
#define xeumeuleu_error_handler_hpp

#include <xeumeuleu/streams/exception.hpp>
#include <xeumeuleu/bridges/xerces/detail/xerces.hpp>
#include <xeumeuleu/bridges/xerces/detail/translate.hpp>
#include <xeumeuleu/bridges/xerces/detail/locator.hpp>

namespace xml
{
// =============================================================================
/** @class  error_handler
    @brief  Error handler
*/
// Created: MAT 2006-01-03
// =============================================================================
class error_handler : public XERCES_CPP_NAMESPACE::DOMErrorHandler
{
public:
    //! @name Constructors/Destructor
    //@{
    error_handler()
    {}
    virtual ~error_handler()
    {}
    //@}

    //! @name Operations
    //@{
    void check()
    {
        if( ! message_.empty() )
            throw exception( message_ );
    }
    virtual bool handleError( const XERCES_CPP_NAMESPACE::DOMError& error )
    {
        if( message_.empty() )
            message_ = interpret( error );
        return false;
    }
    //@}

private:
    //! @name Helpers
    //@{
    const std::string interpret( const XERCES_CPP_NAMESPACE::DOMError& error ) const
    {
        std::string message;
        const XERCES_CPP_NAMESPACE::DOMLocator* const location = error.getLocation();
        if( location )
            message += locator( *location );
        message += translate( error.getMessage() );
        return message;
    }
    //@}

private:
    //! @name Member data
    //@{
    std::string message_;
    //@}
};

}

#endif // xeumeuleu_error_handler_hpp
