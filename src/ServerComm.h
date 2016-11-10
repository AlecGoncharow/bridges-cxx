#ifndef SERVER_COMM_H
#define SERVER_COMM_H

#include <string>
#include <vector>
#include <curl/curl.h> //curl
using namespace std;

namespace bridges{
namespace DataSource
{
    struct Game;        vector<Game> getGameData();
    struct Earthquake;  vector<Earthquake> getEarthquakeData(int);
    struct Shakespeare; vector<Shakespeare> getShakespeareData(string, bool);
    struct Book;        vector<Book> getBookData(int);
}
/** @brief This is a detail class for the Bridges namespace and is not intended for external use */
class ServerComm
{
    //Used to access to this class private functions
    friend void Bridges::visualize();
    friend vector<DataSource::Game> DataSource::getGameData();
    friend vector<DataSource::Earthquake> DataSource::getEarthquakeData(int);
    friend vector<DataSource::Shakespeare> DataSource::getShakespeareData(string, bool);
    friend vector<DataSource::Book> DataSource::getBookData(int);

    ServerComm()=delete;//Prevents instantiation

    /** CURL WRITE FUNCTION PLACEHOLDER (TODO - Replace with something better)*/
    static size_t curlWriteFunction(void *contents, size_t size, size_t nmemb, void *results)
    {
        size_t handled = size*nmemb; if(results) {((string*)results)->append((char*)contents);} return handled;
    }
    /**
     * Uses Easy CURL library to execute a simple request.
     *
     * @param url The url destination for the request
     * @param headers The headers for the request
     * @param data The content sent in POST requests
     * @throw string Thrown if curl request fails
     */
    static string makeRequest(const string& url, const vector<string>& headers, const string& data = "")
    {
        string results;
        curl_global_init(CURL_GLOBAL_ALL);// first load curl enviornment (only need be called once in entire session tho)
        CURL* curl = curl_easy_init(); // get a curl handle
        if (curl)
        {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());// set the URL to GET from
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &results);//pass pointer to callback function
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunction);//sends all data to this function
            if (data.length() > 0)
            {
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());// Now specify the POST data
                curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.length());// Now specify the POST data size
                curl_easy_setopt(curl, CURLOPT_POST, true);//  a post request
            }

            struct curl_slist* curlHeaders = nullptr;
            for (const string& header : headers)
            {
                curlHeaders = curl_slist_append(curlHeaders, header.c_str());
            }
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);
            CURLcode res = curl_easy_perform(curl);// Perform the request, res will get the return code
            if (res != CURLE_OK){throw "curl_easy_perform() failed.\nCurl Error Code "+to_string(res)+": "+curl_easy_strerror(res)+"\n";}
            curl_easy_cleanup(curl);
        }
        else{throw "curl_easy_init() failed!\nNothing retrieved from server.\n";}
        return results;
    }
}; //server comm
}// namespace bridges
#endif