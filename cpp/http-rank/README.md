# http-rank
Given a list of values, and an integer k, return top k largest values.

## GET
```
$ curl "http://localhost:8888/rank?k=3&val=(45.55,1,23.0,67,88.2,0.6,4.452,56)"
{"result":[67.0,88.2,56.0]}
```

## POST
```
$ curl -X 'POST' "http://localhost:8888/rank" -d '{"k":3,"val":[45.55,1,23.0,67,88.2,0.6,4.452,56]}'
{"result":[67.0,88.2,56.0]}
```
