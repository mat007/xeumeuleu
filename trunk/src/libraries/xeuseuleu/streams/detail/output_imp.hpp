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

#ifndef xsl_output_imp_hpp
#define xsl_output_imp_hpp

#include <xeuseuleu/bridges/xalan/translate.hpp>
#include <xeuseuleu/bridges/xalan/xalan.hpp>
#include <fstream>
#include <sstream>
#include <vector>

namespace xsl
{
// =============================================================================
/** @class  output_imp
    @brief  Output implementation declaration
*/
// Created: SLI 2007-07-06
// =============================================================================
class output_imp
{
public:
    //! @name Constructors/Destructor
    //@{
             output_imp() {}
    virtual ~output_imp() {}
    //@}

    //! @name Operations
    //@{
    void parameter( const std::string& key, const std::string& expression )
    {
        parameters_.push_back( std::make_pair( key, "'" + expression + "'" ) );
    }

    virtual const std::string transform( const std::string& input ) const = 0;
    //@}

protected:
    //! @name Helpers
    //@{
    std::string transform( const std::string& input,
        const XALAN_CPP_NAMESPACE::XSLTInputSource& xsl ) const
    {
        std::istringstream is( input );
        XALAN_CPP_NAMESPACE::XSLTInputSource in( is );
        XALAN_CPP_NAMESPACE::XalanTransformer transformer;
        for( CIT_Parameters it = parameters_.begin(); it != parameters_.end(); ++it )
            transformer.setStylesheetParam( xsl::translate( it->first ), xsl::translate( it->second ) );
        std::ostringstream os;
        if( transformer.transform( in, xsl, os ) )
            error( std::string( transformer.getLastError() ) );
        return os.str();
    }
    //@}

    //! @name Operations
    //@{
    virtual void error( const std::string& message ) const = 0;
    //@}

private:
    //! @name Types
    //@{
    typedef std::vector< std::pair< std::string, std::string > > T_Parameters;
    typedef T_Parameters::const_iterator                       CIT_Parameters;
    //@}

private:
    //! @name Copy/Assignment
    //@{
    output_imp( const output_imp& );            //!< Copy constructor
    output_imp& operator=( const output_imp& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    T_Parameters parameters_;
    //@}
};

}

#endif // xsl_output_imp_hpp
