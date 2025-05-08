#ifndef ABSTRACTINSTANCEFINALEVALUATOR_H_
#define ABSTRACTINSTANCEFINALEVALUATOR_H_

/// <summary>
/// 
/// </summary>
class AbstractInstanceFinalEvaluator {
public:
	/// <summary>
	/// Evaluates the round dance based on the given parameters. 
	/// The returned number is between -1 and 1. 
	/// The lower the number, the worse did the judge rate the pair, in comparison to the other judges.
	/// </summary>
	/// <param name="endedUp">On which place did the pair ended up?</param>
	/// <param name="mark">Which mark did the judge give to the pair?</param>
	/// <param name="totalPairs">How many pairs was there?</param>
	/// <returns></returns>
	virtual double evaluateCompFinalDance(double& endedUp, int& mark, int& totalPairs) = 0;
protected:
};


#endif