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
#include <xeumeuleu/xml.hpp>
#include <turtle/mock.hpp>
#include <boost/bind.hpp>

namespace
{
    class my_caller_class
    {
    public:
        void my_method( const std::string&, xml::xistream& ) {}
        void my_method( xml::xistream& ) {}
        void my_method( const std::string&, xml::xistream&, int ) {}
        void my_method( xml::xistream&, int ) {}
        void my_method( const std::string&, xml::xistream&, int, int ) {}
        void my_method( xml::xistream&, int, int ) {}
        void my_method( const std::string&, xml::xistream&, int, int, int ) {}
        void my_method( xml::xistream&, int, int, int ) {}
        void my_method( const std::string&, xml::xistream&, int, int, int, int ) {}
        void my_method( xml::xistream&, int, int, int, int ) {}
        void my_method( const std::string&, xml::xistream&, int, int, int, int, int ) {}
        void my_method( xml::xistream&, int, int, int, int, int ) {}
    };

    void my_function_to_test_caller_implementations()
    {
        xml::xistream& xis = *(xml::xistream*)0;
        my_caller_class c;
        int p = 1;
        xis >> xml::list( c, &my_caller_class::my_method )
            >> xml::list( "node", c, &my_caller_class::my_method )
            >> xml::list( c, &my_caller_class::my_method, p )
            >> xml::list( "node", c, &my_caller_class::my_method, p )
            >> xml::list( c, &my_caller_class::my_method, p, p )
            >> xml::list( "node", c, &my_caller_class::my_method, p, p )
            >> xml::list( c, &my_caller_class::my_method, p, p, p )
            >> xml::list( "node", c, &my_caller_class::my_method, p, p, p )
            >> xml::list( c, &my_caller_class::my_method, p, p, p, p )
            >> xml::list( "node", c, &my_caller_class::my_method, p, p, p, p )
            >> xml::list( c, &my_caller_class::my_method, p, p, p, p, p )
            >> xml::list( "node", c, &my_caller_class::my_method, p, p, p, p, p );
    }

    class my_const_caller_class
    {
    public:
        void my_method( const std::string&, xml::xistream& ) const {}
        void my_method( xml::xistream& ) const {}
        void my_method( const std::string&, xml::xistream&, int ) const {}
        void my_method( xml::xistream&, int ) const {}
        void my_method( const std::string&, xml::xistream&, int, int ) const {}
        void my_method( xml::xistream&, int, int ) const {}
        void my_method( const std::string&, xml::xistream&, int, int, int ) const {}
        void my_method( xml::xistream&, int, int, int ) const {}
        void my_method( const std::string&, xml::xistream&, int, int, int, int ) const {}
        void my_method( xml::xistream&, int, int, int, int ) const {}
        void my_method( const std::string&, xml::xistream&, int, int, int, int, int ) const {}
        void my_method( xml::xistream&, int, int, int, int, int ) const {}
    };

    void my_function_to_test_const_caller_implementations()
    {
        xml::xistream& xis = *(xml::xistream*)0;
        const my_const_caller_class c = my_const_caller_class();
        int p = 1;
        xis >> xml::list( c, &my_const_caller_class::my_method )
            >> xml::list( "node", c, &my_const_caller_class::my_method )
            >> xml::list( c, &my_const_caller_class::my_method, p )
            >> xml::list( "node", c, &my_const_caller_class::my_method, p )
            >> xml::list( c, &my_const_caller_class::my_method, p, p )
            >> xml::list( "node", c, &my_const_caller_class::my_method, p, p )
            >> xml::list( c, &my_const_caller_class::my_method, p, p, p )
            >> xml::list( "node", c, &my_const_caller_class::my_method, p, p, p )
            >> xml::list( c, &my_const_caller_class::my_method, p, p, p, p )
            >> xml::list( "node", c, &my_const_caller_class::my_method, p, p, p, p )
            >> xml::list( c, &my_const_caller_class::my_method, p, p, p, p, p )
            >> xml::list( "node", c, &my_const_caller_class::my_method, p, p, p, p, p );
    }

