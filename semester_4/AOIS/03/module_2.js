import {
  generateTruthTableVariables,
  getVariableMap,
  readFunc,
} from "./module_1.js";

export function getConstituents(snf) {
  const constituents = [];
  let constituent = "";
  snf.split("").forEach((item) => {
    if (item !== "(") {
      if (item === ")") {
        constituents.push(constituent);
        constituent = "";
      } else constituent += item;
    } else constituent = "";
  });
  return constituents;
}

export function getImplicants(variables, snf) {
  const implicants = [];
  const constituents = getConstituents(snf);

  constituents.forEach((constituent, index) => {
    constituent.split("").forEach((item, varIndex, arr) => {
      if (variables.includes(item)) {
        let variable = item;
        if (arr[varIndex - 1] === "!") variable = "!" + variable;
        constituents.forEach((constituent_2, index_2) => {
          if (index_2 !== index && !constituent_2.includes(variable)) {
            let str_1, str_2;
            let pair = [constituent, constituent_2];
            if (variable.includes("!") && constituent_2.includes(variable)) {
              pair.reverse();
            }
            str_1 =
              pair[0].substring(0, constituent.indexOf(variable)) +
              pair[0].substring(constituent.indexOf(variable) + 2);
            str_2 =
              pair[1].substring(0, constituent_2.indexOf(variable[1])) +
              pair[1].substring(constituent_2.indexOf(variable[1]) + 1);
            if (str_1 === str_2) {
              if (str_1.includes("++") || str_1.includes("**")) {
                let prev;
                for (let l of str_1) {
                  if (l === prev) {
                    str_1 =
                      str_1.substring(0, str_1.indexOf(prev + l)) +
                      str_1.substring(str_1.indexOf(prev + l) + 1);
                    break;
                  }
                  prev = l;
                }
              } else if (str_1[0] === "+" || str_1[0] === "*") {
                str_1 = str_1.substring(1);
              } else if (
                str_1[str_1.length - 1] === "+" ||
                str_1[str_1.length - 1] === "*"
              ) {
                str_1 = str_1.slice(0, -1);
              }
              implicants.push(str_1);
            }
          }
        });
      }
    });
  });
  return implicants;
}

export function calcMethod(variables, implicants, funcType) {
  const meanImplicants = [...implicants];
  const sets = generateTruthTableVariables(variables.length);
  const varMap = getVariableMap(variables, sets);
  implicants.forEach((curImplicant) => {
    for (let item of varMap) {
      const map = new Map([...item]);
      if (
        (funcType === "sdnf" && readFunc(curImplicant, map)) ||
        (funcType === "sknf" && !readFunc(curImplicant, map))
      ) {
        let vars = [...new Set(curImplicant.match(/[a-z]+/gi))];
        for (const key of map.keys()) {
          if (!vars.includes(key)) {
            map.set(key, key);
            break;
          }
        }
        let otherImplicants = implicants
          .slice(0, implicants.indexOf(curImplicant))
          .concat(implicants.slice(implicants.indexOf(curImplicant) + 1));
        let wholeImplicant = "";
        if (funcType === "sdnf") {
          otherImplicants.forEach((implicant) => {
            wholeImplicant += `(${implicant})+`;
          });
        } else if (funcType === "sknf") {
          otherImplicants.forEach((implicant) => {
            wholeImplicant += `(${implicant})*`;
          });
        }
        wholeImplicant = wholeImplicant.slice(0, -1);
        if (typeof readFunc(wholeImplicant, map) !== "string") {
          meanImplicants.splice(meanImplicants.indexOf(curImplicant), 1);
        }
        break;
      }
    }
  });
  if (funcType === "sdnf") return `(${meanImplicants.join(")+(")})`;
  else if (funcType === "sknf") return `(${meanImplicants.join(")*(")})`;
}

export function quineMethod(variables, constituentsStr, implicantsStr) {
  const getVariables = (array) => {
    return array.map((implicant) => {
      let vars = [];
      implicant.split("").forEach((elem, index, arr) => {
        if (variables.includes(elem)) {
          if (arr[index - 1] === "!") vars.push("!" + elem);
          else vars.push(elem);
        }
      });
      return vars;
    });
  };
  const constituents = {
    constituents: constituentsStr,
    variables: getVariables(constituentsStr),
  };
  const implicants = {
    implicants: implicantsStr,
    variables: getVariables(implicantsStr),
    covering: [],
  };

  //console.log(constituents, implicants);

  implicants.variables.forEach((implicantVars) => {
    let coveredConstituents = [];
    constituents.variables.forEach((constituent, constituentIndex) => {
      if (implicantVars.every((elem) => constituent.includes(elem))) {
        coveredConstituents.push(constituentIndex);
      }
    });
    implicants.covering.push(coveredConstituents);
  });
  //console.log(implicants.covering);

  const constituentIndexes = constituents.variables.map((elem, index) => index);
  //console.log(constituentIndexes);

  const table = generateTruthTableVariables(implicants.covering.length);
  const coverSets = [];
  table.forEach((set) => {
    let coveredIndexes = [];
    set.forEach((pos, posIndex) => {
      if (pos) coveredIndexes += implicants.covering[posIndex];
    });
    if (constituentIndexes.every((elem) => coveredIndexes.includes(elem))) {
      coverSets.push(set);
    }
  });
  const minSet = coverSets[0];
  coverSets.forEach((set) => {
    if (
      minSet.reduce(
        (accumulator, currentValue) => accumulator + currentValue,
        0
      ) >
      set.reduce((accumulator, currentValue) => accumulator + currentValue, 0)
    ) {
      minSet = set;
    }
  });

  // console.log(table);
  // console.log(coverSets);
  // console.log(minSet);

  const mnf = [];
  minSet.forEach((pos, index) => {
    if (pos) mnf.push(implicants.implicants[index]);
  });
  return mnf[0][1] === "+" || mnf[0][2] === "+"
    ? "(" + mnf.join(")*(") + ")"
    : "(" + mnf.join(")+(") + ")";
}

