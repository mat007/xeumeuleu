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
#include <boost/bind.hpp>

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

    private:
        mock_custom_class( const mock_custom_class& );
        mock_custom_class& operator=( const mock_custom_class& );
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

namespace
{
    mockpp::ChainableMockObject my_function_mock( "my_function_mock" );
    mockpp::ChainableMockMethod< void > my_function_mocker( "my_function", &my_function_mock );
    void my_name_function( const std::string&, xml::xistream& )
    {
        my_function_mocker.forward();
    }
}

// -----------------------------------------------------------------------------
// Name: attributes_accepts_function_as_functor
// Created: MAT 2008-02-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( attributes_accepts_function_as_functor )
{
    xml::xistringstream xis( "<element attribute='my_attribute'/>" );
    xis >> xml::start( "element" );
    my_function_mock.reset();
    my_function_mocker.expects( mockpp::once() );
    xis >> xml::attributes( my_name_function );
    my_function_mock.verify();
}

namespace
{
    class my_functor_class
    {
    public:
        void operator()( const std::string&, xml::xistream& ) const
        {
            my_function_mocker.forward();
        }
    };
}

// -----------------------------------------------------------------------------
// Name: attributes_accepts_functor_and_makes_an_internal_copy
// Created: MAT 2008-02-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( attributes_accepts_functor_and_makes_an_internal_copy )
{
    xml::xistringstream xis( "<element attribute='my_attribute'/>" );
    xis >> xml::start( "element" );
    my_function_mock.reset();
    my_function_mocker.expects( mockpp::once() );
    xis >> xml::attributes( my_functor_class() );
    my_function_mock.verify();
}

namespace
{
    class my_non_copyable_functor_class
    {
    public:
        my_non_copyable_functor_class() {}

        void operator()( const std::string&, xml::xistream& ) const
        {
            my_function_mocker.forward();
        }
    private:
        my_non_copyable_functor_class( const my_non_copyable_functor_class& );
        my_non_copyable_functor_class& operator=( const my_non_copyable_functor_class& );
    };
}

// -----------------------------------------------------------------------------
// Name: attributes_accepts_functor_as_reference
// Created: MAT 2008-11-14
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( attributes_accepts_functor_as_reference )
{
    xml::xistringstream xis( "<element attribute='my_attribute'/>" );
    xis >> xml::start( "element" );
    my_function_mock.reset();
    my_function_mocker.expects( mockpp::once() );
    my_non_copyable_functor_class functor;
    xis >> xml::attributes< my_non_copyable_functor_class& >( functor );
    my_function_mock.verify();
}

namespace
{
    class my_bindable_class : public mockpp::ChainableMockObject
    {
    public:
        my_bindable_class()
            : mockpp::ChainableMockObject( "my_bindable_class", 0 )
            , my_method_mocker( "my_method", this )
        {}

        void my_method_1( xml::xistream& )
        {
            my_method_mocker.forward();
        }
        void const_my_method_1( xml::xistream& ) const
        {
            my_method_mocker.forward();
        }
        void my_method_2( const std::string&, xml::xistream& )
        {
            my_method_mocker.forward();
        }
        void const_my_method_2( const std::string&, xml::xistream& ) const
        {
            my_method_mocker.forward();
        }

        mockpp::ChainableMockMethod< void > my_method_mocker;
    };
}

// -----------------------------------------------------------------------------
// Name: attributes_accepts_boost_bind_as_functor
// Created: MAT 2008-02-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( attributes_accepts_boost_bind_as_functor )
{
    xml::xistringstream xis( "<element attribute='my_attribute'/>" );
    xis >> xml::start( "element" );
    {
        my_bindable_class my_instance;
        my_instance.my_method_mocker.expects( mockpp::once() );
        xis >> xml::attributes( boost::bind( &my_bindable_class::my_method_2, boost::ref( my_instance ), _1, _2 ) );
        my_instance.verify();
    }
    {
        my_bindable_class my_instance;
        my_instance.my_method_mocker.expects( mockpp::once() );
        xis >> xml::attributes( boost::bind( &my_bindable_class::const_my_method_2, boost::ref( my_instance ), _1, _2 ) );
        my_instance.verify();
    }
}
