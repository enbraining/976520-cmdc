const fs = require("fs");
const filePath = process.platform === "linux" ? "/dev/stdin" : "input.txt";
let input = fs.readFileSync(filePath).toString().trim().split("\n");

let [initialX, initialY] = input[0].split(" ").map(Number);
let initialRatio = Math.floor((100 * initialY / initialX));

let left = 1;
let right = 1000000000;
let minimumAdditionalX = Infinity;

while (left <= right) {
  let mid = parseInt((left + right) / 2);
  let newRatio = Math.floor((100 * (initialY + mid) / (initialX + mid)));
  
  if (initialRatio !== newRatio) {
    minimumAdditionalX = Math.min(minimumAdditionalX, mid);
    right = mid - 1;
  } else {
    left = mid + 1;
  }
}

if (minimumAdditionalX === Infinity) {
  console.log(-1);
} else {
  console.log(minimumAdditionalX);
}
