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
        void my_method( xml::xistream& xis, int, const std::string& )
        {
            xis >> ...
        }
    } my_instance;
    xml::xistream& xis = ...;
    xis >> xml::list( "node", my_instance, &my_class::my_method, 3, "string" );
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
    list_visitor( const std::string& name, const T& visitor )
        : name_   ( name )
        , visitor_( visitor )
    {}
    //@}

    //! @name Operations
    //@{
    virtual void process( const std::string& name, xistream& xis ) const
    {
        if( name == name_ )
            visitor_( xis );
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
    std::string name_;
    const T visitor_;
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
template< typename T, typename M >
list_visitor< caller0< T, M > > list( const std::string& name, T& instance, M method )
{
    return list_visitor< caller0< T, M > >( name, caller0< T, M >( instance, method ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-02-01
// -----------------------------------------------------------------------------
template< typename T, typename M, typename P1 >
list_visitor< caller1< T, M, P1& > > list( const std::string& name, T& instance, M method, P1& value )
{
    return list_visitor< caller1< T, M, P1& > >( name, caller1< T, M, P1& >( instance, method, value ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-02-01
// -----------------------------------------------------------------------------
template< typename T, typename M, typename P1, typename P2 >
list_visitor< caller2< T, M, P1&, P2& > > list( const std::string& name, T& instance, M method, P1& value1, P2& value2 )
{
    return list_visitor< caller2< T, M, P1&, P2& > >( name, caller2< T, M, P1&, P2& >( instance, method, value1, value2 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MCO 2006-03-17
// -----------------------------------------------------------------------------
template< typename T, typename M, typename P1, typename P2, typename P3 >
list_visitor< caller3< T, M, P1&, P2&, P3& > > list( const std::string& name, T& instance, M method, P1& value1, P2& value2, P3& value3 )
{
    return list_visitor< caller3< T, M, P1&, P2&, P3& > >( name, caller3< T, M, P1&, P2&, P3& >( instance, method, value1, value2, value3 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: SBO 2006-05-16
// -----------------------------------------------------------------------------
template< typename T, typename M, typename P1, typename P2, typename P3, typename P4 >
list_visitor< caller4< T, M, P1&, P2&, P3&, P4& > > list( const std::string& name, T& instance, M method, P1& value1, P2& value2, P3& value3, P4& value4 )
{
    return list_visitor< caller4< T, M, P1&, P2&, P3&, P4& > >( name, caller4< T, M, P1&, P2&, P3&, P4& >( instance, method, value1, value2, value3, value4 ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: MCO 2006-06-22
// -----------------------------------------------------------------------------
template< typename T, typename M, typename P1, typename P2, typename P3, typename P4, typename P5 >
list_visitor< caller5< T, M, P1&, P2&, P3&, P4&, P5& > > list( const std::string& name, T& instance, M method, P1& value1, P2& value2, P3& value3, P4& value4, P5& value5 )
{
    return list_visitor< caller5< T, M, P1&, P2&, P3&, P4&, P5& > >( name, caller5< T, M, P1&, P2&, P3&, P4&, P5& >( instance, method, value1, value2, value3, value4, value5 ) );
}

}

#endif // _xeumeuleu_list_h_