    class my_caller_class_with_namespace
    {
    public:
        void my_method( const std::string&, const std::string&, xml::xistream& ) {}
        void my_method( const std::string&, const std::string&, xml::xistream&, int ) {}
        void my_method( const std::string&, const std::string&, xml::xistream&, int, int ) {}
        void my_method( const std::string&, const std::string&, xml::xistream&, int, int, int ) {}
        void my_method( const std::string&, const std::string&, xml::xistream&, int, int, int, int ) {}
        void my_method( const std::string&, const std::string&, xml::xistream&, int, int, int, int, int ) {}
    };

    void my_function_to_test_caller_implementations_with_namespace()
    {
        xml::xistream& xis = *(xml::xistream*)0;
        my_caller_class_with_namespace c;
        int p = 1;
        xis >> xml::list( c, &my_caller_class_with_namespace::my_method )
            >> xml::list( c, &my_caller_class_with_namespace::my_method, p )
            >> xml::list( c, &my_caller_class_with_namespace::my_method, p, p )
            >> xml::list( c, &my_caller_class_with_namespace::my_method, p, p, p )
            >> xml::list( c, &my_caller_class_with_namespace::my_method, p, p, p, p )
            >> xml::list( c, &my_caller_class_with_namespace::my_method, p, p, p, p, p );
    }

    class my_const_caller_class_with_namespace
    {
    public:
        void my_method( const std::string&, const std::string&, xml::xistream& ) const {}
        void my_method( const std::string&, const std::string&, xml::xistream&, int ) const {}
        void my_method( const std::string&, const std::string&, xml::xistream&, int, int ) const {}
        void my_method( const std::string&, const std::string&, xml::xistream&, int, int, int ) const {}
        void my_method( const std::string&, const std::string&, xml::xistream&, int, int, int, int ) const {}
        void my_method( const std::string&, const std::string&, xml::xistream&, int, int, int, int, int ) const {}
    };

    void my_function_to_test_const_caller_implementations_with_namespace()
    {
        xml::xistream& xis = *(xml::xistream*)0;
        const my_const_caller_class_with_namespace c = my_const_caller_class_with_namespace();
        int p = 1;
        xis >> xml::list( c, &my_const_caller_class_with_namespace::my_method )
            >> xml::list( c, &my_const_caller_class_with_namespace::my_method, p )
            >> xml::list( c, &my_const_caller_class_with_namespace::my_method, p, p )
            >> xml::list( c, &my_const_caller_class_with_namespace::my_method, p, p, p )
            >> xml::list( c, &my_const_caller_class_with_namespace::my_method, p, p, p, p )
            >> xml::list( c, &my_const_caller_class_with_namespace::my_method, p, p, p, p, p );
    }
}

namespace
{
    class my_class
    {
    public:
        void my_method( xml::xistream& ) {}
        void my_const_method( xml::xistream& ) const {}
    };

    class my_type
    {
    };

    class my_class_ext_1
    {
    public:
        void my_method( xml::xistream& , my_type& ) {}
        void my_const_method( xml::xistream& , my_type& ) const {}
    };

    class my_class_ext_const_1
    {
    public:
        void my_method( xml::xistream& , const my_type& ) {}
        void my_const_method( xml::xistream& , const my_type& ) const {}
    };

    class my_class_ext_2
    {
    public:
        void my_method( xml::xistream& , my_type& , my_type& ) {}
        void my_const_method( xml::xistream& , my_type& , my_type& ) const {}
    };

    class my_class_ext_const_2
    {
    public:
        void my_method( xml::xistream& , const my_type&, my_type& ) {}
        void my_const_method( xml::xistream& , const my_type&, my_type& ) const {}
    };

    class my_class_ext_const_const_2
    {
    public:
        void my_method_const( xml::xistream& , const my_type&, const my_type& ) {}
        void my_const_method_const( xml::xistream& , const my_type&, const my_type& ) const {}
    };

