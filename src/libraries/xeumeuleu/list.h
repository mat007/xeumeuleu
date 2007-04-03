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

#ifndef _xeumeuleu_list_h_
#define _xeumeuleu_list_h_

#include <string>
#include "visitor.h"
#include "xistream.h"
#include "caller.h"

namespace xml
{
// =============================================================================
/** @class  list_visitor
    @brief  List visitor
    @par    Using example
    @code
    class my_class
    {
    public:
        void my_method( xml::xistream& xis )
        {
            xis >> ...
        }
        void my_const_method( xml::xistream& xis ) const
        {
            xis >> ...
        }
    } my_instance;
    xml::xistream& xis = ...;
    xis >> xml::list( "node", my_instance, &my_class::my_method );
    xis >> xml::list( "node", my_instance, &my_class::my_const_method );
    @endcode
*/
// Created: MAT 2006-01-05
// =============================================================================
template< typename T >
class list_visitor : public visitor
{
public:
    //! @name Constructors/Destructor
    //@{
    list_visitor( const std::string& name, const T& functor )
        : name_   ( name )
        , functor_( functor )
    {}
    //@}

    //! @name Operations
    //@{
    virtual void process( const std::string& name, xistream& xis ) const
    {
        if( name == name_ )
            functor_( xis );
    }
    //@}

private:
    //! @name Constructors/Destructor
    //@{
    list_visitor& operator=( const list_visitor& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    const std::string name_;
    const T functor_;
    //@}
};

// -----------------------------------------------------------------------------
// Name: operator>>
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
template< typename T >
xistream& operator>>( xistream& xis, const list_visitor< T >& manipulator )
{
    xis.visit( manipulator );
    return xis;
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
template< typename T >
list_visitor< caller0< T > > list( const std::string& name, T& instance, void (T::*method)( xistream& ) )
{
    return list_visitor< caller0< T > >( name, caller0< T >( instance, method ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
template< typename T >
list_visitor< const_caller0< T > > list( const std::string& name, const T& instance, void (T::*method)( xistream& ) const )
{
    return list_visitor< const_caller0< T > >( name, const_caller0< T >( instance, method ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-02-01
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1 >
list_visitor< caller1< T, Arg1&, T1 > > list( const std::string& name, T& instance, void (T::*method)( xistream&, T1 ), Arg1& value )
{
    return list_visitor< caller1< T, Arg1&, T1 > >( name, caller1< T, Arg1&, T1 >( instance, method, value ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-02-01
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1 >
list_visitor< const_caller1< T, Arg1&, T1 > > list( const std::string& name, const T& instance, void (T::*method)( xistream&, T1 ) const, Arg1& value )
{
    return list_visitor< const_caller1< T, Arg1&, T1 > >( name, const_caller1< T, Arg1&, T1 >( instance, method, value ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-02-01
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2 >
list_visitor< caller2< T, Arg1&, T1, Arg2&, T2 > > list( const std::string& name, T& instance, void (T::*method)( xistream&, T1, T2 ), Arg1& value1, Arg2& value2 )
{
    return list_visitor< caller2< T, Arg1&, T1, Arg2&, T2 > >( name, caller2< T, Arg1&, T1, Arg2&, T2 >( instance, method, value1, value2 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-02-01
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2 >
list_visitor< const_caller2< T, Arg1&, T1, Arg2&, T2 > > list( const std::string& name, const T& instance, void (T::*method)( xistream&, T1, T2 ) const, Arg1& value1, Arg2& value2 )
{
    return list_visitor< const_caller2< T, Arg1&, T1, Arg2&, T2 > >( name, const_caller2< T, Arg1&, T1, Arg2&, T2 >( instance, method, value1, value2 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MCO 2006-03-17
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3 >
list_visitor< caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 > > list( const std::string& name, T& instance, void (T::*method)( xistream&, T1, T2, T3 ), Arg1& value1, Arg2& value2, Arg3& value3 )
{
    return list_visitor< caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 > >( name, caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 >( instance, method, value1, value2, value3 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-03-17
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3 >
list_visitor< const_caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 > > list( const std::string& name, const T& instance, void (T::*method)( xistream&, T1, T2, T3 ) const, Arg1& value1, Arg2& value2, Arg3& value3 )
{
    return list_visitor< const_caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 > >( name, const_caller3< T, Arg1&, T1, Arg2&, T2, Arg3&, T3 >( instance, method, value1, value2, value3 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: SBO 2006-05-16
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4 >
list_visitor< caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 > > list( const std::string& name, T& instance, void (T::*method)( xistream&, T1, T2, T3, T4 ), Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4 )
{
    return list_visitor< caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 > >( name, caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 >( instance, method, value1, value2, value3, value4 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: SBO 2006-05-16
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4 >
list_visitor< const_caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 > > list( const std::string& name, const T& instance, void (T::*method)( xistream&, T1, T2, T3, T4 ) const, Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4 )
{
    return list_visitor< const_caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 > >( name, const_caller4< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4 >( instance, method, value1, value2, value3, value4 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MCO 2006-06-22
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4, typename Arg5, typename T5 >
list_visitor< caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 > > list( const std::string& name, T& instance, void (T::*method)( xistream&, T1, T2, T3, T4, T5 ), Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4, Arg5& value5 )
{
    return list_visitor< caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 > >( name, caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 >( instance, method, value1, value2, value3, value4, value5 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MCO 2006-06-22
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4, typename Arg5, typename T5 >
list_visitor< const_caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 > > list( const std::string& name, const T& instance, void (T::*method)( xistream&, T1, T2, T3, T4, T5 ) const, Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4, Arg5& value5 )
{
    return list_visitor< const_caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 > >( name, const_caller5< T, Arg1&, T1, Arg2&, T2, Arg3&, T3, Arg4&, T4, Arg5&, T5 >( instance, method, value1, value2, value3, value4, value5 ) );
}

}

#endif // _xeumeuleu_list_h_
