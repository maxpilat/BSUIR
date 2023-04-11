import operationPriority from "./operationsPriority.js";

export function generateTruthTableVariables(variablesCount) {
  const truthTableVariables = [];
  for (let i = 0; i < 2 ** variablesCount; i++) {
    truthTableVariables.push(
      Array.from(
        { length: variablesCount },
        (_, j) => Math.floor(i / 2 ** (variablesCount - 1 - j)) % 2
      )
    );
  }
  return truthTableVariables;
}

export function getVariableMap(variables, sets) {
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

export function calc(sign, a, b) {
  if (typeof a === "string" || typeof b === "string") {
    let operand_1 = a;
    let operand_2 = b;
    if (typeof a === "string" && typeof b === "string") {
      if (a === b) return a;
      else {
        if (operand_2.includes("!")) {
          [operand_1, operand_2] = [operand_2, operand_1];
        }
        if (sign === "*") return 0;
        else if (sign === "+") return 1;
      }
    } else {
      if (typeof a !== "number" && typeof a !== "boolean" && b !== undefined) {
        [operand_1, operand_2] = [operand_2, operand_1];
      }
      if (sign === "*") {
        if (operand_1) return operand_2;
        return 0;
      } else if (sign === "+") {
        if (operand_1) return 1;
        return operand_2;
      } else if (sign === "!") {
        return "!" + operand_1;
      }
    }
  } else {
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
}

export function readFunc(func, set) {
  const operationStack = [];
  const variablesStack = [];

  for (let l of func) {
    if (l !== " ") {
      if (operationPriority.has(l)) {
        if (l === ")") {
          if (operationStack.at(-1) === "(") {
            operationStack.pop();
            if (operationStack.length !== 0) {
              if (operationStack.at(-1) === "!") {
                variablesStack.push(
                  calc(operationStack.pop(), variablesStack.pop())
                );
              } else if (operationStack.at(-1) !== "(") {
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
          } else if (operationStack.at(-1) !== "(" && ")") {
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
            operationStack.pop();
          }
        } else operationStack.push(l);
      } else {
        if (set.has(l)) variablesStack.push(set.get(l));
        else return console.log("undefined variable");
        if (
          operationStack.length !== 0 &&
          operationStack.at(-1) !== "(" &&
          ")"
        ) {
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
    variablesStack.push(
      calc(operationStack.pop(), variablesStack.at(-1), variablesStack.at(-2))
    );
  }
  return variablesStack.pop();
}

export function indexForm(sets) {
  let result = [];
  sets.forEach((set) => {
    result.push(set.at(-1));
  });
  if (!result.includes(1)) return 0;
  result.forEach((elem, index, arr) => {
    arr[index] = elem * Math.pow(2, arr.length - 1 - index);
  });
  return result.reduce((sum, elem) => sum + elem);
}

export function getSDNF(varMap, sets) {
  const indexes = [];
  sets.forEach((item, index) => {
    if (item.at(-1) == 1) indexes.push(index);
  });
  if (indexes.length === 0)
    return {
      result: "-",
      numForm: "-",
      indexForm: "-",
    };
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
  return {
    result: result.slice(0, -1),
    numForm: `+(${indexes.map((index) => `${index}, `)}`.slice(0, -2) + ")",
    indexForm: indexForm(sets),
  };
}

export function getSKNF(varMap, sets) {
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
  return {
    result: result.slice(0, -1),
    numForm: `*(${indexes.map((index) => `${index}, `)}`.slice(0, -2) + ")",
    indexForm: indexForm(sets),
  };
}
