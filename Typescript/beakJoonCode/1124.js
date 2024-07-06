const readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function isPrime(num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 === 0 || num % 3 === 0) return false;
    let i = 5;
    while (i * i <= num) {
        if (num % i === 0 || num % (i + 2) === 0) return false;
        i += 6;
    }
    return true;
}

function countPrimeFactors(num) {
    let count = 0;
    for (let i = 2; i * i <= num; i++) {
        while (num % i === 0) {
            if (isPrime(i)) {
                count++;
            }
            num /= i;
        }
    }
    if (num > 1 && isPrime(num)) {
        count++;
    }
    return count;
}

rl.on('line', (input) => {
    const [A, B] = input.split(' ').map(Number);
    
    let underPrimeCount = 0;
    
    for (let x = A; x <= B; x++) {
        let primeFactorCount = countPrimeFactors(x);
        if (isPrime(primeFactorCount)) {
            underPrimeCount++;
        }
    }
    
    console.log(underPrimeCount);
    rl.close();
});
