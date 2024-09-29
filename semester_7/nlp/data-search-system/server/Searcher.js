class Searcher {
  search(documents, expression) {
    const normalizedDocuments = documents.map((doc) => ({
      ...doc,
      keywords: doc.keywords.map((keyword) => ({
        ...keyword,
        word: keyword.word.toLowerCase(),
      })),
    }));

    const keywordResults = this.searchByKeywords(
      normalizedDocuments,
      expression
    );

    let dataResults = this.searchByData(normalizedDocuments, expression);

    dataResults = dataResults.filter(
      (doc) => !keywordResults.some((keywordDoc) => keywordDoc.id === doc.id)
    );

    return [...keywordResults, ...dataResults];
  }

  searchByKeywords(documents, expression) {
    let keywords = [];

    if (typeof expression === 'string') {
      keywords = [expression.toLowerCase()];
    } else if (typeof expression === 'object') {
      keywords = this.extractKeywords(expression);
    }

    const results = documents.filter((doc) =>
      doc.keywords.some((keyword) => keywords.includes(keyword.word))
    );

    results.sort((a, b) => {
      const aWeight = a.keywords.reduce(
        (sum, keyword) =>
          keywords.includes(keyword.word) ? sum + keyword.weight : sum,
        0
      );

      const bWeight = b.keywords.reduce(
        (sum, keyword) =>
          keywords.includes(keyword.word) ? sum + keyword.weight : sum,
        0
      );

      if (bWeight === aWeight) {
        return new Date(b.createdAt) - new Date(a.createdAt);
      }

      return bWeight - aWeight;
    });

    return results;
  }

  extractKeywords(expression) {
    let keywords = [];

    if (typeof expression === 'string') {
      keywords.push(expression.toLowerCase());
    } else if (expression.operator) {
      if (expression.left) {
        keywords = keywords.concat(this.extractKeywords(expression.left));
      }
      if (expression.right) {
        keywords = keywords.concat(this.extractKeywords(expression.right));
      }
    }

    return keywords;
  }

  searchByData(documents, expression) {
    if (typeof expression === 'string') {
      return documents.filter(
        (doc) => doc.data.includes(expression) || doc.name.includes(expression)
      );
    }

    const { operator, left, right } = expression;

    const leftDocuments = left ? this.searchByData(documents, left) : [];
    const rightDocuments = right ? this.searchByData(documents, right) : [];

    switch (operator) {
      case 'AND':
        return leftDocuments.filter((doc) => rightDocuments.includes(doc));
      case 'OR':
        return Array.from(new Set([...leftDocuments, ...rightDocuments]));
      case 'NOT':
        return documents.filter((doc) => !rightDocuments.includes(doc));
      default:
        throw new Error(`Unknown operator: ${operator}`);
    }
  }
}

module.exports = Searcher;
