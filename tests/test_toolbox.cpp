#define BOOST_TEST_MODULE toolbox_test_module

#include "is_container.h"
#include "print_ip.h"

#include <map>
#include <set>
#include <vector>

#include <boost/test/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(toolbox_test_suite)

// https://stackoverflow.com/questions/5405016/can-i-check-my-programs-output-with-boost-test
struct cout_redirect {
    cout_redirect(std::streambuf* new_buffer) : old(std::cout.rdbuf(new_buffer)) {
    }
    ~cout_redirect() {
        std::cout.rdbuf(old);
    }
   private:
    std::streambuf* old;
};

BOOST_AUTO_TEST_CASE(toolbox_test_is_container) {
    BOOST_CHECK(is_container_v<std::vector<int>> == true);
    BOOST_CHECK(is_container_v<std::list<int>> == true);
    BOOST_CHECK(is_container_v<std::set<int>> == true);
    BOOST_CHECK(is_container_v<std::string> == true);
    BOOST_CHECK(is_container_v<int> == false);

    // BOOST_CHECK broken :(
    bool v = is_container_v<std::map<const int, int>>;
    BOOST_CHECK(v == true);
}

BOOST_AUTO_TEST_CASE(toolbox_test_print_ip_integral) {
    boost::test_tools::output_test_stream output;
    {
        cout_redirect guard(output.rdbuf());    // ??? guard
        print_ip(int(0x01020304));
        print_ip(short(0x0506));
    }
    BOOST_CHECK(output.is_equal("1.2.3.4\n5.6\n"));
}

BOOST_AUTO_TEST_CASE(toolbox_test_print_ip_string) {
    boost::test_tools::output_test_stream output;
    {
        cout_redirect guard(output.rdbuf());
        print_ip(std::string("abcd"));
    }
    BOOST_CHECK(output.is_equal("abcd\n"));
}

BOOST_AUTO_TEST_CASE(toolbox_test_print_ip_container) {
    boost::test_tools::output_test_stream output;
    {
        cout_redirect guard(output.rdbuf());
        print_ip(std::vector{1, 2, 3});
        print_ip(std::list{5, 6, 7});
    }
    BOOST_CHECK(output.is_equal("1.2.3\n5.6.7\n"));
}

BOOST_AUTO_TEST_SUITE_END()