    class my_functor
    {
    public:
        void operator()( xml::xistream& ) {}
    };

    class my_functor_ext
    {
    public:
        void operator()( const std::string&, const std::string&, xml::xistream& ) {}
    };

    void warning_check()
    {
        xml::xistream& xis = *(xml::xistream*)0;
        {
            my_class my_instance;
            xis >> xml::list( "node", my_instance, &my_class::my_method );
        }
        {
            my_class my_instance;
            xis >> xml::list( "node", my_instance, &my_class::my_const_method );
        }
        {
            const my_class my_instance = my_class();
            xis >> xml::list( "node", my_instance, &my_class::my_const_method );
        }

        my_type param;
        my_type& param_ref = param;
        const my_type& param_const_ref = param;
        {
            my_class_ext_1 my_instance;
            xis >> xml::list( "node", my_instance, &my_class_ext_1::my_method, param );
            xis >> xml::list( "node", my_instance, &my_class_ext_1::my_const_method, param );
            xis >> xml::list( "node", my_instance, &my_class_ext_1::my_method, param_ref );
            xis >> xml::list( "node", my_instance, &my_class_ext_1::my_const_method, param_ref );
        }
        {
            const my_class_ext_1 my_instance = my_class_ext_1();
            xis >> xml::list( "node", my_instance, &my_class_ext_1::my_const_method, param );
            xis >> xml::list( "node", my_instance, &my_class_ext_1::my_const_method, param_ref );
        }
        {
            my_class_ext_const_1 my_instance;
            xis >> xml::list( "node", my_instance, &my_class_ext_const_1::my_method, param_const_ref );
            xis >> xml::list( "node", my_instance, &my_class_ext_const_1::my_const_method, param_const_ref );
        }
        {
            const my_class_ext_const_1 my_instance = my_class_ext_const_1();
            xis >> xml::list( "node", my_instance, &my_class_ext_const_1::my_const_method, param_const_ref );
        }
        {
            my_class_ext_2 my_instance;
            xis >> xml::list( "node", my_instance, &my_class_ext_2::my_method, param, param );
            xis >> xml::list( "node", my_instance, &my_class_ext_2::my_const_method, param, param );
            xis >> xml::list( "node", my_instance, &my_class_ext_2::my_method, param_ref, param_ref );
            xis >> xml::list( "node", my_instance, &my_class_ext_2::my_const_method, param_ref, param_ref );
       }
       {
            const my_class_ext_2 my_instance = my_class_ext_2();
            xis >> xml::list( "node", my_instance, &my_class_ext_2::my_const_method, param, param );
            xis >> xml::list( "node", my_instance, &my_class_ext_2::my_const_method, param_ref, param_ref );
       }
       {
            my_class_ext_const_2 my_instance;
            xis >> xml::list( "node", my_instance, &my_class_ext_const_2::my_method, param_const_ref, param );
            xis >> xml::list( "node", my_instance, &my_class_ext_const_2::my_const_method, param_const_ref, param_ref );
       }
       {
            const my_class_ext_const_2 my_instance = my_class_ext_const_2();
            xis >> xml::list( "node", my_instance, &my_class_ext_const_2::my_const_method, param_const_ref, param );
            xis >> xml::list( "node", my_instance, &my_class_ext_const_2::my_const_method, param_const_ref, param_ref );
       }
       {
            my_class_ext_const_const_2 my_instance;
            xis >> xml::list( "node", my_instance, &my_class_ext_const_const_2::my_method_const, param_const_ref, param_const_ref );
            xis >> xml::list( "node", my_instance, &my_class_ext_const_const_2::my_const_method_const, param_const_ref, param_const_ref );
       }
       {
            const my_class_ext_const_const_2 my_instance = my_class_ext_const_const_2();
            xis >> xml::list( "node", my_instance, &my_class_ext_const_const_2::my_const_method_const, param_const_ref, param_const_ref );
       }
       {
           my_functor f;
           xis >> xml::list( "node", f );
       }
       {
           my_functor f;
           xis >> xml::list< my_functor& >( "node", f );
       }
       {
           my_functor_ext f;
           xis >> xml::list( f );
       }
       {
           my_functor_ext f;
           xis >> xml::list< my_functor_ext& >( f );
       }
    }
}

