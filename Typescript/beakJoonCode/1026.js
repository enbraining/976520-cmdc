const fileSystemModule = require('fs');
let inputDataLinesFromFile = fileSystemModule.readFileSync('dev/stdin').toString().trim().split('\n');
inputDataLinesFromFile.shift(); // 첫 줄 제거
let numericInputArrays = inputDataLinesFromFile.map((line) => line.split(' ').map(Number));

// 첫 번째 배열 오름차순
let sortedFirstNumericArray = numericInputArrays[0].sort((firstElement, secondElement) => firstElement - secondElement);

// 두 번째 배열 내림차순
let sortedSecondNumericArray = numericInputArrays[1].sort((firstElement, secondElement) => secondElement - firstElement);

let accumulatedSumOfProducts = 0;

// 첫 번째 배열의 각 요소를 필터링 -> 두 번째 배열의 대응 요소와 곱하여 누적 합 계산
sortedFirstNumericArray.filter((currentElement, currentIndex) => {
  accumulatedSumOfProducts += currentElement * sortedSecondNumericArray[currentIndex];
});

console.log(accumulatedSumOfProducts);
