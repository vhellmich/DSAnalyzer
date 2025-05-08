cmake_minimum_required(VERSION 3.10)

project(DSAnalyzer)

set(CMAKE_CXX_STANDARD 17) 

find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(spdlog REQUIRED)
add_executable(DSAnalyzer DSAnalyzer.cpp 

"../DSDatabase/DatabaseCommunicator.cpp" 

"../Logger.cpp" 

"../EmptyStoredProcedures.cpp"

"Source Files/DSConsoleUI.cpp"

"Source Files/DataEvaluator.cpp" 
"Source Files/DSAnalyzerCore.cpp" 
"Source Files/StoredProcedures.cpp" 
"Source Files/RoundEvaluatorOnlyIfRatio.cpp" 
"Source Files/FinalEvaluatorSquaredRatiod.cpp" 
)

target_link_libraries(DSAnalyzer PRIVATE unofficial::sqlite3::sqlite3)
target_link_libraries(DSAnalyzer PRIVATE spdlog::spdlog)

add_custom_command(
    TARGET DSAnalyzer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Procedures
            ${CMAKE_CURRENT_BINARY_DIR}/Procedures
    COMMENT "Copying Procedures folder to build directory"
)
