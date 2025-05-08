#include "../headers/StoredProcedures.h"

void StoredProcedures::InsertEvent(int id, const std::string& name, const std::string& date) {
    std::string procedure = readSQLFile("Procedures/InsertEvent.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;
    varsToReplace["id"] = ReplaceString(std::to_string(id), false);
    varsToReplace["name"] = ReplaceString(name, true);
    varsToReplace["date"] = ReplaceString(date, true);

    replacePlaceholders(procedure, varsToReplace);

    communicator.executeNonQuery(procedure);
    
}

void StoredProcedures::InsertComp(int id, int eventId, const std::string& date, const std::string& discipline,
    const std::string& category, int numberOfDances, int numberOfCouples, const std::string& class_) {
    std::string procedure = readSQLFile("Procedures/InsertComp.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;
    varsToReplace["id"] = ReplaceString(std::to_string(id), false);
    varsToReplace["eventId"] = ReplaceString(std::to_string(eventId), false);
    varsToReplace["date"] = ReplaceString(date, true);
    varsToReplace["discipline"] = ReplaceString(discipline, true);
    varsToReplace["category"] = ReplaceString(category, true);
    varsToReplace["numberOfDances"] = ReplaceString(std::to_string(numberOfDances), false);
    varsToReplace["numberOfCouples"] = ReplaceString(std::to_string(numberOfCouples), false);
    varsToReplace["class"] = ReplaceString(class_, true);

    replacePlaceholders(procedure, varsToReplace);

    communicator.executeNonQuery(procedure);

}

void StoredProcedures::InsertIsJudging(const Person& judge, int compId, int index) {
    std::string procedure = readSQLFile("Procedures/InsertIsJudging.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;

    // Judge details
    varsToReplace["id"] = ReplaceString(std::to_string(judge.id), false);
    varsToReplace["name"] = ReplaceString(judge.name, true);
    varsToReplace["surname"] = ReplaceString(judge.surname, true);
    varsToReplace["state"] = ReplaceString(judge.state, true);

    varsToReplace["compId"] = ReplaceString(std::to_string(compId), false);
    varsToReplace["index"] = ReplaceString(std::to_string(index), false);

    replacePlaceholders(procedure, varsToReplace);

    communicator.executeNonQuery(procedure);

}

void StoredProcedures::InsertResult(const Person& man, const Person& woman, const std::string& clubName, int compId,
    int round, int dance, const std::string& marks, int endedFrom, int endedTo, double endedDance) {
    std::string procedure = readSQLFile("Procedures/InsertResult.sqltemplate");
    std::map<std::string, ReplaceString> varsToReplace;

    // Man details
    varsToReplace["manId"] = ReplaceString(std::to_string(man.id), false);
    varsToReplace["manName"] = ReplaceString(man.name, true);
    varsToReplace["manSurname"] = ReplaceString(man.surname, true);
    varsToReplace["manState"] = ReplaceString(man.state, true);

    // Woman details
    varsToReplace["womanId"] = ReplaceString(std::to_string(woman.id), false);
    varsToReplace["womanName"] = ReplaceString(woman.name, true);
    varsToReplace["womanSurname"] = ReplaceString(woman.surname, true);
    varsToReplace["womanState"] = ReplaceString(woman.state, true);

    // Club
    varsToReplace["clubName"] = ReplaceString(clubName, true);

    // Result details
    varsToReplace["compId"] = ReplaceString(std::to_string(compId), false);
    varsToReplace["round"] = ReplaceString(std::to_string(round), false);
    varsToReplace["dance"] = ReplaceString(std::to_string(dance), false);

    // Marks and placement
    varsToReplace["marks"] = ReplaceString(marks, true);
    varsToReplace["endedFrom"] = ReplaceString(std::to_string(endedFrom), false);
    varsToReplace["endedTo"] = ReplaceString(std::to_string(endedTo), false);
    varsToReplace["endedDance"] = ReplaceString(std::to_string(endedDance), false);

    replacePlaceholders(procedure, varsToReplace);

    communicator.executeNonQuery(procedure);
}