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

#ifndef xeumeuleu_xml_hpp
#define xeumeuleu_xml_hpp

#include <xeumeuleu/streams/xistringstream.hpp>
#include <xeumeuleu/streams/xostringstream.hpp>
#include <xeumeuleu/streams/xifstream.hpp>
#include <xeumeuleu/streams/xofstream.hpp>
#include <xeumeuleu/streams/xobufferstream.hpp>
#include <xeumeuleu/streams/xibufferstream.hpp>
#include <xeumeuleu/streams/xosubstream.hpp>
#include <xeumeuleu/streams/xisubstream.hpp>
#include <xeumeuleu/streams/xistreamstream.hpp>
#include <xeumeuleu/streams/xostreamstream.hpp>
#include <xeumeuleu/streams/ximultistream.hpp>
#include <xeumeuleu/streams/exception.hpp>
#include <xeumeuleu/streams/grammar.hpp>
#include <xeumeuleu/manipulators/start.hpp>
#include <xeumeuleu/manipulators/end.hpp>
#include <xeumeuleu/manipulators/content.hpp>
#include <xeumeuleu/manipulators/cdata.hpp>
#include <xeumeuleu/manipulators/instruction.hpp>
#include <xeumeuleu/manipulators/attribute.hpp>
#include <xeumeuleu/manipulators/prefix.hpp>
#include <xeumeuleu/manipulators/ns.hpp>
#include <xeumeuleu/manipulators/list.hpp>
#include <xeumeuleu/manipulators/name_list.hpp>
#include <xeumeuleu/manipulators/attributes.hpp>
#include <xeumeuleu/manipulators/optional.hpp>
#include <xeumeuleu/manipulators/helpers.hpp>

#endif // xeumeuleu_xml_hpp
