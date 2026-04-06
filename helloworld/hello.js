"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var readline = require("readline");
var rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});
rl.question('Enter your name: ', function (name) {
    console.log("Hello, ".concat(name, "!"));
    rl.close();
});
