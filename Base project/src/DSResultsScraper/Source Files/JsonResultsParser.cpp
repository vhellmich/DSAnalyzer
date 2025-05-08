#include "../headers/JsonResultsParser.h"

bool JsonResultsParser::SaveEventsToDatabase(nlohmann::json data) {
	try {
		// Check if the JSON data contains the expected keys
		if (!data.contains(JK_COLLECTION)) {
			return false;
		}
		// Iterate through the "events" array in the JSON data
		for (auto& dsEvent : data[JK_COLLECTION]) {
			int id = std::stoi(dsEvent[JK_EVENT_ID].dump());
			std::string dateFrom = removeEscapedQuotes(dsEvent[JK_DATE_FROM].dump());
			std::string eventTitle = removeEscapedQuotes(dsEvent[JK_EVENT_TITLE].dump());

			// Writing to database using StoredProcedures class
			writer.InsertEvent(id, eventTitle, dateFrom);
		}
	}
	catch (std::exception& e) {
		return false;
	}
	return true;
}

bool JsonResultsParser::SaveCompsToDatabase(nlohmann::json data) {
	// If anything fails, it return false
	try {
		// Check if the JSON data contains the expected keys
		if (!data.contains(JK_ENTITY)) {
			return false;
		}
		else if (!data[JK_ENTITY].contains(JK_COMPS)) {
			return false;
		}
		// Iterate through the "comps" array in the JSON data
		for (auto& dsEvent : data[JK_ENTITY][JK_COMPS]) {
			int id = std::stoi(dsEvent[JK_COMP_ID].dump());
			int eventId = std::stoi(data[JK_ENTITY][JK_EVENT_ID].dump());
			int numberOfDances = dsEvent[JK_DANCES].size();
			int numberOfCouples = std::stoi(dsEvent[JK_REGISTERED].dump());

			// Writing to database using StoredProcedures class
			writer.InsertComp(id,
				eventId,
				removeEscapedQuotes(dsEvent[JK_DATE].dump()),
				removeEscapedQuotes(dsEvent[JK_DISCIPLINE].dump()),
				removeEscapedQuotes(dsEvent[JK_AGE].dump()),
				numberOfDances,
				numberOfCouples,
				removeEscapedQuotes(dsEvent[JK_CLASS].dump()));
		}
	}
	catch (std::exception& e) {
		return false;
	}
	return true;
}

