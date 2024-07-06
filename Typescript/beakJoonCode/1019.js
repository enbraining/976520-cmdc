const fileSystem = require('fs');
const inputNumbers = fileSystem.readFileSync('/dev/stdin').toString().split(' ');
const upperBound = +inputNumbers[0];
const digitCountArray = Array.from({length: 10}, () => 0);

const calculateDigitOccurrences = (start, end, digitMultiplier) => {
  const digitCount = Math.floor(end / 10) - Math.floor(start / 10) + 1;
  digitCountArray.forEach((_, index) => {
    digitCountArray[index] += digitCount * digitMultiplier;
  });
};

const incrementDigitCounts = (number, digitMultiplier) => {
  while (number > 0) {
    digitCountArray[number % 10] += digitMultiplier;
    number = Math.floor(number / 10);
  }
};

const computeDigitFrequencies = (start, end, digitMultiplier) => {
  while (start % 10 !== 0 && start <= end) {
    incrementDigitCounts(start, digitMultiplier);
    start += 1;
  }

  if (start > end) {
    return;
  }

  while (end % 10 !== 9 && end >= start) {
    incrementDigitCounts(end, digitMultiplier);
    end -= 1;
  }

  calculateDigitOccurrences(start, end, digitMultiplier);
  computeDigitFrequencies(Math.floor(start / 10), Math.floor(end / 10), digitMultiplier * 10);
};

computeDigitFrequencies(1, upperBound, 1);
let digitCountString = "";
for (let count of digitCountArray) {
  digitCountString += count + " ";
}
console.log(digitCountString.trim());
