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

#ifndef _xeumeuleu_input_h_
#define _xeumeuleu_input_h_

#include "input_context.h"
#include "input_base.h"
#include <string>
#include <memory>

namespace xml
{
// =============================================================================
/** @class  input
    @brief  Input
*/
// Created: MAT 2006-01-04
// =============================================================================
class input : private input_context
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit input( std::auto_ptr< input_base > pInput );
    virtual ~input();
    //@}

    //! @name Operations
    //@{
    void start( const std::string& tag );
    void end();

    template< typename T > void read( T& value ) const
    {
        pInput_->read( value );
    }

    std::auto_ptr< input > branch( bool clone ) const;

    void copy( output& destination ) const;

    void error( const std::string& message ) const;
    //@}

    //! @name Accessors
    //@{
    template< typename T > void attribute( const std::string& name, T& value ) const
    {
        pInput_->attribute( name, value );
    }

    void nodes( const visitor& v ) const;
    void attributes( const visitor& v ) const;
    //@}

    //! @name Modifiers
    //@{
    void optional();
    //@}

private:
    //! @name Copy/Assignment
    //@{
    input( const input& );            //!< Copy constructor
    input& operator=( const input& ); //!< Assignment operator
    //@}

    //! @name Operations
    //@{
    virtual input_base& reset( std::auto_ptr< input_base > pInput );
    //@}

private:
    //! @name Member data
    //@{
    std::auto_ptr< input_base > pInput_;
    //@}
};

}

#endif // _xeumeuleu_input_h_
