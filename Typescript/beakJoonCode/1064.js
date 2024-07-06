const readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

class Pair {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
}

function solve() {
    let arr = [];
    let min = Infinity;
    let max = -Infinity;
    let leng = new Array(3);

    rl.on('line', (input) => {
        let tokens = input.split(' ').map(Number);
        for (let i = 0; i < 3; i++) {
            arr.push(new Pair(tokens[2*i], tokens[2*i+1]));
        }

        if ((arr[1].y - arr[0].y) * (arr[2].x - arr[1].x) === (arr[1].x - arr[0].x) * (arr[2].y - arr[1].y)) {
            console.log("-1");
        } else {
            let one = Math.sqrt(Math.pow(arr[1].y - arr[0].y, 2) + Math.pow(arr[1].x - arr[0].x, 2));
            let two = Math.sqrt(Math.pow(arr[2].y - arr[0].y, 2) + Math.pow(arr[2].x - arr[0].x, 2));
            let three = Math.sqrt(Math.pow(arr[2].y - arr[1].y, 2) + Math.pow(arr[2].x - arr[1].x, 2));
            leng[0] = one + two;
            leng[1] = two + three;
            leng[2] = one + three;

            for (let i = 0; i < 3; i++) {
                if (min > leng[i]) {
                    min = leng[i];
                }
                if (max < leng[i]) {
                    max = leng[i];
                }
            }

            console.log(2 * max - 2 * min);
        }

        rl.close();
    });
}

solve();
