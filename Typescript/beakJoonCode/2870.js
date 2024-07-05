const fs = require('fs');
const input = fs.readFileSync('/dev/stdin').toString().trim().split('\n');

const numberOfCases = Number(input[0]);
let numberList = [];

for (let i = 1; i <= numberOfCases; i++) {
    let currentNumber = '';
    for (let character of input[i]) {
        if (!isNaN(character)) {
            currentNumber += character;
        } else if (isNaN(character)) {
            if (currentNumber.length > 0) {
                numberList.push(BigInt(currentNumber));
            }
            currentNumber = '';
        }
    }
    if (currentNumber.length > 0) {
        numberList.push(BigInt(currentNumber));
    }
}

numberList.sort((a, b) => (a < b) ? -1 : ((a > b) ? 1 : 0));
console.log(numberList.join('\n').trim());
