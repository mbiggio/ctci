#!/bin/bash

# TODO: replace by simple Makefile
g++ --std=c++11 1_route_between_nodes.cpp /usr/lib/libgtest.a /usr/lib/libgtest_main.a /usr/lib/libgmock.a /usr/lib/libgmock_main.a  -pthread  -o 1_route_between_nodes
g++ --std=c++11 2_minimal_tree.cpp /usr/lib/libgtest.a /usr/lib/libgtest_main.a /usr/lib/libgmock.a /usr/lib/libgmock_main.a  -pthread  -o 2_minimal_tree
