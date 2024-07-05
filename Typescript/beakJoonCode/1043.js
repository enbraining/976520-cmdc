const fs = require("fs");
const input = fs.readFileSync("dev/stdin").toString().trim().split("\n");

const [numberOfPeople, numberOfGroups] = input[0].split(" ").map((element) => +element);
const initialTruth = input[1].split(" ").map((element) => +element);
if (initialTruth[0] === 0) {
  console.log(numberOfGroups);
  return;
}

const startingNodes = initialTruth.slice(1);

let knowingPeopleSet = new Set(initialTruth.slice(1));
let countUntruthfulGroups = 0;

const graph = Array.from(Array(numberOfPeople + 1), () => Array(numberOfPeople + 1).fill(0));

for (let i = 2; i < input.length; i++) {
  const participantInfo = input[i].split(" ").map((element) => +element);
  if (participantInfo[0] === 0) continue;
  const participants = participantInfo.slice(1);
  connectParticipants(participants);
}

collectKnowingPeople();

for (let i = 2; i < input.length; i++) {
  const participantInfo = input[i].split(" ").map((element) => +element);
  if (participantInfo[0] === 0) {
    countUntruthfulGroups++;
    continue;
  }
  const participants = participantInfo.slice(1);
  if (!containsKnowingPeople(participants)) countUntruthfulGroups++;
}

console.log(countUntruthfulGroups);

function containsKnowingPeople(participants) {
  const knownParticipants = participants.filter((element) => knowingPeopleSet.has(element));
  return knownParticipants.length > 0;
}

function connectParticipants(participants) {
  for (let i = 0; i < participants.length - 1; i++) {
    const startNode = participants[i];
    for (let j = i + 1; j < participants.length; j++) {
      const endNode = participants[j];
      graph[startNode][endNode] = 1;
      graph[endNode][startNode] = 1;
    }
  }
}

function collectKnowingPeople() {
  const visitedNodes = Array(numberOfPeople + 1).fill(false);
  const stack = [];
  stack.push(...startingNodes);
  startingNodes.forEach((node) => (visitedNodes[node] = true));
  while (stack.length) {
    const currentNode = stack.pop();
    for (let i = 0; i < graph[currentNode].length; i++) {
      if (graph[currentNode][i] && !visitedNodes[i]) {
        stack.push(i);
        knowingPeopleSet.add(i);
        visitedNodes[i] = true;
      }
    }
  }
}
