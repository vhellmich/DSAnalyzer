#include "../headers/DSAnalyzerCore.h"

std::vector<PresentingJudgeData> AnalyzerCore::RateAllJudges(const std::string& from, const std::string& to) {
	StoredProcedures sp;

	Table results = sp.GetAllResultsBetweenDates(from, to);

	Table judges = sp.GetAllJudgesBetweenDates(from, to);
	Table judgesPersonalInfo = sp.GetAllJudgesPersonInfoBetweenDates(from, to);

	DataEvaluator de(std::make_shared<FinalEvaluatorSquaredRatiod>(), std::make_shared<RoundEvaluatorOnlyIfRatio>(REASONABLE_THRESHOLD));
	std::map<int, JudgeRatingData> finalRating = de.EvaluateAllJudgesFromGivenResults(results, judges);

	auto result = LinkRatingToPersonData(finalRating, judgesPersonalInfo);
	std::sort(result.begin(), result.end(), RatingComparator());
	return result;
}

std::vector<PresentingJudgeData> AnalyzerCore::RatePositivityOfJudgesToPair(const std::string& from, const std::string& to, const int& pairId) {
	StoredProcedures sp;

	Table results = sp.GetAllResultsOfPairBetweenDates(from, to, pairId);

	Table judges = sp.GetAllJudgesOfPairBetweenDates(from, to, pairId);
	Table judgesPersonalInfo = sp.GetAllJudgesToPairPersonInfoBetweenDates(from, to, pairId);

	DataEvaluator de(std::make_shared<FinalEvaluatorSquaredRatiod>(), std::make_shared<RoundEvaluatorOnlyIfRatio>(REASONABLE_THRESHOLD));
	std::map<int, JudgeRatingData> finalRating = de.EvaluateAllJudgesFromGivenResults(results, judges, false);

	auto result = AnalyzerCore::LinkRatingToPersonData(finalRating, judgesPersonalInfo);
	std::sort(result.begin(), result.end(), RatingComparator());
	return result;
}

std::vector<PresentingJudgeData> AnalyzerCore::RatePositivityOfJudgesToClub(const std::string& from, const std::string& to, const int& clubId) {
	StoredProcedures sp;

	Table results = sp.GetAllResultsOfClubBetweenDates(from, to, clubId);

	Table judges = sp.GetAllJudgesOfClubBetweenDates(from, to, clubId);
	Table judgesPersonalInfo = sp.GetAllJudgesToClubPersonInfoBetweenDates(from, to, clubId);

	DataEvaluator de(std::make_shared<FinalEvaluatorSquaredRatiod>(), std::make_shared<RoundEvaluatorOnlyIfRatio>(REASONABLE_THRESHOLD));
	std::map<int, JudgeRatingData> finalRating = de.EvaluateAllJudgesFromGivenResults(results, judges, false);

	auto result = AnalyzerCore::LinkRatingToPersonData(finalRating, judgesPersonalInfo);
	std::sort(result.begin(), result.end(), RatingComparator());
	return result;
}


std::vector<PresentingPairData> AnalyzerCore::RatePositivityOfPairsToJudge(const std::string& from, const std::string& to, const int& judgeId) {
	StoredProcedures sp;

	Table results = sp.GetAllPairsByOneJudgeResultsBetweenDates(from, to, judgeId);

	Table pairsPersonalInfo = sp.GetAllPairsPersonInfoByOneJudgeBetweenDates(from, to, judgeId);

	DataEvaluator de(std::make_shared<FinalEvaluatorSquaredRatiod>(), std::make_shared<RoundEvaluatorOnlyIfRatio>(REASONABLE_THRESHOLD));
	std::vector<JudgeRatingData> finalRating = de.EvaluateAllPairsPositivity(results);

	
	auto result = AnalyzerCore::LinkRatingToPairData(finalRating, pairsPersonalInfo);
	std::sort(result.begin(), result.end(), RatingComparator());
	return result;
}

std::vector<PresentingClubData> AnalyzerCore::RatePositivityOfClubsToJudge(const std::string& from, const std::string& to, const int& judgeId) {
	StoredProcedures sp;

	Table results = sp.GetAllClubsByOneJudgeResultsBetweenDates(from, to, judgeId);

	Table clubsInfo = sp.GetAllClubsInfoByOneJudgeBetweenDates(from, to, judgeId);

	DataEvaluator de(std::make_shared<FinalEvaluatorSquaredRatiod>(), std::make_shared<RoundEvaluatorOnlyIfRatio>(REASONABLE_THRESHOLD));
	std::vector<JudgeRatingData> finalRating = de.EvaluateAllPairsPositivity(results);


	auto result = AnalyzerCore::LinkRatingToClubData(finalRating, clubsInfo);
	std::sort(result.begin(), result.end(), RatingComparator());
	return result;
}

std::vector<PresentingPairData> AnalyzerCore::LinkRatingToPairData(const std::vector<JudgeRatingData>& finalRating, const Table& pairsPersonalInfo) {
	auto result = std::vector<PresentingPairData>();

	auto pairIt = pairsPersonalInfo.begin();
	for (auto it = finalRating.begin(); it != finalRating.end(); ++it) {
		PresentingPairData pairData;
		pairData.id = std::stoi(pairIt->at("pairId"));
		pairData.manName = pairIt->at("manName");
		pairData.manSurname = pairIt->at("manSurname");
		pairData.manState = pairIt->at("manState");
		pairData.womanName = pairIt->at("womanName");
		pairData.womanSurname = pairIt->at("womanSurname");
		pairData.womanState = pairIt->at("womanState");
		pairData.rating = it->getRating();
		pairData.sampled = it->samples;

		result.push_back(pairData);

		pairIt++;
	}

	return result;
}

std::vector<PresentingJudgeData> AnalyzerCore::LinkRatingToPersonData(const std::map<int, JudgeRatingData>& finalRating, const Table& judgesPersonalInfo) {
	auto result = std::vector<PresentingJudgeData>();

	std::size_t counter = 0;
	for (auto it = finalRating.begin(); it != finalRating.end(); ++it) {
		PresentingJudgeData judgeData;
		judgeData.id = it->first;
		judgeData.rating = it->second.getRating();
		judgeData.sampled = it->second.samples;
		judgeData.name = judgesPersonalInfo.at(counter).at("name");
		judgeData.surname = judgesPersonalInfo.at(counter).at("surname");

		result.push_back(judgeData);
		counter++;
	}

	return result;
}

std::pair<std::string, std::string> AnalyzerCore::SplitName(const std::string& fullName) {
	std::size_t delimiterPos = fullName.find(' ');
	if (delimiterPos == std::string::npos) {
		// If no space is found, return the full name as the first part and an empty string as the second part
		return { fullName, "" };
	}

	std::string firstName = fullName.substr(0, delimiterPos);
	std::string lastName = fullName.substr(delimiterPos + 1);
	return { firstName, lastName };
}


std::vector<PresentingClubData> AnalyzerCore::LinkRatingToClubData(const std::vector<JudgeRatingData>& finalRating, const Table& clubsPersonalInfo) {
	auto result = std::vector<PresentingClubData>(); 

	auto clubIt = clubsPersonalInfo.begin();
	for (auto it = finalRating.begin(); it != finalRating.end(); ++it) {
		PresentingClubData clubData;
		clubData.id = std::stoi(clubIt->at("clubId"));
		clubData.name = clubIt->at("name");
		clubData.rating = it->getRating();
		clubData.sampled = it->samples;

		result.push_back(clubData);

		clubIt++;
	}

	return result;
}



