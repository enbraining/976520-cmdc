var fileSystem = require("fs");

const inputLines = fileSystem.readFileSync('/dev/stdin').toString().split('\n');

const numberOfTestCases = inputLines[0];

let stateTransitionTable = [
    [2, 1],
    [3, 8],
    [8, 7],
    [4, 8],
    [4, 5],
    [2, 6],
    [9, 6],
    [2, 1],
    [8, 8],
    [4, 7]
];

function doesStringMatchPattern(binaryString) {
    let currentState = 0;
    for (let character of binaryString) {
        if (character === "0") {
            currentState = stateTransitionTable[currentState][0];
        } else if (character === "1") {
            currentState = stateTransitionTable[currentState][1];
        }
    }

    if (currentState === 5 || currentState === 6 || currentState === 7) return true;
    return false;
}

for (let currentTestCaseIndex = 1; currentTestCaseIndex <= numberOfTestCases; currentTestCaseIndex++) {
    if (doesStringMatchPattern(inputLines[currentTestCaseIndex])) {
        console.log("YES");
    } else {
        console.log("NO");
    }
}
