# DanceSport Analyzer

The aim of this project is to analyze the accuracy of judges' evaluations in couple dance competitions.  
Evaluation in dance sport is always subjective, and judges do not always agree on their assessments. Couples sometimes become upset after competitions because a judge rated them poorly, either due to personal bias or favoritism toward a competitor.

This program objectively uses data to assess:
- The general accuracy of judges
- Specific biases against particular couples and clubs

> **Important**:  
> The accuracy rating of a judge depends on comparisons with other judges' ratings, who themselves may not always be accurate.  
> Therefore, the results are not purely objective, and interpretations should be approached with caution.

---

## Overview

This project consists of three main parts:

### DSDatabase
Contains data scraped from the CSTS site using **DSResultsScraper**. The DSDatabase.db is prepared in DSDatabase folder. There are already some valid data (not all of them) to help you get started.

- More details can be found in `DSResultsScraper/DSDatabase-schema.pdf`.


### DSResultsScraper
A simple scraper designed specifically for the new CSTS pages.

- It is **not** intended to be a fully generic scraper.
- It relies on the CSTS API, which occasionally changes in structure, potentially causing the scraper to write invalid data that must be manually corrected.
- More information about structure, features, and functionality can be found in the `DSResultsScraper/` folder.


### DSAnalyzer
Provides analysis features, including:
- Ranking all judges by accuracy
- Ranking a specific judge's accuracy
- Ranking judges based on bias against a pair
- Ranking judges based on bias against a club
- Ranking pairs by a judge's bias
- Ranking clubs by a judge's bias

All analyses can also be restricted to data from a specific time period.

More details about structure, features, and functionality are located in the `DSAnalyzer/` folder.

## Possible extensions
In the future, this will become a part of backend to a web application with user friendly GUI. Before that, there will be some changes. 
 - Sqlite3 will be replaced by Postgresql
 - The program takes too long to respond, so there will be some precomputing of the data
 - There will be another scraper, which will scrape also old results, from before 2018, which are only on the old website
 - There will be more possible evaluators