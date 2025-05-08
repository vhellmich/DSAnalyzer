#include "../headers/StoredProcedures.h"


Table StoredProcedures::GetAllResultsBetweenDates(const std::string& from, const std::string& to) {
    std::string procedure = readSQLFile("Procedures/GetAllResultsBetweenDates.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;

    varsToReplace["from"] = ReplaceString(from, true);
    varsToReplace["to"] = ReplaceString(to, true);
    replacePlaceholders(procedure, varsToReplace);

    return dbCommunicator.executeQuery(procedure);
}

Table StoredProcedures::GetAllJudgesBetweenDates(const std::string& from, const std::string& to) {
    std::string procedure = readSQLFile("Procedures/GetAllJudgesBetweenDates.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;

    varsToReplace["from"] = ReplaceString(from, true);
    varsToReplace["to"] = ReplaceString(to, true);
    replacePlaceholders(procedure, varsToReplace);

    return dbCommunicator.executeQuery(procedure);
}

Table StoredProcedures::GetAllJudgesPersonInfoBetweenDates(const std::string& from, const std::string& to) {
    std::string procedure = readSQLFile("Procedures/GetAllJudgesPersonInfoBetweenDates.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;

    varsToReplace["from"] = ReplaceString(from, true);
    varsToReplace["to"] = ReplaceString(to, true);
    replacePlaceholders(procedure, varsToReplace);

    return dbCommunicator.executeQuery(procedure);
}

Table StoredProcedures::GetOneJudgeResultsBetweenDatesByName(const std::string& from, const std::string& to, const std::string& name, const std::string& surname) {
    std::string procedure = readSQLFile("Procedures/GetOneJudgeResultsBetweenDatesByName.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;

    varsToReplace["from"] = ReplaceString(from, true);
    varsToReplace["to"] = ReplaceString(to, true);
    varsToReplace["name"] = ReplaceString(name, true);
    varsToReplace["surname"] = ReplaceString(surname, true);
    replacePlaceholders(procedure, varsToReplace);

    return dbCommunicator.executeQuery(procedure);
}

Table StoredProcedures::GetOneJudgeResultsBetweenDatesById(const std::string& from, const std::string& to, const int& id) {
    std::string procedure = readSQLFile("Procedures/GetOneJudgeResultsBetweenDatesById.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;

    varsToReplace["from"] = ReplaceString(from, true);
    varsToReplace["to"] = ReplaceString(to, true);
    varsToReplace["judgeId"] = ReplaceString(std::to_string(id), false);
    replacePlaceholders(procedure, varsToReplace);

    return dbCommunicator.executeQuery(procedure);
}

Table StoredProcedures::GetNameById(const int& id) {
    std::string procedure = readSQLFile("Procedures/GetNameById.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;

    varsToReplace["id"] = ReplaceString(std::to_string(id), false);
    replacePlaceholders(procedure, varsToReplace);

    return dbCommunicator.executeQuery(procedure);
}

Table StoredProcedures::GetAllJudgesOfPairBetweenDates(const std::string& from, const std::string& to, const int& pairId) {
    std::string procedure = readSQLFile("Procedures/GetAllJudgesOfPairBetweenDates.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;

    varsToReplace["from"] = ReplaceString(from, true);
    varsToReplace["to"] = ReplaceString(to, true);
    varsToReplace["pairId"] = ReplaceString(std::to_string(pairId), false);
    replacePlaceholders(procedure, varsToReplace);

    return dbCommunicator.executeQuery(procedure);
}

Table StoredProcedures::GetAllResultsOfPairBetweenDates(const std::string& from, const std::string& to, const int& pairId) {
    std::string procedure = readSQLFile("Procedures/GetAllResultsOfPairBetweenDates.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;

    varsToReplace["from"] = ReplaceString(from, true);
    varsToReplace["to"] = ReplaceString(to, true);
    varsToReplace["pairId"] = ReplaceString(std::to_string(pairId), false);
    replacePlaceholders(procedure, varsToReplace);

    return dbCommunicator.executeQuery(procedure);
}

Table StoredProcedures::GetAllJudgesToPairPersonInfoBetweenDates(const std::string& from, const std::string& to, const int& pairId) {
    std::string procedure = readSQLFile("Procedures/GetAllJudgesToPairPersonInfoBetweenDates.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;

    varsToReplace["from"] = ReplaceString(from, true);
    varsToReplace["to"] = ReplaceString(to, true);
    varsToReplace["pairId"] = ReplaceString(std::to_string(pairId), false);
    replacePlaceholders(procedure, varsToReplace);

    return dbCommunicator.executeQuery(procedure);
}

Table StoredProcedures::GetAllPairsByOneJudgeResultsBetweenDates(const std::string& from, const std::string& to, const int& judgeId) {
    std::string procedure = readSQLFile("Procedures/GetAllPairsByOneJudgeResultsBetweenDates.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;

    varsToReplace["from"] = ReplaceString(from, true);
    varsToReplace["to"] = ReplaceString(to, true);
    varsToReplace["judgeId"] = ReplaceString(std::to_string(judgeId), false);
    replacePlaceholders(procedure, varsToReplace);

    return dbCommunicator.executeQuery(procedure);
}

Table StoredProcedures::GetAllPairsPersonInfoByOneJudgeBetweenDates(const std::string& from, const std::string& to, const int& judgeId) {
    std::string procedure = readSQLFile("Procedures/GetAllPairsPersonInfoByOneJudgeBetweenDates.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;

    varsToReplace["from"] = ReplaceString(from, true);
    varsToReplace["to"] = ReplaceString(to, true);
    varsToReplace["judgeId"] = ReplaceString(std::to_string(judgeId), false);
    replacePlaceholders(procedure, varsToReplace);

    return dbCommunicator.executeQuery(procedure);
}

Table StoredProcedures::GetAllClubsByOneJudgeResultsBetweenDates(const std::string& from, const std::string& to, const int& judgeId) {
	std::string procedure = readSQLFile("Procedures/GetAllClubsByOneJudgeResultsBetweenDates.sqltemplate");
	std::map<std::string, ReplaceString> varsToReplace;

	varsToReplace["from"] = ReplaceString(from, true);
	varsToReplace["to"] = ReplaceString(to, true);
	varsToReplace["judgeId"] = ReplaceString(std::to_string(judgeId), false);
	replacePlaceholders(procedure, varsToReplace);

	return dbCommunicator.executeQuery(procedure);
}

Table StoredProcedures::GetAllClubsInfoByOneJudgeBetweenDates(const std::string& from, const std::string& to, const int& judgeId) {
	std::string procedure = readSQLFile("Procedures/GetAllClubsInfoByOneJudgeBetweenDates.sqltemplate");
	std::map<std::string, ReplaceString> varsToReplace;

	varsToReplace["from"] = ReplaceString(from, true);
	varsToReplace["to"] = ReplaceString(to, true);
	varsToReplace["judgeId"] = ReplaceString(std::to_string(judgeId), false);
	replacePlaceholders(procedure, varsToReplace);

	return dbCommunicator.executeQuery(procedure);
}

Table StoredProcedures::GetAllJudgesToClubPersonInfoBetweenDates(const std::string& from, const std::string& to, const int& clubId) {
    std::string procedure = readSQLFile("Procedures/GetAllJudgesToClubPersonInfoBetweenDates.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;

    varsToReplace["from"] = ReplaceString(from, true);
    varsToReplace["to"] = ReplaceString(to, true);
    varsToReplace["clubId"] = ReplaceString(std::to_string(clubId), false);
    replacePlaceholders(procedure, varsToReplace);

    return dbCommunicator.executeQuery(procedure);
}

Table StoredProcedures::GetAllJudgesOfClubBetweenDates(const std::string& from, const std::string& to, const int& clubId) {
    std::string procedure = readSQLFile("Procedures/GetAllJudgesOfClubBetweenDates.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;

    varsToReplace["from"] = ReplaceString(from, true);
    varsToReplace["to"] = ReplaceString(to, true);
    varsToReplace["clubId"] = ReplaceString(std::to_string(clubId), false);
    replacePlaceholders(procedure, varsToReplace);

    return dbCommunicator.executeQuery(procedure);
}

Table StoredProcedures::GetAllResultsOfClubBetweenDates(const std::string& from, const std::string& to, const int& clubId) {
    std::string procedure = readSQLFile("Procedures/GetAllResultsOfClubBetweenDates.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;

    varsToReplace["from"] = ReplaceString(from, true);
    varsToReplace["to"] = ReplaceString(to, true);
    varsToReplace["clubId"] = ReplaceString(std::to_string(clubId), false);
    replacePlaceholders(procedure, varsToReplace);

    return dbCommunicator.executeQuery(procedure);
}
