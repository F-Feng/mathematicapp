#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "mathematica++ Unit Test (Module::STL)"
#include <boost/test/unit_test.hpp>
#include <string>
#include <cmath>
#include <complex>
#include <map>
#include <vector>
#include <iostream>
#include <boost/format.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include "boost/tuple/tuple.hpp"
#include "mathematica++/connector.h"
#include "mathematica++/m.h"
#include "mathematica++/io.h"
#include "mathematica++/declares.h"
#include "mathematica++/operators.h"
#include "mathematica++/rules.h"

using namespace mathematica;

// MATHEMATICA_DECLARE(FactorInteger)

BOOST_AUTO_TEST_SUITE(stl)

BOOST_AUTO_TEST_CASE(stl_vector){
    connector shell;
    BOOST_CHECK(shell.connected());
    {
        value result;
        std::vector<int> list = {1,2,3,4,5};
        shell << Total(list);
        shell >> result;
        // std::cout << result << std::endl; // Prints 15
        BOOST_CHECK(*result == 15);
    }
    {
        value result;
        typedef std::vector<std::vector<int>> ivv_type;
        shell << FactorInteger(2434500);
        shell >> result;
        ivv_type prime_powers = mathematica::cast<ivv_type>(result);
        int sbase = 0 , spow = 0;
        for(auto pp: prime_powers){
            // std::cout << pp[0] << " ^ " << pp[1] << std::endl;
            sbase += pp[0];
            spow  += pp[1];
        }
        BOOST_CHECK(sbase == 551);
        BOOST_CHECK(spow == 8);
    }
    {
        value result;
        typedef std::vector<std::pair<int, int>>    ipv_type;
        typedef std::vector<boost::tuple<int, int>> itv_type;
        shell << FactorInteger(2434500);
        shell >> result;
        
        int sbase = 0 , spow = 0;
        
        ipv_type prime_powers_pair = mathematica::cast<ipv_type>(result);
        for(auto pp: prime_powers_pair){
            // std::cout << pp.first << " ^ " << pp.second << std::endl;
            sbase += pp.first;
            spow  += pp.second;
        }
        BOOST_CHECK(sbase == 551);
        BOOST_CHECK(spow == 8);
        
        sbase = 0, spow = 0;
        itv_type prime_powers_tuple = mathematica::cast<itv_type>(result);
        for(auto pp: prime_powers_tuple){
            // std::cout << pp << std::endl;
            sbase += boost::tuples::get<0>(pp);
            spow  += boost::tuples::get<1>(pp);
        }
        BOOST_CHECK(sbase == 551);
        BOOST_CHECK(spow == 8);
    }
}

BOOST_AUTO_TEST_SUITE_END()