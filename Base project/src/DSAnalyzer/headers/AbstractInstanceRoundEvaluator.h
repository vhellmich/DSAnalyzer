#ifndef ABSTRACTINSTANCEROUNDEVALUATOR_H_
#define ABSTRACTINSTANCEROUNDEVALUATOR_H_

/// <summary>
/// Creates an interface for non-final round evaluation.
/// </summary>
class AbstractInstanceRoundEvaluator {
public:
	/// <summary>
	/// Evaluates the round dance based on the given parameters. 
	/// The returned number is between -1 and 1. 
	/// The lower the number, the worse did the judge rate the pair, in comparison to the other judges.
	/// </summary>
	/// <param name="gotX">Did the pair get an x from a judge?</param>
	/// <param name="Xs">How many xs did the pair got?</param>
	/// <param name="total">How many xs was there to get?</param>
	/// <returns></returns>
	virtual double evaluateCompRoundDance(bool gotX, int& Xs, int& total) = 0;
protected:
};


#endif