namespace
{
    MOCK_CLASS( mock_custom_class )
    {
        void process( xml::xistream& xis )
        {
            std::string content;
            xis >> content;
            forward( content );
        }
        MOCK_METHOD_EXT( forward, 1, void( std::string ), forward )
    };
}

// -----------------------------------------------------------------------------
// Name: read_list_from_element_calls_a_custom_method
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_list_from_element_calls_a_custom_method )
{
    mock_custom_class mock_custom;
    MOCK_EXPECT( mock_custom.forward ).once().with( "content number one" );
    MOCK_EXPECT( mock_custom.forward ).once().with( "content number two" );
    xml::xistringstream xis( "<element>"
                               "<sub-node>content number one</sub-node>"
                               "<sub-node>content number two</sub-node>"
                             "</element>" );
    xis >> xml::start( "element" )
            >> xml::list( "sub-node", mock_custom, &mock_custom_class::process );
}

namespace
{
    MOCK_CLASS( mock_custom_class_with_parameters )
    {
        void process( xml::xistream& xis, int p1, const float p2 )
        {
            std::string content;
            xis >> content;
            forward( content, p1, p2 );
        }
        MOCK_METHOD_EXT( forward, 3, void( std::string, int, float ), forward )
    };
}

// -----------------------------------------------------------------------------
// Name: read_list_from_element_calls_a_custom_method_with_parameters
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_list_from_element_calls_a_custom_method_with_parameters )
{
    mock_custom_class_with_parameters mock_custom;
    int p1 = 12;
    const float p2 = 12.42f;
    MOCK_EXPECT( mock_custom.forward ).once().with( "content", p1, p2 );
    xml::xistringstream xis( "<element>"
                               "<sub-node>content</sub-node>"
                             "</element>" );
    xis >> xml::start( "element" )
            >> xml::list( "sub-node", mock_custom, &mock_custom_class_with_parameters::process, p1, p2 );
}

namespace
{
    class an_interface
    {
    };

    MOCK_CLASS( mock_custom_class_with_polymorphic_parameter )
    {
        void process( xml::xistream& xis, an_interface& p1 )
        {
            std::string content;
            xis >> content;
            forward( content, p1 );
        }
        MOCK_METHOD_EXT( forward, 2, void( std::string, an_interface& ), forward )
    };

    class a_class : public an_interface
    {
    };
}

// -----------------------------------------------------------------------------
// Name: read_list_from_element_calls_a_custom_method_with_polymorphic_parameter
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_list_from_element_calls_a_custom_method_with_polymorphic_parameter )
{
    mock_custom_class_with_polymorphic_parameter mock_custom;
    a_class my_instance;
    MOCK_EXPECT( mock_custom.forward ).once().with( "content", mock::same( my_instance ) );
    xml::xistringstream xis( "<element>"
                               "<sub-node>content</sub-node>"
                             "</element>" );
    xis >> xml::start( "element" )
            >> xml::list( "sub-node", mock_custom, &mock_custom_class_with_polymorphic_parameter::process, my_instance );
}

namespace
{
    class custom_class
    {
    public:
        void process( xml::xistream& xis )
        {
            xis >> xml::end;
        }
    };
}

// -----------------------------------------------------------------------------
// Name: move_up_from_sub_node_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( move_up_from_sub_node_throws_an_exception )
{
    custom_class custom;
    xml::xistringstream xis( "<element>"
                               "<sub-node>content number one</sub-node>"
                             "</element>" );
    BOOST_CHECK_THROW( xis >> xml::start( "element" ) >> xml::list( "sub-node", custom, &custom_class::process ), xml::exception );
}

