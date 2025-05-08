#ifndef STOREDPROCEDURES_H_
#define STOREDPROCEDURES_H_

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include "../../EmptyStoredProcedures.h"


/// <summary>
/// Contains all preseted stored procedures for the database.
/// </summary>
class StoredProcedures : public EmptyStoredProcedures {
public:
    StoredProcedures() : dbCommunicator(DatabaseCommunicator()) {}

    /// <summary>
	/// Gets all results between two dates sorted by compId from the database.
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <returns>
	/// Each row contains these values as string. In the database, they are stored as:
    /// compId: int,
    /// marks: string,
    /// endedDance: double,
    /// numberOfCouples: int, 
    /// round: int
    /// </returns>
    Table GetAllResultsBetweenDates(const std::string& from, const std::string& to);

    /// <summary>
   /// Gets all judges info between two dates sorted by compId from the database.
   /// </summary>
   /// <param name="from"></param>
   /// <param name="to"></param>
   /// <returns>
   /// Each row contains these values as string. In the database, they are stored as:
   /// compId: int,
   /// judgeId: int,
   /// index: int - index of the judge in the round
   /// </returns>
    Table GetAllJudgesBetweenDates(const std::string& from, const std::string& to);

    /// <summary>
	/// Gets all judges personal informaion such as name and surname between two dates sorted by compId from the database.
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <returns>
    /// Each row contains these values as string. In the database, they are stored as:
    /// compId: int,
    /// judgeId: int,
	/// index: int,
	/// name: string,
	/// surname: string,
    /// state: string
    /// </returns>
    Table GetAllJudgesPersonInfoBetweenDates(const std::string& from, const std::string& to);

    /// <summary>
	/// Gets all results of a judge between two dates sorted by compId from the database. The judge is selected by the name and surname.
	/// WARNING: The name and surname are not unique. This means that if there are two judges with the same name and surname, the results of both will be returned.
	/// WARNING: It has problems with czech characters. Primarily use GetOneJudgeResultsBetweenDatesById
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <param name="name"></param>
    /// <param name="surname"></param>
    /// <returns>
    /// Each row contains these values as string. In the database, they are stored as:
    /// compId: int,
    /// marks: string,
	/// endedDance: double,
	/// numberOfCouples: int,
	/// round: int,
    /// index: int
    /// </returns>
    Table GetOneJudgeResultsBetweenDatesByName(const std::string& from, const std::string& to, const std::string& name, const std::string& surname);

    /// <summary>
    /// Gets all results of a judge between two dates sorted by compId from the database. The judge is selected by the id.
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <param name="name"></param>
    /// <param name="surname"></param>
    /// <returns>
    /// Each row contains these values as string. In the database, they are stored as:
    /// compId: int,
    /// marks: string,
    /// endedDance: double,
    /// numberOfCouples: int,
    /// round: int,
    /// index: int
    /// </returns>
    Table GetOneJudgeResultsBetweenDatesById(const std::string& from, const std::string& to, const int& id);
    
    /// <summary>
	/// Gets the name, surname and nationality of a person by the id from the database.
    /// </summary>
    /// <param name="id"></param>
    /// <returns>
    /// Each row contains these values as string. In the database, they are stored as:
    /// name: string,
    /// surname: string,
    /// nationality: string
    /// </returns>
    Table GetNameById(const int& id);

    /// <summary>
    /// Gets all judges info between which have judged a specified pair two dates sorted by compId from the database.
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <returns>
    /// Each row contains these values as string. In the database, they are stored as:
    /// compId: int,
    /// judgeId: int,
    /// index: int - index of the judge in the round
    /// </returns>
    Table GetAllJudgesOfPairBetweenDates(const std::string& from, const std::string& to, const int& pairId);

