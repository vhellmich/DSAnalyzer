#ifndef DSRESULTSSCRAPER_H_
#define DSRESULTSSCRAPER_H_

#include "DateHandler.h"
#include "ResultsScraper.h"
#include "JsonResultsParser.h"
#include <chrono>
#include <thread>
#include <random>
#include <iostream>
#include <filesystem>

class DSResultsScraper {
public:	
	DSResultsScraper(std::string month, std::string year) {
		
		int mon = std::stoi(month);
		int yea = std::stoi(year);
		auto dates = DateHandler::GetMonthDateRange(yea, mon);

		from = dates.first;
		to = dates.second;
		
	}

    DSResultsScraper(int month, int year) {
        int mon = month;
        int yea = year;
        auto dates = DateHandler::GetMonthDateRange(yea, mon);

        from = dates.first;
        to = dates.second;
    }

	void run() {
        ResultsScraper resScr(from,to);

        JsonResultsParser writer;

        // Logger setup
        Logger::Init();
        auto loggerPtr = Logger::Get();
        loggerPtr->set_level(spdlog::level::trace);

        auto result = resScr.getResults();

        // Randomize sleep between requests
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 3);

        while (result.type != END) {
            if (result.errorMessage != "") {
                SPDLOG_LOGGER_CALL(loggerPtr.get(), spdlog::level::warn, "Error occurred while requesting data: {}", result.errorMessage);
            }

            SPDLOG_LOGGER_CALL(loggerPtr.get(), spdlog::level::trace, "Site returned: {}", result.response.dump());

            switch (result.type) {
            case EVENTS:
                SPDLOG_LOGGER_CALL(loggerPtr.get(), spdlog::level::info, "Type of json: EVENTS");
                if (!writer.SaveEventsToDatabase(result.response)) {
                    SPDLOG_LOGGER_CALL(loggerPtr.get(), spdlog::level::warn, "Not parsed data: {}", result.response.dump());
                }
                break;
            case COMPS:
                SPDLOG_LOGGER_CALL(loggerPtr.get(), spdlog::level::info, "Type of json: COMPS");
                if (!writer.SaveCompsToDatabase(result.response)) {
                    SPDLOG_LOGGER_CALL(loggerPtr.get(), spdlog::level::warn, "Not parsed data: {}", result.response.dump());
                }
                break;
            case RESULTS:
                SPDLOG_LOGGER_CALL(loggerPtr.get(), spdlog::level::info, "Type of json: RESULTS");
                if (!writer.SaveResultsToDatabase(result.response)) {
                    SPDLOG_LOGGER_CALL(loggerPtr.get(), spdlog::level::warn, "Not parsed data: {}", result.response.dump());
                }
                break;
            case INVALID:
                SPDLOG_LOGGER_CALL(loggerPtr.get(), spdlog::level::info, "Type of json: INVALID");
                break;
            case END:
                SPDLOG_LOGGER_CALL(loggerPtr.get(), spdlog::level::info, "Type of json: END");
                break;
            default:
                SPDLOG_LOGGER_CALL(loggerPtr.get(), spdlog::level::info, "Type of json: UNKNOWN");
            }

            std::this_thread::sleep_for(std::chrono::seconds(distrib(gen))); // Wait 2 seconds before next request

            result = resScr.getResults();
        }

        SPDLOG_LOGGER_CALL(loggerPtr.get(), spdlog::level::info, "The end");
	}

	static void printHelp() {
		std::cout << "Usage: DSResultsScraper <month> <year>\n"
		"Example: DSResultsScraper 10 2023\n"
        "Will scrape all results from October 2023.\n"
            "Keep in mind, that The process can take up to half an hour\n" << std::endl;
	}

private:
	std::string from;
	std::string to;

};

#endif 
