#include <curl/curl.h>
#include <vector>
int globalMysqlCounter = -1;

class Mysql {
    private:
        int localIndex;
        std::string endpoint_url;
        std::vector<std::string> headers;
        CURL *curl;
        CURLcode res;

        size_t writeCallback(void *contents, size_t size_, size_t nmemb, std::string *output) {//Convert response to string
            size_t tot_size = size_ * nmemb;
            output->append((char*)contents, tot_size);
            return tot_size;
        }
    public:
        Mysql(std::string url_in, std::vector<std::string> headers) {
            localIndex = ++globalMysqlCounter;
            endpoint_url = url_in;
        }
        int getIndex() {
            return localIndex;
        }
        std::string getEndpointUrl() {
            return endpoint_url;
        }
};
