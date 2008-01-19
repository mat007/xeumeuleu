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

#include "xeumeuleu_test_pch.h"
#include "xeumeuleu/xml.h"

using namespace mockpp;

namespace
{
    class mock_custom_class : public mockpp::ChainableMockObject
    {
    public:
        mock_custom_class()
            : mockpp::ChainableMockObject( "mock_custom_class", 0 )
            , process_mocker( "process", this )
        {}
        void process( const std::string& name, xml::xistream& xis )
        {
            std::string content;
            xis >> xml::attribute( name, content );
            process_mocker.forward( name, content );
        }
        mockpp::ChainableMockMethod< void, std::string, std::string > process_mocker;
    };
}

// -----------------------------------------------------------------------------
// Name: read_attributes_from_element_calls_a_custom_method
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_attributes_from_element_calls_a_custom_method )
{
    mock_custom_class mock_custom;
    mock_custom.process_mocker.expects( once() ).with( eq< std::string >( "first" ), eq< std::string >( "attribute content 1" ) );
    mock_custom.process_mocker.expects( once() ).with( eq< std::string >( "second" ), eq< std::string >( "attribute content 2" ) );
    xml::xistringstream xis( "<element first='attribute content 1' second='attribute content 2'/>" );
    xis >> xml::start( "element" )
            >> xml::attributes( mock_custom, &mock_custom_class::process )
        >> xml::end();
    mock_custom.verify();
}

// -----------------------------------------------------------------------------
// Name: read_attributes_from_element_without_attribute_does_not_call_the_custom_method
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_attributes_from_element_without_attribute_does_not_call_the_custom_method )
{
    mock_custom_class mock_custom;
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
            >> xml::attributes( mock_custom, &mock_custom_class::process )
        >> xml::end();
}
