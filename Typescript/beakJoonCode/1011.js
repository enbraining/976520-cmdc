let fileSystemModule = require('fs');
let inputFileData = fileSystemModule.readFileSync('/dev/stdin').toString().split('\n');

let numberOfTestCases = Number(inputFileData[0]);
let startingPoint;
let endingPoint;
let firstThreshold;
let secondThreshold;

let resultsArray = [];
for (let testCaseIndex = 1; testCaseIndex <= numberOfTestCases; testCaseIndex++) {
  let currentTestCaseData = inputFileData[testCaseIndex].split(" ");
  startingPoint = Number(currentTestCaseData[0]);
  endingPoint = Number(currentTestCaseData[1]);
  let distanceToTravel = endingPoint - startingPoint;

  if (Math.sqrt(distanceToTravel) % 1 === 0) {
    resultsArray.push(2 * Math.sqrt(distanceToTravel) - 1);
  } else {
    firstThreshold = Math.pow(Math.ceil(Math.sqrt(distanceToTravel)), 2);
    secondThreshold = Math.pow(Math.ceil(Math.sqrt(distanceToTravel)) - 1, 2) + 1;

    if ((firstThreshold + secondThreshold) / 2 <= distanceToTravel) {
      resultsArray.push(2 * Math.ceil(Math.sqrt(distanceToTravel)) - 1);
    } else {
      resultsArray.push(2 * Math.ceil(Math.sqrt(distanceToTravel)) - 2);
    }
  }
  console.log(resultsArray[resultsArray.length - 1]);
}
