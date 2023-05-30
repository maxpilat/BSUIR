// Лабораторная работа №1 по дисциплине ЛОИС
// Выполнена студентом группы 121702 БГУИР Пилат М.Д.
// Проверка является ли формула СКНФ
// 27.03.2023

// Массивы хранят допустимые символы для переменных и операций
const variableTokens = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"];
const operationTokens = ["(", ")", "*", "+", "!"];

// Преобразование формулы строкового вида в массив с заменой знаков вида /\ на знаки вида +
function formatFunc(funcStr) {
    if (!funcStr) return false;
    const func = funcStr.split("");
    for(let i = 0; i < func.length; i++) {
        if (!isNaN(Number(func[i])) && func[i] !== null) return false; // если цифра
        if (func[i] !== null) {
            // если символ в нижнем регистре
            if (variableTokens.includes(func[i].toUpperCase())
            && func[i] === func[i].toLowerCase()) return false;
        }
        if (func[i] === "\\") {
            if (func[i + 1] === "/") {
                func[i] = "*";
                func[i + 1] = null;
            } else return false;
        } else if (func[i] === "/") {
            if (func[i + 1] === "\\") {
                func[i] = "+";
                func[i + 1] = null;
            } else return false;
        } else if (['+', '*'].includes(func[i])) return false;
    }
    return func.filter(token => token !== null);
}

// Получение переменных формулы (ищем переменные только в первом терме)
function getVariables(funcArr) {
    let variables = [];
    for (let i = 0; i < funcArr.length; i++) {
        if (variableTokens.includes(funcArr[i]) && isNaN(Number(funcArr[i]))) {
            variables.push(funcArr[i]);
        }
    }
    return Array.from(new Set(variables));
}

// Является ли символ переменной
function isVariable(letter) {
    return variableTokens.includes(letter);
}

// Проверка формулы
function readFunc(funcArr) {
    const variables = getVariables(funcArr);

    // пары скобок == операции
    if ((funcArr.filter(elem => elem === '(').length !== funcArr.filter(elem => elem === ')').length)
    || (funcArr.filter(elem => elem === '(').length !== funcArr.filter(elem => ['*', '+', '!'].includes(elem)).length))
        return false;

    // A
    if (JSON.stringify(variables) === JSON.stringify(funcArr) && funcArr.length === 1) return true;

    // проверяем и удаляем крайние скобки
    if (funcArr.shift() !== '(' || funcArr.pop() !== ')') return false;

    // !A
    if (funcArr.length === 2 && funcArr[0] === '!' && variables.includes(funcArr[1])) return true;

    const operationStack = [];
    let variableStack = [];
    let curSign = true;
    const terms = [];

    for (let i = 0; i < funcArr.length; i++) {
        if (funcArr[i] === '(') {
            if (funcArr[i - 1] === ')' || variables.includes(funcArr[i - 1])) return false;
            operationStack.push(funcArr[i]);
        } else if (isVariable(funcArr[i])) {
            if ([')', '+'].includes(funcArr[i - 1]) || variableStack.includes(funcArr[i])
            || isVariable(funcArr[i - 1])) return false;
            variableStack.push({ variable: funcArr[i], sign: curSign });
        } else if (funcArr[i] === '*') {
            if (['!', '+'].includes(funcArr[i - 1])) return false;
            operationStack.push(funcArr[i]);
        } else if (funcArr[i] === ')') {
            if (!operationStack.includes('(')
            || (!isVariable(funcArr[i - 1]) && funcArr[i - 1] !== ')')) return false;
            if (curSign) {
                let variableValues = variableStack.map(item => item.variable);
                // проверяем содержит ли терм весь набор переменных
                if (variables.every(variable => variableValues.includes(variable))) {
                    if (operationStack[operationStack.length-1] === '+'
                    || funcArr[i + 1] == undefined
                    || (terms.length === 0 && funcArr[i + 1] !== ')')) {
                        terms.push(variableStack);
                        variableStack = [];
                    } else if (operationStack[operationStack.length-1] !== '*') return false;
                } else if (funcArr[i + 1] !== '*') return false;
            } else curSign = true;
            operationStack.pop(); operationStack.pop();
        } else if (funcArr[i] === '+') {
            if (!isVariable(funcArr[i - 1]) && funcArr[i - 1] !== ')') return false;
            operationStack.push(funcArr[i]);
        } else if (funcArr[i] === '!') {
            if (funcArr[i - 1] !== '(') return false;
            operationStack.push(funcArr[i]);
            curSign = false;
        }
    }

    return checkTerms(terms);
}

// Проверяем термы на уникальность
function checkTerms(terms) {
    for (let i = 0; i < terms.length; i++) {
        let isUnique = false;
        for (let j = 0; j < terms.length; j++) {
            if (i !== j) {
                terms[i].forEach(item1 => {
                    if (!terms[j].find(item2 => item2.variable === item1.variable && item2.sign === item1.sign)) isUnique = true;
                });
            }
        }
        if (!isUnique) return false;
    }
    return true;
}

// Является ли формула скнф
function getResult(funcStr) {
    let func = formatFunc(funcStr);
    if (func) return readFunc(func);
    return false;
}

// Главная функция
(function() {
    const label = document.querySelector('#answLabel');
    const input = document.querySelector('#input');

    input.addEventListener("change", () => {
        let result = getResult(input.value);
        if (result) label.style.color = 'green';
        else label.style.color = 'red';
        label.innerHTML = result;
    });
    
    const tests = [
        ["((A\\/(B\\/C))/\\((A\\/(!B))\\/C))", true],
        ["((B\\/(!B))/\\((A\\/(!B))\\/C))", false],
        ["((A\\/C)/\\(A\\/(B\\/C)))", false],
        ["((A\\/(B\\/C))/\\((A\\/B)\\/C))", false],
        ["((X\\/R)->Q)", false],
        ["(B~C)", false],
        ["(((A\\/B)/\\(A\\/(!B)))/\\((!A)\\/(!B)))", true],
        ["((!A)/\\(B\\/C))", false],
        ["((A\\/B)/\\(((!B)\\/(C\\/D))/\\(D\\/E)))", false],
        ["((A\\/(B\\/(C\\/D)))/\\((((!A)\\/(!B))\\/(!C))\\/(!D)))", true]
    ];
    tests.forEach(test => console.log(getResult(test[0]) == test[1]));
 
})();