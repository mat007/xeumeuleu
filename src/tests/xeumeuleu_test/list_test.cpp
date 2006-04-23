// *****************************************************************************
//
// This file is part of a MASA library or program.
// Refer to the included end-user license agreement for restrictions.
//
// Copyright (c) 2005 Mathématiques Appliquées SA (MASA)
//
// *****************************************************************************

#include "xeumeuleu_test_pch.h"
#include "xeumeuleu/xml.h"

using namespace mockpp;

namespace
{
    class xistream_constraint : public mockpp::Constraint< xml::xistream >
    {
    public:
        xistream_constraint( const std::string& content )
            : content_( content )
        {}
        virtual bool eval( const xml::xistream& arg ) const
        {
            xml::xistream& xis = const_cast< xml::xistream& >( arg );
            std::string content;
            xis >> content;
            return content_ == content;
        }
        virtual mockpp::String describeTo( mockpp::String &buffer ) const
        {
            mockpp::String fmt = MOCKPP_PCHAR( "xistream content '%1'" );
            fmt << content_;
            buffer += fmt;
            return buffer;
        }
    private:
        const std::string content_;
    };

    class mock_custom_class : public mockpp::ChainableMockObject
    {
    public:
        mock_custom_class()
            : mockpp::ChainableMockObject( "mock_custom_class", 0 )
            , process_mocker             ( "process", this )
        {}
        void process( xml::xistream& xis )
        {
            process_mocker.forward( xis );
        }
        mockpp::ChainableMockMethod< void, xml::xistream > process_mocker;
    };
}

// -----------------------------------------------------------------------------
// Name: read_list_from_element_calls_a_custom_method
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( read_list_from_element_calls_a_custom_method )
{
    mock_custom_class mock_custom;
    mock_custom.process_mocker.expects( once() ).with( new xistream_constraint( "content number one" ) );
    mock_custom.process_mocker.expects( once() ).with( new xistream_constraint( "content number two" ) );
    xml::xistringstream xis( "<element>"
                               "<sub-node>content number one</sub-node>"
                               "<sub-node>content number two</sub-node>"
                             "</element>" );
    xis >> xml::start( "element" )
            >> xml::list( "sub-node", mock_custom, &mock_custom_class::process )
        >> xml::end();
    mock_custom.verify();
}

namespace
{
    class mock_custom_class_with_parameters : public mockpp::ChainableMockObject
    {
    public:
        mock_custom_class_with_parameters()
            : mockpp::ChainableMockObject( "mock_custom_class", 0 )
            , process_mocker             ( "process", this )
        {}
        void process( xml::xistream& xis, int& p1, const float& p2 )
        {
            process_mocker.forward( xis, p1, p2 );
        }
        mockpp::ChainableMockMethod< void, xml::xistream, int, float > process_mocker;
    };
}

// -----------------------------------------------------------------------------
// Name: read_list_from_element_calls_a_custom_method_with_parameters
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( read_list_from_element_calls_a_custom_method_with_parameters )
{
    mock_custom_class_with_parameters mock_custom;
    int p1 = 12;
    const float p2 = 12.42f;
    mock_custom.process_mocker.expects( mockpp::once() ).with( new xistream_constraint( "content" ), eq( p1 ), eq( p2 ) );
    xml::xistringstream xis( "<element>"
                               "<sub-node>content</sub-node>"
                             "</element>" );
    xis >> xml::start( "element" )
            >> xml::list( "sub-node", mock_custom, &mock_custom_class_with_parameters::process, p1, p2 )
        >> xml::end();
    mock_custom.verify();
}

namespace
{
    class my_interface
    {
    };

    class mock_custom_class_with_polymorphic_parameter : public mockpp::ChainableMockObject
    {
    public:
        mock_custom_class_with_polymorphic_parameter()
            : mockpp::ChainableMockObject( "mock_custom_class", 0 )
            , process_mocker             ( "process", this )
        {}
        void process( xml::xistream& xis, my_interface& p1 )
        {
            process_mocker.forward( xis, &p1 );
        }
        mockpp::ChainableMockMethod< void, xml::xistream, my_interface* > process_mocker;
    };

    class my_class : public my_interface
    {
    };
}

// -----------------------------------------------------------------------------
// Name: read_list_from_element_calls_a_custom_method_with_polymorphic_parameter
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( read_list_from_element_calls_a_custom_method_with_polymorphic_parameter )
{
    mock_custom_class_with_polymorphic_parameter mock_custom;
    my_class my_instance;
    mock_custom.process_mocker.expects( mockpp::once() ).with( new xistream_constraint( "content" ), eq< my_interface* >( &my_instance ) );
    xml::xistringstream xis( "<element>"
                               "<sub-node>content</sub-node>"
                             "</element>" );
    xis >> xml::start( "element" )
            >> xml::list( "sub-node", mock_custom, &mock_custom_class_with_polymorphic_parameter::process, my_instance )
        >> xml::end();
    mock_custom.verify();
}

namespace
{
    class custom_class
    {
    public:
        void process( xml::xistream& xis )
        {
            xis >> xml::end();
        }
    };
}

// -----------------------------------------------------------------------------
// Name: move_up_from_sub_node_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( move_up_from_sub_node_throws_an_exception )
{
    custom_class custom;
    xml::xistringstream xis( "<element>"
                               "<sub-node>content number one</sub-node>"
                             "</element>" );
    BOOST_CHECK_THROW( xis >> xml::start( "element" ) >> xml::list( "sub-node", custom, &custom_class::process ), xml::exception );
}
