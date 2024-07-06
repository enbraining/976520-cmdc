const fs = require("fs");
const filePath = process.platform === "linux" ? "/dev/stdin" : "./input.txt";
let inputLines = fs.readFileSync(filePath).toString().trim().split("\n");

const [numRows, numCols] = inputLines
    .shift()
    .split(" ")
    .map((item) => +item);

let maxSquareSize = 1;
let startValue = 0;
let currentWidth = 0;

for (let row = 0; row < numRows; row++) {
    for (let col = 0; col < numCols; col++) {
        startValue = +inputLines[row][col]; // 시작점 설정

        for (let nextCol = col + 1; nextCol < numCols; nextCol++) {
            if (+inputLines[row][nextCol] === startValue) { // 같은걸 찾으면
                currentWidth = nextCol - col + 1; // 너비 계산

                if (
                    row + currentWidth - 1 < numRows && // 세로 길이가 numRows보다 작고
                    startValue === +inputLines[row + currentWidth - 1][col] && // 시작점과 왼쪽 아래의 값이 같고
                    inputLines[row + currentWidth - 1][col] === inputLines[row + currentWidth - 1][nextCol] && // 왼쪽 아래와 오른쪽 위의 값이 같고
                    currentWidth * currentWidth > maxSquareSize // 넓이가 현재 최대 넓이보다 크면
                ) {
                    maxSquareSize = currentWidth * currentWidth; // 업데이트
                }
            }
        }
    }
}

console.log(maxSquareSize);
