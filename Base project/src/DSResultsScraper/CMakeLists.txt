cmake_minimum_required(VERSION 3.10)

project(DSResultsScraper)

set(CMAKE_CXX_STANDARD 17) 

find_package(CURL CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)
add_executable(DSResultsScraper DSResultsScraper.cpp "headers/JsonRetriever.h" "Source Files/JsonRetriever.cpp" "headers/ResultsScraper.h" "headers/StoredProcedures.h" "Source Files/StoredProcedures.cpp" "headers/JsonResultsParser.h" "Source Files/ResultsScraper.cpp" "Source Files/JsonResultsParser.cpp" "../DSDatabase/DatabaseCommunicator.h" "../DSDatabase/DatabaseCommunicator.cpp" "../Logger.h" "../Logger.cpp" "../EmptyStoredProcedures.h" "../EmptyStoredProcedures.cpp" "headers/DateHandler.h" "headers/DSResultsScraper.h")

target_link_libraries(DSResultsScraper PRIVATE CURL::libcurl)
target_link_libraries(DSResultsScraper PRIVATE unofficial::sqlite3::sqlite3)
target_link_libraries(DSResultsScraper PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(DSResultsScraper PRIVATE spdlog::spdlog)



add_custom_command(
    TARGET DSResultsScraper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Procedures
            ${CMAKE_CURRENT_BINARY_DIR}/Procedures
    COMMENT "Copying Procedures folder to build directory"
)
