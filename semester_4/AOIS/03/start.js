import {
  generateTruthTableVariables,
  getVariableMap,
  readFunc,
  getSDNF,
  getSKNF,
} from "./module_1.js";

import {
  getConstituents,
  getImplicants,
  calcMethod,
  quineMethod,
  karnoMethod,
} from "./module_2.js";

function start() {
  const func = "!((!A*B)+(!B*C))";
  const variables = [...new Set(func.match(/[a-z]+/gi))];
  const sets = generateTruthTableVariables(variables.length);
  const varMap = getVariableMap(variables, sets);

  varMap.forEach((set, index) => {
    sets[index].push(readFunc(func, set));
  });

  const sdnf = getSDNF(varMap, sets);
  const sknf = getSKNF(varMap, sets);
  console.log(sdnf);
  console.log(sknf);
  console.log("\n");

  const implicantsSDNF = getImplicants(variables, sdnf.result);
  const implicantsSKNF = getImplicants(variables, sknf.result);
  console.log("Implicants:", "\n", implicantsSDNF, "\n", implicantsSKNF);
  console.log("\n");

  console.log("calcMethod:");
  console.log("SDNF: " + calcMethod(variables, implicantsSDNF, "sdnf"));
  console.log("SKNF: " + calcMethod(variables, implicantsSKNF, "sknf"));
  console.log("\n");

  const constituentsSDNF = getConstituents(sdnf.result);
  const constituentsSKNF = getConstituents(sknf.result);
  console.log("quineMethod:");
  console.log(
    "SDNF: " + quineMethod(variables, constituentsSDNF, implicantsSDNF)
  );
  console.log(
    "SKNF: " + quineMethod(variables, constituentsSKNF, implicantsSKNF)
  );
  console.log("\n");

  console.log("karnoMethod:");
  console.log("SDNF: " + karnoMethod(func, "sdnf"));
  console.log("SKNF: " + karnoMethod(func, "sknf"));

  console.log("\n");
}
start();
