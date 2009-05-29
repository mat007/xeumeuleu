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

#ifndef xeumeuleu_caller1_hpp
#define xeumeuleu_caller1_hpp

namespace xml
{
    class xistream;

// =============================================================================
/** @class  caller1
    @brief  Method call functor with one fixed parameter
*/
// Created: AGE 2006-01-27
// =============================================================================
template< typename T, typename Arg, typename T1 >
class caller1
{
private:
    //! @name Types
    //@{
    typedef void (T::*M)( xistream&, T1 );
    //@}

public:
    //! @name Constructors/Destructor
    //@{
    template< typename I >
    caller1( I& instance, M method, Arg value )
        : method_  ( method )
        , instance_( instance )
        , value_   ( value )
    {}
    //@}

    //! @name Operations
    //@{
    void operator()( xistream& xis ) const
    {
        (instance_.*method_)( xis, value_ );
    }
    //@}

private:
    //! @name Constructors/Destructor
    //@{
    caller1& operator=( const caller1& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    M method_;
    T& instance_;
    Arg value_;
    //@}
};

// =============================================================================
/** @class  const_caller1
    @brief  Const method call functor with one fixed parameter
*/
// Created: AGE 2006-01-27
// =============================================================================
template< typename T, typename Arg, typename T1 >
class const_caller1
{
private:
    //! @name Types
    //@{
    typedef void (T::*M)( xistream&, T1 ) const;
    //@}

public:
    //! @name Constructors/Destructor
    //@{
    template< typename I >
    const_caller1( const I& instance, M method, Arg value )
        : method_  ( method )
        , instance_( instance )
        , value_   ( value )
    {}
    //@}

    //! @name Operations
    //@{
    void operator()( xistream& xis ) const
    {
        (instance_.*method_)( xis, value_ );
    }
    //@}

private:
    //! @name Constructors/Destructor
    //@{
    const_caller1& operator=( const const_caller1& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    M method_;
    const T& instance_;
    Arg value_;
    //@}
};

}

#endif // xeumeuleu_caller1_hpp
