#!/bin/bash

g++ -fPIC -shared -o decison_layer.so decision_layer.cpp
g++ -Wall -pedantic -o decision_layer.out  decision_layer.cpp
./decision_layer.out
#python test.py