/*
 *   Copyright (c) 2010, Mathieu Champlon
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

#ifndef xeumeuleu_call_hpp
#define xeumeuleu_call_hpp

namespace xml
{
    class xistream;
    class xostream;

// =============================================================================
/** @class  call
    @brief  Call manipulator
    @code
    xml::xistream& xis = ...;
    xis >> xml::call( functor );

    xml::xostream& xos = ...;
    xos << xml::call( functor );
    @endcode
*/
// Created: MAT 2010-11-26
// =============================================================================
template< typename F >
class call_manipulator
{
public:
    //! @name Constructors/Destructor
    //@{
    call_manipulator( F functor )
        : functor_( functor )
    {}
    friend xistream& operator>>( xistream& xis, const call_manipulator& m )
    {
        m.functor_( xis );
        return xis;
    }
    friend xostream& operator<<( xostream& xos, const call_manipulator& m )
    {
        m.functor_( xos );
        return xos;
    }
    //@}

private:
    //! @name Constructors/Destructor
    //@{
    call_manipulator& operator=( const call_manipulator& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    F functor_;
    //@}
};

template< typename F >
call_manipulator< F > call( F functor )
{
    return call_manipulator< F >( functor );
}

}

#endif // xeumeuleu_call_hpp
