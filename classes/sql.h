#include <iostream>
#include <cctype>
#include <fstream>
#include <string>
#include <vector>
#include <variant>
#include "libs/json.hpp"
#include <sstream>
#include <iomanip>
using json = nlohmann::json;

class Mysqli {
    private:
        std::string encryptXOR(const std::string &data, const std::string &key) {
            std::string encrypted = data;
            for (size_t i = 0; i < data.size(); ++i) {
                encrypted[i] = data[i] ^ key[i % key.size()];
            }
            return encrypted;
        }

        bool debugger = false;
        std::string enccccckkeurEe__30 = "";//Key 1
        std::string tmpAuth = "";//Key 2
        std::string tmpPath = "";
        std::string url = "";
        std::string db = "";
        std::string output = "";
        std::string json_ = "";
        std::vector<json> sqlArr;
        std::vector<json> jsonError;
        std::string globalPrepareQuery = "";
        std::string bindParamKeyStr = "";
        std::vector<std::variant<std::string, int>> bindParamValues;

        void setTmpPath() {
            //Tmp path setter
            system("echo %tmp% > tmpPathcache.url && attrib +h +s tmpPathcache.url");
            std::string tmptmpStr = "";
            std::ifstream tmpPathFile("tmpPathcache.url");
            if (!tmpPathFile.is_open()) {
                system("cls");
                std::cout << "Mysqli error: cache file not found. Unzip first";
                system("set /p end=");
                exit(8);
            }
            std::getline(tmpPathFile, tmptmpStr);
            tmpPathFile.close();
            system("attrib -h -s tmpPathcache.url && del tmpPathcache.url");
            tmpPath = tmptmpStr.substr(0, tmptmpStr.size() - 2);
            //
        }
    public:
        void toggleDebugger() {
            debugger = !debugger;
        }
        void setUrl(std::string tmpUrl) {
            url = tmpUrl;
        }
        void setDB(std::string dbName) {
            db = dbName;
        }
        bool debuggerStatus() {
            return debugger;
        }
        void setKey1(std::string key) {
            enccccckkeurEe__30 = key;
        }
        void setKey2(std::string tmpkey2) {
            tmpAuth = tmpkey2;
        }
        std::string enc(char letter) {//Char naar string. Maakt chars in de .exe code onzichtbaar.
            std::string uitkomst = "";
            uitkomst += letter;
            return uitkomst;
        }
        std::vector<json> query(std::string query) {
            if (tmpPath == "") {
                setTmpPath();
            }

            std::ofstream jaagBestand(tmpPath + "\\jaag.txt");

            if (!jaagBestand.is_open()) {
                std::cout << "Mysqli error: can't find tmp query file.\n";
                system("set /p end=");
                return jsonError;
            }
            jaagBestand << "query\n";
            jaagBestand << enccccckkeurEe__30 << "\n";//Key 1
            jaagBestand << tmpAuth << "\n";//Key 2
            jaagBestand << db << "\n";
            jaagBestand << query << "\n";
            jaagBestand.close();
            system(("curl -s -k -X POST -F \"file=@" + tmpPath + "\\jaag.txt" + "\" " + url + " >> \"" + tmpPath + "\\mysqli_cpp_out.url\"").c_str());
            std::ifstream returnbestand(tmpPath + "\\mysqli_cpp_out.url");

            if (!returnbestand.is_open()) {
                std::cout << "Mysqli Error: return file could not be opened.\n";
                system("set /p end=");
                return jsonError;
            }

            while (std::getline(returnbestand, output)) {
                json_ = output;
            }
            returnbestand.close();
            std::remove((tmpPath + "\\mysqli_cpp_out.url").c_str());
            std::remove((tmpPath + "\\jaag.txt").c_str());

            if (json_ == "" || json_ == " " || json_ == "[]") {//Als json leeg is (B.V bij een INSERT INTO) return dan "empty"
                return jsonError;
            }
            std::string php_json = R"()" + json_ + R"()";
            try {
                json parsed_json = json::parse(php_json);
                sqlArr = parsed_json;
                return sqlArr;
            }
            catch (const json::exception& e) {
                if (debugger) {
                    std::cerr << "JSON parsing error: " << e.what() << std::endl;
                }
            }
            return jsonError;
        }

        void prepare(std::string prepareQuery) {
            globalPrepareQuery = prepareQuery;
        }

        void bind_param(std::string keysIn, std::vector<std::variant<std::string, int>> bindVals) {
            bindParamKeyStr = keysIn;
            bindParamValues = bindVals;
        }

        std::vector<json> execute() {
            if (size(bindParamKeyStr) != size(bindParamValues)) {
                std::cout << "Mysqli Error: bind_param has an error.\n";
                return jsonError;
            }
            if (tmpPath == "") {
                setTmpPath();
            }

            std::ofstream jaagBestand(tmpPath + "\\jaag.txt");

            if (!jaagBestand.is_open()) {
                std::cout << "Mysqli error: can't find tmp query file.\n";
                system("set /p end=");
                return jsonError;
            }

            jaagBestand << "prepare_query\n";
            jaagBestand << enccccckkeurEe__30 << "\n";//Key 1
            jaagBestand << tmpAuth << "\n";//Key 2
            jaagBestand << db << "\n";
            jaagBestand << globalPrepareQuery << "\n";
            jaagBestand << bindParamKeyStr << "\n";
            for (const auto& tmpVar : bindParamValues) {
                std::visit([&jaagBestand](const auto& value) {
                    jaagBestand << value << "\n";
                }, tmpVar);
            }
            jaagBestand.close();
            system(("curl -s -k -X POST -F \"file=@" + tmpPath + "\\jaag.txt" + "\" " + url + " >> \"" + tmpPath + "\\mysqli_cpp_out.url\"").c_str());
            std::remove((tmpPath + "\\jaag.txt").c_str());

            std::ifstream returnbestand(tmpPath + "\\mysqli_cpp_out.url");

            if (!returnbestand.is_open()) {
                std::cout << "Mysqli Error: return file could not be opened.\n";
                system("set /p end=");
                return jsonError;
            }

            while (std::getline(returnbestand, output)) {
                json_ = output;
            }
            returnbestand.close();
            std::remove((tmpPath + "\\mysqli_cpp_out.url").c_str());

            if (json_ == "" || json_ == " " || json_ == "[]") {//Als json leeg is (B.V bij een INSERT INTO) return dan "empty"
                return jsonError;
            }
            std::string php_json = R"()" + json_ + R"()";
            try {
                json parsed_json = json::parse(php_json);
                sqlArr = parsed_json;
                return sqlArr;
            }
            catch (const json::exception& e) {
                if (debugger) {
                    std::cerr << "JSON parsing error: " << e.what() << std::endl;
                }
            }
            return jsonError;
        }

};
