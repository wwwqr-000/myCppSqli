#include <iostream>

#include "classes/Mysql.hpp"

int main() {
    Mysql conn = Mysql("https://ipinfo.io", {"Content-Type: application/json"});

    std::cout << conn.getIndex() << "\n";
    return 0;
}
