/*
 *   Copyright (c) 2009, Mathieu Champlon
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

#ifndef xeumeuleu_name_caller5_hpp
#define xeumeuleu_name_caller5_hpp

namespace xml
{
    class xistream;

// =============================================================================
/** @class  name_caller5
    @brief  Method call functor with element name and five fixed parameters
*/
// Created: MAT 2009-06-22
// =============================================================================
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4, typename Arg5, typename T5 >
class name_caller5
{
private:
    //! @name Types
    //@{
    typedef void (T::*M)( const std::string&, xistream&, T1, T2, T3, T4, T5 );
    //@}

public:
    //! @name Constructors/Destructor
    //@{
    template< typename I >
    name_caller5( I& instance, M method, Arg1 value1, Arg2 value2, Arg3 value3, Arg4 value4, Arg5 value5 )
        : method_  ( method )
        , instance_( instance )
        , value1_  ( value1 )
        , value2_  ( value2 )
        , value3_  ( value3 )
        , value4_  ( value4 )
        , value5_  ( value5 )
    {}
    //@}

    //! @name Operations
    //@{
    void operator()( const std::string& name, xistream& xis ) const
    {
        (instance_.*method_)( name, xis, value1_, value2_, value3_, value4_, value5_ );
    }
    //@}

private:
    //! @name Constructors/Destructor
    //@{
    name_caller5& operator=( const name_caller5& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    M method_;
    T& instance_;
    Arg1 value1_;
    Arg2 value2_;
    Arg3 value3_;
    Arg4 value4_;
    Arg5 value5_;
    //@}
};

// =============================================================================
/** @class  const_name_caller5
    @brief  Const method call functor with element name and five fixed parameters
*/
// Created: MAT 2009-06-22
// =============================================================================
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4, typename Arg5, typename T5 >
class const_name_caller5
{
private:
    //! @name Types
    //@{
    typedef void (T::*M)( const std::string&, xistream&, T1, T2, T3, T4, T5 ) const;
    //@}

public:
    //! @name Constructors/Destructor
    //@{
    template< typename I >
    const_name_caller5( const I& instance, M method, Arg1 value1, Arg2 value2, Arg3 value3, Arg4 value4, Arg5 value5 )
        : method_  ( method )
        , instance_( instance )
        , value1_  ( value1 )
        , value2_  ( value2 )
        , value3_  ( value3 )
        , value4_  ( value4 )
        , value5_  ( value5 )
    {}
    //@}

    //! @name Operations
    //@{
    void operator()( const std::string& name, xistream& xis ) const
    {
        (instance_.*method_)( name, xis, value1_, value2_, value3_, value4_, value5_ );
    }
    //@}

private:
    //! @name Constructors/Destructor
    //@{
    const_name_caller5& operator=( const const_name_caller5& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    M method_;
    const T& instance_;
    Arg1 value1_;
    Arg2 value2_;
    Arg3 value3_;
    Arg4 value4_;
    Arg5 value5_;
    //@}
};

}

#endif // xeumeuleu_name_caller5_hpp
