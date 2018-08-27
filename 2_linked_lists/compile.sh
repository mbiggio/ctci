#!/bin/bash

# TODO: replace by simple Makefile
g++ --std=c++11 1_remove_dups.cpp /usr/lib/libgtest.a /usr/lib/libgtest_main.a /usr/lib/libgmock.a /usr/lib/libgmock_main.a  -pthread  -o 1_remove_dups
g++ --std=c++11 2_kth_to_last.cpp /usr/lib/libgtest.a /usr/lib/libgtest_main.a /usr/lib/libgmock.a /usr/lib/libgmock_main.a  -pthread  -o 2_kth_to_last
g++ --std=c++11 3_delete_not_last.cpp /usr/lib/libgtest.a /usr/lib/libgtest_main.a /usr/lib/libgmock.a /usr/lib/libgmock_main.a  -pthread  -o 3_delete_not_last
g++ --std=c++11 4_partition.cpp /usr/lib/libgtest.a /usr/lib/libgtest_main.a /usr/lib/libgmock.a /usr/lib/libgmock_main.a  -pthread  -o 4_partition
g++ --std=c++11 5_sum_lists.cpp /usr/lib/libgtest.a /usr/lib/libgtest_main.a /usr/lib/libgmock.a /usr/lib/libgmock_main.a  -pthread  -o 5_sum_lists
