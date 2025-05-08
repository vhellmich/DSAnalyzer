#ifndef FINALEVALUATORSQUAREDRATIOD_H
#define FINALEVALUATORSQUAREDRATIOD_H

#include "AbstractInstanceFinalEvaluator.h"

/// <summary>
/// Basic evaluator model for evaluation of the final rounds.
/// </summary>
class FinalEvaluatorSquaredRatiod : public AbstractInstanceFinalEvaluator {
public:
	double evaluateCompFinalDance(double& endedUp, int& mark, int& totalPairs) override;
};

#endif