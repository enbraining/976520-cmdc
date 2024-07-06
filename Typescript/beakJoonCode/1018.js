const fileSystem = require('fs');
let inputLines = fileSystem.readFileSync('/dev/stdin').toString().split('\n');

let boardDimensions = inputLines.shift().split(' ');
let numberOfRows = Number(boardDimensions.shift());
let numberOfColumns = Number(boardDimensions.shift());
let whitePattern = ['WBWBWBWB', 'BWBWBWBW', 'WBWBWBWB', 'BWBWBWBW', 'WBWBWBWB', 'BWBWBWBW', 'WBWBWBWB', 'BWBWBWBW'];
let blackPattern = ['BWBWBWBW', 'WBWBWBWB', 'BWBWBWBW', 'WBWBWBWB', 'BWBWBWBW', 'WBWBWBWB', 'BWBWBWBW', 'WBWBWBWB'];

let chessBoard = [];
for (let rowIndex = 0; rowIndex < numberOfRows; rowIndex++) {
  chessBoard[rowIndex] = inputLines.shift().split('');
}

let minimumRepaintsRequired = 90;

for (let startRow = 0; startRow <= numberOfRows - 8; startRow++) {
  for (let startColumn = 0; startColumn <= numberOfColumns - 8; startColumn++) {
    calculateRepaints(startColumn, startRow);
  }
}

function calculateRepaints(startColumn, startRow) {
  let repaintsForWhitePattern = 0;
  let repaintsForBlackPattern = 0;

  for (let rowIndex = startRow; rowIndex < startRow + 8; rowIndex++) {
    for (let columnIndex = startColumn; columnIndex < startColumn + 8; columnIndex++) {
      if (chessBoard[rowIndex][columnIndex] !== whitePattern[rowIndex - startRow][columnIndex - startColumn]) {
        repaintsForWhitePattern++;
      }
      if (chessBoard[rowIndex][columnIndex] !== blackPattern[rowIndex - startRow][columnIndex - startColumn]) {
        repaintsForBlackPattern++;
      }
    }
  }

  let minimumRepaintsForCurrentSection = Math.min(repaintsForWhitePattern, repaintsForBlackPattern);

  if (minimumRepaintsForCurrentSection < minimumRepaintsRequired) {
    minimumRepaintsRequired = minimumRepaintsForCurrentSection;
  }
}

console.log(minimumRepaintsRequired);
