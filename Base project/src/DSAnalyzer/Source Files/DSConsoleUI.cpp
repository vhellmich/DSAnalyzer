#include <iostream>
#include <iomanip> // For std::setw
#include <locale>  // For std::locale
#include <codecvt> // For std::codecvt_utf8 (if needed on older compilers)

#include "../headers/DSConsoleUI.h"


void DSConsoleUi::run(const std::vector<std::string>& args) {

	if (args.size() < 2) {
		std::cout << HELP_MESSAGE << std::endl;
		return;
	}
	std::string from = DEFAULT_FROM;
	std::string to = DEFAULT_TO;

	AnalyzerCore ac;
	std::string firstArg = args[1];

	try {
		if (firstArg == FA_ALL) {
			if (args.size() == 4) {
				from = args[2];
				to = args[3];
			}

			auto result = ac.RateAllJudges(from, to);

			CzechPrintingHelper cph;

			cph.printJudgeHeader();
			for (const auto& judge : result) {
				cph.printJudgeData(judge);
			}
		}
		else if (firstArg == FA_JUDGE) {
			if (args[2] == FA_COUPLE) {
				if (args.size() == 6) {
					from = args[4];
					to = args[5];
				}

				int judgeId = std::stoi(args[3]);
				auto result = ac.RatePositivityOfPairsToJudge(from, to, judgeId);

				CzechPrintingHelper cph;
				cph.printPairHeader();

				for (const auto& pair : result) {
					cph.printPairData(pair);
				}
			}
			else if (args[2] == FA_CLUB) {
				if (args.size() == 6) {
					from = args[4];
					to = args[5];
				}

				int judgeId = std::stoi(args[3]);
				auto result = ac.RatePositivityOfClubsToJudge(from, to, judgeId);

				CzechPrintingHelper cph;
				cph.printClubHeader();

				for (const auto& club : result) {
					cph.printClubData(club);
				}
			}
			else if (args[2] == SA_ID) {
				int id;
				id = std::stoi(args[3]);

				auto result = ac.RateOneJudge("", from, to, id);
				CzechPrintingHelper cph;

				cph.printJudgeHeader(); 
				cph.printJudgeData(result);
			}
			else if (args[2] == SA_NAME) {
				auto result = ac.RateOneJudge(args[3], from, to);
				CzechPrintingHelper cph;

				cph.printJudgeHeader();
				cph.printJudgeData(result);
			}
			else {
				std::cout << HELP_MESSAGE << std::endl;
				return;
			}
		}
		else if (firstArg == FA_CLUB && args[2] == SA_ID) {
			CzechPrintingHelper cph;
			if (args.size() == 6) {
				from = args[4];
				to = args[5];
			}
			auto result = ac.RatePositivityOfJudgesToClub(from, to, std::stoi(args[3]));
			cph.printJudgeHeader();

			for (const auto& judge : result) {
				cph.printJudgeData(judge);
			}
		}
		else if (firstArg == FA_COUPLE && args[2] == SA_ID) {
			if (args.size() == 6) {
				from = args[4];
				to = args[5];
			}
			auto result = ac.RatePositivityOfJudgesToPair(from, to, std::stoi(args[3]));


			CzechPrintingHelper cph;

			cph.printJudgeHeader();

			// Print each judge's data
			for (const auto& judge : result) {
				cph.printJudgeData(judge);
			}
		}
		else {
			std::cout << HELP_MESSAGE << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::cout << HELP_MESSAGE << std::endl;
	}
}