const Parser = require('./Parser');
const Searcher = require('./Searcher');
const https = require('https');
const http = require('http');
const { hostname, port, mockapiUrl } = require('./config');

let documents = [];
let documentsCount = 0;

const getDocumentCount = () => {
  return new Promise((resolve, reject) => {
    https.get(`${mockapiUrl}/documents`, (res) => {
      let data = '';

      if (res.statusCode !== 200) {
        return reject(new Error(`Third party service error`));
      }

      res.on('data', (chunk) => {
        data += chunk;
      });

      res.on('end', () => {
        try {
          const parsedData = JSON.parse(data);
          console.log(parsedData.length);
          resolve(parsedData.length);
          r;
        } catch (err) {
          reject(new Error('Failed to parse response'));
        }
      });

      res.on('error', (err) => reject(err));
    });
  });
};

const getDocuments = () => {
  return new Promise((resolve, reject) => {
    https.get(`${mockapiUrl}/documents`, (res) => {
      let data = '';

      if (res.statusCode !== 200) {
        return reject(new Error(`Third party service error`));
      }

      res.on('data', (chunk) => {
        data += chunk;
      });

      res.on('end', () => {
        try {
          resolve(JSON.parse(data));
        } catch (err) {
          reject(new Error('Failed to parse response'));
        }
      });

      res.on('error', (err) => reject(err));
    });
  });
};

const handleError = (res, statusCode, message) => {
  res.statusCode = statusCode;
  res.end(JSON.stringify({ message }));
};

const checkDocumentUpdates = async () => {
  try {
    const newDocumentsCount = await getDocumentCount();
    if (newDocumentsCount !== documentsCount) {
      console.log(
        `Document count changed from ${documentsCount} to ${newDocumentsCount}`
      );
      documentsCount = newDocumentsCount;
      documents = await getDocuments();
    }
  } catch (err) {
    console.error('Error checking document updates:', err.message);
  }
};

setInterval(checkDocumentUpdates, 5000);

const handleSearch = async (req, res) => {
  const url = new URL(req.url, `http://${req.headers.host}`);
  const query = url.searchParams.get('query');

  if (!query) {
    return res.end(JSON.stringify(documents));
  }

  const parser = new Parser();
  let parsedQuery = '';

  try {
    parsedQuery = parser.parse(query);
  } catch (err) {
    return handleError(res, 400, err.message);
  }

  const searcher = new Searcher();

  try {
    const filteredDocuments = searcher.search(documents, parsedQuery);
    res.end(JSON.stringify(filteredDocuments));
  } catch (err) {
    handleError(res, 500, err.message);
  }
};

const handleDocuments = async (res) => {
  res.end(JSON.stringify(documents));
};

const server = http.createServer((req, res) => {
  res.setHeader('Access-Control-Allow-Origin', '*');

  const url = new URL(req.url, `http://${req.headers.host}`);

  switch (url.pathname) {
    case '/search':
      handleSearch(req, res);
      break;

    case '/documents':
      handleDocuments(res);
      break;

    default:
      handleError(res, 404, 'Page not found');
      break;
  }
});

server.listen(port, hostname, () => {
  console.log(`Server is running at http://${hostname}:${port}/`);
});

(async () => {
  try {
    documentsCount = await getDocumentCount();
    documents = await getDocuments();
    console.log(`Initial document count: ${documentsCount}`);
  } catch (err) {
    console.error('Error initializing document data:', err.message);
  }
})();
