#include <iostream>

#include "classes/sql.h"
#include "classes/json.hpp"
using json = nlohmann::json;

int main() {
    Mysqli conn;

    conn.toggleDebugger();//Is now on, default off.

    conn.setKey1("123");
    conn.setKey2("321");

    conn.setUrl("https://example.com/betterBrain.php");
    conn.setDB("testDB");

    std::vector<json> pull = conn.query("SELECT COUNT(ID) AS c FROM test");
    std::vector<json> data = conn.query("SELECT * FROM test");

    std::string tmpCountStr = pull[0]["c"];
    int aantal = std::stoi(tmpCountStr);
    std::cout << "List of usernames\n-------------------------\n";
    for (int i = 0; i < aantal; i++) {
        std::string tmpNaam = data[i]["name"];
        std::cout << tmpNaam << "\n";
    }
    std::cout << "\n-------------------------\n\n";

    conn.prepare("SELECT ID FROM test WHERE name = ? AND ID = ?");
    conn.bind_param("si", {"Wieger", 4});

    std::vector<json> name = conn.execute();

    if (name[0]["ID"] != "empty") {
        std::cout << "Name and ID found!\n\n";
    }

    conn.prepare("SELECT name FROM test WHERE ID = ?");
    conn.bind_param("i", {4});
    std::vector<json> nameOutput = conn.execute();
    std::string tmpName = nameOutput[0]["name"];//Do this to remove the "" of the json string.

    std::cout << "Name on ID 4 is: " << tmpName << "\n";

    system("set /p end=");
    return 0;
}
