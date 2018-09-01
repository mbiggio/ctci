#include <iostream>
#include <queue>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "graph.h"
using namespace std;

struct item {
  item(int node, int level, int origin) : 
    node(node), level(level), origin(origin) {};
  int node;
  int level;
  int origin;
};

/**
 * Given an undirected graph g and source and dest nodes,
 * find whether there exists a path between source and dest.
 * Uses bidirectional search, that allows better performance 
 * wrt standard BFS in case a path exists.
 */
bool route_between_nodes(int source, int dest, const graph &g) {
  queue<item> q;
  vector<int> visited(g.size(),-1);
  q.push(item(source, 0, source));
  q.push(item(dest, 0, dest));
  visited[source] = source;
  visited[dest] = dest;

  while (!q.empty()) {
    item cur = move(q.front());
    q.pop();
    for (auto n : g[cur.node]) {
      if (visited[n] != -1) {
        if (visited[n] != cur.origin) return true;
      }
      else {
        q.push(item(n,cur.level+1,cur.origin));
        visited[n] = cur.origin;
      }
    }
  }

  return false;
}


TEST(route_between_nodes_test, two_connected_components) {

  graph g = {/* node 0 */ {1},
             /* node 1 */ {2},
             /* node 2 */ {0},
             /* node 3 */ {4},
             /* node 4 */ {5},
             /* node 5 */ {3}};

  EXPECT_FALSE(route_between_nodes(0,3,g));
  EXPECT_TRUE(route_between_nodes(0,2,g));
  EXPECT_TRUE(route_between_nodes(0,1,g));
  EXPECT_TRUE(route_between_nodes(3,4,g));
  EXPECT_TRUE(route_between_nodes(3,5,g));
}

TEST(route_between_nodes_test, no_edge) {

  graph g = {/* node 0 */ {},
             /* node 1 */ {},
             /* node 2 */ {}};

  EXPECT_FALSE(route_between_nodes(0,1,g));
  EXPECT_FALSE(route_between_nodes(0,2,g));
  EXPECT_FALSE(route_between_nodes(1,2,g));
}

TEST(route_between_nodes_test, fully_connected) {

  graph g = {/* node 0 */ {1,2},
             /* node 1 */ {0,2},
             /* node 2 */ {0,1}};

  EXPECT_TRUE(route_between_nodes(0,1,g));
  EXPECT_TRUE(route_between_nodes(0,2,g));
  EXPECT_TRUE(route_between_nodes(1,2,g));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
