const http = require('http');
const fs = require('fs');

const hostname = '127.0.0.1';
const port = 8888;

const server = http.createServer((req, res) => {
  if (req.method === 'GET') {
    res.statusCode = 200;
    res.setHeader('Content-Type', 'text/html');
    fs.createReadStream(__dirname + '/index.html').pipe(res);
  } else {

    let body = [];
    req.on('data', (chunk) => {
      body.push(chunk);
    }).on('end', () => {
      body = Buffer.concat(body).toString();

      res.statusCode = 200;
      res.setHeader('Content-Type', 'text/plain');
      res.end(body);
    });
    // const msg = 'Upload completed\n';
  }
});

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});
