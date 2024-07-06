let [initialPositions, ...commands] = require("fs")
  .readFileSync(process.platform === "linux" ? "/dev/stdin" : "input.txt")
  .toString()
  .trim()
  .split("\n");

const moveDirections = {
  R: [1, 0],
  L: [-1, 0],
  B: [0, -1],
  T: [0, 1],
  RT: [1, 1],
  LT: [-1, 1],
  RB: [1, -1],
  LB: [-1, -1],
};

const columnLabels = {
  A: 1,
  B: 2,
  C: 3,
  D: 4,
  E: 5,
  F: 6,
  G: 7,
  H: 8,
};


const [kingInitialPos, stoneInitialPos, numCommands] = initialPositions.split(" ");
const finalPositions = [];
let [kingColumn, kingRow] = kingInitialPos.split("");
let [stoneColumn, stoneRow] = stoneInitialPos.split("");
kingRow = Number(kingRow);
stoneRow = Number(stoneRow);

let kingPosition = [columnLabels[kingColumn], kingRow];
let stonePosition = [columnLabels[stoneColumn], stoneRow];

for (let i = 0; i < numCommands; i++) {
  const newKingX = kingPosition[0] + moveDirections[commands[i]][0];
  const newKingY = kingPosition[1] + moveDirections[commands[i]][1];

  if (0 < newKingX && newKingX <= 8 && 0 < newKingY && newKingY <= 8) { 
    if (newKingX === stonePosition[0] && newKingY === stonePosition[1]) { 
      const newStoneX = stonePosition[0] + moveDirections[commands[i]][0];
      const newStoneY = stonePosition[1] + moveDirections[commands[i]][1];
      if (0 < newStoneX && newStoneX <= 8 && 0 < newStoneY && newStoneY <= 8) { 
        kingPosition = [newKingX, newKingY];
        stonePosition = [newStoneX, newStoneY];
      } else {
        continue;
      }
    } else {
      kingPosition = [newKingX, newKingY];
    }
  } else {
    continue;
  }
}

const kingFinalColumn = Object.keys(columnLabels).find((key) => columnLabels[key] === kingPosition[0]);
const stoneFinalColumn = Object.keys(columnLabels).find((key) => columnLabels[key] === stonePosition[0]);
finalPositions.push([kingFinalColumn, kingPosition[1]].join(""));
finalPositions.push([stoneFinalColumn, stonePosition[1]].join(""));
console.log(finalPositions.join("\n"));
