#include <iostream>

#include "classes/Mysql.hpp"

int main() {
    Mysql conn = Mysql("https://ipinfo.io", {"Content-Type: application/json"}, "test_db");

    std::cout << conn.getIndex() << "\n";
    return 0;
}
