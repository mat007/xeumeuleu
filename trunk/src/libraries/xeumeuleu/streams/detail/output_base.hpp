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

#ifndef xeumeuleu_output_base_hpp
#define xeumeuleu_output_base_hpp

#include <string>

namespace xml
{
// =============================================================================
/** @class  output_base
    @brief  Output base
*/
// Created: MAT 2009-11-25
// =============================================================================
class output_base
{
public:
    //! @name Constructors/Destructor
    //@{
             output_base() {}
    virtual ~output_base() {}
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string* ns, const std::string& tag ) = 0;
    virtual void end() = 0;

    virtual void write( const std::string& value ) = 0;
    virtual void write( bool value ) = 0;
    virtual void write( int value ) = 0;
    virtual void write( long value ) = 0;
    virtual void write( long long value ) = 0;
    virtual void write( float value ) = 0;
    virtual void write( double value ) = 0;
    virtual void write( long double value ) = 0;
    virtual void write( unsigned int value ) = 0;
    virtual void write( unsigned long value ) = 0;
    virtual void write( unsigned long long value ) = 0;

    virtual void cdata( const std::string& value ) = 0;
    virtual void instruction( const std::string& target, const std::string& data ) = 0;
    virtual void prefix( const std::string& ns, const std::string& prefix ) = 0;

    virtual std::auto_ptr< output_base > attribute( const std::string* ns, const std::string& name ) = 0;

    virtual void copy( const input_base& input ) = 0;

    virtual std::auto_ptr< output_base > branch() const = 0;
    //@}

private:
    //! @name Copy/Assignment
    //@{
    output_base( const output_base& );            //!< Copy constructor
    output_base& operator=( const output_base& ); //!< Assignment operator
    //@}
};

}

#endif // xeumeuleu_output_base_hpp
