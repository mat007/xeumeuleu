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

#ifndef _xeumeuleu_xistream_h_
#define _xeumeuleu_xistream_h_

#include <string>
#include <memory>

namespace xml
{
    class input;
    class visitor;
    class output;
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
    virtual ~xistream();
    //@}

    //! @name Operations
    //@{
    void start( const std::string& tag );
    void end();

    std::auto_ptr< input > branch( bool clone ) const;

    void copy( output& destination ) const;

    void error( const std::string& message ) const;
    //@}

    //! @name Accessors
    //@{
    void read( std::string& value ) const;
    void read( float& value ) const;
    void read( double& value ) const;
    void read( short& value ) const;
    void read( int& value ) const;
    void read( long& value ) const;
    void read( long long& value ) const;
    void read( bool& value ) const;
    void read( unsigned short& value ) const;
    void read( unsigned int& value ) const;
    void read( unsigned long& value ) const;
    void read( unsigned long long& value ) const;
    void read( xostream& xos ) const;

    void attribute( const std::string& name, std::string& value ) const;
    void attribute( const std::string& name, float& value ) const;
    void attribute( const std::string& name, double& value ) const;
    void attribute( const std::string& name, short& value ) const;
    void attribute( const std::string& name, int& value ) const;
    void attribute( const std::string& name, long& value ) const;
    void attribute( const std::string& name, long long& value ) const;
    void attribute( const std::string& name, bool& value ) const;
    void attribute( const std::string& name, unsigned short& value ) const;
    void attribute( const std::string& name, unsigned int& value ) const;
    void attribute( const std::string& name, unsigned long& value ) const;
    void attribute( const std::string& name, unsigned long long& value ) const;

    void nodes( const visitor& v ) const;
    void attributes( const visitor& v ) const;
    //@}

    //! @name Modifiers
    //@{
    void optional();
    //@}

protected:
    //! @name Constructors/Destructor
    //@{
    xistream( std::auto_ptr< input > pInput );
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
    std::auto_ptr< input > pInput_;
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

#endif // _xeumeuleu_xistream_h_
