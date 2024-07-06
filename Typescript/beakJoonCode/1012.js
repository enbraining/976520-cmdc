const fileSystemModule = require("fs");
const inputData = fileSystemModule.readFileSync("/dev/stdin").toString().trim().split("\n");
const numberOfTestCases = Number(inputData.shift());
const directionOffsets = [
  [-1, 0],
  [1, 0],
  [0, 1],
  [0, -1],
];

function breadthFirstSearch(startingXCoordinate, startingYCoordinate) {
  const searchQueue = [[startingXCoordinate, startingYCoordinate]];

  while (searchQueue.length) {
    const [currentXCoordinate, currentYCoordinate] = searchQueue.shift();

    if (!farmMap[currentXCoordinate][currentYCoordinate]) continue;
    else farmMap[currentXCoordinate][currentYCoordinate] = 0;

    for (let directionIndex = 0; directionIndex < 4; directionIndex++) {
      const adjacentXCoordinate = currentXCoordinate + directionOffsets[directionIndex][0];
      const adjacentYCoordinate = currentYCoordinate + directionOffsets[directionIndex][1];

      if (adjacentXCoordinate < 0 || adjacentYCoordinate < 0 || adjacentXCoordinate >= numberOfRows || adjacentYCoordinate >= numberOfColumns) continue;
      if (farmMap[adjacentXCoordinate][adjacentYCoordinate]) searchQueue.push([adjacentXCoordinate, adjacentYCoordinate]);
    }
  }
}

for (let testCaseIndex = 0; testCaseIndex < numberOfTestCases; testCaseIndex++) {
  let numberOfWormsRequired = 0;
  var [numberOfRows, numberOfColumns, numberOfCabbages] = inputData.shift().split(" ").map(Number);
  var farmMap = Array.from(Array(numberOfRows), () => new Array(numberOfColumns).fill(0));

  for (let cabbageIndex = 0; cabbageIndex < numberOfCabbages; cabbageIndex++) {
    let [cabbageXCoordinate, cabbageYCoordinate] = inputData.shift().split(" ").map(Number);
    farmMap[cabbageXCoordinate][cabbageYCoordinate] = 1;
  }

  for (let rowIndex = 0; rowIndex < numberOfRows; rowIndex++) {
    for (let columnIndex = 0; columnIndex < numberOfColumns; columnIndex++) {
      if (farmMap[rowIndex][columnIndex]) {
        breadthFirstSearch(rowIndex, columnIndex);
        numberOfWormsRequired++;
      }
    }
  }
  console.log(numberOfWormsRequired);
}
