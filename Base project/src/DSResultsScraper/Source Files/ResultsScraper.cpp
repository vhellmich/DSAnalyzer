#include "../headers/ResultsScraper.h"

ScraperResponse ResultsScraper::getResults() {
	nlohmann::json emptyJson;
	if (from == "" || to == "") {
		return ScraperResponse(INVALID, emptyJson, ERROR_PARAMS_NOT_SET);
	}

	std::string url;

	//Load Events
	if (!startedEvents && eventIds.empty()) {
		url = EVENTS_URL_BASE + EVENTS_URL_FROM_PARAM + from + "&" + EVENTS_URL_TO_PARAM + to;
		auto jsonResponse = JsonRetriever::RetrieveFromUrl(url);

		if (!jsonResponse.contains(JK_COLLECTION)) {
			return ScraperResponse(INVALID, emptyJson, ERROR_COLLECTION_OF_EVENTS_NOT_FOUND);
		}
		for (auto& dsEvent : jsonResponse[JK_COLLECTION]) {
			int id = std::stoi(dsEvent[JK_EVENT_ID].dump());
			eventIds.push(id);
		}
		startedEvents = true;
		return ScraperResponse(EVENTS, jsonResponse, "");
	}
	//Load Comps
	else if (!startedComps && compIds.empty() && !eventIds.empty()) {
		int eventId = eventIds.front();
		eventIds.pop();

		url = COMP_URL_BASE + std::to_string(eventId);

		auto jsonResponse = JsonRetriever::RetrieveFromUrl(url);

		if (!jsonResponse.contains(JK_ENTITY)) {
			return ScraperResponse(INVALID, emptyJson, ERROR_ENTITY_NOT_FOUND);
		}
		else if (!jsonResponse[JK_ENTITY].contains(JK_COMPS)) {
			return ScraperResponse(INVALID, emptyJson, ERROR_COMPS_NOT_FOUN);
		}
		for (auto& dsEvent : jsonResponse[JK_ENTITY][JK_COMPS]) {
			// Skip if the competitor is "SoloDancer"
			if (dsEvent[JK_COMPETITORS].dump() == JK_SOLO_DANCER) {
				continue;
			}
			if (dsEvent[JK_SERIES].dump() == JK_DANCE_FOR_ALL) {
				continue;
			}
			int id = std::stoi(dsEvent[JK_COMP_ID].dump());
			compIds.push(id);
		}

		if (!compIds.empty()) {
			startedComps = true;
			return ScraperResponse(COMPS, jsonResponse, "");
		} 
		return ScraperResponse(INVALID, emptyJson, ERROR_NO_EVALUATABLE_COMP + std::to_string(eventId));
	}
	//Iterate Comps
	else if (startedComps && !compIds.empty()) {
		int compId = compIds.front();
		compIds.pop();

		url = RESULTS_URL_BASE_BEGIN + std::to_string(compId) + RESULTS_URL_BASE_END;

		auto jsonResponse = JsonRetriever::RetrieveFromUrl(url);

		if (compIds.empty()) {
			startedComps = false;
		}

		return ScraperResponse(RESULTS, jsonResponse, "");
	}
	//No more data
	else if (startedEvents && eventIds.empty()) {
		startedEvents = false;
		return ScraperResponse(END, emptyJson, "");
	}
	return ScraperResponse(INVALID, emptyJson, ERROR_UNEXPECTED);
}