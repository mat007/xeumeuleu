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

#ifndef xeumeuleu_xostream_hpp
#define xeumeuleu_xostream_hpp

#include <xeumeuleu/bridges/xerces/output.hpp>
#include <string>
#include <memory>

namespace xml
{
    class xistream;

// =============================================================================
/** @class  xostream
    @brief  Xml output stream
*/
// Created: MAT 2006-01-04
// =============================================================================
class xostream
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit xostream( output& output )
        : output_( output )
    {}
    virtual ~xostream()
    {}
    //@}

    //! @name Operations
    //@{
    void start( const std::string& tag )
    {
        output_.start( tag );
    }
    void end()
    {
        output_.end();
    }

    std::auto_ptr< output > branch()
    {
        return output_.branch();
    }
    //@}

    //! @name Modifiers
    //@{
    void write( const char* value ) { write( std::string( value ) ); }
    void write( const std::string& value ) { output_.write( value ); }
    void write( bool value ) { output_.write( value ); }
    void write( int value ) { output_.write( value ); }
    void write( long value ) { output_.write( value ); }
    void write( long long value ) { output_.write( value ); }
    void write( float value ) { output_.write( value ); }
    void write( double value ) { output_.write( value ); }
    void write( long double value ) { output_.write( value ); }
    void write( unsigned int value ) { output_.write( value ); }
    void write( unsigned long value ) { output_.write( value ); }
    void write( unsigned long long value ) { output_.write( value ); }
    void write( const xistream& xis );

    void attribute( const std::string& name, const char* value )
    {
        attribute( name, std::string( value ) );
    }
    template< typename T >
    void attribute( const std::string& name, const T& value )
    {
        output_.attribute( name, value );
    }

    void cdata( const std::string& content )
    {
        output_.cdata( content );
    }
    void instruction( const std::string& target, const std::string& data )
    {
        output_.instruction( target, data );
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    xostream( const xostream& );            //!< Copy constructor
    xostream& operator=( const xostream& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    output& output_;
    //@}
};

// -----------------------------------------------------------------------------
// Name: operator<<
// Created: MAT 2008-01-19
// -----------------------------------------------------------------------------
template< typename T >
xostream& operator<<( xostream& xos, const T& value )
{
    xos.write( value );
    return xos;
}

}

#include <xeumeuleu/streams/xistream.hpp>

namespace xml
{
    inline void xostream::write( const xistream& xis )
    {
        xis.copy( output_ );
    }
}

#endif // xeumeuleu_xostream_hpp
