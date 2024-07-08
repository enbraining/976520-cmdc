const fs = require("fs");
let inputLines = fs.readFileSync("/dev/stdin").toString().split("\n");

const totalLines = inputLines.length;
let results = [];

for (let i = 0; i < totalLines; i++) {
    let lineCharacters = inputLines[i].split("");

    if (lineCharacters.length === 0) { 
        continue; 
    }

    let characterCounts = [0, 0, 0, 0];

    for (let char of lineCharacters) {
        let asciiValue = char.charCodeAt();

        if (asciiValue >= 97 && asciiValue <= 122) {
            characterCounts[0]++;
        } else if (asciiValue >= 65 && asciiValue <= 90) {
            characterCounts[1]++;
        } else if (asciiValue >= 48 && asciiValue <= 57) {
            characterCounts[2]++;
        } else if (asciiValue === 32) {
            characterCounts[3]++;
        }
    }

    results.push(characterCounts.join(" "));
}

console.log(results.join("\n"));
