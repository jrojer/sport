#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

struct Item
{
    int64_t c;
    int64_t w;
};

int main()
{
    int n;
    int total_w;
    scanf("%d%d",&n,&total_w);
    std::vector<Item> items;
    for(int i=0;i<n;++i)
    {
        int c,w;
        scanf("%d%d",&c,&w);
        items.push_back(Item{c,w});
    }
    std::sort(items.begin(),items.end(),[](const Item& a, const Item& b){return a.c * b.w > b.c * a.w;});

    double total_cost = 0;
    for(const auto& item: items)
    {
        if(item.w <= total_w)
        {
            total_cost += item.c;
            total_w -= item.w;
        }
        else
        {
            total_cost += static_cast<double>(item.c * total_w)/item.w;
            break;
        }
    }
    printf("%.3f\n",total_cost);
    return 0;
}
