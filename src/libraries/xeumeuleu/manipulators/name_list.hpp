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

#ifndef xeumeuleu_name_list_hpp
#define xeumeuleu_name_list_hpp

#include <xeumeuleu/manipulators/detail/name_caller.hpp>
#include <iterator>

namespace xml
{
// =============================================================================
/** @class  name_list_manipulator
    @brief  Name list manipulator
*/
// Created: ZEBRE 2006-08-30
// =============================================================================
template< typename T >
class name_list_manipulator
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit name_list_manipulator( const T& t )
        : t_( t )
    {}
    //@}

    //! @name Operators
    //@{
    void operator()( const std::string& ns, const std::string& name, xistream& xis ) const
    {
        t_( ns, name, xis );
    }
    void operator()( xostream& xos ) const
    {
        for( auto it = std::begin( t_ ); it != std::end( t_ ); ++it )
            xml::xosubstream( xos ) << *it;
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    name_list_manipulator& operator=( const name_list_manipulator& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    const T t_;
    //@}
};

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2008-02-29
// -----------------------------------------------------------------------------
template< typename F >
name_list_manipulator< const F& > list( const F& functor )
{
    return name_list_manipulator< const F& >( functor );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-08-30
// -----------------------------------------------------------------------------
template< typename I, typename T >
name_list_manipulator< name_caller0< T > > list( I& instance, void (T::*method)( const std::string&, xistream& ) )
{
    return name_list_manipulator< name_caller0< T > >( name_caller0< T >( instance, method ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
template< typename I, typename T >
name_list_manipulator< ns_name_caller0< T > > list( I& instance, void (T::*method)( const std::string&, const std::string&, xistream& ) )
{
    return name_list_manipulator< ns_name_caller0< T > >( ns_name_caller0< T >( instance, method ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-08-30
// -----------------------------------------------------------------------------
template< typename I, typename T >
name_list_manipulator< const_name_caller0< T > > list( const I& instance, void (T::*method)( const std::string&, xistream& ) const )
{
    return name_list_manipulator< const_name_caller0< T > >( const_name_caller0< T >( instance, method ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
template< typename I, typename T >
name_list_manipulator< const_ns_name_caller0< T > > list( const I& instance, void (T::*method)( const std::string&, const std::string&, xistream& ) const )
{
    return name_list_manipulator< const_ns_name_caller0< T > >( const_ns_name_caller0< T >( instance, method ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-08-30
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1 >
name_list_manipulator< name_caller1< T, Arg1&, T1 > > list( I& instance, void (T::*method)( const std::string&, xistream&, T1 ), Arg1& value )
{
    return name_list_manipulator< name_caller1< T, Arg1&, T1 > >( name_caller1< T, Arg1&, T1 >( instance, method, value ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1 >
name_list_manipulator< ns_name_caller1< T, Arg1&, T1 > > list( I& instance, void (T::*method)( const std::string&, const std::string&, xistream&, T1 ), Arg1& value )
{
    return name_list_manipulator< ns_name_caller1< T, Arg1&, T1 > >( ns_name_caller1< T, Arg1&, T1 >( instance, method, value ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-08-30
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1 >
name_list_manipulator< const_name_caller1< T, Arg1&, T1 > > list( const I& instance, void (T::*method)( const std::string&, xistream&, T1 ) const, Arg1& value )
{
    return name_list_manipulator< const_name_caller1< T, Arg1&, T1 > >( const_name_caller1< T, Arg1&, T1 >( instance, method, value ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1 >
name_list_manipulator< const_ns_name_caller1< T, Arg1&, T1 > > list( const I& instance, void (T::*method)( const std::string&, const std::string&, xistream&, T1 ) const, Arg1& value )
{
    return name_list_manipulator< const_ns_name_caller1< T, Arg1&, T1 > >( const_ns_name_caller1< T, Arg1&, T1 >( instance, method, value ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-08-30
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2 >
name_list_manipulator< name_caller2< T, Arg1&, T1, Arg2&, T2 > > list( I& instance, void (T::*method)( const std::string&, xistream&, T1, T2 ), Arg1& value1, Arg2& value2 )
{
    return name_list_manipulator< name_caller2< T, Arg1&, T1, Arg2&, T2 > >( name_caller2< T, Arg1&, T1, Arg2&, T2 >( instance, method, value1, value2 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2 >
name_list_manipulator< ns_name_caller2< T, Arg1&, T1, Arg2&, T2 > > list( I& instance, void (T::*method)( const std::string&, const std::string&, xistream&, T1, T2 ), Arg1& value1, Arg2& value2 )
{
    return name_list_manipulator< ns_name_caller2< T, Arg1&, T1, Arg2&, T2 > >( ns_name_caller2< T, Arg1&, T1, Arg2&, T2 >( instance, method, value1, value2 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-08-30
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2 >
name_list_manipulator< const_name_caller2< T, Arg1&, T1, Arg2&, T2 > > list( const I& instance, void (T::*method)( const std::string&, xistream&, T1, T2 ) const, Arg1& value1, Arg2& value2 )
{
    return name_list_manipulator< const_name_caller2< T, Arg1&, T1, Arg2&, T2 > >( const_name_caller2< T, Arg1&, T1, Arg2&, T2 >( instance, method, value1, value2 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2 >
name_list_manipulator< const_ns_name_caller2< T, Arg1&, T1, Arg2&, T2 > > list( const I& instance, void (T::*method)( const std::string&, const std::string&, xistream&, T1, T2 ) const, Arg1& value1, Arg2& value2 )
{
    return name_list_manipulator< const_ns_name_caller2< T, Arg1&, T1, Arg2&, T2 > >( const_ns_name_caller2< T, Arg1&, T1, Arg2&, T2 >( instance, method, value1, value2 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2007-09-08
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3 >
name_list_manipulator< name_caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 > > list( I& instance, void (T::*method)( const std::string&, xistream&, T1, T2, T3 ), Arg1& value1, Arg2& value2, Arg3& value3 )
{
    return name_list_manipulator< name_caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 > >( name_caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 >( instance, method, value1, value2, value3 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3 >
name_list_manipulator< ns_name_caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 > > list( I& instance, void (T::*method)( const std::string&, const std::string&, xistream&, T1, T2, T3 ), Arg1& value1, Arg2& value2, Arg3& value3 )
{
    return name_list_manipulator< ns_name_caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 > >( ns_name_caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 >( instance, method, value1, value2, value3 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2007-09-08
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3 >
name_list_manipulator< const_name_caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 > > list( const I& instance, void (T::*method)( const std::string&, xistream&, T1, T2, T3 ) const, Arg1& value1, Arg2& value2, Arg3& value3 )
{
    return name_list_manipulator< const_name_caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 > >( const_name_caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 >( instance, method, value1, value2, value3 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3 >
name_list_manipulator< const_ns_name_caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 > > list( const I& instance, void (T::*method)( const std::string&, const std::string&, xistream&, T1, T2, T3 ) const, Arg1& value1, Arg2& value2, Arg3& value3 )
{
    return name_list_manipulator< const_ns_name_caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 > >( const_ns_name_caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 >( instance, method, value1, value2, value3 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2009-06-22
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4 >
name_list_manipulator< name_caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 > > list( I& instance, void (T::*method)( const std::string&, xistream&, T1, T2, T3, T4 ), Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4 )
{
    return name_list_manipulator< name_caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 > >( name_caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 >( instance, method, value1, value2, value3, value4 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4 >
name_list_manipulator< ns_name_caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 > > list( I& instance, void (T::*method)( const std::string&, const std::string&, xistream&, T1, T2, T3, T4 ), Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4 )
{
    return name_list_manipulator< ns_name_caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 > >( ns_name_caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 >( instance, method, value1, value2, value3, value4 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2009-06-22
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4 >
name_list_manipulator< const_name_caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 > > list( const I& instance, void (T::*method)( const std::string&, xistream&, T1, T2, T3, T4 ) const, Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4 )
{
    return name_list_manipulator< const_name_caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 > >( const_name_caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 >( instance, method, value1, value2, value3, value4 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4 >
name_list_manipulator< const_ns_name_caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 > > list( const I& instance, void (T::*method)( const std::string&, const std::string&, xistream&, T1, T2, T3, T4 ) const, Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4 )
{
    return name_list_manipulator< const_ns_name_caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 > >( const_ns_name_caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 >( instance, method, value1, value2, value3, value4 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2009-06-22
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4, typename Arg5, typename T5 >
name_list_manipulator< name_caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 > > list( I& instance, void (T::*method)( const std::string&, xistream&, T1, T2, T3, T4, T5 ), Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4, Arg5& value5 )
{
    return name_list_manipulator< name_caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 > >( name_caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 >( instance, method, value1, value2, value3, value4, value5 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4, typename Arg5, typename T5 >
name_list_manipulator< ns_name_caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 > > list( I& instance, void (T::*method)( const std::string&, const std::string&, xistream&, T1, T2, T3, T4, T5 ), Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4, Arg5& value5 )
{
    return name_list_manipulator< ns_name_caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 > >( ns_name_caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 >( instance, method, value1, value2, value3, value4, value5 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2009-06-22
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4, typename Arg5, typename T5 >
name_list_manipulator< const_name_caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 > > list( const I& instance, void (T::*method)( const std::string&, xistream&, T1, T2, T3, T4, T5 ) const, Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4, Arg5& value5 )
{
    return name_list_manipulator< const_name_caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 > >( const_name_caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 >( instance, method, value1, value2, value3, value4, value5 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
template< typename I, typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4, typename Arg5, typename T5 >
name_list_manipulator< const_ns_name_caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 > > list( const I& instance, void (T::*method)( const std::string&, const std::string&, xistream&, T1, T2, T3, T4, T5 ) const, Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4, Arg5& value5 )
{
    return name_list_manipulator< const_ns_name_caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 > >( const_ns_name_caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 >( instance, method, value1, value2, value3, value4, value5 ) );
}

}

#endif // xeumeuleu_name_list_hpp
