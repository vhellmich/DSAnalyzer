# DanceSport Results Scraper

A simple scraper designed specifically for the new CSTS pages.  
It is **not** intended to be fully generic. It works with the CSTS API as it is, but since the API structure often changes slightly, the scraper might occasionally write invalid data into the database — requiring manual corrections by the maintainer.

---

## Installation and Build

### On Windows (using Visual Studio 2022 and cmd)

1. Set up vcpkg:
```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
```

2. Set the environment variable `$VCPKG_ROOT` to the path of your vcpkg root directory:
```bash
set VCPKG_ROOT="<path-to-vcpkg-root>"
```

3. Set the environment variable `$DS_DATABASE_PATH` to the path of the database
```bash
set DS_DATABASE_PATH="<path-to-databse.db>"
```

4. Open the project in Visual Studio 2022.

5. Set the target to vcpkg.

6. Build and run.

---

### On Linux

1. Set up vcpkg:
```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
```

2. Set the environment variable for the database path:
```bash
export VCPKG_ROOT="<path-to-vcpkg-root>"
```

3. Set the environment variable `$DS_DATABASE_PATH` to the path of the database
```bash
export DS_DATABASE_PATH="<path-to-databse.db>"
```

4. Navigate to the project folder and run:
```bash
cmake --preset vcpkg
cmake --build build
```

5. Run the program:
```bash
./build/DSResultsScraper
```

---

## Usage

**DSResultsScraper** can scrape data **by month** — collecting all competition data within a specific month.

The program takes two arguments: `<month> <year>`, both numbers.  
Example for February 2020:
```bash
./build/DSResultsScraper 2 2020
```

---

### Logging

- If everything goes smoothly, the program may not output anything during its run (it may take up to half an hour).
- Logs detailed events and errors into `logs/events.log`.
- Logs warnings and errors directly to the console as well.

---

## Dependencies

- `curl`
- `sqlite3`
- `nlohmann-json`
- `spdlog`

---

# Programmer Documentation

## File Structure

The application uses CMake and vcpkg for library management.

Main directory contains:
- `CMakeLists.txt`
- `CMakePresets.json`
- `vcpkg.json`
- `vcpkg-configuration.json`
- `README.md`
- `DSResultsScraper/` — main program entry point
- `Headers/` — specific header files
- `Source Files/` — matching source files
- `Stored Procedures/` — SQL templates

> Note:  
> `CMakeLists.txt` refers to the parent directory because the whole project consists of DSAnalyzer, DSDatabase, and DSResultsScraper.

---

## Class Structure Overview

### DSResultsScraper
- The main class controlling the flow.
- In `run()`, it uses `ResultsScraper` to download data and `JsonResultsParser` to store it in the database.

### ResultsScraper
- Initializes with the target month.
- The `getResults()` method systematically requests data.
- Uses `JsonRetriever` to handle web requests.
- Returns a `ScraperResponse` each call.

### ScraperResponse
- A simple data structure holding the type of response and the actual response (`nlohmann::json` format).
- Response types:
  - `EVENTS` — Events data
  - `COMPS` — Competitions data
  - `RESULTS` — Results data
  - `INVALID` — Unparseable response
  - `END` — No more data

### JsonRetriever
- Static method `RetrieveFromUrl`.
- Fetches URL content using curl, parses into `nlohmann::json`.

### JsonResultsParser
- Three methods for parsing and saving different types of responses into the database.
- Returns `true` if successful, `false` if an error occurs.
- Uses `StoredProcedures` for database interaction.

### EmptyStoredProcedures
- Base class for reading and filling `.sqltemplate` files.
- Executes SQL using `DatabaseCommunicator`.

### .sqltemplate Files
- Text files with SQL queries containing `<{varName}>` placeholders.
- Dynamically replaced with actual parameters during execution.

### DatabaseCommunicator
- Provides `executeQuery` (write) and `executeNonQuery` (read) SQL methods.

### StoredProcedures
- Inherits from `EmptyStoredProcedures`.
- Implements specific SQL procedures for writing results.

