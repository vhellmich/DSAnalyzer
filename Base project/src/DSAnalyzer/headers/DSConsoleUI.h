#ifndef DSCONSOLEUI_H
#define DSCONSOLEUI_H

#include <iostream>
#include <vector>
#include "../headers/StoredProcedures.h"
#include "../headers/DataEvaluator.h"
#include "../headers/FinalEvaluatorSquaredRatiod.h"
#include "../headers/RoundEvaluatorOnlyIfRatio.h"
#include "../headers/DSAnalyzerCore.h"
#include "../headers/CzechPrintingHelper.h"
#include "../headers/RateDataStructures.h"


/// <summary>
/// Very basic console UI.
/// Prints the data to the console based on giver arguments.
/// </summary>
class DSConsoleUi {
public:
	void run(const std::vector<std::string>& args);
private:
	const std::string HELP_MESSAGE =
		"This is a console UI for the DanceSport application.\n"
		"\n"
		"Usage:\n"
		"DSAnalyzer <command> [arguments]\n"
		"\n"
		"Available commands:\n"
		"\n"
		"1. all [<from> <to>]\n"
		"   - Rank all judges by judging accuracy.\n"
		"\n"
		"2. judge id <judgeId> [<from> <to>]\n"
		"   - Rank the accuracy of a specific judge by ID.\n"
		"\n"
		"3. judge name \"<judgeName>\" [<from> <to>]\n"
		"   - Rank the accuracy of a specific judge by name.\n"
		"\n"
		"4. couple id <coupleId> [<from> <to>]\n"
		"   - Analyze judges' bias against a specific couple.\n"
		"\n"
		"5. club id <clubId> [<from> <to>]\n"
		"   - Analyze judges' bias against a specific club.\n"
		"\n"
		"6. judge couple <judgeId> [<from> <to>]\n"
		"   - Analyze a judge's bias across couples.\n"
		"\n"
		"7. judge club <judgeId> [<from> <to>]\n"
		"   - Analyze a judge's bias across clubs.\n";


	//first arguments
	const std::string FA_ALL = "all";
	const std::string FA_JUDGE = "judge";
	const std::string FA_CLUB = "club";
	const std::string FA_COUPLE = "couple";

	//second arguments
	const std::string SA_CLUB = "club";
	const std::string SA_COUPLE = "couple";
	const std::string SA_ID = "id";
	const std::string SA_NAME = "name";


	const std::string DEFAULT_FROM = "1900-10-04";
	const std::string DEFAULT_TO = "2100-10-04";

};

#endif 
