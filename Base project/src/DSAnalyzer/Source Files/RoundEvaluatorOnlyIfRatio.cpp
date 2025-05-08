#include "../headers/RoundEvaluatorOnlyIfRatio.h"
#include <cmath>

double RoundEvaluatorOnlyIfRatio::evaluateCompRoundDance(bool gotX, int& Xs, int& total) {
	int xsCount = Xs;
	if (gotX) {
		xsCount = total - Xs;
	}

	if (xsCount == 0) {
		return 0.0; // Avoid division by zero
	}

	double ratio = static_cast<double>(xsCount) / static_cast<double>(total); // Calculate the ratio
	if (std::isinf(ratio) || std::isnan(ratio)) {
		ratio = 0.0; // Handle infinite or NaN values
	}
	if (ratio < threshold) {
		return 0.0; // Return 0 if the ratio is below the threshold
	}

	if (!gotX) {
		ratio = -ratio; // Negate the ratio if gotX is true
	}

	return ratio; // Return ratio only if it meets the threshold
}