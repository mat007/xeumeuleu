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

#ifndef xsl_buffer_output_imp_h
#define xsl_buffer_output_imp_h

#include "output_imp.h"
#include "exception.h"
#include "xalan.h"
#include "xeumeuleu/xml.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

namespace xsl
{
// =============================================================================
/** @class  buffer_output_imp
    @brief  Buffer output implementation
*/
// Created: SLI 2007-07-06
// =============================================================================
class buffer_output_imp : public output_imp
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit buffer_output_imp( std::istream& stylesheet )
        : stylesheet_( stylesheet )
    {}
    virtual ~buffer_output_imp()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void parameter( const std::string& key, const std::string& expression )
    {
        parameters_.push_back( std::make_pair( key, "'" + expression + "'" ) );
    }

    virtual const std::string transform( const std::string& input ) const
    {
        std::istringstream is( input );
        XALAN_CPP_NAMESPACE::XSLTInputSource in( &is );
        XALAN_CPP_NAMESPACE::XSLTInputSource xsl( &stylesheet_ );
        XALAN_CPP_NAMESPACE::XalanTransformer transformer;
        for( CIT_Parameters it = parameters_.begin(); it != parameters_.end(); ++it )
            transformer.setStylesheetParam( it->first.c_str(), it->second.c_str() );
        std::ostringstream os;
        if( transformer.transform( in, xsl, os ) )
            throw xsl::exception( "XSL buffer : " + std::string( transformer.getLastError() ) );
        return os.str();
    }
    //@}

private:
    //! @name Types
    //@{
    typedef std::vector< std::pair< std::string, std::string > > T_Parameters;
    typedef T_Parameters::const_iterator                       CIT_Parameters;
    //@}

private:
    //! @name Member data
    //@{
    std::istream& stylesheet_;
    T_Parameters parameters_;
    //@}
};

}

#endif // xsl_buffer_output_imp_h
