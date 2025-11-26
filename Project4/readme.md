Pokedex Project
Overview
This is a terminal-based Pokédex built in Node.js using the PokeAPI.  
The user can search for a Pokemon, an item, a move, or browse lists of these things.  
The project demonstrates asynchronous code, callbacks, API usage, and console input handling.

How to Run
1. Install Node.js
2. Open the project folder in the terminal.
3. Run the program with:
   node main.js

Main Functions
--showMenu() – displays menu options.
--run() – main program loop; routes the user to the correct action.
--prompt(cb) – asks for a search term and calls the provided callback.
--searchPoke/searchItem/searchMove – async API calls to the PokeAPI.
--printPoke/printItem/printMove – formats and prints the API data.
--list(type) – page lists of Pokémon, items, or moves.

Objectives
--Use async/await and fetch.
--Practice callback-based program flow.
--Work with API data and JSON.
--Build a looping console application that is user-friendly.

Reflection
We learned how JavaScript handles asynchronous operations, how callbacks fit into program flow, how to use fetch to retrieve, and how to format API data. This project helped us better understand JavaScript code and organizing a simple terminal program.
