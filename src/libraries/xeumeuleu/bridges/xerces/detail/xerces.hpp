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

#ifndef xeumeuleu_xerces_hpp
#define xeumeuleu_xerces_hpp

#ifdef __GNUC__
#   pragma GCC system_header
#endif

#include <xercesc/dom/DOMLocator.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/dom/DOMProcessingInstruction.hpp>
#include <xercesc/dom/DOMCDATASection.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#if XERCES_VERSION_MAJOR == 3
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/dom/DOMLSOutput.hpp>
#include <xercesc/parsers/DOMLSParserImpl.hpp>
#else
#include <xercesc/dom/DOMWriter.hpp>
#include <xercesc/parsers/DOMBuilderImpl.hpp>
#endif // XERCES_VERSION_MAJOR
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/util/XMLFloat.hpp>
#include <xercesc/util/XMLDouble.hpp>
#include <xercesc/util/XMLInteger.hpp>
#include <xercesc/util/XMLChar.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/validators/common/Grammar.hpp>
#include <xercesc/internal/XMLScanner.hpp>

#if XERCES_VERSION_MAJOR == 3
typedef XMLSize_t Count_t;
#else
typedef XMLSSize_t XMLFileLoc;
typedef XMLSSize_t XMLFilePos;
typedef unsigned int Count_t;
XERCES_CPP_NAMESPACE_BEGIN
typedef DOMBuilderImpl DOMLSParserImpl;
typedef DOMBuilder DOMLSParser;
XERCES_CPP_NAMESPACE_END
#endif // XERCES_VERSION_MAJOR

namespace xml
{
    inline const XMLCh* lookupPrefix( const XERCES_CPP_NAMESPACE::DOMNode& node, const XMLCh* prefix )
    {
#if XERCES_VERSION_MAJOR == 3
        return node.lookupPrefix( prefix );
#else
        return node.lookupNamespacePrefix( prefix, false );
#endif // XERCES_VERSION_MAJOR
    }
}

#endif // xeumeuleu_xerces_hpp
