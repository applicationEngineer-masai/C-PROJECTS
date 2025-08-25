const readline = require("readline");

let array = [];

let string = "PUSH 1:\nPOP 2:\nSHIFT 3:\nUNSHIFT 4:\nSPLICE 5 <value>:\nPRINT 6:\nEXIT:\n> ";

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function processInput(input) {
    input = input.trim();
    let parts = input.split(" ");
    let main = parts[0].toLowerCase();
    let arg1 = parts[1];
    let arg2 = parts[2];

    if (main === "push") {
        array.push(Number(arg1));
        console.log("------------------------------");

    } else if (main === "pop") {
        array.pop();
        console.log("------------------------------");

    } else if (main === "print") {
        console.log("===============================");
        console.log(array);
        console.log("===============================");

    } else if (main === "shift") {
        array.shift();
        console.log("------------------------------");

    } else if (main === "unshift") {
        array.unshift(Number(arg1));
        console.log("------------------------------");

    } else if (main === "splice") {
        if (!isNaN(arg1) && arg2 !== undefined) {
            array.splice(Number(arg1), 1, Number(arg2));
        }
        console.log("------------------------------");

    } else if (main === "exit") {
        rl.close();
        return;

    } else {
        console.log("Unknown command:", main);
    }

    rl.question(string, processInput);
}

rl.question(string, processInput);
