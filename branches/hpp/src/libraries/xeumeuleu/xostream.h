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

#ifndef _xeumeuleu_xostream_h_
#define _xeumeuleu_xostream_h_

#include "output.h"
#include "chained_exception.h"
#include "xerces.h"
#include <string>
#include <memory>

#define TRY try {
#define CATCH } \
            catch( const XERCES_CPP_NAMESPACE::OutOfMemoryException& ) { throw xml::exception( "Out of memory" ); } \
            catch( const XERCES_CPP_NAMESPACE::XMLException& e ) { throw chained_exception( e ); } \
            catch( const XERCES_CPP_NAMESPACE::DOMException& e ) { throw chained_exception( e ); }

namespace xml
{
    class output;
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
    virtual ~xostream()
    {}
    //@}

    //! @name Operations
    //@{
    void start( const std::string& tag )
    {
        TRY
            output_.start( tag );
        CATCH
    }
    void end()
    {
        TRY
            output_.end();
        CATCH
    }

    std::auto_ptr< output > branch()
    {
        TRY
            return output_.branch();
        CATCH
    }
    //@}

    //! @name Modifiers
    //@{
    void write( const char* value )
    {
        write( std::string( value ) );
    }
#define WRITE( type ) void write( type value ) { TRY output_.write( value ); CATCH }
    WRITE( const std::string& )
    WRITE( bool )
    WRITE( int )
    WRITE( long )
    WRITE( long long )
    WRITE( float )
    WRITE( double )
    WRITE( long double )
    WRITE( unsigned int )
    WRITE( unsigned long )
    WRITE( unsigned long long )
#undef WRITE
    void write( const xistream& xis );

    void attribute( const std::string& name, const char* value )
    {
        attribute( name, std::string( value ) );
    }
    template< typename T >
    void attribute( const std::string& name, const T& value )
    {
        TRY
            output_.attribute( name, value );
        CATCH
    }

    void cdata( const std::string& content )
    {
        TRY
            output_.cdata( content );
        CATCH
    }
    void instruction( const std::string& target, const std::string& data )
    {
        TRY
            output_.instruction( target, data );
        CATCH
    }
    //@}

protected:
    //! @name Constructors/Destructor
    //@{
    xostream( output& output )
        : output_( output )
    {}
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

#undef TRY
#undef CATCH

#include "xistream.h"

namespace xml
{
    inline void xostream::write( const xistream& xis )
    {
//        TRY
            xis.copy( output_ );
//        CATCH
    }
}

#endif // _xeumeuleu_xostream_h_
