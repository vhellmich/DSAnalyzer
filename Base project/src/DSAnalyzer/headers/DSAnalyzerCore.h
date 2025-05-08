#ifndef DSANALYZERCORE_H_
#define DSANALYZERCORE_H_

#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <algorithm>
#include "DataEvaluator.h"
#include "StoredProcedures.h"
#include "FinalEvaluatorSquaredRatiod.h"
#include "RoundEvaluatorOnlyIfRatio.h"
#include "RateDataStructures.h"



/// <summary>
/// Provides a method for each analysis use case. 
/// </summary>
class AnalyzerCore {
public:
	/// <summary>
	/// Rates all judges between two dates and returns a sorted vector of PresentingJudgeData.
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <returns></returns>
	std::vector<PresentingJudgeData> RateAllJudges(const std::string& from, const std::string& to);

	/// <summary>
	/// Rates all judges which has judged a specific pair between two dates and returns a sorted vector of PresentingJudgeData.
	/// It mesures the positivity of judges to a specific pair.
	/// The higher the rating, the more positive the judge was to the pair. 
	/// Meaning that the judge rated the pair higher than the other judges on average.
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="pairId"></param>
	/// <returns></returns>
	std::vector<PresentingJudgeData> RatePositivityOfJudgesToPair(const std::string& from, const std::string& to, const int& pairId);

	/// <summary>
	/// Rates all judges which has judged a specific club between two dates and returns a sorted vector of PresentingJudgeData.
	/// It mesures the positivity of judges to a specific club.
	/// The higher the rating, the more positive the judge was to the club. 
	/// Meaning that the judge rated the club higher than the other judges on average.
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="clubId"></param>
	/// <returns></returns>
	std::vector<PresentingJudgeData> RatePositivityOfJudgesToClub(const std::string& from, const std::string& to, const int& clubId);


	/// <summary>
	/// Rates one judge's accuracy between two dates.
	/// If the name is empty, the judge is selected by id. 
	/// Otherwise, the judge is selected by name which contains their full name.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="id"></param>
	/// <returns></returns>
	PresentingJudgeData RateOneJudge(const std::string& name, const std::string& from, const std::string& to, const int& id = 0) {
		StoredProcedures sp;
		std::pair<std::string, std::string> nameParts = SplitName(name);

		Table results;

		if (name.size() == 0) {
			results = sp.GetOneJudgeResultsBetweenDatesById(from, to, id);
			auto names = sp.GetNameById(id);
			if (names.size() > 0) {
				nameParts.first = names.at(0).at("name");
				nameParts.second = names.at(0).at("surname");
			}
		}
		else {
			results = sp.GetOneJudgeResultsBetweenDatesByName(from, to, nameParts.first, nameParts.second);
		}

		DataEvaluator de(std::make_shared<FinalEvaluatorSquaredRatiod>(), std::make_shared<RoundEvaluatorOnlyIfRatio>(REASONABLE_THRESHOLD));
		auto rating = de.EvaluateJudge(results);

		auto result = PresentingJudgeData();
		result.id = id;
		result.rating = rating.getRating();
		result.sampled = rating.samples;
		result.name = nameParts.first;
		result.surname = nameParts.second;

		return result;
	}

	/// <summary>
	/// Rates the positivity of rating of all pairs which have been judged by a specific judge between two dates.
	/// The higher the rating, the more positive the judge was to the pair.
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="judgeId"></param>
	/// <returns></returns>
	std::vector<PresentingPairData> RatePositivityOfPairsToJudge(const std::string& from, const std::string& to, const int& judgeId);

	/// <summary>
	/// Rates the positivity of rating of all clubs which have been judged by a specific judge between two dates.
	/// The higher the rating, the more positive the judge was to the club.
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="judgeId"></param>
	/// <returns></returns>
	std::vector<PresentingClubData> RatePositivityOfClubsToJudge(const std::string& from, const std::string& to, const int& judgeId);

private:
	/// <summary>
	/// Splits name into first and last name by the first space character.
	/// example: "John Doe" -> ("John", "Doe")
	/// example: "John Doe II" -> ("John", "Doe II")
	/// </summary>
	/// <param name="fullName"></param>
	/// <returns></returns>
	std::pair<std::string, std::string> SplitName(const std::string& fullName);

	/// <summary>
	/// Links the final rating of judges to their personal information.
	/// </summary>
	/// <param name="finalRating"></param>
	/// <param name="judgesPersonalInfo"></param>
	/// <returns>Unsorted vector of filled in personal data and ratings</returns>
	std::vector<PresentingJudgeData> LinkRatingToPersonData(const std::map<int, JudgeRatingData>& finalRating, const Table& judgesPersonalInfo);

	/// <summary>
	/// Links the final rating of judges to couples personal information.
	/// </summary>
	/// <param name="finalRating"></param>
	/// <param name="judgesPersonalInfo"></param>
	/// <returns>Unsorted vector of filled in personal data and ratings</returns>
	std::vector<PresentingPairData> LinkRatingToPairData(const std::vector<JudgeRatingData>& finalRating, const Table& pairsPersonalInfo);

	/// <summary>
	/// Links the final rating of judges to clubs personal information.
	/// </summary>
	/// <param name="finalRating"></param>
	/// <param name="judgesPersonalInfo"></param>
	/// <returns>Unsorted vector of filled in personal data and ratings</returns>
	std::vector<PresentingClubData> LinkRatingToClubData(const std::vector<JudgeRatingData>& finalRating, const Table& clubsPersonalInfo);



	/// <summary>
	/// I find this threshold reasonable for the current use case. 
	/// May be changed or even changed to a user input in the future.
	/// </summary>
	const double REASONABLE_THRESHOLD = 0.7;
};





#endif