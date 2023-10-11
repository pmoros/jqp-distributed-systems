# json-graph-solver-distributed-systems
This project is a tool for solving the best route in a graph that comes from a JSON file. The goal is to solve this problem leveraging parallel computing.
## Description
In 2021 Amazon created a challenge for finding the best route for delivering a package. As part of the challenge a dataset with this structure was provided.

```javascript

{
  "RouteID_00092558-dece-4fb7-8d0d-7d0df3a4864e": {
    "AH": {
      "AH": 0,
      "AJ": 484.5,
      "AL": 399.3,    
    },
    "AJ": {
      "AH": 484.5,
      "AJ": 0,
      "AL": 85.2,    
    },
    "AL": {
      "AH": 399.3,
      "AJ": 85.2,
      "AL": 0,    
    }
  }
}   

```

In this JSON file the first key is the route ID, the second key is the origin and the third key is the destination. The value is the distance between the origin and the destination. The goal is to find the best route for delivering a package. The best route is the one with the lowest distance. The problem is that the dataset is huge and the solution must be fast.

## Expected Solution

The expected solution is a program that receives a JSON file with the structure described above and returns the best route for delivering a package. The resulting json file must have the following structure.

```javascript
{
    "RouteID_00092558-dece-4fb7-8d0d-7d0df3a4864e": {
        "best_route": ["AH", "AL"],
        "distance": 484.5
    }
}
```

The best route is a list of the nodes that must be visited in order to deliver the package. The distance is the sum of the distances between the nodes in the best route.

## Requirements
 The program must be able to receive a JSON file with any number of routes and destinations. The program must be able to run in a distributed system. The program must be able to run in a single machine. The program must be able to run in a single machine with parallel computing. The program must be able to run in a distributed system with parallel computing.