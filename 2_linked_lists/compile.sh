#!/bin/bash

# TODO: replace by simple Makefile
g++ --std=c++11 1_remove_dups.cpp /usr/lib/libgtest.a /usr/lib/libgtest_main.a /usr/lib/libgmock.a /usr/lib/libgmock_main.a  -lpthread  -o 1_remove_dups
