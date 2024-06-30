const fs = require("fs");

const 입력_숫자: number = Number(fs.readFileSync('/dev/stdin').toString());

const 배열: number[] = [];
let 결과: number[] = [];

for(let i=1; i<=입력_숫자; i++) {
    if(i%2 === 0) 배열.push(i);
    else 배열.splice(0, 0, i);
}

let 현재_인덱스: number = 배열.indexOf(1);
for(let i=1; i<=입력_숫자; i++) {
    결과.push(현재_인덱스+1);
    현재_인덱스 += i%2 === 0 ? -배열[현재_인덱스] : 배열[현재_인덱스];
}

console.log("YES");
console.log(배열.join(' '));
console.log(결과.join(' '));
