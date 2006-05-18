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

#ifndef _xeumeuleu_output_h_
#define _xeumeuleu_output_h_

#include <sstream>
#include <memory>
#include <xercesc/dom/DOMDocument.hpp>

namespace xml
{

// =============================================================================
/** @class  output
    @brief  Output
*/
// Created: MAT 2006-01-04
// =============================================================================
class output
{

public:
    //! @name Constructors/Destructor
    //@{
             output( XERCES_CPP_NAMESPACE::DOMDocument& document, XERCES_CPP_NAMESPACE::DOMNode& root );
    virtual ~output();
    //@}

    //! @name Operations
    //@{
    void start( const std::string& tag );
    void end();

    void write( const std::string& value );

    template< typename T > void write( const T value )
    {
        write( serialize( value ) );
    }

    void attribute( const std::string& name, const std::string& value );

    template< typename T > void attribute( const std::string& name, T value )
    {
        attribute( name, serialize( value ) );
    }

    void attach( const output& rhs );

    std::auto_ptr< output > branch();

    void flush();
    //@}

protected:
    //! @name Operations
    //@{
    virtual void finished() = 0;
    //@}

private:
    //! @name Copy/Assignement
    //@{
    output( const output& );            //!< Copy constructor
    output& operator=( const output& ); //!< Assignment operator
    //@}

    //! @name Helpers
    //@{
    std::string context() const;

    template< typename T > std::string serialize( T& value )
    {
        std::stringstream stream;
        stream << std::boolalpha << value;
        return stream.str();
    }
    
    bool isRoot() const;
    //@}

private:
    //! @name Member data
    //@{
    XERCES_CPP_NAMESPACE::DOMDocument& document_;
    XERCES_CPP_NAMESPACE::DOMNode&     root_;
    XERCES_CPP_NAMESPACE::DOMNode*     pCurrent_;
    //@}
};

}

#endif // _xeumeuleu_output_h_
