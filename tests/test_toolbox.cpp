#define BOOST_TEST_MODULE toolbox_test_module

#include "print_ip.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(toolbox_test_suite)

BOOST_AUTO_TEST_CASE(toolbox_test_extract_ip) {
    IP4Address addr;
    bool rv = extract_ip("1.2.3.4\t xyz", &addr);

    BOOST_CHECK(rv == true);
    BOOST_CHECK(addr == (IP4Address{1, 2, 3, 4}));

    rv = extract_ip("1.2.3", &addr);
    BOOST_CHECK(rv == false);
}

BOOST_AUTO_TEST_SUITE_END()
