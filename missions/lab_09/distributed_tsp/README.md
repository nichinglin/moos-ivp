# Distributed Travelling Salesman

## What is this mission for?

The Travelling Salesman Problem (TSP) is the problem of path finding to visit a set of points. Calculate the distences between points. In this lab we are running two vehicle with greedy shortest path algorithm.

Step 1: 100 points are randomly ganerate in a specified region by uTimerScript.

Step 2: pPointAssign will send half the points to one vehicle and half to the other and show the point on pMarineViewer in different color. In this app you can choose assign by region or not (the parameter could be set in launch.sh.

Step 3: pGenPath
Calculate the path and send to Waypoint behavior

## How to set parameters?

* Points number assign: mission/lab_09/launch.sh --> RANDOM_POINT=100

* Region assign: mission/lab_09/launch.sh --> REGION_X_MIN, REGION_X_MAX, REGION_Y_MIN, REGION_Y_MAX

* Assign by region or not: mission/lab_09/launch.sh --> ASSIGN_BY_REGION="false"

## How to run?

```
$ cd ~/moos-ivp-monica/miision/lab_09/launch.sh
$ ./launch
```

## Who do I talk to?

Monica Lin
nclin94@gmail.com
