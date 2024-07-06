const findExtremeNumbers = (inputLines) => {
  const N = +inputLines[0];
  const inequalitySigns = inputLines[1].split(" ");
  const visit = new Array(10).fill(0);
  let maxResult = String(Number.MIN_SAFE_INTEGER);
  let minResult = String(Number.MAX_SAFE_INTEGER);

  function dfs(L, prev, result) {
    if (L === N) {
      maxResult = result > maxResult ? result : maxResult;
      minResult = result < minResult ? result : minResult;
      return;
    }
    if (inequalitySigns[L] === "<") {
      for (let i = prev + 1; i < 10; i++) {
        if (visit[i]) continue;
        visit[i] = 1;
        dfs(L + 1, i, result + i);
        visit[i] = 0;
      }
    } else {
      for (let i = prev - 1; i > -1; i--) {
        if (visit[i]) continue;
        visit[i] = 1;
        dfs(L + 1, i, result + i);
        visit[i] = 0;
      }
    }
    return;
  }

  for (let i = 0; i < 10; i++) {
    visit[i] = 1;
    dfs(0, i, `${i}`);
    visit[i] = 0;
  }

  return `${maxResult}\n${minResult}`;
};

const input = [];
require("readline")
  .createInterface(process.stdin, process.stdout)
  .on("line", (line) => {
    input.push(line);
  })
  .on("close", () => {
    console.log(findExtremeNumbers(input));
    process.exit();
  });
