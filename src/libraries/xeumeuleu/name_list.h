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
        void my_method( const std::string& name, xml::xistream& xis, int, const std::string& )
        {
            if( name == ... )
                xis >> ...
            else if( name == ... )
                xis >> ...
        }
    } my_instance;
    xml::xistream& xis = ...;
    xis >> xml::list( my_instance, &my_class::my_method, 3, "string" );
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
template< typename T, typename M >
list_name_visitor< name_caller0< T, M > > list( T& instance, M method )
{
    return list_name_visitor< name_caller0< T, M > >( name_caller0< T, M >( instance, method ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-08-30
// -----------------------------------------------------------------------------
template< typename T, typename M, typename P1 >
list_name_visitor< name_caller1< T, M, P1& > > list( T& instance, M method, P1& value )
{
    return list_name_visitor< name_caller1< T, M, P1& > >( name_caller1< T, M, P1& >( instance, method, value ) );
}

// -----------------------------------------------------------------------------
// Name: list
// Created: AGE 2006-08-30
// -----------------------------------------------------------------------------
template< typename T, typename M, typename P1, typename P2 >
list_name_visitor< name_caller2< T, M, P1&, P2& > > list( T& instance, M method, P1& value1 )
{
    return list_name_visitor< name_caller2< T, M, P1&, P2& > >( name_caller2< T, M, P1&, P2& >( instance, method, value1, value2 ) );
}

}

#endif // _xeumeuleu_name_list_h_
