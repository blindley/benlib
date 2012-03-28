#include <iostream>
#include <algorithm>
#include <sstream>
#include <SFML/Network.hpp>

#include <ben/container_algo.hpp>
#include <boost/algorithm/string/predicate.hpp>

std::string ExtractTag(const std::string & page, const std::string & tag)
{
    auto start = page.find("<" + tag);
    if (start == std::string::npos) return "";
    auto end = page.find("</" + tag + ">");
    if (end == std::string::npos)
        end = page.find("</ " + tag + ">");
    if (end == std::string::npos)
        return page.substr(start);
    return page.substr(start, end-start) + "</" + tag + ">";
}

std::string DownloadPage(std::string url)
{
    if (boost::starts_with(url, "http://"))
        url = url.substr(7);
        
    auto i = std::find(url.begin(), url.end(), '/');
    std::string host(url.begin(), i);
    std::string uri(i, url.end());
    
    sf::Http Http(host);
    sf::Http::Request req(uri);    

    auto response = Http.SendRequest(req);
    
    switch(response.GetStatus())
    {
        case sf::Http::Response::Ok:
            return response.GetBody();
        case sf::Http::Response::MovedPermanently:
        case sf::Http::Response::MovedTemporarily:
            url = response.GetField("Location");            
            return DownloadPage(url);
        default:
        {
            std::ostringstream oss;
            oss << "Error: " << response.GetStatus();
            return oss.str();
        }
    }    
}

int main()
{
    while (true)
    {
        std::cout << "\n\n> ";
        
        std::string url;
        std::cin >> url;
        if (url == "quit")
            break;
        std::string page = DownloadPage(url);
        
        auto start = page.find("<title");
        if (start == std::string::npos)
        {
            continue;
        }
        
        auto title = ExtractTag(page, "title");
        std::cout << title;
        
        int line_count = ben::Count(page,'\n');
        int char_count = page.size();
        
        std::cout << "\nLines: " << line_count;
        std::cout << ", Characters: " << char_count;
    }     
}