bool JsonResultsParser::SaveResultsToDatabase(nlohmann::json data) {
	try {
		int indexCounter = 0;

		// Check if the JSON data contains the expected keys
		if (!data.contains(JK_ENTITY)) {
			return false;
		}
		else if (!data[JK_ENTITY].contains(JK_OFFICIALS)) {
			return false;
		}
		// Iterate through the "officials" array in the JSON data
		for (auto& dsPerson : data[JK_ENTITY][JK_OFFICIALS]) {
			// Saves only judges
			if (!dsPerson.contains(JK_LABEL) && !dsPerson.contains(JK_INDEX)) continue;

			int id = INT_MIN;
			if (dsPerson.contains(JK_ID)) {
				id = std::stoi(dsPerson[JK_ID].dump());

			}

			int compId = std::stoi(data[JK_ENTITY][JK_COMP_ID].dump());

			Person judge = Person(id, 
				removeEscapedQuotes(dsPerson[JK_NAME].dump()),
				removeEscapedQuotes(dsPerson[JK_SURNAME].dump()),
				removeEscapedQuotes(dsPerson[JK_COUNTRY].dump())
			);

			// Writing to database using StoredProcedures class
			writer.InsertIsJudging(judge, compId, indexCounter);
			indexCounter++;
		}

		// Check if the JSON data contains the expected keys
		if (!data[JK_ENTITY].contains(JK_COMPETITORS)) {
			return false;
		}
		std::map<std::string, int> roundsMap;
		int roundCounter = 1;
		// Count the number of rounds in the competition
		for (auto it = data[JK_ENTITY][JK_ROUNDS].rbegin(); it != data[JK_ENTITY][JK_ROUNDS].rend(); it++) {
			roundsMap[removeEscapedQuotes(it->at(JK_ROUND).dump())] = roundCounter;
			roundCounter++;
		}
		// Iterate through the "competitors" array in the JSON data
		for (auto& dsCompetitor : data[JK_ENTITY][JK_COMPETITORS]) {

			// Information about man
			int manId = std::stoi(dsCompetitor[JK_COMPETITOR][JK_IDT1].dump());
			Person man = Person(manId,
				removeEscapedQuotes(dsCompetitor[JK_COMPETITOR][JK_NAME1].dump()),
				removeEscapedQuotes(dsCompetitor[JK_COMPETITOR][JK_SURNAME1].dump()),
				removeEscapedQuotes(dsCompetitor[JK_COMPETITOR][JK_COUNTRY].dump())
			);

			// Information about woman
			int womanId = std::stoi(dsCompetitor[JK_COMPETITOR][JK_IDT2].dump());
			Person woman = Person(womanId,
				removeEscapedQuotes(dsCompetitor[JK_COMPETITOR][JK_NAME2].dump()),
				removeEscapedQuotes(dsCompetitor[JK_COMPETITOR][JK_SURNAME2].dump()),
				removeEscapedQuotes(dsCompetitor[JK_COMPETITOR][JK_COUNTRY].dump()));

			// Information about couple
			std::string clubName = removeEscapedQuotes(dsCompetitor[JK_COMPETITOR][JK_CLUB].dump());
			int compId = std::stoi(data[JK_ENTITY][JK_COMP_ID].dump());


			if (!dsCompetitor.contains(JK_ROUNDS)) {
				return false;
			}
			// Iterate through the "rounds" of one couple
			for (auto& dsResult : dsCompetitor[JK_ROUNDS]) {
				int numberOfDances = dsResult[JK_DANCE_RESULTS].size();
				int round = roundsMap[dsResult[JK_ROUND]];

				std::string marksStringWithQuotes = dsResult[JK_MARKS].dump();
				marksStringWithQuotes.erase(std::remove(marksStringWithQuotes.begin(), marksStringWithQuotes.end(), '\"'), marksStringWithQuotes.end());
				auto marksVector = splitString(marksStringWithQuotes, MARKS_DELIMETER);
				if (marksVector.size() % numberOfDances != 0) return false;


				// Checks and ignores for MCR final type of marks: "1|6|2|.|4|1|5|-|-|-|-|-|-|-..."
				// These data can not be analyzed, because there is no information about dance nor judge's marks
				if (std::find(marksVector.begin(), marksVector.end(), ".") != marksVector.end()) {
					continue;
				}
				if (std::find(marksVector.begin(), marksVector.end(), "-") != marksVector.end() && round == 1) {
					continue;
				}

				int endedFrom = std::stoi(dsResult[JK_RANKING].dump());
				int endedTo = std::stoi(dsResult[JK_RANKING_TO].dump());

				// Iterate trough marks, split them into dances
				std::string marksString = "";
				int counter = 0;
				int danceCounter = 0;
				for (auto& mark : marksVector) {
					marksString += mark;
					counter++;
					if (counter == indexCounter) {
						counter = 0;

						double endedDance = std::stod(dsResult[JK_DANCE_RESULTS][danceCounter].dump());

						// Writing to database using StoredProcedures class
						writer.InsertResult(man, woman, clubName, compId, round, danceCounter, marksString, endedFrom, endedTo, endedDance);
						marksString = "";
						danceCounter++;
					}
					else {
						marksString += "|";
					}
				}
			}

		}

	}
	catch (std::exception& e) {
		return false;
	}
	return true;
}

std::vector<std::string> JsonResultsParser::splitString(const std::string& input, char delimiter) {
	std::vector<std::string> result;
	std::stringstream ss(input);
	std::string token;

	while (std::getline(ss, token, delimiter)) {
		result.push_back(token);
	}

	return result;
}

// Generated by AI
std::string JsonResultsParser::removeEscapedQuotes(const std::string& input) {
	std::string result;
	result.reserve(input.size());  // Reserve space for efficiency

	for (size_t i = 0; i < input.length(); ++i) {
		// Check for escaped quote (\")
		if (input[i] == '\\' && i + 1 < input.length() && input[i + 1] == '"') {
			++i;  // Skip the escaped quote
		}
		else if (input[i] == '\"') {

		}
		else {
			result += input[i];  // Add valid characters to result
		}
	}

	return result;
}