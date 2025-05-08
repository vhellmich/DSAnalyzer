# DSAnalyzer

The analyzer includes:
- Ranking all judges by accuracy
- Ranking the accuracy of a specific judge
- Ranking judges by bias against a specific couple
- Ranking judges by bias against a specific club
- Ranking couples based on the bias of a designated judge
- Ranking clubs based on the bias of a designated judge

All analyses can be limited to a specified time period.

> **Note**:  
> The UI is minimal, as the focus was on functionality. In the future, this application will be paired with a web server using a different API.

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
./build/DSAnalyzer
```

---

## Usage

The DSAnalyzer takes different numbers of arguments depending on the use case.  
All names and IDs in the examples are fictional - they are not meant to work. Some IDs, such as club IDs, are only available in the database and not visible through the CSTS site or API.

You can optionally add two arguments `<from>` and `<to>` after every command to define a custom time span.

### Ranking All Judges by Accuracy

Takes one argument: `"all"`

```bash
./build/DSAnalyzer all
```

Example output:
```
Name                Surname                           Rating   Sampled
----------------------------------------------------------------------
Ailish              Green                              14.38        34
Bob                 Blue                               14.25        98
Chuck               Black                              14.01       117
Daniel              Yellow                             13.12      1352
...
```

- Name and surname of the judge
- Rating (0–100): 100 means completely opposite judging to others; 0 means perfect agreement
- Number of samples: more samples = greater reliability

### Ranking the Accuracy of One Judge

Identify a judge by **ID** (preferred) or **name**.

By ID:
```bash
./build/DSAnalyzer judge id <judgeId>
```

Example:
```bash
./build/DSAnalyzer judge id 1234567
```

By Name:
```bash
./build/DSAnalyzer judge name "<judgeName>"
```

Example:
```bash
./build/DSAnalyzer judge name "John Doe II"
```

Example output:
```
Name                Surname                           Rating   Sampled
----------------------------------------------------------------------
John                Doe II                              7.96      1752
```

> **Tip**: Identifying by name is less reliable due to possible duplicates and issues with special characters on Windows. Prefer using IDs.

### Ranking Judges by Bias Against a Specific Couple

```bash
./build/DSAnalyzer couple id <coupleId>
```

Example output:
```
Name                Surname                           Rating   Sampled
----------------------------------------------------------------------
Ailish              Black                              21.21        15
Bob                 Brown                               5.82        25
Chuck               Green                               0.00        15
Daniel              Blue                               -6.06        15
Emilia              Red                               -17.58        15
```

- Rating range: -100 to 100
- Positive: Judge favored the couple
- Negative: Judge rated the couple worse than others

### Ranking Judges by Bias Against a Specific Club

```bash
./build/DSAnalyzer club id <clubId>
```

Same output format and meaning as the couple example.

### Ranking Couples by Bias of a Designated Judge

```bash
./build/DSAnalyzer judge couple <judgeId>
```

Example output:
```
Man                                          Woman                                        Rating    Sampled
--------------------------------------------------------------------------------------------------------------
Liam               Blue                     Emma               Purple                    81.82     5
Noah               Green                    Olivia             Magenta                   34.65     10
Ethan              Red                      Sophia             Cyan                      0.00      10
Mason              Yellow                   Ava                Indigo                    -0.05     20
Logan              Orange                   Isabella           Violet                    -14.55    5
Lucas              Pink                     Mia                Teal                      -39.39    15
```

### Ranking Clubs by Bias of a Designated Judge

```bash
./build/DSAnalyzer judge club <judgeId>
```

Example output:
```
Name                                        Rating   Sampled
------------------------------------------------------------
TK Blue                                      45.45        15
TK Green                                      1.97       140
TK Black                                     -5.42        25
TK Red                                      -17.58        15
```

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
- `DSAnalyzer.cpp`
- `Headers/`
- `Source Files/`
- `Stored Procedures/`

Note: `CMakeLists.txt` refers to the parent directory (the whole project contains DSAnalyzer, DSDatabase, and DSResultsScraper).

## Class Structure Overview

### DSConsoleUi
- Called from `main`
- Provides the basic console UI
- Uses `DSAnalyzerCore` and `CzechPrintingHelper`

### CzechPrintingHelper
- Assists in printing tables with Czech characters correctly.

### DSAnalyzerCore
- Implements one method for each use case.
- Returns printable data.
- Internally uses `StoredProcedures` and `DataEvaluator`.

### EmptyStoredProcedures
- Reads and fills SQL templates.
- Uses `DatabaseCommunicator` to execute queries.

### .sqltemplate Files
- SQL templates with `<{varName}>` placeholders.

### DatabaseCommunicator
- Executes SQL queries (read and write).

### StoredProcedures
- Inherits from `EmptyStoredProcedures`.
- Implements specific stored procedures.

### DataEvaluator
- Evaluates SQL results.
- Expects a `shared_ptr<Table>` (alias for `vector<map<string, string>>`).

Uses two internal evaluators:
- `FinalEvaluatorSquaredRatiod`
- `RoundEvaluatorOnlyIfRatio`

### AbstractInstanceFinalEvaluator
- Abstract class for final round evaluation.

### AbstractInstanceRoundEvaluator
- Abstract class for non-final round evaluation.

### FinalEvaluatorSquaredRatiod
- Squares and normalizes judge-place differences.

### RoundEvaluatorOnlyIfRatio
- Filters bias if not enough confirmation from other judges.
