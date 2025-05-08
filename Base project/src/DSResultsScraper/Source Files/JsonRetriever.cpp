#include "../headers/JsonRetriever.h"
#include <iostream>
#include "../../Logger.h"

nlohmann::json JsonRetriever::RetrieveFromUrl(const std::string& url) {
	nlohmann::json response;
    CURL* curl = curl_easy_init();
    std::string responseString;
    CURLcode res;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/109.0.0.0 Safari/537.36");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);
		// IMPORTANT: This is needed to for the server to accept the request more frequently
        curl_easy_setopt(curl, CURLOPT_REFERER, "https://www.csts.cz/dancesport/vysledky_soutezi");

        /* use a GET to fetch this */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        /* Perform the request */
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            SPDLOG_LOGGER_CALL(Logger::Get().get(), spdlog::level::err, "cURL request failed: {}", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }

    try {
        response = nlohmann::json::parse(responseString);
    }
    catch (std::exception& e) {
        SPDLOG_LOGGER_CALL(Logger::Get().get(), spdlog::level::err, "Can not parse response to json");
    }
    return response;
}

size_t JsonRetriever::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

const std::string JsonRetriever::USERAGENT = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/109.0.0.0 Safari/537.36";
const std::string JsonRetriever::REFERER = "https://www.csts.cz/dancesport/vysledky_soutezi";