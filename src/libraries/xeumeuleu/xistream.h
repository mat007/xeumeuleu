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

#ifndef xeumeuleu_xistream_h
#define xeumeuleu_xistream_h

#include "input.h"
#include <string>
#include <memory>

namespace xml
{
    class xostream;

// =============================================================================
/** @class  xistream
    @brief  Xml input stream
*/
// Created: MAT 2006-01-04
// =============================================================================
class xistream
{
public:
    //! @name Constructors/Destructor
    //@{
    virtual ~xistream()
    {}
    //@}

    //! @name Operations
    //@{
    void start( const std::string& tag )
    {
        input_->start( tag );
    }
    void end()
    {
        input_->end();
    }

    std::auto_ptr< input > branch( bool clone ) const
    {
        return input_->branch( clone );
    }
    void copy( output& destination ) const
    {
        input_->copy( destination );
    }

    void error( const std::string& message ) const
    {
        input_->error( message );
    }
    //@}

    //! @name Accessors
    //@{
#define READ( type ) void read( type& value ) const { input_->read( value ); }
    READ( std::string )
    READ( bool )
    READ( short )
    READ( int )
    READ( long )
    READ( long long )
    READ( float )
    READ( double )
    READ( long double )
    READ( unsigned short )
    READ( unsigned int )
    READ( unsigned long )
    READ( unsigned long long )
#undef READ
    void read( xostream& xos ) const;

    template< typename T >
    void attribute( const std::string& name, T& value ) const
    {
        input_->attribute( name, value );
    }

    void nodes( const visitor& v ) const
    {
        input_->nodes( v );
    }
    void attributes( const visitor& v ) const
    {
        input_->attributes( v );
    }

    bool has_child( const std::string& name ) const
    {
        return input_->has_child( name );
    }
    bool has_attribute( const std::string& name ) const
    {
        return input_->has_attribute( name );
    }
    bool has_content() const
    {
        return input_->has_content();
    }
    //@}

    //! @name Modifiers
    //@{
    void optional()
    {
        input_->optional();
    }
    //@}

protected:
    //! @name Constructors/Destructor
    //@{
    xistream( std::auto_ptr< input > input )
        : input_( input )
    {}
    //@}

private:
    //! @name Copy/Assignment
    //@{
    xistream( const xistream& );            //!< Copy constructor
    xistream& operator=( const xistream& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    std::auto_ptr< input > input_;
    //@}
};

// -----------------------------------------------------------------------------
// Name: operator>>
// Created: MAT 2008-01-19
// -----------------------------------------------------------------------------
template< typename T >
xistream& operator>>( xistream& xis, T& value )
{
    xis.read( value );
    return xis;
}

}

#include "xostream.h"

namespace xml
{
    inline void xistream::read( xostream& xos ) const
    {
        xos.write( *this );
    }
}

#endif // xeumeuleu_xistream_h
