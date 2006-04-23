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

#include <string>
#include <memory>

namespace xml
{
    class output;
    class xobufferstream;

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
    virtual ~xostream();
    //@}

    //! @name Operations
    //@{
    void start( const std::string& tag );
    void end();

    std::auto_ptr< output > branch();
    //@}

    //! @name Modifiers
    //@{
    void attribute( const std::string& name, const char* value );
    void attribute( const std::string& name, const std::string& value );
    void attribute( const std::string& name, float value );
    void attribute( const std::string& name, double value );
    void attribute( const std::string& name, int value );
    void attribute( const std::string& name, bool value );
    //@}

    //! @name Operators
    //@{
    xostream& operator<<( const char* value );
    xostream& operator<<( const std::string& value );
    xostream& operator<<( float value );
    xostream& operator<<( double value );
    xostream& operator<<( int value );
    xostream& operator<<( bool value );

    xostream& operator<<( xobufferstream& xobs );
    //@}

protected:
    //! @name Constructors/Destructor
    //@{
    xostream( output& o );
    //@}

private:
    //! @name Copy/Assignement
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

}

#endif // _xeumeuleu_xostream_h_
