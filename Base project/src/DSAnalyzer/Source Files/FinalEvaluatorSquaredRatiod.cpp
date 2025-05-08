#include "../headers/FinalEvaluatorSquaredRatiod.h"

#include <cmath>

double FinalEvaluatorSquaredRatiod::evaluateCompFinalDance(double& endedUp, int& mark, int& totalPairs) {
	if (endedUp == mark) {
		return 0.0; // Return 0 if endedUp equals mark
	}
	double rating = (double)((fabs(endedUp - mark) + 1) * (fabs(endedUp - mark) + 1)) / (double)(totalPairs * totalPairs);
	if (endedUp < mark) {
		rating = -rating;
	}
	if (std::isinf(rating) || std::isnan(rating)) {
		rating = 0.0; // Handle infinite or NaN values
	}
	return rating; // Return the square of the ratio
}