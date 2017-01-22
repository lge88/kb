const express = require('express');
const app = express();

app.get('/rank', function(req, res) {
  const k = req.query.k;
  const values = req.query.v;
  values.sort((a, b) => b - a);
  const result = values.slice(0, k);
  res.send({ result });
});

app.listen(8888, () => {
  console.log('http://localhost:8888/rank?k=3&v=45.55&v=1&v=23.0&v=67&v=88.2&v=0.6&v=4.452&v=56');
});
