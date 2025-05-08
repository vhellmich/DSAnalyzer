#ifndef JSONRESULTSPARSER_H_ 
#define JSONRESULTSPARSER_H_

#include <nlohmann/json.hpp>
#include "StoredProcedures.h"
#include <vector>
#include <sstream>

/// <summary>
/// Contains methods to parse json data and save it to the database.
/// </summary>
class JsonResultsParser {
public:
	/// <summary>
	/// Parses json data about events and saves them to the database.
	/// Returns false, if it can not parse the data, or if it cant store it in the database.
	/// Return true, if it was successful.
	/// </summary>
	/// <param name="data"></param>
	/// <returns></returns>
	bool SaveEventsToDatabase(nlohmann::json data);

	/// <summary>
	/// Parses json data about competitions and saves them to the database.
	/// Returns false, if it can not parse the data, or if it cant store it in the database.
	/// Return true, if it was successful.
	/// </summary>
	/// <param name="data"></param>
	/// <returns></returns>
	bool SaveCompsToDatabase(nlohmann::json data);

	/// <summary>
	/// Parses json data about results and saves them to the database.
	/// Returns false, if it can not parse the data, or if it cant store it in the database.
	/// Return true, if it was successful.
	/// </summary>
	/// <param name="data"></param>
	/// <returns></returns>
	bool SaveResultsToDatabase(nlohmann::json data);
private:
	std::shared_ptr<spdlog::logger> loggerPtr = nullptr;

	/// <summary>
	/// Handles database operations.
	/// </summary>
	StoredProcedures writer;

	/// <summary>
	/// Splits string by delimiter and returns vector of strings.
	/// </summary>
	/// <param name="input"></param>
	/// <param name="delimiter"></param>
	/// <returns></returns>
	std::vector<std::string> splitString(const std::string& input, char delimiter);

	/// <summary>
	/// Removes escaped quotes from the input string and return new string without them.
	/// </summary>
	/// <param name="input"></param>
	/// <returns></returns>
	std::string removeEscapedQuotes(const std::string& input);


	// Json keys constants
	const std::string JK_ENTITY = "entity";
	const std::string JK_COMPS = "comps";
	const std::string JK_OFFICIALS = "officials";
	const std::string JK_COMP_ID = "compId";
	const std::string JK_EVENT_ID = "eventId";
	const std::string JK_DATE = "date";
	const std::string JK_DISCIPLINE = "discipline";
	const std::string JK_AGE = "age";
	const std::string JK_DANCES = "dances";
	const std::string JK_REGISTERED = "registered";
	const std::string JK_CLASS = "class";
	const std::string JK_EVENT_TITLE = "eventTitle";
	const std::string JK_DATE_FROM = "dateFrom";
	const std::string JK_COLLECTION = "collection";
	const std::string JK_ROUNDS = "rounds";
	const std::string JK_LABEL = "label";
	const std::string JK_ID = "id";
	const std::string JK_NAME = "name";
	const std::string JK_SURNAME = "surname";
	const std::string JK_COUNTRY = "country";
	const std::string JK_INDEX = "index";
	const std::string JK_ROUND = "round";
	const std::string JK_COMPETITORS = "competitors";
	const std::string JK_COMPETITOR = "competitor";
	const std::string JK_IDT1 = "idt1";
	const std::string JK_IDT2 = "idt2";
	const std::string JK_NAME1 = "name1";
	const std::string JK_NAME2 = "name2";
	const std::string JK_SURNAME1 = "surname1";
	const std::string JK_SURNAME2 = "surname2";
	const std::string JK_CLUB = "club";
	const std::string JK_DANCE_RESULTS = "danceResults";
	const std::string JK_MARKS = "marks";
	const std::string JK_RANKING = "ranking";
	const std::string JK_RANKING_TO = "rankingTo";

	const char MARKS_DELIMETER = '|';
};

#endif
