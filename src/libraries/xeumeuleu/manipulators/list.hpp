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

#ifndef xeumeuleu_list_hpp
#define xeumeuleu_list_hpp

#include <xeumeuleu/manipulators/detail/caller.hpp>

namespace xml
{
// =============================================================================
/** @class  list_manipulator
    @brief  List manipulator
*/
// Created: MAT 2006-01-05
// =============================================================================
template< typename T >
class list_manipulator
{
public:
    //! @name Constructors/Destructor
    //@{
    list_manipulator( const std::string& name, const T& functor )
        : name_   ( name )
        , functor_( functor )
    {}
    //@}

    //! @name Operators
    //@{
    void operator()( const std::string& /*ns*/, const std::string& name, xistream& xis )
    {
        if( name == name_ )
            functor_( xis );
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    list_manipulator& operator=( const list_manipulator& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    std::string name_;
    T functor_;
    //@}
};

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2008-02-29
// -----------------------------------------------------------------------------
template< typename F >
list_manipulator< F > list( const std::string& name, const F& functor )
{
    return list_manipulator< F >( name, functor );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
template< typename I, typename T >
list_manipulator< caller0< xistream, T > > list( const std::string& name, I& instance, void (T::*method)( xistream& ) )
{
    return list_manipulator< caller0< xistream, T > >( name, caller0< xistream, T >( instance, method ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
template< typename I, typename T >
list_manipulator< const_caller0< xistream, T > > list( const std::string& name, const I& instance, void (T::*method)( xistream& ) const )
{
    return list_manipulator< const_caller0< xistream, T > >( name, const_caller0< xistream, T >( instance, method ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-02-01
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1 >
list_manipulator< caller1< xistream, T, Arg1&, T1 > > list( const std::string& name, I& instance, void (T::*method)( xistream&, T1 ), Arg1& value )
{
    return list_manipulator< caller1< xistream, T, Arg1&, T1 > >( name, caller1< xistream, T, Arg1&, T1 >( instance, method, value ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-02-01
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1 >
list_manipulator< const_caller1< xistream, T, Arg1&, T1 > > list( const std::string& name, const I& instance, void (T::*method)( xistream&, T1 ) const, Arg1& value )
{
    return list_manipulator< const_caller1< xistream, T, Arg1&, T1 > >( name, const_caller1< xistream, T, Arg1&, T1 >( instance, method, value ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-02-01
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2 >
list_manipulator< caller2< xistream, T, Arg1&, T1, Arg2&, T2 > > list( const std::string& name, I& instance, void (T::*method)( xistream&, T1, T2 ), Arg1& value1, Arg2& value2 )
{
    return list_manipulator< caller2< xistream, T, Arg1&, T1, Arg2&, T2 > >( name, caller2< xistream, T, Arg1&, T1, Arg2&, T2 >( instance, method, value1, value2 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-02-01
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2 >
list_manipulator< const_caller2< xistream, T, Arg1&, T1, Arg2&, T2 > > list( const std::string& name, const I& instance, void (T::*method)( xistream&, T1, T2 ) const, Arg1& value1, Arg2& value2 )
{
    return list_manipulator< const_caller2< xistream, T, Arg1&, T1, Arg2&, T2 > >( name, const_caller2< xistream, T, Arg1&, T1, Arg2&, T2 >( instance, method, value1, value2 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MCO 2006-03-17
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3 >
list_manipulator< caller3< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3 > > list( const std::string& name, I& instance, void (T::*method)( xistream&, T1, T2, T3 ), Arg1& value1, Arg2& value2, Arg3& value3 )
{
    return list_manipulator< caller3< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3 > >( name, caller3< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3 >( instance, method, value1, value2, value3 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-03-17
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3 >
list_manipulator< const_caller3< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3 > > list( const std::string& name, const I& instance, void (T::*method)( xistream&, T1, T2, T3 ) const, Arg1& value1, Arg2& value2, Arg3& value3 )
{
    return list_manipulator< const_caller3< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3 > >( name, const_caller3< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3 >( instance, method, value1, value2, value3 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: SBO 2006-05-16
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4 >
list_manipulator< caller4< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 > > list( const std::string& name, I& instance, void (T::*method)( xistream&, T1, T2, T3, T4 ), Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4 )
{
    return list_manipulator< caller4< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 > >( name, caller4< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 >( instance, method, value1, value2, value3, value4 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: SBO 2006-05-16
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4 >
list_manipulator< const_caller4< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 > > list( const std::string& name, const I& instance, void (T::*method)( xistream&, T1, T2, T3, T4 ) const, Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4 )
{
    return list_manipulator< const_caller4< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 > >( name, const_caller4< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 >( instance, method, value1, value2, value3, value4 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MCO 2006-06-22
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4, typename Arg5, typename T5 >
list_manipulator< caller5< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 > > list( const std::string& name, I& instance, void (T::*method)( xistream&, T1, T2, T3, T4, T5 ), Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4, Arg5& value5 )
{
    return list_manipulator< caller5< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 > >( name, caller5< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 >( instance, method, value1, value2, value3, value4, value5 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MCO 2006-06-22
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4, typename Arg5, typename T5 >
list_manipulator< const_caller5< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 > > list( const std::string& name, const I& instance, void (T::*method)( xistream&, T1, T2, T3, T4, T5 ) const, Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4, Arg5& value5 )
{
    return list_manipulator< const_caller5< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 > >( name, const_caller5< xistream, T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 >( instance, method, value1, value2, value3, value4, value5 ) );
}

}

#endif // xeumeuleu_list_hpp
