const fs = require('fs');
const [instructionCount, ...instructions] = fs.readFileSync('/dev/stdin').toString().trim().split('\n');

let machineCodeOutput = '';
for (let i = 0; i < instructions.length; i++) {
    let instructionParts = instructions[i].trim().split(' ');
    machineCodeOutput += getOpcodeBinary(instructionParts[0]);
    if (getOpcodeBinary(instructionParts[0]).charAt(4) === '0') {
        machineCodeOutput += getBinaryString(parseInt(instructionParts[1]), 3);
        machineCodeOutput += getBinaryString(parseInt(instructionParts[2]), 3);
        machineCodeOutput += getBinaryString(parseInt(instructionParts[3]), 3);
        machineCodeOutput += '0';
    } else {
        machineCodeOutput += getBinaryString(parseInt(instructionParts[1]), 3);
        machineCodeOutput += getBinaryString(parseInt(instructionParts[2]), 3);
        machineCodeOutput += getBinaryString(parseInt(instructionParts[3]), 4);
    }
    if (i !== instructions.length - 1) {
        machineCodeOutput += '\n';
    }
}

console.log(machineCodeOutput);

function getOpcodeBinary(opcode) {
    let binaryRepresentation = '';

    if (opcode === 'ADD' || opcode === 'ADDC') {
        binaryRepresentation = '0000';
    } else if (opcode === 'SUB' || opcode === 'SUBC') {
        binaryRepresentation = '0001';
    } else if (opcode === 'MOV' || opcode === 'MOVC') {
        binaryRepresentation = '0010';
    } else if (opcode === 'AND' || opcode === 'ANDC') {
        binaryRepresentation = '0011';
    } else if (opcode === 'OR' || opcode === 'ORC') {
        binaryRepresentation = '0100';
    } else if (opcode === 'NOT') {
        binaryRepresentation = '0101';
    } else if (opcode === 'MULT' || opcode === 'MULTC') {
        binaryRepresentation = '0110';
    } else if (opcode === 'LSFTL' || opcode === 'LSFTLC') {
        binaryRepresentation = '0111';
    } else if (opcode === 'LSFTR' || opcode === 'LSFTRC') {
        binaryRepresentation = '1000';
    } else if (opcode === 'ASFTR' || opcode === 'ASFTRC') {
        binaryRepresentation = '1001';
    } else if (opcode === 'RL' || opcode === 'RLC') {
        binaryRepresentation = '1010';
    } else if (opcode === 'RR' || opcode === 'RRC') {
        binaryRepresentation = '1011';
    }

    if (opcode.charAt(opcode.length - 1) === 'C') {
        binaryRepresentation += '1';
    } else {
        binaryRepresentation += '0';
    }
    return binaryRepresentation + '0';
}

function getBinaryString(number, bitSize) {
    let binaryString = '';

    while (number > 0) {
        binaryString = (number % 2) + binaryString;
        number = Math.floor(number / 2);
    }

    while (binaryString.length < bitSize) {
        binaryString = '0' + binaryString;
    }

    return binaryString;
}