namespace
{
    MOCK_CLASS( mock_custom_class_name_list )
    {
        void process( const std::string& name, xml::xistream& xis )
        {
            std::string content;
            xis >> content;
            forward( name, content );
        }
        MOCK_METHOD_EXT( forward, 2, void( std::string, std::string ), forward )
    };
}

// -----------------------------------------------------------------------------
// Name: read_name_list_is_called_with_each_element
// Created: MAT 2010-07-12
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_name_list_is_called_with_each_element )
{
    xml::xistringstream xis( "<element>"
                               "<sub-node1>content number one</sub-node1>"
                               "<sub-node2>content number two</sub-node2>"
                             "</element>" );
    mock_custom_class_name_list mock_custom;
    MOCK_EXPECT( mock_custom.forward ).once().with( "sub-node1", "content number one" );
    MOCK_EXPECT( mock_custom.forward ).once().with( "sub-node2", "content number two" );
    xis >> xml::start( "element" )
            >> xml::list( mock_custom, &mock_custom_class_name_list::process );
}

// -----------------------------------------------------------------------------
// Name: read_name_list_is_not_called_with_content
// Created: ZEBRE 2006-08-30
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_name_list_is_not_called_with_content )
{
    xml::xistringstream xis( "<element>"
                               "content not to be read"
                               "<sub-node>content</sub-node>"
                             "</element>" );
    mock_custom_class_name_list mock_custom;
    MOCK_EXPECT( mock_custom.forward ).once().with( "sub-node", "content" );
    xis >> xml::start( "element" )
            >> xml::list( mock_custom, &mock_custom_class_name_list::process );
}

namespace
{
    MOCK_CLASS( mock_custom_class_name_list_with_parameters )
    {
        void process( const std::string& name, xml::xistream& xis, int p1 )
        {
            std::string content;
            xis >> content;
            forward( name, content, p1 );
        }
        MOCK_METHOD_EXT( forward, 3, void( std::string, std::string, int ), forward )
    };
}

// -----------------------------------------------------------------------------
// Name: read_name_list_with_parameters
// Created: ZEBRE 2006-08-30
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_name_list_with_parameters )
{
    xml::xistringstream xis( "<element>"
                               "<sub-node1>content number one</sub-node1>"
                               "<sub-node2>content number two</sub-node2>"
                             "</element>" );
    int p1 = 12;
    mock_custom_class_name_list_with_parameters mock_custom;
    MOCK_EXPECT( mock_custom.forward ).once().with( "sub-node1", "content number one", p1 );
    MOCK_EXPECT( mock_custom.forward ).once().with( "sub-node2", "content number two", p1 );
    xis >> xml::start( "element" )
            >> xml::list( mock_custom, &mock_custom_class_name_list_with_parameters::process, p1 );
}

namespace
{
    class a_class_virtually_inheriting_from_another : virtual public an_interface
    {
    public:
        void process( xml::xistream& /*xis*/ )
        {}
    };
}

// -----------------------------------------------------------------------------
// Name: msvc_does_not_issue_packing_related_warning_C4355_or_C4121_when_using_virtual_inheritance
// Created: MAT 2007-06-28
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( msvc_does_not_issue_packing_related_warning_C4355_or_C4121_when_using_virtual_inheritance )
{
    xml::xistringstream xis( "<element/>" );
    a_class_virtually_inheriting_from_another my_instance;
    xis >> xml::list( "element", my_instance, &a_class_virtually_inheriting_from_another::process );
}
namespace
{
    MOCK_FUNCTOR( forward, void() );
    void my_function( xml::xistream& )
    {
        forward();
    }
    void my_name_function( const std::string&, const std::string&, xml::xistream& )
    {
        forward();
    }
}

