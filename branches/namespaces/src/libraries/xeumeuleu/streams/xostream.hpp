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

#include <xeumeuleu/streams/detail/output_base.hpp>
#include <xeumeuleu/streams/detail/attribute_output.hpp>
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
    explicit xostream( output_base& output )
        : output_( output )
    {}
    virtual ~xostream()
    {}
    //@}

    //! @name Operations
    //@{
    void start( const std::string& tag )
    {
        if( ns_.empty() )
            output_.start( tag );
        else
        {
            std::string ns;
            ns.swap( ns_ );
            output_.start( ns, tag );
        }
    }
    void end()
    {
        output_.end();
    }

    std::auto_ptr< output_base > branch() const
    {
        return output_.branch();
    }
    //@}

    //! @name Modifiers
    //@{
    xostream& operator<<( const char* value ) { output_.write( std::string( value ) ); return *this; }
    xostream& operator<<( const std::string& value ) { output_.write( value ); return *this; }
    xostream& operator<<( bool value ) { output_.write( value ); return *this; }
    xostream& operator<<( int value ) { output_.write( value ); return *this; }
    xostream& operator<<( long value ) { output_.write( value ); return *this; }
    xostream& operator<<( long long value ) { output_.write( value ); return *this; }
    xostream& operator<<( float value ) { output_.write( value ); return *this; }
    xostream& operator<<( double value ) { output_.write( value ); return *this; }
    xostream& operator<<( long double value ) { output_.write( value ); return *this; }
    xostream& operator<<( unsigned int value ) { output_.write( value ); return *this; }
    xostream& operator<<( unsigned long value ) { output_.write( value ); return *this; }
    xostream& operator<<( unsigned long long value ) { output_.write( value ); return *this; }
    xostream& operator<<( const xistream& xis );

    void attribute( const std::string& name, const char* value )
    {
        attribute( name, std::string( value ) );
    }
    template< typename T > void attribute( const std::string& name, const T& value )
    {
        attribute_output output( output_, name );
        xostream xos( output );
        xos << value;
    }

    void cdata( const std::string& content )
    {
        output_.cdata( content );
    }
    void instruction( const std::string& target, const std::string& data )
    {
        output_.instruction( target, data );
    }
    void ns( const std::string& name )
    {
        ns_ = name;
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
    output_base& output_;
    std::string ns_;
    //@}
};

}

#include <xeumeuleu/streams/xistream.hpp>

namespace xml
{
    inline xostream& xostream::operator<<( const xistream& xis )
    {
        xis.copy( output_ );
        return *this;
    }
}

#endif // xeumeuleu_xostream_hpp
