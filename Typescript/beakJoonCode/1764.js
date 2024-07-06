const fileSystem = require("fs");
const input = fileSystem.readFileSync("/dev/stdin").toString().split("\n");

const [numberOfElementsInSetN, numberOfElementsInSetM] = input.shift().split(" ").map(Number);
const setContainingElementsOfN = new Set();
const setContainingElementsOfM = new Set();
const commonElements = [];

input.forEach((element, index) => {
  if (index < numberOfElementsInSetN) {
    setContainingElementsOfN.add(element);
  } else {
    setContainingElementsOfM.add(element);
  }
});

setContainingElementsOfN.forEach((element) => {
  if (setContainingElementsOfM.has(element)) {
    commonElements.push(element);
  }
});

commonElements.sort();
console.log(commonElements.length + "\n" + commonElements.join("\n"));
