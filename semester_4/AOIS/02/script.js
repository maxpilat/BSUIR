const operationStack = [];
const variablesStack = [];

const operationPriority = new Map();
operationPriority.set("*", 4); //and
operationPriority.set("+", 3); //or
operationPriority.set("!", 5); //not
operationPriority.set(">", 2); //->
operationPriority.set("=", 1); //~
operationPriority.set("(", 0);
operationPriority.set(")", 0);

function run() {
  const func = "((!A)+B)*((!A)*(C))";
  const variables = [...new Set(func.match(/[a-z]+/gi))];
  const sets = generateTruthTableVariables(variables.length);
  const varMap = getVariableMap(variables, sets);

  varMap.forEach((map, index) => {
    sets[index].push(readFunc(func, map));
  });

  const sknf_ = sknf(varMap, sets);
  const sdnf_ = sdnf(varMap, sets);
  const indexForm_ = indexForm(sets);

  console.log(sets);
  console.log(sknf_);
  console.log(sdnf_);
  console.log(indexForm_);
}
run();

function generateTruthTableVariables(n) {
  const truthTableVariables = [];
  for (let i = 0; i < 2 ** n; i++) {
    truthTableVariables.push(
      Array.from({ length: n }, (_, j) => Math.floor(i / 2 ** (n - 1 - j)) % 2)
    );
  }
  return truthTableVariables;
}

function getVariableMap(variables, sets) {
  const varMap = [];
  sets.forEach((set) => {
    let varObj = new Map();
    variables.forEach((variable, index) => {
      varObj.set(variable, set[index]);
    });
    varMap.push(varObj);
  });
  return varMap;
}

function calc(sign, a, b) {
  if (sign === "*") {
    if (a && b) return 1;
    return 0;
  } else if (sign === "+") {
    if (!a && !b) return 0;
    return 1;
  } else if (sign === "!") {
    return !a;
  } else if (sign === ">") {
    if (a && !b) return 0;
    return 1;
  } else if (sign === "=") {
    if (a == b) return 1;
    return 0;
  }
}

function readFunc(func, set) {
  for (let l of func) {
    if (l !== " ") {
      if (operationPriority.has(l)) {
        if (l === ")") {
          operationStack.pop();
          if (operationStack.at(-1) !== "(" && ")") {
            if (operationStack.at(-1) === "!") {
              variablesStack.push(
                calc(operationStack.pop(), variablesStack.pop())
              );
            } else if (operationStack.length !== 0) {
              variablesStack.splice(
                -2,
                2,
                calc(
                  operationStack.pop(),
                  variablesStack.at(-1),
                  variablesStack.at(-2)
                )
              );
            }
          }
        } else operationStack.push(l);
      } else {
        if (set.has(l)) variablesStack.push(set.get(l));
        else return console.log("undefined variable");
        if (operationStack.at(-1) !== "(" && ")") {
          if (operationStack.at(-1) === "!") {
            variablesStack.push(
              calc(operationStack.pop(), variablesStack.pop())
            );
          } else {
            variablesStack.splice(
              -2,
              2,
              calc(
                operationStack.pop(),
                variablesStack.at(-1),
                variablesStack.at(-2)
              )
            );
          }
        }
      }
    }
  }
  if (operationStack.length != 0) {
    variablesStack.push(calc(operationStack.pop(), variablesStack.pop()));
  }
  return variablesStack.pop();
}

function sknf(varMap, sets) {
  const indexes = [];
  sets.forEach((item, index) => {
    if (item.at(-1) == 0) indexes.push(index);
  });
  let result = "";
  indexes.forEach((index) => {
    result += "(";
    for (let key of varMap[index].keys()) {
      if (varMap[index].get(key) == 1) result += `!${key}`;
      else result += key;
      result += "+";
    }
    result = result.slice(0, -1);
    result += ")*";
  });
  result = result.slice(0, -1) + ` = *(${indexes.map((index) => `${index}, `)}`;
  return result.slice(0, -2) + ")";
}

function sdnf(varMap, sets) {
  const indexes = [];
  sets.forEach((item, index) => {
    if (item.at(-1) == 1) indexes.push(index);
  });
  let result = "";
  indexes.forEach((index) => {
    result += "(";
    for (let key of varMap[index].keys()) {
      if (varMap[index].get(key) == 0) result += `!${key}`;
      else result += key;
      result += "*";
    }
    result = result.slice(0, -1);
    result += ")+";
  });
  result = result.slice(0, -1) + ` = +(${indexes.map((index) => `${index}, `)}`;
  return result.slice(0, -2) + ")";
}

function indexForm(sets) {
  let result = [];
  sets.forEach((set) => {
    result.push(set.at(-1));
  });
  if (!result.includes(1)) result = 0;
  result.forEach((elem, index, arr) => {
    arr[index] = elem * Math.pow(2, arr.length - 1 - index);
  });
  result = result.reduce((sum, elem) => sum + elem);

  return result;
}
