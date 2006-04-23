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

#include "xeumeuleu_pch.h"
#include "list.h"

using namespace xml;

namespace
{
    class my_class
    {
    public:
        void my_method( xistream& ) {}
        void my_const_method( xistream& ) const {}
    };

    class my_type
    {
    };

    class my_class_ext_1
    {
    public:
        void my_method( xml::xistream& , my_type& ) {};
        void my_const_method( xml::xistream& , my_type& ) const {};
    };

    class my_class_ext_const_1
    {
    public:
        void my_method( xml::xistream& , const my_type& ) {};
        void my_const_method( xml::xistream& , const my_type& ) const {};
    };

    class my_class_ext_2
    {
    public:
        void my_method( xml::xistream& , my_type& , my_type& ) {};
        void my_const_method( xml::xistream& , my_type& , my_type& ) const {};
    };

    class my_class_ext_const_2
    {
    public:
        void my_method( xml::xistream& , const my_type&, my_type& ) {};
        void my_const_method( xml::xistream& , const my_type&, my_type& ) const {};
    };

    class my_class_ext_const_const_2
    {
    public:
        void my_method_const( xml::xistream& , const my_type&, const my_type& ) {};
        void my_const_method_const( xml::xistream& , const my_type&, const my_type& ) const {};
    };

    void warning_check()
    {
        xistream& xis = *(xistream*)0;
        {
            my_class my_instance;
            xis >> list( "node", my_instance, &my_class::my_method );
        }
        {
            my_class my_instance;
            xis >> list( "node", my_instance, &my_class::my_const_method );
        }
        {
            const my_class my_instance = my_class();
            xis >> list( "node", my_instance, &my_class::my_const_method );
        }

        my_type param;
        my_type& param_ref = param;
        const my_type& param_const_ref = param;
        {
            my_class_ext_1 my_instance;
            xis >> list( "node", my_instance, &my_class_ext_1::my_method, param );
            xis >> list( "node", my_instance, &my_class_ext_1::my_const_method, param );
            xis >> list( "node", my_instance, &my_class_ext_1::my_method, param_ref );
            xis >> list( "node", my_instance, &my_class_ext_1::my_const_method, param_ref );
        }
        {
            const my_class_ext_1 my_instance = my_class_ext_1();
            xis >> list( "node", my_instance, &my_class_ext_1::my_const_method, param );
            xis >> list( "node", my_instance, &my_class_ext_1::my_const_method, param_ref );
        }
        {
            my_class_ext_const_1 my_instance;
            xis >> list( "node", my_instance, &my_class_ext_const_1::my_method, param_const_ref );
            xis >> list( "node", my_instance, &my_class_ext_const_1::my_const_method, param_const_ref );
        }
        {
            const my_class_ext_const_1 my_instance = my_class_ext_const_1();
            xis >> list( "node", my_instance, &my_class_ext_const_1::my_const_method, param_const_ref );
        }
        {
            my_class_ext_2 my_instance;
            xis >> list( "node", my_instance, &my_class_ext_2::my_method, param, param );
            xis >> list( "node", my_instance, &my_class_ext_2::my_const_method, param, param );
            xis >> list( "node", my_instance, &my_class_ext_2::my_method, param_ref, param_ref );
            xis >> list( "node", my_instance, &my_class_ext_2::my_const_method, param_ref, param_ref );
       }
       {
            const my_class_ext_2 my_instance = my_class_ext_2();
            xis >> list( "node", my_instance, &my_class_ext_2::my_const_method, param, param );
            xis >> list( "node", my_instance, &my_class_ext_2::my_const_method, param_ref, param_ref );
       }
       {
            my_class_ext_const_2 my_instance;
            xis >> list( "node", my_instance, &my_class_ext_const_2::my_method, param_const_ref, param );
            xis >> list( "node", my_instance, &my_class_ext_const_2::my_const_method, param_const_ref, param_ref );
       }
       {
            const my_class_ext_const_2 my_instance = my_class_ext_const_2();
            xis >> list( "node", my_instance, &my_class_ext_const_2::my_const_method, param_const_ref, param );
            xis >> list( "node", my_instance, &my_class_ext_const_2::my_const_method, param_const_ref, param_ref );
       }
       {
            my_class_ext_const_const_2 my_instance;
            xis >> list( "node", my_instance, &my_class_ext_const_const_2::my_method_const, param_const_ref, param_const_ref );
            xis >> list( "node", my_instance, &my_class_ext_const_const_2::my_const_method_const, param_const_ref, param_const_ref );
       }
       {
            const my_class_ext_const_const_2 my_instance = my_class_ext_const_const_2();
            xis >> list( "node", my_instance, &my_class_ext_const_const_2::my_const_method_const, param_const_ref, param_const_ref );
        }
    }
}
