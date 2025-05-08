#ifndef ROUNDEVALUATORONLYIFRATIO_H
#define ROUNDEVALUATORONLYIFRATIO_H

#include "AbstractInstanceRoundEvaluator.h"

/// <summary>
/// Basic evaluation model for evaluation of the non-final rounds.
/// </summary>
class RoundEvaluatorOnlyIfRatio : public AbstractInstanceRoundEvaluator {
public:
    /// <summary>
	/// Threashold for the ratio to be considered for evaluation. 
    /// Example:
	/// If a couple has 2 xs out of 5, the ratio of xs is 0.4.
	/// If the threshold is 0.5, the ratio is not considered for evaluation and it returns 0.
	/// If the threshold is 0.3, the ratio is considered for evaluation and it returns 0.4.
    /// </summary>
    /// <param name="thresholdValue"></param>
    RoundEvaluatorOnlyIfRatio(double thresholdValue) : threshold(thresholdValue) {}

    double evaluateCompRoundDance(bool gotX, int& Xs, int& total) override;

    // Getter for the threshold
    double getThreshold() const {
        return threshold;
    }

    // Setter for the threshold
    void setThreshold(double newThreshold) {
        threshold = newThreshold;
    }
private:
    double threshold; // Ratio threshold for evaluation
};

#endif 
