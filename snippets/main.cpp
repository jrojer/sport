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

struct MergeResult
{
   std::vector<int> merged;
   int64_t num_inv;
};

static std::vector<int64_t> left;
static std::vector<int64_t> right;

MergeResult AugmentedMerge(const std::vector<int> &a, const std::vector<int> &b)
{
   int i = 0;
   int j = 0;
   std::vector<int> merged;
   int64_t num_inv = 0;
   int64_t val = 0;
   while (i < a.size() && j < b.size())
   {
      if (a[i] < b[j])
      {
         merged.push_back(a[i]);
         ++i;
         if(i < a.size())
            right[a[i]] += val;
      }
      else
      {
         merged.push_back(b[j]);
         left[b[j]] += a.size() - i;
         //++val;
         //right[a[i]] += val;
         ++right[a[i]];
         ++val;
         ++j;
      }
   }
   while (i < a.size())
   {
      merged.push_back(a[i]);
      if(i+1<a.size())
         right[a[i+1]] += val;
      ++i;
   }
   while (j < b.size())
   {
      merged.push_back(b[j]);
      ++j;
   }
   return {merged, num_inv};
}

int64_t NumInv(const std::vector<int> &values)
{
   int n = values.size();
   std::vector<std::vector<int>> q(n, std::vector<int>(1));
   for (int i = 0; i < n; ++i)
   {
      q[i][0] = values[i];
   }
   int64_t answer = 0;
   while (q.size() > 1)
   {
      std::vector<std::vector<int>> tmp;
      for (int i = 1; i < q.size(); i += 2)
      {
         const auto &res = AugmentedMerge(q[i - 1], q[i]);
         answer += res.num_inv;
         tmp.push_back(res.merged);
      }
      if (q.size() % 2 > 0)
      {
         tmp.push_back(q.back());
      }
      q = tmp;
   }
   return answer;
}

std::vector<int> ReadInput()
{
   int n;
   scanf("%d", &n);
   std::vector<int> values(n);
   for (int i = 0; i < n; ++i)
   {
      scanf("%d", &values[i]);
   }
   return values;
}

int main()
{
   //freopen("input.txt", "r", stdin);

   auto values = ReadInput();
   left = std::vector<int64_t>(values.size() + 1);
   right = std::vector<int64_t>(values.size() + 1);
   //printf("%lld\n", );
   NumInv(values);
   int64_t ans = 0;
   for (int i = 0; i < values.size() + 1; ++i)
   {
      ans += left[i] * right[i];
   }

   printf("%ld\n", ans);

   return 0;
}