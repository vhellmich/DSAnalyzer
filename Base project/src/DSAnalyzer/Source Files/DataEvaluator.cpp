#include "../headers/DataEvaluator.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>

// Constructor implementation
DataEvaluator::DataEvaluator(std::shared_ptr<AbstractInstanceFinalEvaluator> finalEvaluator,
                             std::shared_ptr<AbstractInstanceRoundEvaluator> roundEvaluator)
    : finalEvaluator(std::move(finalEvaluator)), roundEvaluator(std::move(roundEvaluator)) {}


std::map<int, JudgeRatingData> DataEvaluator::EvaluateAllJudgesFromGivenResults(const Table& results, const Table& compsJudges, bool onlyAccuracy) {
    std::map<int, JudgeRatingData> analyzed;

	auto judgesItRight = compsJudges.begin();
    auto judgesItLeft = compsJudges.begin();

	int lastCompId = -1;


	// Iterate through the results table
	for (const auto& row : results) {
		// If the current row's compId is not linked to current judging info's compId, it finds the right judging info
		// Because the scraped data is sometimes not perfect, it may happen, that the judging info contains some compIds, that is not linked to a single result. (It is handled)
		while (row.at(COMP_ID) != std::to_string(lastCompId)) {
			
            int last = std::stoi(judgesItRight->at(COMP_ID));

            judgesItLeft = judgesItRight;
            while (judgesItRight != compsJudges.end() && judgesItRight->at(COMP_ID) == std::to_string(last)) {
				judgesItRight++;
            }
            lastCompId = std::stoi(judgesItLeft->at(COMP_ID));
		}

		auto ratingsVector = splitString(row.at(MARKS), DELIMETER);
        int totalPairs = std::stoi(row.at(NUMBER_OF_COUPLES));
		double endedDance = std::stod(row.at(ENDED_DANCE));

		// Iterate through the judging info for the current compId.
		// In other words, iterate trought each judge that judged the current competition.
		for (auto it = judgesItLeft; it != judgesItRight; ++it) {
			double judgeRating = 0.0;

            // calculates the rating for one judge from a final round
            if (row.at(ROUND) == FINAL_ROUND) {
                int mark = std::stoi(ratingsVector[std::stoi(it->at(JUDGE_INDEX))]);
				
                judgeRating = finalEvaluator->evaluateCompFinalDance(endedDance, mark, totalPairs);
                if (onlyAccuracy) {
					judgeRating = std::fabs(judgeRating);
                }
            }
			// calculates the rating for one judge from every other non-final round
            else {
                bool gotX = (gaveX(ratingsVector[std::stoi(it->at(JUDGE_INDEX))][0]));
                int ratingsVectorSize = ratingsVector.size();
				int Xs = endedDance;
                judgeRating = roundEvaluator->evaluateCompRoundDance(gotX, Xs, ratingsVectorSize);
                if (onlyAccuracy) {
                    judgeRating = std::fabs(judgeRating);
                }
            }
                       
            int judgeId = std::stoi(it->at(JUDGE_ID));

			// If the judgeId is not in the analyzed map, add it with the current judgeRating
			auto analyzedIt = analyzed.find(judgeId);
			if (analyzedIt == analyzed.end()) {
				analyzed[judgeId] = JudgeRatingData(judgeRating);
            }
			// If the judgeId is already in the analyzed map, update its rating
            else {
				analyzedIt->second.samples++;
                analyzedIt->second.ratingSum += judgeRating;
            }
		}
	}

    return analyzed;
}

std::vector<JudgeRatingData> DataEvaluator::EvaluateAllPairsPositivity(const Table& results) {
	int lastPairId = -1;
	std::vector<JudgeRatingData> analyzed;
	int vectorIndex = -1;

	// I can just loop trough the results table, because it is already sorted by pairId
    for (const auto& row : results) {
		int currentPairId = std::stoi(row.at(PAIR_ID)); 

		// If the current row's pairId is not equal to the last one, it means we are on a new pair
        if (lastPairId != currentPairId) {
			lastPairId = std::stoi(row.at(PAIR_ID));
			vectorIndex++;
			analyzed.push_back(JudgeRatingData());
        }

		double judgeRating = 0.0;

        auto ratingsVector = splitString(row.at(MARKS), DELIMETER);
        int totalPairs = std::stoi(row.at(NUMBER_OF_COUPLES));
        double endedDance = std::stod(row.at(ENDED_DANCE));

		// calculates the rating from a final round
		if (row.at(ROUND) == FINAL_ROUND) {
			int mark = std::stoi(ratingsVector[std::stoi(row.at(JUDGE_INDEX))]);
			judgeRating = finalEvaluator->evaluateCompFinalDance(endedDance, mark, totalPairs);
		}
		// calculates the rating from a non-final round
		else {
			bool gotX = (gaveX(ratingsVector[std::stoi(row.at(JUDGE_INDEX))][0]));
			int ratingsVectorSize = ratingsVector.size();
			int Xs = endedDance;
			judgeRating = roundEvaluator->evaluateCompRoundDance(gotX, Xs, ratingsVectorSize);
		}

		// Updates the rating data and number of samples
		analyzed[vectorIndex].samples++;
		analyzed[vectorIndex].ratingSum += judgeRating;
    }

	return analyzed;
}



JudgeRatingData DataEvaluator::EvaluateJudge(const Table& results) {
	auto result = JudgeRatingData(0,0);

	// Iterate through the results table
    for (const auto& row : results) {
        auto ratingsVector = splitString(row.at(MARKS), DELIMETER);
        int totalPairs = std::stoi(row.at(NUMBER_OF_COUPLES));
        double endedDance = std::stod(row.at(ENDED_DANCE));

        double judgeRating = 0.0;

		// calculates the rating from a final round
        if (row.at(ROUND) == "1") {
            int mark = std::stoi(ratingsVector[std::stoi(row.at(JUDGE_INDEX))]);
            judgeRating = std::fabs(finalEvaluator->evaluateCompFinalDance(endedDance, mark, totalPairs));
        }
		// calculates the rating from a non-final round
        else {
            bool gotX = (gaveX(ratingsVector[std::stoi(row.at(JUDGE_INDEX))][0]));

            int ratingsVectorSize = ratingsVector.size();
            int Xs = endedDance;
            judgeRating = std::fabs(roundEvaluator->evaluateCompRoundDance(gotX, Xs, ratingsVectorSize));
        }

        // Updates the rating data and number of samples
        result.samples++;
        result.ratingSum += judgeRating;
    }
	return result;
}




// Helper method to split a string by a delimiter
std::vector<std::string> DataEvaluator::splitString(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}




