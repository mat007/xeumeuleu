/*
 *   Copyright (c) 2017, Mathieu Champlon
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

#ifndef xeumeuleu_range_list_hpp
#define xeumeuleu_range_list_hpp

#include <iterator>

namespace xml
{
    class xitream;
    class xostream;

// =============================================================================
/** @class  range_list_manipulator
    @brief  Range list manipulator
*/
// Created: MAT 2017-04-09
 // =============================================================================
template< typename R, typename F >
class range_list_manipulator
{
public:
    //! @name Constructors/Destructor
    //@{
    range_list_manipulator( const R& range, const F& f )
        : range_  ( range )
        , functor_( f )
    {}
    //@}

    //! @name Operators
    //@{
    void operator()( xostream& xos ) const
    {
        for( auto it = std::begin( range_ ); it != std::end( range_ ); ++it )
            functor_( xml::xosubstream( xos ), *it );
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    range_list_manipulator& operator=( const range_list_manipulator& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    const R& range_;
    const F& functor_;
    //@}
};

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2017-04-10
// -----------------------------------------------------------------------------
template< typename R, typename F >
range_list_manipulator< R, F > list( const R& range, const F& functor )
{
    return range_list_manipulator< R, F >( range, functor );
}

// =============================================================================
/** @class  range_name_list_manipulator
    @brief  Range name list manipulator
*/
// Created: MAT 2017-04-10
// =============================================================================
template< typename R, typename F >
class range_name_list_manipulator
{
public:
    //! @name Constructors/Destructor
    //@{
    range_name_list_manipulator( const std::string& tag, const R& range, const F& f )
        : tag_    ( tag )
        , range_  ( range )
        , functor_( f )
    {}
    //@}

    //! @name Operators
    //@{
    void operator()( xostream& xos ) const
    {
        for( auto it = std::begin( range_ ); it != std::end( range_ ); ++it )
            functor_( xml::xosubstream( xos ) << xml::start( tag_ ), *it );
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    range_name_list_manipulator& operator=( const range_name_list_manipulator& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    const std::string tag_;
    const R& range_;
    const F& functor_;
    //@}
};

// -----------------------------------------------------------------------------
// Name: list
// Created: MAT 2017-04-10
// -----------------------------------------------------------------------------
template< typename R, typename F >
range_name_list_manipulator< R, F > list( const std::string& tag, const R& range, const F& f )
{
    return range_name_list_manipulator< R, F >( tag, range, f );
}

}

#endif // xeumeuleu_range_list_hpp
