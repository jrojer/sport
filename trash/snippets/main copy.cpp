#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <array>
#include <map>
#include <cstring>
#include <memory>
#include <deque>

using namespace std;

struct Segment
{
   int start;
   int end;
   int weight;
};

int solve(vector<Segment> &segments)
{
   sort(segments.begin(), segments.end(), [](const Segment &a, const Segment &b) { return a.end < b.end; });

   map<int, int> table;
   table[0] = 0;

   vector<int> ends(1,0);

   for (auto &s : segments)
   {
      auto last_leq_start = lower_bound(ends.rbegin(), ends.rend(), s.start, [](int a, int b) { return a > b; });
      auto last_leq_end = lower_bound(ends.rbegin(), ends.rend(), s.end, []( int a, int b) { return a > b; });

      int val = *last_leq_start;
      int val2 = *last_leq_end;

      if(ends.empty() || s.end > ends.back())
      {
         ends.push_back(s.end);
      }

      if (table.find(val2) != table.end() && table[val2] > table[val] + s.weight)
      {
         table[s.end] = table[val2];
      }
      else
      {
         table[s.end] = table[val] + s.weight;
      }
   }
   return table[segments.back().end];
}

struct TestCase
{
   vector<Segment> s;
   int ans;
};

static const vector<TestCase> cases = {
    {{{1, 3, 15}, {3, 7, 25}, {2,6,30}}, 40},
    {{{0, 1, 2}, {2, 3, 8}}, 10},
    {{{0, 1, 2}}, 2},
    {{{1, 3, 15}, {3, 7, 25}, {2,6,30}, {5,8,26}}, 41},
};

void test()
{
   for (const auto &tc : cases)
   {
      auto s = tc.s;
      printf(tc.ans == solve(s) ? "OK\n" : "FAIL\n");
   }
}

int main()
{
   test();
   return 0;
   //freopen("/home/jrojer/Documents/work/vscode_sandbox/test.txt", "r", stdin);
   int n;
   vector<Segment> segments(n);
   for (int i = 0; i < n; ++i)
   {
      scanf("%d%d%d", &segments[i].start, &segments[i].end, &segments[i].weight);
   }
   printf("%d\n", solve(segments));
   return 0;
}
