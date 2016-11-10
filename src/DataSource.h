#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H

#include <rapidjson/document.h>
#include "ServerComm.h" //string, vector, using std

namespace bridges{
namespace DataSource
{
    struct Game
    {
        string game, platform;
        double rating;
        vector<string> genre;
    };
    vector<Game> getGameData()
    {
        using namespace rapidjson;
        Document d;
        d.Parse(ServerComm::makeRequest("http://bridgesdata.herokuapp.com/api/games",{"Accept: application/json"}).c_str());

        const Value& D = d["data"];
        vector<Game> wrapper;
        for(SizeType i=0; i<D.Size(); i++)
        {
            const Value& V = D[i];
            const Value& G = V["genre"];

            vector<string> genre;
            for(SizeType j=0; j<G.Size(); j++)
            {
                genre.push_back(G[j].GetString());
            }
            wrapper.push_back({V["game"].GetString(),V["platform"].GetString(),V["rating"].GetDouble(),genre});
        }
        return wrapper;
    }

    struct Earthquake
    {
        double magnitude, lat, lng;
        string location, title, url, time;
    };
    vector<Earthquake> getEarthquakeData(int number = 0)
    {
        using namespace rapidjson;
        Document d;
        vector<Earthquake> wrapper;
        if(number <= 0)
        {
            d.Parse(ServerComm::makeRequest("http://earthquakes-uncc.herokuapp.com/eq",{"Accept: application/json"}).c_str());
            for(SizeType i=0; i<d.Size(); i++)
            {
                const Value& V = d[i]["properties"];
                const Value& G = d[i]["geometry"]["coordinates"];
                wrapper.push_back({V["mag"].GetDouble(),G[0].GetDouble(),G[1].GetDouble(),V["place"].GetString(),V["title"].GetString(),V["url"].GetString(),V["time"].GetString()});
            }
        }
        else
        {
            d.Parse(ServerComm::makeRequest("http://earthquakes-uncc.herokuapp.com/eq/latest/"+to_string(number),{"Accept: application/json"}).c_str());
            const Value& D = d["Earthquakes"];
            for(SizeType i=0; i<D.Size(); i++)
            {
                const Value& V = D[i]["properties"];
                const Value& G = D[i]["geometry"]["coordinates"];
                wrapper.push_back({V["mag"].GetDouble(),G[0].GetDouble(),G[1].GetDouble(),V["place"].GetString(),V["title"].GetString(),V["url"].GetString(),V["time"].GetString()});
            }
        }
        return wrapper;
    }
    struct Shakespeare
    {
        string title, type, text;
    };
    /**
    Valid endpoints: 'poems','plays', <title>
    Valid queryParams: format{simple}
    */
    vector<Shakespeare> getShakespeareData(string endpoint = "", bool simple = false)
    {
        using namespace rapidjson;
        Document d;
        vector<Shakespeare> wrapper;
        string url = "http://bridgesdata.herokuapp.com/api/shakespeare/"+endpoint;
        if(simple){url += "?format=simple";}

        d.Parse(ServerComm::makeRequest(url,{"Accept: application/json"}).c_str());
        const Value& D = d["data"];
        for(SizeType i=0; i<D.Size(); i++)
        {
            const Value& V = D[i];
            wrapper.push_back({V["title"].GetString(),V["type"].GetString(),V["text"].GetString()});
        }
        return wrapper;
    }

    struct Book
    {
        string authorName;
        int authorBirth, authorDeath;
        string title;
        vector<string> lang, genre, subject;
        int numChars, numWords, numSentences, numDifficultWords;
        string url;
        int downloads;
    };
    /**
    Valid endpoints: 'poems','plays', <title>
    Valid queryParams: format{simple}
    */
    vector<Book> getBookData(int num = 0)
    {
        using namespace rapidjson;
        Document d;
        vector<Book> wrapper;
        string url = "http://bridgesdata.herokuapp.com/api/books";
        if(num>0){url += "?limit="+to_string(num);}

        d.Parse(ServerComm::makeRequest(url,{"Accept: application/json"}).c_str());
        const Value& D = d["data"];
        for(SizeType i=0; i<D.Size(); i++)
        {
            const Value& V = D[i];

            const Value& A = V["author"];
            const Value& L = V["languages"];
            vector<string> lang;
            for(SizeType j=0; j<L.Size(); j++)
            {
                lang.push_back(L[j].GetString());
            }
            const Value& G = V["genres"];
            vector<string> genre;
            for(SizeType j=0; j<G.Size(); j++)
            {
                genre.push_back(G[j].GetString());
            }
            const Value& S = V["subjects"];
            vector<string> subject;
            for(SizeType j=0; j<S.Size(); j++)
            {
                genre.push_back(S[j].GetString());
            }
            const Value& M = V["metrics"];
            wrapper.push_back(
              {
                A["name"].GetString(),A["birth"].GetInt(),A["death"].GetInt(),
                V["title"].GetString(),
                lang, genre, subject,
                M["characters"].GetInt(),M["words"].GetInt(),M["sentences"].GetInt(),M["difficultWords"].GetInt(),
                V["url"].GetString(),
                V["downloads"].GetInt()
              });
        }
        return wrapper;
    }
} // namespace DataSource
} // namespace bridges
#endif