// -----------------------------------------------------------------------------
// Name: list_accepts_function_as_functor
// Created: MAT 2008-02-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( list_accepts_function_as_functor )
{
    xml::xistringstream xis( "<element/>" );
    MOCK_RESET( forward );
    {
        MOCK_EXPECT( forward ).once();
        xis >> xml::list( "element", &my_function );
        mock::verify();
    }
    {
        MOCK_EXPECT( forward ).once();
        xis >> xml::list( &my_name_function );
    }
}

namespace
{
    class my_functor_class
    {
    public:
        void operator()( xml::xistream& ) const
        {
            forward();
        }
        void operator()( const std::string&, const std::string&, xml::xistream& ) const
        {
            forward();
        }
    };
}

// -----------------------------------------------------------------------------
// Name: list_accepts_functor_by_copy
// Created: MAT 2008-02-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( list_accepts_functor_by_copy )
{
    xml::xistringstream xis( "<element/>" );
    MOCK_RESET( forward );
    {
        MOCK_EXPECT( forward ).once();
        xis >> xml::list( "element", my_functor_class() );
        mock::verify();
    }
    {
        MOCK_EXPECT( forward ).once();
        xis >> xml::list( my_functor_class() );
    }
}

// -----------------------------------------------------------------------------
// Name: list_accepts_functor_by_reference
// Created: MAT 2008-11-21
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( list_accepts_functor_by_reference )
{
    xml::xistringstream xis( "<element/>" );
    MOCK_RESET( forward );
    {
        MOCK_EXPECT( forward ).once();
        my_functor_class functor;
        xis >> xml::list< my_functor_class& >( "element", functor );
        mock::verify();
    }
    {
        MOCK_EXPECT( forward ).once();
        my_functor_class functor;
        xis >> xml::list< my_functor_class& >( functor );
    }
}

namespace
{
    MOCK_CLASS( my_bindable_class )
    {
    public:
        void my_method_1( xml::xistream& )
        {
            forward();
        }
        void const_my_method_1( xml::xistream& ) const
        {
            forward();
        }
        void my_method_2( const std::string&, xml::xistream& )
        {
            forward();
        }
        void const_my_method_2( const std::string&, xml::xistream& ) const
        {
            forward();
        }
        MOCK_METHOD_EXT( forward, 0, void(), forward )
    };
}

// -----------------------------------------------------------------------------
// Name: list_accepts_boost_bind_as_functor
// Created: MAT 2008-02-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( list_accepts_boost_bind_as_functor )
{
    xml::xistringstream xis( "<element/>" );
    {
        my_bindable_class my_instance;
        MOCK_EXPECT( my_instance.forward ).once();
        xis >> xml::list( "element", boost::bind( &my_bindable_class::my_method_1, boost::ref( my_instance ), _1 ) );
        mock::verify();
    }
    {
        my_bindable_class my_instance;
        MOCK_EXPECT( my_instance.forward ).once();
        xis >> xml::list( "element", boost::bind( &my_bindable_class::const_my_method_1, boost::ref( my_instance ), _1 ) );
        mock::verify();
    }
    {
        my_bindable_class my_instance;
        MOCK_EXPECT( my_instance.forward ).once();
        xis >> xml::list( boost::bind( &my_bindable_class::my_method_2, boost::ref( my_instance ), _2, _3 ) );
        mock::verify();
    }
    {
        my_bindable_class my_instance;
        MOCK_EXPECT( my_instance.forward ).once();
        xis >> xml::list( boost::bind( &my_bindable_class::const_my_method_2, boost::ref( my_instance ), _2, _3 ) );
    }
}

namespace
{
    class super_type
    {
    public:
        void process( xml::xistream& ) {}
    };
    class sub_type : public super_type
    {};
}

// -----------------------------------------------------------------------------
// Name: list_accepts_instance_of_sub_type_of_the_type_with_the_method_to_call
// Created: MAT 2009-05-11
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( list_accepts_instance_of_sub_type_of_the_type_with_the_method_to_call )
{
    sub_type type;
    xml::xistringstream xis( "<element/>" );
    xis >> xml::list( "element", type, &super_type::process );
}
