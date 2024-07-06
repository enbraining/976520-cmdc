const fs = require("fs");
const input = fs.readFileSync("/dev/stdin").toString().trim().split(/\s/);
const numOfStrings = +input[0];
const numOfBrands = +input[1];
const prices = input.slice(2).map(value => +value);
const packagePrices = [];
const piecePrices = [];

for (let i = 0; i < numOfBrands; i++) {
    packagePrices.push(prices[2 * i]);
    piecePrices.push(prices[2 * i + 1]);
}

const minPackagePrice = packagePrices.reduce((min, price) => min < price ? min : price, 1000);
const minPiecePrice = piecePrices.reduce((min, price) => min < price ? min : price, 1000);
const numOfPackages = Math.floor(numOfStrings / 6);
const numOfPieces = numOfStrings - 6 * numOfPackages;
let minimumCost;

if (minPackagePrice / 6 < minPiecePrice) {
    minimumCost = numOfPackages * minPackagePrice + (numOfPieces * minPiecePrice < minPackagePrice ? numOfPieces * minPiecePrice : minPackagePrice);
} else {
    minimumCost = numOfStrings * minPiecePrice;
}

console.log(minimumCost);
