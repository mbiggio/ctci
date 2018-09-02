#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "graph.h"
using namespace std;

struct timestamp {
  timestamp(int node, int time) :
    node(node), time(time) {};
  int node;
  int time;
};

bool dfs(const graph &g, int node, vector<timestamp> &discovery, vector<timestamp> &completion, int &current_time) {
  discovery[node] = timestamp(node,current_time++);
  for (auto n : g[node]) {
    if (completion[n].time == -1) {
      if (discovery[n].time == -1) {
        // recurse on node n
        if (!dfs(g,n,discovery,completion,current_time)) return false;
      }
      else {
        // this is a back edge --> cycle
        return false;
      }
    }
  }
  completion[node] = timestamp(node,current_time++);
  return true;
}

vector<int> build_order(const graph &g) {
  vector<int> result;
  vector<timestamp> discovery(g.size(), timestamp(-1,-1));
  vector<timestamp> completion(g.size(), timestamp(-1,-1));
  int current_time = 0;
  for (int i=0; i<g.size(); ++i) {
    if (completion[i].time == -1) {
      if (!dfs(g,i,discovery,completion,current_time)) return result;
    }
  }

  sort(completion.begin(),completion.end(),[](const timestamp &t1, const timestamp &t2){ return t1.time > t2.time; });

  for (const auto &t : completion) result.push_back(t.node);
  return move(result);
}


TEST(build_order_test, ok) {
  graph g = {/* node a=0 */ {3},
             /* node b=1 */ {3},
             /* node c=2 */ {},
             /* node d=3 */ {2},
             /* node e=4 */ {},
             /* node f=5 */ {0,1}};

  vector<int> ex = {5,4,1,0,3,2};
  ASSERT_THAT(build_order(g), ::testing::ContainerEq(ex));
}


TEST(build_order_test, cycle) {
  graph g = {/* node a=0 */ {3},
             /* node b=1 */ {3},
             /* node c=2 */ {5},
             /* node d=3 */ {2},
             /* node e=4 */ {},
             /* node f=5 */ {0,1}};

  ASSERT_TRUE(build_order(g).empty());
}



int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
