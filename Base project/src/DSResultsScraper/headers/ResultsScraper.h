#ifndef RESULTSSCRAPER_H_ 
#define RESULTSSCRAPER_H_

#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <string>
#include <queue>
#include <iostream>

#include "JsonRetriever.h"

/// <summary>
/// Describes 5 types of responses from the scraper.
/// EVENTS - Events data
/// COMPS - Competitions data
/// RESULTS - Results data
/// INVALID - Invalid data
/// END - End of data
/// </summary>
enum ResponseType {
	EVENTS, COMPS, RESULTS, INVALID, END
};

/// <summary>
/// Simple structure that holds type of response and the response itself in nlohmannjson format.
/// </summary>
struct ScraperResponse {
	ScraperResponse(ResponseType typ, nlohmann::json res, std::string err) : type(typ), response(res), errorMessage(err) {}
	ResponseType type;
	nlohmann::json response;
	std::string errorMessage;
};

/// <summary>
/// Controls what data is being scraped.
/// It is responsible for getting the right data in the right order.
/// </summary>
class ResultsScraper {
public:
	ResultsScraper(std::string& from, std::string& to) {
		this->from = from;
		this->to = to;
	}

	/// <summary>
	/// From set dates, it will always return the next needed data.
	/// At the end, it will give you ScraperResponse with type END.
	/// MUST BE CALLED AFTER CALLING setDates()!
	/// </summary>
	/// <returns></returns>
	ScraperResponse getResults();

private:
	std::queue<int> eventIds;
	bool startedEvents = false;

	std::queue<int> compIds;
	bool startedComps = false;

	std::string from;
	std::string to;

	const std::string EVENTS_URL_BASE = "https://www.csts.cz/api/1/competition_events?";
	const std::string COMP_URL_BASE = "https://www.csts.cz/api/1/competition_events/";
	const std::string RESULTS_URL_BASE_BEGIN = "https://www.csts.cz/api/1/competitions/";
	const std::string RESULTS_URL_BASE_END = "/result";
	const std::string EVENTS_URL_FROM_PARAM = "from=";
	const std::string EVENTS_URL_TO_PARAM = "to=";

	// Error constants
	const std::string ERROR_PARAMS_NOT_SET = "Parameters from or to are not set";
	const std::string ERROR_COLLECTION_OF_EVENTS_NOT_FOUND = "Collection of events not found";
	const std::string ERROR_ENTITY_NOT_FOUND = "Entity not found";
	const std::string ERROR_COMPS_NOT_FOUN = "Comps not found";
	const std::string ERROR_NO_EVALUATABLE_COMP = "There are no evaluatable competitions in event with id: ";
	const std::string ERROR_UNEXPECTED = "Unexpected error";

	// Json key constants
	const std::string JK_COMPETITORS = "competitors";
	const std::string JK_SERIES = "series";
	const std::string JK_COMP_ID = "compId";
	const std::string JK_EVENT_ID = "eventId";
	const std::string JK_COLLECTION = "collection";
	const std::string JK_ENTITY = "entity";
	const std::string JK_COMPS = "comps";

	// Skip constants
	const std::string JK_SOLO_DANCER = "\"SoloDancer\"";
	const std::string JK_DANCE_FOR_ALL = "\"DanceForAll\"";
};

#endif
