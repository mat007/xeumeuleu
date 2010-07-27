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

#ifndef _xeumeuleu_adapter_hpp_
#define _xeumeuleu_adapter_hpp_

#include <xeumeuleu/streams/xistream.hpp>
#include <xeumeuleu/streams/detail/visitor.hpp>

namespace xml
{
// =============================================================================
/** @class  adapter
    @brief  Adapter
*/
// Created: MAT 2007-08-01
// =============================================================================
template< typename T >
class adapter : public visitor
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit adapter( T functor )
        : functor_( functor )
    {}
    //@}

    //! @name Operations
    //@{
    virtual void operator()( const std::string& ns, const std::string& name, xistream& xis ) const
    {
        functor_( ns, name, xis );
    }
    //@}

private:
    //! @name Constructors/Destructor
    //@{
    adapter& operator=( const adapter& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    mutable T functor_;
    //@}
};

}

#endif // _xeumeuleu_adapter_hpp_
