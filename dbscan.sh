#!/bin/bash

g++ -I include/ main.cpp src/dbscan.cpp src/cluster.cpp src/point.cpp -o dbscan.out

./dbscan.out > data/output.txt

python3 scripts/plot.py
