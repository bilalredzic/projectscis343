const readline = require("readline"); // Import the readline module to handle user input
const rl = readline.createInterface({ // Create an interface for reading input and output
    input: process.stdin, // Set the input to standard input (keyboard)
    output: process.stdout // Set the output to standard output (console)
});



function showMenu() { // Function to display the menu options
    console.log("\n=== Pokedex Menu ===");
    console.log("1. Search Pokémon");
    console.log("2. Search Item");
    console.log("3. Search Move");
    console.log("4. Quit");
}
function run() {
    showMenu(); // Display the menu to the user
    rl.question("Enter your choice: ", (choice) => { // Prompt the user for their choice, choice is callback parameter
        if (choice === "1") { // If the user chose option 1
            prompt(searchPoke); // Call the prompt function with searchPoke as the callback
        } else if (choice === "2") { // If the user chose option 2
            prompt(searchItem); // Call the prompt function with searchItem as the callback
        } else if (choice === "3") { // If the user chose option 3
            prompt(searchMove); // Call the prompt function with searchMove as the callback
        } else if (choice === "4") { // If the user chose option 4
            console.log("byebye"); // Print a goodbye message
            rl.close(); // Close the readline interface
        } else { // If the user entered an invalid choice
            console.log("Invalid choice, try again."); // Inform the user of the invalid choice
            run(); // Restart the menu
        }
    });
}


run(); // Start the program by running the main function

function prompt(cb) { // Function to prompt the user for a search term
    rl.question("Enter a search term: ", (term) => { // Ask the user for a search term
        cb(term);  // call the callback function with the user’s input
    });
}

async function searchPoke(term) { // Function to search for a Pokémon
    try { // fetch data from the Pokémon API
        
        const response = await fetch(`https://pokeapi.co/api/v2/pokemon/${term.toLowerCase()}`); // fetch data from the Pokémon API3
        const json = await response.json(); // parse the response as JSON
        printPoke(json); // send the data to print

    } catch (error) { // catch any errors that occur during the fetch
        console.log("Error fetching data:", error); // log the error message
        run(); // go back to menu
    }
}
function printPoke(json) { // Function to print Pokémon information
    console.log("\n=== Pokémon Info ===");
    console.log("Name:", json.name);
    console.log("Height:", json.height);
    console.log("Weight:", json.weight);
    console.log("Base Experience:", json.base_experience);

    console.log("Moves:");
    json.moves.forEach(moveObj => { // Loop through each move object in the moves array
        console.log(" -", moveObj.move.name); // Print the name of each move
    });

    run(); // go back to menu
}

async function searchItem(term) { // Function to search for an item
    try { // fetch item data from the API
        const response = await fetch(`https://pokeapi.co/api/v2/item/${term.toLowerCase()}`); // fetch item data from the API
        const json = await response.json(); // parse the response as JSON
        printItem(json); // send the data to print

    } catch (error) { // catch any errors that occur during the fetch
        console.log("Error fetching item:", error);
        run(); // go back to menu
    }
}

function printItem(json) { // Function to print item information
    console.log("\n=== Item Info ===");
    console.log("Name:", json.name);
    console.log("Cost:", json.cost);
    console.log("Category:", json.category.name);
    console.log("Effect:", json.effect_entries[0].effect);

    run(); // go back to menu
}



async function searchMove(term) {
    try { // fetch move data from the API
        const response = await fetch(`https://pokeapi.co/api/v2/move/${term.toLowerCase()}`); // fetch move data from the API
        const json = await response.json();
        printMove(json);

    } catch (error) { // catch any errors that occur during the fetch
        console.log("Error fetching move:", error); // log the error message
        run(); // go back to menu
    }
}

function printMove(json) { // Function to print move information
    console.log("\n=== Move Info ===");
    console.log("Name:", json.name);
    console.log("Accuracy:", json.accuracy);
    console.log("Power:", json.power);
    console.log("PP:", json.pp);
    console.log("Type:", json.type.name);
    console.log("Damage Class:", json.damage_class.name);

    run(); // go back to menu
}
