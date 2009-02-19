/*
 *   Copyright (c) 2007, Mathieu Champlon
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

#ifndef xeuseuleu_xtransform_h
#define xeuseuleu_xtransform_h

#include "buffer.h"
#include "string_output.h"
#include "buffer.h"

namespace xsl
{
    class xbuffertransform;

// =============================================================================
/** @class  xtransform
    @brief  Xsl transform base class
*/
// Created: SLI 2007-09-10
// =============================================================================
class xtransform
{
public:
    //! @name Constructors/Destructor
    //@{
    virtual ~xtransform()
    {}
    //@}

    //! @name Operations
    //@{
    void add( const std::string& stylesheet )
    {
        buffer_.reset( new buffer( *new string_output( stylesheet ), buffer_ ) );
    }
    void add( std::istream& stylesheet )
    {
        buffer_.reset( new buffer( *new string_output( stylesheet ), buffer_ ) );
    }

    void write( const xbuffertransform& buffer );

    template< typename T > void write( const T& value )
    {
        buffer_.reset( buffer_->apply( value ) );
    }

    void parameter( const std::string& key, const std::string& expression )
    {
        buffer_->parameter( key, expression );
    }
    //@}

protected:
    //! @name Constructors/Destructor
    //@{
    explicit xtransform( output& output )
        : buffer_( new buffer( output ) )
    {}
    //@}

private:
    //! @name Copy/Assignment
    //@{
    xtransform( const xtransform& );            //!< Copy constructor
    xtransform& operator=( const xtransform& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    std::auto_ptr< buffer > buffer_;
    //@}
};

// -----------------------------------------------------------------------------
// Name: operator<<
// Created: MAT 2008-04-04
// -----------------------------------------------------------------------------
template< typename T >
xtransform& operator<<( xtransform& xt, const T& value )
{
    xt.write( value );
    return xt;
}

}

#include "xbuffertransform.h"

namespace xsl
{
    inline void xtransform::write( const xbuffertransform& buffer )
    {
        buffer.apply( *this );
    }
}

#endif // xeuseuleu_xtransform_h
