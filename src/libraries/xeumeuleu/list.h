// *****************************************************************************
//
// This file is part of a MASA library or program.
// Refer to the included end-user license agreement for restrictions.
//
// Copyright (c) 2006 Mathématiques Appliquées SA (MASA)
//
// *****************************************************************************

#ifndef _xeumeuleu_list_h_
#define _xeumeuleu_list_h_

#include <string>
#include "functor.h"
#include "xistream.h"
#include "caller.h"

namespace xml
{

// =============================================================================
/** @class  list_manipulator
    @brief  List manipulator
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
class list_manipulator : private functor
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
    xistream& operator()( xistream& xis ) const
    {
        xis.list( name_, *this );
        return xis;
    }
    //@}

private:
    //! @name Constructors/Destructor
    //@{
    list_manipulator& operator=( const list_manipulator& ); //!< Assignment operator
    //@}

    //! @name Operations
    //@{
    virtual void process( xistream& xis ) const
    {
        functor_( xis );
    }
    //@}

private:
    //! @name Member data
    //@{
    std::string name_;
    const T functor_;
    //@}
};

// -----------------------------------------------------------------------------
// Name: operator>>
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
template< typename T >
xistream& operator>>( xistream& xis, const list_manipulator< T >& manipulator )
{
    return manipulator( xis );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
template< typename T >
list_manipulator< caller0< T > > list( const std::string& name, T& instance, void (T::*method)( xistream& ) )
{
    return list_manipulator< caller0< T > >( name, caller0< T >( instance, method ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
template< typename T >
list_manipulator< const_caller0< T > > list( const std::string& name, const T& instance, void (T::*method)( xistream& ) const )
{
    return list_manipulator< const_caller0< T > >( name, const_caller0< T >( instance, method ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-02-01
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1 >
list_manipulator< caller1< T, Arg1&, T1& > > list( const std::string& name, T& instance, void (T::*method)( xistream&, T1& ), Arg1& value )
{
    return list_manipulator< caller1< T, Arg1&, T1& > >( name, caller1< T, Arg1&, T1& >( instance, method, value ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-02-01
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1 >
list_manipulator< const_caller1< T, Arg1&, T1& > > list( const std::string& name, const T& instance, void (T::*method)( xistream&, T1& ) const, Arg1& value )
{
    return list_manipulator< const_caller1< T, Arg1&, T1& > >( name, const_caller1< T, Arg1&, T1& >( instance, method, value ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-02-01
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2 >
list_manipulator< caller2< T, Arg1&, T1&, Arg2&, T2& > > list( const std::string& name, T& instance, void (T::*method)( xistream&, T1&, T2& ), Arg1& value1, Arg2& value2 )
{
    return list_manipulator< caller2< T, Arg1&, T1&, Arg2&, T2& > >( name, caller2< T, Arg1&, T1&, Arg2&, T2& >( instance, method, value1, value2 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-02-01
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2 >
list_manipulator< const_caller2< T, Arg1&, T1&, Arg2&, T2& > > list( const std::string& name, const T& instance, void (T::*method)( xistream&, T1&, T2& ) const, Arg1& value1, Arg2& value2 )
{
    return list_manipulator< const_caller2< T, Arg1&, T1&, Arg2&, T2& > >( name, const_caller2< T, Arg1&, T1&, Arg2&, T2& >( instance, method, value1, value2 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MCO 2006-03-17
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3 >
list_manipulator< caller3< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3& > > list( const std::string& name, T& instance, void (T::*method)( xistream&, T1&, T2&, T3& ), Arg1& value1, Arg2& value2, Arg3& value3 )
{
    return list_manipulator< caller3< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3& > >( name, caller3< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3& >( instance, method, value1, value2, value3 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-03-17
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3 >
list_manipulator< const_caller3< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3& > > list( const std::string& name, const T& instance, void (T::*method)( xistream&, T1&, T2&, T3& ) const, Arg1& value1, Arg2& value2, Arg3& value3 )
{
    return list_manipulator< const_caller3< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3& > >( name, const_caller3< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3& >( instance, method, value1, value2, value3 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: SBO 2006-05-16
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4 >
list_manipulator< caller4< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3&, Arg4&, T4& > > list( const std::string& name, T& instance, void (T::*method)( xistream&, T1&, T2&, T3&, T4& ), Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4 )
{
    return list_manipulator< caller4< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3&, Arg4&, T4& > >( name, caller4< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3&, Arg4&, T4& >( instance, method, value1, value2, value3, value4 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: SBO 2006-05-16
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4 >
list_manipulator< const_caller4< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3&, Arg4&, T4& > > list( const std::string& name, const T& instance, void (T::*method)( xistream&, T1&, T2&, T3&, T4& ) const, Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4 )
{
    return list_manipulator< const_caller4< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3&, Arg4&, T4& > >( name, const_caller4< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3&, Arg4&, T4& >( instance, method, value1, value2, value3, value4 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MCO 2006-06-22
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4, typename Arg5, typename T5 >
list_manipulator< caller5< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3&, Arg4&, T4&, Arg5&, T5& > > list( const std::string& name, T& instance, void (T::*method)( xistream&, T1&, T2&, T3&, T4&, T5& ), Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4, Arg5& value5 )
{
    return list_manipulator< caller5< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3&, Arg4&, T4&, Arg5&, T5& > >( name, caller5< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3&, Arg4&, T4&, Arg5&, T5& >( instance, method, value1, value2, value3, value4, value5 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MCO 2006-06-22
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2, typename Arg3, typename T3, typename Arg4, typename T4, typename Arg5, typename T5 >
list_manipulator< const_caller5< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3&, Arg4&, T4&, Arg5&, T5& > > list( const std::string& name, const T& instance, void (T::*method)( xistream&, T1&, T2&, T3&, T4&, T5& ) const, Arg1& value1, Arg2& value2, Arg3& value3, Arg4& value4, Arg5& value5 )
{
    return list_manipulator< const_caller5< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3&, Arg4&, T4&, Arg5&, T5& > >( name, const_caller5< T, Arg1&, T1&, Arg2&, T2&, Arg3&, T3&, Arg4&, T4&, Arg5&, T5& >( instance, method, value1, value2, value3, value4, value5 ) );
}

}

#endif // _xeumeuleu_list_h_
