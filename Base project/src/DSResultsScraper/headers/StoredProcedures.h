#ifndef STOREDPROCEDURES_H_
#define STOREDPROCEDURES_H_

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../../EmptyStoredProcedures.h"

/// <summary>
/// Basic data structure to store organized data about a person.
/// </summary>
struct Person {
    Person() : id(-1), name(""), surname(""), state("") {}
    Person(int id, std::string name, std::string surname, std::string state) : id(id), name(name), surname(surname), state(state) {}
    int id;
    std::string name;
    std::string surname;
    std::string state;
};

/// <summary>
/// Class with predifined stored procedures for the database.
/// </summary>
class StoredProcedures : public EmptyStoredProcedures {
public:
    StoredProcedures() : loggerPtr(Logger::Get()) { }

    /// <summary>
	/// Insert event into the database.
    /// </summary>
    /// <param name="id"></param>
    /// <param name="name"></param>
    /// <param name="date"></param>
    void InsertEvent(int id, const std::string& name, const std::string& date);

    /// <summary>
	/// Inserts competition into the database.
    /// </summary>
    /// <param name="id"></param>
    /// <param name="eventId"></param>
    /// <param name="date"></param>
    /// <param name="discipline"></param>
    /// <param name="category"></param>
    /// <param name="numberOfDances"></param>
    /// <param name="numberOfCouples"></param>
    /// <param name="class_"></param>
    void InsertComp(int id, int eventId, const std::string& date, const std::string& discipline, const std::string& category, int numberOfDances, int numberOfCouples, const std::string& class_);

    /// <summary>
	/// Inserts data about which judge is judging which competition.
	/// If the judge is not yet in the database, it will be inserted.
    /// </summary>
    /// <param name="judge"></param>
    /// <param name="compId"></param>
    /// <param name="index"></param>
    void InsertIsJudging(const Person& judge, int compId, int index);

    /// <summary>
	/// Inserts data about results of a competition.
	/// If the person, couple or club is not yet in the database, it will be inserted.
    /// </summary>
    /// <param name="man"></param>
    /// <param name="woman"></param>
    /// <param name="clubName"></param>
    /// <param name="compId"></param>
    /// <param name="round"></param>
    /// <param name="dance"></param>
    /// <param name="marks"></param>
    /// <param name="endedFrom"></param>
    /// <param name="endedTo"></param>
    /// <param name="endedDance"></param>
    void InsertResult(const Person& man, const Person& woman, const std::string& clubName, int compId, int round, int dance, const std::string& marks, int endedFrom, int endedTo, double endedDance);

private:
    std::shared_ptr<spdlog::logger> loggerPtr;
};

#endif
