/*
 * Copyright (c) 2018, Sunanda Bose (Neel Basu) (neel.basu.z@gmail.com) 
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met: 
 * 
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
 * DAMAGE. 
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "mathematica++ Unit Test (Module::Common)"
#include <boost/test/unit_test.hpp>
#include <string>
#include <cmath>
#include <iostream>
#include <functional>
#include <numeric>
#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include "mathematica++/m.h"
#include "mathematica++/io.h"
#include "mathematica++/connector.h"
#include "mathematica++/tokens.h"
#include "mathematica++/variant.h"
#include "mathematica++/declares.h"
#include "mathematica++/tokens.h"
#include "mathematica++/accessor.h"
#include "mathematica++/variant.h"
#include "mathematica++/operators.h"

MATHEMATICA_DECLARE(Mod)
MATHEMATICA_DECLARE(Dot)
MATHEMATICA_DECLARE(Det)
MATHEMATICA_DECLARE(Plus)
MATHEMATICA_DECLARE(Plot)
MATHEMATICA_DECLARE(Pow)
MATHEMATICA_DECLARE(Values)
MATHEMATICA_DECLARE(N)
MATHEMATICA_DECLARE(FindRoot)

using namespace mathematica;

BOOST_AUTO_TEST_SUITE(common)

BOOST_AUTO_TEST_CASE(matrix){
    int argc = 4;
    char* argv[] = {(char*)"-linkname", (char*)"math -mathlink", (char*)0x0};
//     connector shell(argc, argv);
    connector shell;
    BOOST_CHECK(shell.connected());
    {
        value result_list;
        value result_sum;
        
        symbol i("i");
        shell << Table(i, List(i, 1, 10));
        shell >> result_list;
        // std::cout << result_list << std::endl; // Prints List[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        // std::cout << result_list->stringify() << std::endl; // Prints List[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        
        std::vector<int> list;
        list = cast<std::vector<int>>(result_list);
        
        shell << Total(Table(i, List(i, 1, 10)));
        shell >> result_sum;
        // std::cout << result_sum << std::endl; // Prints 55
        // std::cout << result_sum->stringify() << std::endl; // Prints 55
        
        int sum1 = *result_sum; // auto coercion through type operator overloading for scaler types
        int sum2 = cast<int>(result_sum);
        double sum3 = *result_sum;
        double sum4 = cast<double>(result_sum);
        
        // std::cout << sum1 << " " << sum2 << " " << sum3 << " " << sum4 << std::endl;// Prints 55 55 55 55
        
        BOOST_CHECK(std::accumulate(list.begin(), list.end(), 0) == sum1);
        BOOST_CHECK(sum1 == sum3);
        BOOST_CHECK(sum1 == sum4);
        
        value determinant;
        
        symbol j("j");
        
        m mata = Table(Mod(i+j, 2), List(i, 1, 2), List(j, 1, 2));
        m matb = Table(Mod(i+j, 3), List(i, 1, 2), List(j, 1, 2));
        m matc = Dot(mata, matb);
        m matd = Det(matc);
        shell << matd;
        shell >> determinant;
        // std::cout << determinant << std::endl; // Prints -2
        
        BOOST_CHECK((int)*determinant == -2);
        
        value res_mata;
        value res_matb;
        value res_matc;
        value res_det;
        
        shell << Table(Mod(i+j, 2), List(i, 1, 2), List(j, 1, 2));
        shell >> res_mata;
        shell << Table(Mod(i+j, 3), List(i, 1, 2), List(j, 1, 2));
        shell >> res_matb;
        shell << Dot(res_mata, res_matb);
        shell >> res_matc;
        shell << Det(res_matc);
        shell >> res_det;
        // std::cout << res_det << std::endl; // Prints -2
        
        BOOST_CHECK((int)*res_det == -2);
        
//         symbol x("x");
//         value plot;
//         
//         shell << Plot(Pow(x, 2), List(x, 0.0, 6.3));
//         std::cout << "START" << std::endl;
//         shell >> plot;
//         std::cout << "Plot: " << plot << std::endl;
        
        {
//             symbol x("x");
//             value  res;
//             std::string method = "Newton";
//             
 //             shell << N(Flatten(Values(Solve(Power(x, 2) + 2*x -7 == 0, x))));
//             shell << Values(FindRoot(Sin(x-10)-x+10, List(x, 0), (Rule("AccuracyGoal") = 4, Rule("PrecisionGoal") = 4)));
//             shell << Values(FindRoot(ArcTan(1000 * Cos(x)), List(x, 1, 2),  Rule("Method") = method));
//             shell >> res;
//             std::vector<double> results = cast<std::vector<double>>(res);
//             std::cout << results[0] << std::endl;
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()
