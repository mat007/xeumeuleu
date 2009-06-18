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

#ifndef xeumeuleu_xerces_wrapper_hpp
#define xeumeuleu_xerces_wrapper_hpp

#include <stdexcept>

namespace xml
{
// =============================================================================
/** @class  xerces_ptr
    @brief  Xerces object wrapper to automatically release it
*/
// Created: MAT 2006-03-20
// =============================================================================
template< typename T >
class xerces_ptr
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit xerces_ptr( T* object )
        : object_( object )
    {}
    explicit xerces_ptr( T& object )
        : object_( &object )
    {}
    virtual ~xerces_ptr()
    {
        if( object_ )
            object_->release();
    }
    //@}

    //! @name Operations
    //@{
    T& release()
    {
        if( ! object_ )
            throw std::logic_error( "dereferencing null pointer" );
        T* object = object_;
        object_ = 0;
        return *object;
    }
    //@}

    //! @name Operators
    //@{
    T* operator->()
    {
        return object_;
    }
    const T* operator->() const
    {
        return object_;
    }
    T& operator*()
    {
        if( ! object_ )
            throw std::logic_error( "dereferencing null pointer" );
        return *object_;
    }
    const T& operator*() const
    {
        if( ! object_ )
            throw std::logic_error( "dereferencing null pointer" );
        return *object_;
    }
    //@}

    //! @name Accessors
    //@{
    T* get()
    {
        return object_;
    }
    const T* get() const
    {
        return object_;
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    xerces_ptr( const xerces_ptr& );            //!< Copy constructor
    xerces_ptr& operator=( const xerces_ptr& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    T* object_;
    //@}
};

}

#endif // xeumeuleu_xerces_wrapper_hpp