export function karnoMethod(func, funcType) {
  const sets = [
    [0, 1],
    [0, 0, 1, 1],
    [0, 1, 1, 0],
  ];

  const results = [];
  sets[1].forEach((posB, indexB) => {
    let column = [];
    sets[0].forEach((posA) => {
      column.push(
        readFunc(
          func,
          new Map([
            ["A", posA],
            ["B", posB],
            ["C", sets[2][indexB]],
          ])
        )
      );
    });
    results.push(column);
  });
  //console.log(results);

  const groups = [];
  let typeValue = 1;
  if (funcType === "sknf") typeValue = 0;
  for (let i = 0; i < results.length; i++) {
    if (results[i].every((elem) => elem == typeValue)) {
      groups.push({ type: "col", index: i });
      if (
        results[i + 1] !== undefined &&
        results[i + 1].toString() === results[i].toString()
      ) {
        groups.splice(-1, 1, { type: "rect", index: [i, i + 1] });
        i++;
      } else if (
        results[i + 1] === undefined &&
        results[0].toString() === results.at(-1).toString()
      ) {
        groups.pop();
        if (groups.find((item) => item.type === "col" && item.index === 0)) {
          groups.splice(0, 1, {
            type: "rect",
            index: [0, results.length - 1],
          });
        } else groups.push({ type: "rect", index: [0, results.length - 1] });
      }
    }
  }
  for (let i = 0; i < results.length; i++) {
    let check = false;
    if (results[i + 1] !== undefined && i % 2 !== 1) {
      if (results[i][0] == typeValue && results[i + 1][0] == typeValue) {
        check = true;
        groups.push({ type: "row", colIndexes: [i, i + 1], rowIndex: 0 });
      }
      if (results[i][1] == typeValue && results[i + 1][1] == typeValue) {
        if (!check) {
          groups.push({ type: "row", colIndexes: [i, i + 1], rowIndex: 1 });
        } else groups.pop();
      }
    }
    // else {
    //   if (results[i][0] == typeValue && results[0][0] == typeValue) {
    //     check = true;
    //     groups.push({
    //       type: "row",
    //       colIndexes: [0, results.length - 1],
    //       rowIndex: 0,
    //     });
    //   }
    //   if (results[i][1] == typeValue && results[0][1] == typeValue) {
    //     if (!check) {
    //       groups.push({
    //         type: "row",
    //         colIndexes: [0, results.length - 1],
    //         rowIndex: 1,
    //       });
    //     } else groups.pop();
    //   }
    // }
  }
  //console.log(groups);

  const mnf = [];
  groups.forEach((group) => {
    let implicant = [];
    if (group.type === "col") {
      if (sets[1][group.index] !== typeValue) implicant.push("!B");
      else implicant.push("B");
      if (sets[2][group.index] !== typeValue) implicant.push("!C");
      else implicant.push("C");
    } else if (group.type === "rect") {
      if (sets[0][group.index[0]] === sets[0][group.index[1]]) {
        if (sets[0][group.index[0]] !== typeValue) implicant.push("!A");
        else implicant.push("A");
      } else {
        if (sets[2][group.index[0]] !== typeValue) implicant.push("!C");
        else implicant.push("C");
      }
    } else if (group.type === "row") {
      if (sets[1][group.colIndexes[0]] === sets[1][group.colIndexes[1]]) {
        if (sets[1][group.colIndexes[0]] !== typeValue) implicant.push("!B");
        else implicant.push("B");
      } else {
        if (sets[2][group.colIndexes[0]] !== typeValue) implicant.push("!C");
        else implicant.push("C");
      }
      if (sets[0][group.rowIndex] !== typeValue) implicant.push("!A");
      else implicant.push("A");
      implicant.reverse();
    }
    mnf.push(implicant);
  });
  //console.log(mnf);

  let outSign = "+";
  let inSign = "*";
  if (funcType === "sknf") [outSign, inSign] = [inSign, outSign];
  return (
    "(" + mnf.map((set) => set.join(`${inSign}`)).join(`)${outSign}(`) + ")"
  );
}
