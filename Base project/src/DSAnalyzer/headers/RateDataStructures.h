#ifndef RATEDATASTRUCTURES_H_
#define RATEDATASTRUCTURES_H_

/// <summary>
/// Basic datastructure to hold all the rating information about, which the DataEvaluator needs.
/// </summary>
struct RateData {
	double rating;
	int sampled;
};

/// <summary>
/// Data structure to hold all the information about a judge, which is meant to be seen by a user.
/// </summary>
struct PresentingJudgeData : public RateData {
	std::string name;
	std::string surname;
	int id;
};

/// <summary>
/// Data structure to hold all the information about a pair, which is meant to be seen by a user.
/// </summary>
struct PresentingPairData : public RateData {
	std::string manName;
	std::string manSurname;
	std::string manState;
	std::string womanName;
	std::string womanSurname;
	std::string womanState;
	int id;
};

/// <summary>
/// Data structure to hold all the information about a club, which is meant to be seen by a user.
/// </summary>
struct PresentingClubData : public RateData {
	std::string name;
	int id;
};

/// <summary>
/// Used to sort judges by rating. Higher (worse) rating first.
/// </summary>
struct RatingComparator {
	bool operator()(const RateData& a, const RateData& b) const {
		return a.rating > b.rating; // Descending order by rating
	}
};

#endif // !
