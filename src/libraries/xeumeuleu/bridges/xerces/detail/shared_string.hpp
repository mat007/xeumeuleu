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

#ifndef xeumeuleu_shared_string_hpp
#define xeumeuleu_shared_string_hpp

#include <string>
#include <ostream>

namespace xml
{
// =============================================================================
/** @class  shared_string
    @brief  Shared string
*/
// Created: MAT 2009-10-10
// =============================================================================
class shared_string
{
public:
    //! @name Constructors/Destructor
    //@{
    shared_string( const std::string& str )
        : impl_( new impl( str ) )
    {}
    explicit shared_string( const shared_string& rhs )
        : impl_( rhs.impl_ )
    {
        ++impl_->count_;
    }
    ~shared_string()
    {
        if( --impl_->count_ == 0 )
            delete impl_;
    }
    //@}

    //! @name Operators
    //@{
    shared_string& operator=( const shared_string& rhs )
    {
        shared_string tmp( rhs );
        swap( tmp );
        return *this;
    }

    friend std::ostream& operator<<( std::ostream& os, const shared_string& s )
    {
        return os << s.impl_->str_;
    }
    //@}

    //! @name Helpers
    //@{
    void swap( shared_string& rhs )
    {
        impl* impl = impl_;
        impl_ = rhs.impl_;
        rhs.impl_ = impl;
    }
    //@}

private:
    //! @name Types
    //@{
    struct impl
    {
        impl( const std::string& str )
            : str_  ( str )
            , count_( 1 )
        {}
        std::string str_;
        int count_;
    };
    //@}

private:
    //! @name Member data
    //@{
    impl* impl_;
    //@}
};

}

#endif // xeumeuleu_shared_string_hpp