    /// <summary>
    /// Gets all results of a specified pair between two dates sorted by compId from the database.
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <returns>
    /// Each row contains these values as string. In the database, they are stored as:
    /// compId: int,
    /// marks: string,
    /// endedDance: double,
    /// numberOfCouples: int, 
    /// round: int
    /// </returns>
    Table GetAllResultsOfPairBetweenDates(const std::string& from, const std::string& to, const int& pairId);

    /// <summary>
    /// Gets all judges which have judged a specified club personal informaion such as name and surname between two dates sorted by compId from the database.
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <returns>
    /// Each row contains these values as string. In the database, they are stored as:
    /// compId: int,
    /// judgeId: int,
    /// index: int,
    /// name: string,
    /// surname: string,
    /// state: string
    /// </returns>
    Table GetAllJudgesToPairPersonInfoBetweenDates(const std::string& from, const std::string& to, const int& clubId);

    /// <summary>
/// Gets all judges info between which have judged a specified club two dates sorted by compId from the database.
/// </summary>
/// <param name="from"></param>
/// <param name="to"></param>
/// <returns>
/// Each row contains these values as string. In the database, they are stored as:
/// compId: int,
/// judgeId: int,
/// index: int - index of the judge in the round
/// </returns>
    Table GetAllJudgesOfClubBetweenDates(const std::string& from, const std::string& to, const int& clubId);

    /// <summary>
    /// Gets all results of a specified club between two dates sorted by compId from the database.
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <returns>
    /// Each row contains these values as string. In the database, they are stored as:
    /// compId: int,
    /// marks: string,
    /// endedDance: double,
    /// numberOfCouples: int, 
    /// round: int
    /// </returns>
    Table GetAllResultsOfClubBetweenDates(const std::string& from, const std::string& to, const int& clubId);

    /// <summary>
    /// Gets all judges which have judged a specified pair personal informaion such as name and surname between two dates sorted by compId from the database.
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <returns>
    /// Each row contains these values as string. In the database, they are stored as:
    /// compId: int,
    /// judgeId: int,
    /// index: int,
    /// name: string,
    /// surname: string,
    /// state: string
    /// </returns>
    Table GetAllJudgesToClubPersonInfoBetweenDates(const std::string& from, const std::string& to, const int& pairId);

	/// <summary>
	/// Gets all pairs results, which have been judged by a specified judge between two dates sorted by pairId from the database.
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="judgeId"></param>
	/// <returns>
    /// Each row contains these values as string. In the database, they are stored as:
    /// index: int,
    /// round: int,
    /// pairId: int,
    /// marks: string,
    /// endedDance: double,
    /// numberOfCouples: int
    /// </returns>
	Table GetAllPairsByOneJudgeResultsBetweenDates(const std::string& from, const std::string& to, const int& judgeId);

	/// <summary>
	/// Gets all clubs personal information, which have been judged by a specified judge between two dates sorted by pairId from the database.
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="judgeId"></param>
	/// <returns>
    /// Each row contains these values as string. In the database, they are stored as:
	/// pairId: int,
	/// manName: string,
	/// manSurname: string,
	/// manState: string,
	/// womanName: string,
	/// womanSurname: string,
	/// womanState: string
    /// </returns>
	Table GetAllPairsPersonInfoByOneJudgeBetweenDates(const std::string& from, const std::string& to, const int& judgeId);

	/// <summary>
	/// Gets all results of clubs, which have been judged by a specified judge between two dates sorted by pairId from the database.
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="judgeId"></param>
	/// <returns></returns>
	Table GetAllClubsByOneJudgeResultsBetweenDates(const std::string& from, const std::string& to, const int& judgeId);

	/// <summary>
	/// Gets info about all clubs which have been judged by a specified judge between two dates sorted by pairId from the database.
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="judgeId"></param>
	/// <returns></returns>
	Table GetAllClubsInfoByOneJudgeBetweenDates(const std::string& from, const std::string& to, const int& judgeId);
private:
	DatabaseCommunicator dbCommunicator;
};

#endif
