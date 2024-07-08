const fs = require('fs');
const filePath = process.platform === 'linux' ? '/dev/stdin' : './input.txt';
const input = fs.readFileSync(filePath).toString().trim().split('').sort();

function findPalindromeOrPermutation(input) {
    const head = [];
    const body = [];
    
    while (input.length > 0) {
        const first = input.shift();
        const idx = input.indexOf(first);
        
        if (idx === -1) {
            body.push(first);
        } else {
            head.push(first);
            input.splice(idx, 1);
        }
    }
    
    const tail = [...head].reverse().join('');
    
    if (body.length > 1) {
        console.log("I'm Sorry Hansoo");
    } else {
        console.log(head.join('') + body.join('') + tail);
    }
}

findPalindromeOrPermutation(input);
