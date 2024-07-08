let 입력개수;
const 입력값 = [];
const 첫자리 = [];

const 해결 = () => {
  const 숫자맵 = new Map();
  입력값.sort((a, b) => b.값 - a.값);

  if (입력값.length === 10) {
    for (let i = 9; i >= 0; i--) {
      const 문자 = 입력값[i].문자;
      if (!첫자리[문자]) {
        숫자맵.set(문자, 0);
        break;
      }
    }
  }

  let 숫자 = 9;
  입력값.forEach(({ 문자 }) => {
    if (!숫자맵.has(문자)) {
      숫자맵.set(문자, 숫자--);
    }
  });

  const 합계 = 입력값.reduce((acc, { 문자, 값 }) => acc + 값 * 숫자맵.get(문자), 0);
  console.log(합계);
};

require('readline')
  .createInterface(process.stdin, process.stdout)
  .on('line', 줄 => {
    if (!입력개수) {
      입력개수 = parseInt(줄);
      return;
    }
    const 길이 = 줄.length;
    줄.split('').forEach((문자, 인덱스) => {
      const 항목 = 입력값.find(({ 문자: 키 }) => 키 === 문자);
      const 값 = Math.pow(10, 길이 - 인덱스 - 1);
      if (!항목) {
        입력값.push({ 문자, 값 });
      } else {
        항목.값 += 값;
      }

      if (인덱스 === 0) {
        첫자리[문자] = true;
      }
    });
  })
  .on('close', () => {
    해결();
    process.exit();
  });
