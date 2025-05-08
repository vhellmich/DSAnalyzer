#ifndef JSONRETRIEVER_H_ 
#define JSONRETRIEVER_H_

#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <string>

/// <summary>
/// Retrieves json data from the given URL.
/// </summary>
class JsonRetriever {
public:
	/// <summary>
	/// Retrieves json data from the given URL.
	/// </summary>
	/// <param name="url"></param>
	/// <returns></returns>
	static nlohmann::json RetrieveFromUrl(const std::string& url);
private:
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);

	static const std::string USERAGENT;
	static const std::string REFERER;
};

#endif
