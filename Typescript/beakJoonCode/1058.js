const fs = require('fs');
const filePath = '/dev/stdin';
const input = fs.readFileSync(filePath).toString().trim().split('\n');

const numberOfPeople = Number(input.shift());
let friendsMatrix = input.map(str => str.split(''));

let maxTwoFriendsCount = 0;

friendsMatrix.forEach((personFriends, personIndex) => {
    const tempTwoFriends = new Set();

    personFriends.forEach((friendshipStatus, friendIndex) => {
        if (friendshipStatus === 'Y') {
            tempTwoFriends.add(friendIndex);

            friendsMatrix[friendIndex].forEach((secondLevelFriendship, secondLevelIndex) => {
                if (secondLevelFriendship === 'Y' && secondLevelIndex !== personIndex) {
                    tempTwoFriends.add(secondLevelIndex);
                }
            });
        }
    });

    tempTwoFriends.delete(personIndex);

    const currentTwoFriendsCount = tempTwoFriends.size;
    if (currentTwoFriendsCount > maxTwoFriendsCount) {
        maxTwoFriendsCount = currentTwoFriendsCount;
    }
});

console.log(maxTwoFriendsCount);
