#!/bin/bash

g++ -fPIC -shared -o decison_layer.so decision_layer.cpp

python tic_tac_toe_automatic.py