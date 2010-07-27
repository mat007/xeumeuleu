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

#ifndef xeumeuleu_input_base_hpp
#define xeumeuleu_input_base_hpp

#include <string>
#include <memory>

namespace xml
{
    class visitor;
    class output;
    class data;

// =============================================================================
/** @class  input_base
    @brief  Input definition
*/
// Created: MAT 2006-01-08
// =============================================================================
class input_base
{
public:
    //! @name Constructors/Destructor
    //@{
             input_base() {}
    virtual ~input_base() {}
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string* ns, const std::string& tag ) = 0;
    virtual void end() = 0;

    virtual data read() const = 0;

    virtual std::auto_ptr< input_base > attribute( const std::string* ns, const std::string& name ) const = 0;

    virtual std::auto_ptr< input_base > branch( bool clone ) const = 0;

    virtual void copy( output& destination ) const = 0;
    //@}

    //! @name Accessors
    //@{
    virtual bool has_child( const std::string* ns, const std::string& name ) const = 0;
    virtual bool has_attribute( const std::string* ns, const std::string& name ) const = 0;
    virtual bool has_content() const = 0;
    virtual bool has_prefix( const std::string& ns ) const = 0;

    virtual void nodes( const std::string* ns, const visitor& v ) const = 0;
    virtual void attributes( const std::string* ns, const visitor& v ) const = 0;

    virtual void prefix( const std::string& ns, std::string& prefix ) const = 0;

    virtual std::string context() const = 0;
    //@}

private:
    //! @name Copy/Assignment
    //@{
    input_base( const input_base& );            //!< Copy constructor
    input_base& operator=( const input_base& ); //!< Assignment operator
    //@}
};

}

#endif // xeumeuleu_input_base_hpp
