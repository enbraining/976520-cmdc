const fs = require('fs');
const inputLines = fs.readFileSync('/dev/stdin').toString().split('\n').map(Number);
const caseCount = inputLines[0];
const numberStack = [];

for (let i = 1; i <= caseCount; i++) {
    const value = inputLines[i];

    if (value === 0) {
        numberStack.pop();
    } else {
        numberStack.push(value);
    }
}
console.log(numberStack.reduce((acc, cur) => acc + cur, 0));
