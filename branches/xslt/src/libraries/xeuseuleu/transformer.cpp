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

#include "transformer.h"
#include "exception.h"
#include "xalan.h"
#include <fstream>
#include <sstream>

using namespace xsl;
using namespace XALAN_CPP_NAMESPACE;

// -----------------------------------------------------------------------------
// Name: transformer constructor
// Created: SLI 2007-10-03
// -----------------------------------------------------------------------------
transformer::transformer( const std::string& stylesheet )
    : stylesheet_( stylesheet )
{
    std::ifstream file( stylesheet.c_str() );
    if( ! file.is_open() )
        throw exception( "Unable to open style sheet '" + stylesheet + "'" );
}

// -----------------------------------------------------------------------------
// Name: transformer destructor
// Created: SLI 2007-10-03
// -----------------------------------------------------------------------------
transformer::~transformer()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: transformer::parameter
// Created: SLI 2007-10-03
// -----------------------------------------------------------------------------
void transformer::parameter( const std::string& key, const std::string& expression )
{
    parameters_.push_back( std::make_pair( key, "'" + expression + "'" ) );
}

// -----------------------------------------------------------------------------
// Name: transformer::transform
// Created: SLI 2007-10-03
// -----------------------------------------------------------------------------
std::string transformer::transform( const std::string& input )
{
    std::istringstream is( input );
    XSLTInputSource in( &is );
    XSLTInputSource xsl( stylesheet_.c_str() );
    XalanTransformer transformer;
    for( CIT_Parameters it = parameters_.begin(); it != parameters_.end(); ++it )
        transformer.setStylesheetParam( it->first.c_str(), it->second.c_str() );
    std::ostringstream os;
    if( transformer.transform( in, xsl, os ) )
        throw exception( transformer.getLastError() );
    return os.str();
}
