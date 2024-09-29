class Parser {
  constructor() {
    this.tokens = [];
    this.index = 0;
  }

  parse(expression) {
    if (typeof expression !== 'string') {
      throw new Error('Input must be a string');
    }

    this.index = 0;
    this.tokens = expression.match(/NOT|AND|OR|\(|\)|[\wа-яА-ЯёЁ]+/g) || [];

    if (!this.tokens) {
      throw new Error('No valid tokens found');
    }

    const result = this._parseOrExpression();

    if (this.index < this.tokens.length) {
      throw new Error('Unexpected token: ' + this.tokens[this.index]);
    }

    return result;
  }

  _parseAtom() {
    if (this.tokens[this.index] === 'NOT') {
      this.index++;
      const right = this.tokens[this.index++];
      return { operator: 'NOT', right };
    } else if (this.tokens[this.index] === '(') {
      this.index++;
      const expr = this._parseOrExpression();
      this.index++;
      return expr;
    } else {
      return this.tokens[this.index++];
    }
  }

  _parseTerm() {
    const left = this._parseAtom();
    while (
      this.index < this.tokens.length &&
      this.tokens[this.index] === 'AND'
    ) {
      this.index++;
      const right = this._parseAtom();
      return { operator: 'AND', left, right };
    }
    return left;
  }

  _parseOrExpression() {
    const left = this._parseTerm();
    while (
      this.index < this.tokens.length &&
      this.tokens[this.index] === 'OR'
    ) {
      this.index++;
      const right = this._parseTerm();
      return { operator: 'OR', left, right };
    }
    return left;
  }
}

module.exports = Parser;
