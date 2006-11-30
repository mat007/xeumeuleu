// *****************************************************************************
//
// This file is part of a MASA library or program.
// Refer to the included end-user license agreement for restrictions.
//
// Copyright (c) 2006 Mathématiques Appliquées SA (MASA)
//
// *****************************************************************************

#ifndef _xeumeuleu_name_list_h_
#define _xeumeuleu_name_list_h_

#include <string>
#include "visitor.h"
#include "xistream.h"
#include "name_caller.h"

namespace xml
{

// =============================================================================
/** @class  list_name_visitor
    @brief  List name visitor
    @par    Using example
    @code
    class my_class
    {
    public:
        void my_method( const std::string& name, xml::xistream& xis )
        {
            if( name == ... )
                xis >> ...
            else if( name == ... )
                xis >> ...
        }
        void my_const_method( const std::string& name, xml::xistream& xis ) const
        {
            if( name == ... )
                xis >> ...
            else if( name == ... )
                xis >> ...
        }
    } my_instance;
    xml::xistream& xis = ...;
    xis >> xml::list( my_instance, &my_class::my_method );
    xis >> xml::list( my_instance, &my_class::my_const_method );
    @endcode
*/
// Created: ZEBRE 2006-08-30
// =============================================================================
template< typename T >
class list_name_visitor : public visitor
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit list_name_visitor( const T& visitor )
        : visitor_( visitor )
    {}
    //@}

    //! @name Operations
    //@{
    virtual void process( const std::string& name, xistream& xis ) const
    {
        visitor_( name, xis );
    }
    //@}

private:
    //! @name Constructors/Destructor
    //@{
    list_name_visitor& operator=( const list_name_visitor& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    const T visitor_;
    //@}
};

// -----------------------------------------------------------------------------
// Name: operator>>
// Created: AGE 2006-08-30
// -----------------------------------------------------------------------------
template< typename T >
xistream& operator>>( xistream& xis, const list_name_visitor< T >& manipulator )
{
    xis.visit( manipulator );
    return xis;
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-08-30
// -----------------------------------------------------------------------------
template< typename T >
list_name_visitor< name_caller0< T > > list( T& instance, void (T::*method)( const std::string&, xistream& ) )
{
    return list_name_visitor< name_caller0< T > >( name_caller0< T >( instance, method ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-08-30
// -----------------------------------------------------------------------------
template< typename T >
list_name_visitor< const_name_caller0< T > > list( const T& instance, void (T::*method)( const std::string&, xistream& ) const )
{
    return list_name_visitor< const_name_caller0< T > >( const_name_caller0< T >( instance, method ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-08-30
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1 >
list_name_visitor< name_caller1< T, Arg1&, T1& > > list( T& instance, void (T::*method)( const std::string&, xistream&, T1& ), Arg1& value )
{
    return list_name_visitor< name_caller1< T, Arg1&, T1& > >( name_caller1< T, Arg1&, T1& >( instance, method, value ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-08-30
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1 >
list_name_visitor< const_name_caller1< T, Arg1&, T1& > > list( const T& instance, void (T::*method)( const std::string&, xistream&, T1& ) const, Arg1& value )
{
    return list_name_visitor< const_name_caller1< T, Arg1&, T1& > >( const_name_caller1< T, Arg1&, T1& >( instance, method, value ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-08-30
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2 >
list_name_visitor< name_caller2< T, Arg1&, T1&, Arg2&, T2& > > list( T& instance, void (T::*method)( const std::string&, xistream&, T1&, T2& ), Arg1& value1, Arg2& value2 )
{
    return list_name_visitor< name_caller2< T, Arg1&, T1&, Arg2&, T2& > >( name_caller2< T, Arg1&, T1&, Arg2&, T2& >( instance, method, value1, value2 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-08-30
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2 >
list_name_visitor< const_name_caller2< T, Arg1&, T1&, Arg2&, T2& > > list( const T& instance, void (T::*method)( const std::string&, xistream&, T1&, T2& ) const, Arg1& value1, Arg2& value2 )
{
    return list_name_visitor< const_name_caller2< T, Arg1&, T1&, Arg2&, T2& > >( const_name_caller2< T, Arg1&, T1&, Arg2&, T2& >( instance, method, value1, value2 ) );
}

}

#endif // _xeumeuleu_name_list_h_
