#!/bin/bash

# TODO: replace by simple Makefile
g++ --std=c++11 2_stack_with_min.cpp /usr/lib/libgtest.a /usr/lib/libgtest_main.a /usr/lib/libgmock.a /usr/lib/libgmock_main.a  -pthread  -o 2_stack_with_min
g++ --std=c++11 5_sort_stack.cpp /usr/lib/libgtest.a /usr/lib/libgtest_main.a /usr/lib/libgmock.a /usr/lib/libgmock_main.a  -pthread  -o 5_sort_stack
g++ --std=c++14 6_animal_shelter.cpp /usr/lib/libgtest.a /usr/lib/libgtest_main.a /usr/lib/libgmock.a /usr/lib/libgmock_main.a  -pthread  -o 6_animal_shelter
