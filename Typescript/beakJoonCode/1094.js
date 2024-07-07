const fs = require('fs');
const input = fs.readFileSync("./dev/stdin").toString().trim();

const countOnesInBinary = (input) => {
  let number = +input;
  let oneCount = 0;

  while (number > 0) {
    if (number & 1) {
      oneCount++;
    }
    number >>= 1;
  }
  console.log(oneCount);
}

countOnesInBinary(input);
