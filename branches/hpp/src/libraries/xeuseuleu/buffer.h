/*
 *   Copyright (c) 2007, Mathieu Champlon
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

#ifndef xeuseuleu_buffer_h
#define xeuseuleu_buffer_h

#include "output.h"

namespace xsl
{
// =============================================================================
/** @class  buffer
    @brief  Buffer implementation
*/
// Created: MCO 2007-10-02
// =============================================================================
class buffer
{
public:
    //! @name Constructors/Destructor
    //@{
             buffer( output& output, std::auto_ptr< buffer > next );
    explicit buffer( output& output );
            ~buffer();
    //@}

    //! @name Operations
    //@{
    void parameter( const std::string& key, const std::string& expression );

    buffer* apply( const xml::start& start );
    buffer* apply( const xml::end_manipulator& end );

    template< typename T > buffer* apply( const T& value )
    {
        output_.apply( value );
        return transform();
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    buffer( const buffer& );            //!< Copy constructor
    buffer& operator=( const buffer& ); //!< Assignment operator
    //@}

private:
    //! @name Helpers
    //@{
    buffer* transform();
    buffer* chain();
    //@}

private:
    //! @name Member data
    //@{
    output& output_;
    bool owned_; // $$$$ MAT : not so great...
    std::auto_ptr< buffer > next_;
    unsigned int level_;
    //@}
};

}

#endif // xeuseuleu_buffer_h
