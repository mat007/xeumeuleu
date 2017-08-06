/*
 *   Copyright (c) 2016, Mathieu Champlon
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

#ifndef xeumeuleu_locator_handler_hpp
#define xeumeuleu_locator_handler_hpp

#include <xeumeuleu/bridges/xerces/detail/xerces.hpp>
#include <xeumeuleu/bridges/xerces/detail/locator.hpp>

namespace xml
{
// =============================================================================
/** @class  locator_handler
    @brief  User data handler
*/
// Created: MAT 2016-31-03
// =============================================================================
class locator_handler : public XERCES_CPP_NAMESPACE::DOMUserDataHandler
{
public:
    //! @name Constructors/Destructor
    //@{
    locator_handler()
    {}
    virtual ~locator_handler()
    {}
    //@}

    //! @name Operations
    //@{
    void locate( XERCES_CPP_NAMESPACE::DOMNode& node, const std::string& uri )
    {
        node.setUserData( translate( "locator" ), new locator( uri ), this );
    }

    void locate( XERCES_CPP_NAMESPACE::DOMNode& node, const shared_string& uri, XERCES_CPP_NAMESPACE::XMLScanner& scanner )
    {
        node.setUserData( translate( "locator" ), new locator( uri, scanner ), this );
    }

    virtual void handle( DOMOperationType operation, const XMLCh* const key, void* data, const XERCES_CPP_NAMESPACE::DOMNode* src, XERCES_CPP_NAMESPACE::DOMNode* dst )
    {
        switch( operation )
        {
        case NODE_DELETED:
            delete static_cast< locator* >( data );
            break;
        case NODE_CLONED:
        case NODE_IMPORTED:
        {
            const locator* l = static_cast< locator* >( src->getUserData( key ) );
            delete static_cast< locator* >( dst->getUserData( key ) );
            dst->setUserData( key, l ? new locator( *l ) : 0, this );
            break;
        }
        default:
            break;
        }
    }
    //@}
};


inline std::string context( const XERCES_CPP_NAMESPACE::DOMNode& node )
{
    const locator* loc = static_cast< locator* >( node.getUserData( translate( "locator" ) ) );
    if( loc )
        return *loc;
    return "";
}

}

#endif // xeumeuleu_locator_handler_hpp
