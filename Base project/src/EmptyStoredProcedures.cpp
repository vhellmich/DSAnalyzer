#include "EmptyStoredProcedures.h"

void EmptyStoredProcedures::replacePlaceholders(std::string& sql, const std::map<std::string, ReplaceString>& varsToReplace) {
    size_t pos;
    for (auto& [key, value] : varsToReplace) {
        std::string valString = value.val;
        if (value.isString_) valString = "'" + valString + "'";
        while ((pos = sql.find("{" + key + "}")) != std::string::npos) sql.replace(pos, key.length() + 2, valString);
    }
}

std::string EmptyStoredProcedures::readSQLFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        SPDLOG_LOGGER_CALL(Logger::Get().get(), spdlog::level::err, "Unable to open file: {}", filename);
        return "";
    }
    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}