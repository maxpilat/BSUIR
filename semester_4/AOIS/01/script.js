const SIZE_EXPONENT = 8;
const SIZE_MANTISSA = 12;
const num_1 = 14;
const num_2 = -7;

const directCode = (num) => {
  let exponent = [];
  let sign = 0;
  if (num < 0) sign = 1;
  let whole = Math.abs(Math.floor(num));
  while (whole > 0) {
    exponent.unshift(whole % 2);
    whole = (whole - (whole % 2)) / 2;
  }
  while (exponent.length < SIZE_EXPONENT - 1) exponent.unshift(0);
  exponent.unshift(sign);
  if (Number.isInteger(num)) return exponent;

  let fraction = num % 1;
  let mantissa = [];
  for (let i = 0; i < SIZE_MANTISSA; i++) {
    fraction = (fraction % 1) * 2;
    mantissa.push(Math.trunc(fraction));
  }
  exponent.push(null);
  return exponent.concat(mantissa);
};

const reversCode = (num) => {
  if (typeof num === "number") num = directCode(num);
  if (num[0] !== 0) {
    for (let i = 1; i < SIZE_EXPONENT; i++) {
      num[i] ? (num[i] = 0) : (num[i] = 1);
    }
  }
  return num;
};

const additioanalCode = (num) => sum(num, 1);

const getSignificance = (num) => {
  if (!num.includes(1)) return [0];
  num.splice(0, 1);
  num.splice(0, num.indexOf(1));
  return num;
};

const defaultFormat = (num) => {
  if (!num.includes(1)) return 0;
  let sign = num[0];
  num = getSignificance(num);
  num.forEach((elem, index, arr) => {
    arr[index] = elem * Math.pow(2, arr.length - 1 - index);
  });
  num = num.reduce((sum, elem) => sum + elem);
  if (sign) return -num;
  return num;
};

const makeOperand = (num, sign, part) => {
  let result = [...num];
  if (!part) part = "exponent";
  if (part === "exponent") {
    while (result.length < SIZE_EXPONENT - 1) result.unshift(0);
    result.unshift(sign);
  } else if (part === "mantissa") {
    while (result.length < SIZE_EXPONENT) result.push(0);
  }
  return result;
};

const sumInstruction = (a, b, mantissa) => {
  let size = SIZE_EXPONENT;
  if (mantissa) size = SIZE_MANTISSA;
  let result = [];
  let reminder = 0;
  for (let i = size; i >= 0; i--) {
    let sum = a[i] + b[i] + reminder;
    if (sum <= 1) {
      result.push(sum);
      reminder = 0;
    } else if (sum === 2) {
      result.push(0);
      reminder = 1;
    } else if (sum === 3) {
      result.push(1);
    }
  }
  if (mantissa && reminder === 1) result.push(1);
  return result.reverse();
};

const sum = (a, b) => {
  if (Number.isInteger(num_1) && Number.isInteger(num_2)) {
    let result = [];
    if (a * b < 0) {
      if (Math.abs(a) == Math.abs(b)) return [0];
      if (a < 0) [a, b] = [b, a];
      result = sumInstruction(directCode(a), reversCode(b));
      if (Math.abs(a) < Math.abs(b)) {
        return reversCode(result);
      }
      return additioanalCode(defaultFormat(result));
    } else {
      result = sumInstruction(directCode(a), directCode(b));
      if (a < 0) result[0] = 1;
      return result;
    }
  } else {
    let result = {
      exponent: null,
      mantissa: null,
    };
    if (a < b) [a, b] = [b, a];
    a = directCode(a);
    b = directCode(b);

    a = {
      exponent: a.slice(0, a.indexOf(null)),
      mantissa: a.slice(a.indexOf(null) + 1),
    };
    b = {
      exponent: b.slice(0, b.indexOf(null)),
      mantissa: b.slice(b.indexOf(null) + 1),
    };
    result.exponent = sumInstruction(a.exponent, b.exponent);

    a.mantissa = makeOperand(a.mantissa, 0, "mantissa");
    b.mantissa = makeOperand(b.mantissa, 0, "mantissa");

    result.mantissa = sumInstruction(a.mantissa, b.mantissa, true);
    if (result.mantissa.length > SIZE_MANTISSA) {
      result.mantissa.shift();
      result.exponent = sumInstruction(result.exponent, directCode(1));
    }
  }
};
//console.log("Сумма", sum(num_1, num_2));
console.log("Сумма", defaultFormat(sum(num_1, num_2)));

const mul = (a, b) => {
  let sign = 0;
  if (a * b < 0) sign = 1;

  a = getSignificance(directCode(a));
  b = getSignificance(directCode(b));

  let result = [];

  [...b].reverse().forEach((elemB) => {
    let mul = [];
    [...a].reverse().forEach((elemA) => {
      mul.push(elemA * elemB);
    });
    result.push(mul.reverse());
  });

  for (let i = 0; i < result.length - 1; i++) {
    for (let j = 0; j < i + 1; j++) {
      result[i + 1].push(0);
    }
    while (result[i + 1].length != result[i].length) {
      result[i].unshift(0);
    }
    while (result[i].length != SIZE_EXPONENT) {
      result[i].unshift(0);
      result[i + 1].unshift(0);
    }

    result[i + 1] = sumInstruction(result[i], result[i + 1]);
    result[i + 1] = result[i + 1].slice(result[i + 1].indexOf(1));
  }
  result = result[result.length - 1];
  while (result.length < SIZE_EXPONENT) result.unshift(0);
  result[0] = sign;
  return result;
};
//console.log("Произведение", mul(num_1, num_2));
console.log("Произведение", defaultFormat(mul(num_1, num_2)));

const div = (a, b) => {
  if (Math.abs(a) - Math.abs(b) < 0) return [0];

  let result = [];
  let remainder = [];
  let sign = 0;
  if (a * b < 0) sign = 1;

  a = getSignificance(directCode(a));
  b = getSignificance(directCode(b));

  remainder = a.slice(0, b.length);
  let oper_2 = makeOperand(b, 1);

  for (let i = b.length; i < a.length + 1; i++) {
    let oper_1 = makeOperand(remainder, 0);
    let dif = sum(defaultFormat([...oper_1]), defaultFormat([...oper_2]), true);
    if (dif[0] === 0) {
      result.push(1);
      remainder = getSignificance(dif);
    } else {
      result.push(0);
    }
    remainder.push(a[i]);
  }
  return makeOperand(result, sign);
};
//console.log("Частное", div(num_1, num_2));
console.log("Частное", defaultFormat(div(num_1, num_2)));
