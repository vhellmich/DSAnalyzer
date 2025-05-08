#ifndef DATAEVALUATOR_H_
#define DATAEVALUATOR_H_

#include <map>
#include <vector>
#include <string>
#include <memory> 
#include "AbstractInstanceFinalEvaluator.h"
#include "AbstractInstanceRoundEvaluator.h"

using Row = std::map<std::string, std::string>;
using Table = std::vector<Row>;

/// <summary>
/// Basic data strucure to hold all the rating information about, which the DataEvaluator needs.
/// </summary>
struct JudgeRatingData {
public:
	/// <summary>
	/// Creates a new instance of JudgeRatingData with 0 rating and 0 samples.
	/// </summary>
	JudgeRatingData() : ratingSum(0.0), samples(0) {}

    /// <summary>
    /// Creates a new instance of JudgeRatingData with specified rating and 1 sample.
    /// </summary>
    /// <param name="rating"></param>
    JudgeRatingData(double rating) : ratingSum(rating), samples(1) {}

    /// <summary>
	/// Creates a new instance of JudgeRatingData with specified rating and number of samples.
    /// </summary>
    /// <param name="rating"></param>
    /// <param name="samples"></param>
    JudgeRatingData(double rating, int samples) : ratingSum(rating), samples(samples) {}

	/// <summary>
	/// Calculates the average rating based on the total rating sum and number of samples.
	/// </summary>
	/// <returns></returns>
	double getRating() const {
		return samples > 0 ? ratingSum / samples : 0.0;
	}

    double ratingSum;
    int samples;
};


/// <summary>
/// 
/// </summary>
class DataEvaluator {
public:
    DataEvaluator(std::shared_ptr<AbstractInstanceFinalEvaluator> finalEvaluator,
                  std::shared_ptr<AbstractInstanceRoundEvaluator> roundEvaluator);


    /// <summary>
	/// Evaluates all judges from the given results and judges table. 
	/// BOTH TABLES MUST BE SORTED BY compId and must be linkable by compId.
    /// </summary>
    /// <param name="results"></param>
    /// <param name="compsJudges">Each row must contain "compId", "judgeId", "index"</param>
    /// <param name="onlyAccuracy">Each row must contain "compId", "marks", "endedDance", "numberOfCouples", "round"</param>
    /// <returns></returns>
    std::map<int, JudgeRatingData> EvaluateAllJudgesFromGivenResults(const Table& results, const Table& compsJudges, bool onlyAccuracy = true);

    /// <summary>
	/// Evaluates a single judge from the given results.
    /// It is up to the caller to ensure that all the results are from the same judge.
    /// </summary>
    /// <param name="results">>Each row must contain "compId", "marks", "endedDance", "numberOfCouples", "round", "index"</param>
    /// <returns></returns>
    JudgeRatingData EvaluateJudge(const Table& results);

	/// <summary>
	/// Evaluates the positivity of one judge to a specific pair.
	/// The higher the rating, the more positive the judge was to the pair.
    /// The Table must be sorted by pairId.
	/// </summary>
	/// <param name="results">
	/// Each row must contain "marks", "endedDance", "numberOfCouples", "round", "index", "pairId"
    /// </param>
	/// <returns></returns>
	std::vector<JudgeRatingData> EvaluateAllPairsPositivity(const Table& results);

private:
    /// <summary>
	/// Helps to split a string into a vector of strings based on a given delimiter.
	/// This is used to split the marks of the judges.
    /// </summary>
    /// <param name="input"></param>
    /// <param name="delimiter"></param>
    /// <returns></returns>
    std::vector<std::string> splitString(const std::string& input, char delimiter);

    /// <summary>
	/// Evalutaor model for evaluation of the final rounds.
    /// </summary>
    std::shared_ptr<AbstractInstanceFinalEvaluator> finalEvaluator;

    /// <summary>
    /// Evalutaor model for evaluation of all other than final rounds.
    /// </summary>
    std::shared_ptr<AbstractInstanceRoundEvaluator> roundEvaluator;

    inline bool gaveX(char mark) {
        return (mark == 'X' || mark == 'x');
    }

	// Constants for the column names in the tables
	const std::string COMP_ID = "compId";
	const std::string JUDGE_ID = "judgeId";
	const std::string JUDGE_INDEX = "index";
	const std::string MARKS = "marks";
	const std::string ENDED_DANCE = "endedDance";
	const std::string NUMBER_OF_COUPLES = "numberOfCouples";
	const std::string ROUND = "round";
	const std::string PAIR_ID = "pairId";

    // Special strings and chars constants used in evaluations
	const char DELIMETER = '|';
	const std::string FINAL_ROUND = "1";
};




#endif