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

struct Node
{
   map<int, int> driver_dist_map;
   struct Edge
   {
      shared_ptr<Node> node;
      int dist;
   };
   vector<Edge> next;
};

struct BfsItem
{
   shared_ptr<Node> node;
   int dist;
};

void bfs(const shared_ptr<Node> driver, int driver_id, int dist_limit)
{
   deque<BfsItem> q;
   q.push_back({driver, 0});
   while (!q.empty())
   {
      auto item = q.front();
      q.pop_front();
      for (auto &next : item.node->next)
      {
         int new_dist = item.dist + next.dist;
         if (new_dist < dist_limit)
         {
            auto &m = next.node->driver_dist_map;
            if (m.find(driver_id) == m.end() || m.find(driver_id) != m.end() && m[driver_id] > new_dist)
            {
               m[driver_id] = new_dist;
            }
            q.push_back({next.node, new_dist});
         }
      }
   }
}

shared_ptr<Node> get_or_create(map<int, shared_ptr<Node>> &m, int key)
{
   if (m.find(key) == m.end())
      m.emplace(key, make_shared<Node>());
   return m[key];
}

int main()
{
   int num_drivers, num_clients, dist_limit, base_price;
   scanf("%d%d%d%d", &num_drivers, &num_clients, &dist_limit, &base_price);
   map<int, shared_ptr<Node>> drivers;
   map<int, shared_ptr<Node>> clients;
   int s;
   scanf("%d", &s);
   for (int i = 0; i < s; ++i)
   {
      int driver_id, client_id, dist;
      scanf("%d%d%d", &driver_id, &client_id, &dist);
      auto driver = get_or_create(drivers, driver_id);
      auto client = get_or_create(clients, client_id);
      driver->next.push_back({client, dist});
   }
   int t;
   scanf("%d", &t);
   for (int i = 0; i < t; ++i)
   {
      int client_id_1, client_id_2, dist;
      scanf("%d%d%d", &client_id_1, &client_id_2, &dist);
      auto client_1 = get_or_create(clients, client_id_1);
      auto client_2 = get_or_create(clients, client_id_2);
      client_1->next.push_back({client_2, dist});
   }
   for (auto &driver : drivers)
   {
      bfs(driver.second, driver.first, dist_limit);
   }
   int min_price = base_price;
   for (auto &client : clients)
   {
      int price = base_price;
      auto &m = client.second->driver_dist_map;
      for (auto &x : m)
      {
         price -= dist_limit - x.second;
         if (price < 1)
         {
            price = 1;
            break;
         }
      }
      if (price < min_price)
      {
         min_price = price;
      }
   }
   printf("%d\n", min_price);
   return 0;
}
