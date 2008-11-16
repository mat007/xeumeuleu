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

#ifndef _xeumeuleu_null_input_h_
#define _xeumeuleu_null_input_h_

#include "input_base.h"

namespace xml
{
    class input_context;

// =============================================================================
/** @class  null_input
    @brief  Null input implementation
*/
// Created: MAT 2006-01-08
// =============================================================================
class null_input : public input_base
{
public:
    //! @name Constructors/Destructor
    //@{
             null_input();
             null_input( std::auto_ptr< input_base > input, input_context& context );
    virtual ~null_input();
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string& tag );
    virtual void end();

    virtual void read( std::string& value ) const;
    virtual void read( float& value ) const;
    virtual void read( double& value ) const;
    virtual void read( short& value ) const;
    virtual void read( int& value ) const;
    virtual void read( long& value ) const;
    virtual void read( long long& value ) const;
    virtual void read( bool& value ) const;
    virtual void read( unsigned short& value ) const;
    virtual void read( unsigned int& value ) const;
    virtual void read( unsigned long& value ) const;
    virtual void read( unsigned long long& value ) const;

    virtual std::auto_ptr< input_base > branch( bool clone ) const;

    virtual void copy( output& destination ) const;

    virtual void error( const std::string& message ) const;
    //@}

    //! @name Accessors
    //@{
    virtual bool has_element( const std::string& tag ) const;
    virtual bool has_attribute( const std::string& name ) const;
    virtual bool has_content() const;

    virtual void attribute( const std::string& name, std::string& value ) const;
    virtual void attribute( const std::string& name, float& value ) const;
    virtual void attribute( const std::string& name, double& value ) const;
    virtual void attribute( const std::string& name, short& value ) const;
    virtual void attribute( const std::string& name, int& value ) const;
    virtual void attribute( const std::string& name, long& value ) const;
    virtual void attribute( const std::string& name, long long& value ) const;
    virtual void attribute( const std::string& name, bool& value ) const;
    virtual void attribute( const std::string& name, unsigned short& value ) const;
    virtual void attribute( const std::string& name, unsigned int& value ) const;
    virtual void attribute( const std::string& name, unsigned long& value ) const;
    virtual void attribute( const std::string& name, unsigned long long& value ) const;

    virtual void nodes( const visitor& v ) const;
    virtual void attributes( const visitor& v ) const;
    //@}

private:
    //! @name Copy/Assignment
    //@{
    null_input( const null_input& );            //!< Copy constructor
    null_input& operator=( const null_input& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    std::auto_ptr< input_base > input_;
    input_context* context_;
    int level_;
    //@}
};

}

#endif // _xeumeuleu_optional_input_h_
