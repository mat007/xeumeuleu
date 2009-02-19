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

#include "transform.h"
#include "xalan.h"
#include "xeumeuleu/chained_exception.h"

using namespace xsl;

// -----------------------------------------------------------------------------
// Name: transform constructor
// Created: SLI 2007-07-06
// -----------------------------------------------------------------------------
transform::transform()
{
    try
    {
        static const struct Initializer
        {
            Initializer()
            {
                XERCES_CPP_NAMESPACE::XMLPlatformUtils::Initialize();
                XALAN_CPP_NAMESPACE::XalanTransformer::initialize();
            }
            ~Initializer()
            {
#ifdef _MSC_VER // $$$$ MAT : xalan seems to have a problem with cygwin/gcc, not sure why it crashes exactly...
                XALAN_CPP_NAMESPACE::XalanTransformer::terminate();
#endif
                XERCES_CPP_NAMESPACE::XMLPlatformUtils::Terminate();
            }
        } initializer;
    }
    catch( const XERCES_CPP_NAMESPACE::XMLException& e )
    {
        throw xml::chained_exception( e );
    }
}

// -----------------------------------------------------------------------------
// Name: transform destructor
// Created: SLI 2007-07-06
// -----------------------------------------------------------------------------
transform::~transform()
{
    // NOTHING
}
