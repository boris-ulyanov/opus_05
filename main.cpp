
#include "print_ip.h"

#include <list>
#include <vector>

int main() {

    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(8875824491850138409LL);
    print_ip(std::string("[string]"));
    // print_ip(std::vector{1,2,3,4,5});
    // print_ip(std::list{6,7,8,9});

    return 0;
}
