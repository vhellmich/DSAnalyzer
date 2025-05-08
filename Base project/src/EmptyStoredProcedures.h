#ifndef EMPTYSTOREDPROCEDURES_H_
#define EMPTYSTOREDPROCEDURES_H_

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "DSDatabase/DatabaseCommunicator.h"
#include "Logger.h"



class EmptyStoredProcedures {
public:

protected:
    /// <summary>
	/// Simple structure to hold a string and a boolean indicating if the string is a SQL string or not.
    /// </summary>
    struct ReplaceString {
        ReplaceString(std::string value, bool isString) : val(value), isString_(isString) {}
        ReplaceString() : val(""), isString_(true) {}

        std::string val;
        bool isString_;
    };

    DatabaseCommunicator communicator;

    /// <summary>
	/// Replaces placeholders in the .sqltemplate string with actual values.
    /// </summary>
    /// <param name="sql"></param>
    /// <param name="varsToReplace"></param>
    void replacePlaceholders(std::string& sql, const std::map<std::string, ReplaceString>& varsToReplace);

    /// <summary>
	/// Loads file into string.
    /// </summary>
    /// <param name="filename"></param>
    /// <returns></returns>
    std::string readSQLFile(const std::string& filename);
};

#endif
