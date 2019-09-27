#include <iostream>
#include <vector>
#include <algorithm>

struct Segment
{
    int l;
    int r;
};

int main()
{
    int n;
    scanf("%d",&n);
    std::vector<Segment> segments;
    for(int i=0;i<n;++i)
    {
        int l;
        int r;
        scanf("%d%d",&l,&r);
        segments.push_back({l,r});
    }
    std::sort(segments.begin(),segments.end(),[](const auto& a,const auto& b){return a.r<b.r;});
    int p = -1;
    std::vector<int> ans;
    for(const auto& s: segments)
    {
        if(s.l > p)
        {
            p = s.r;
            ans.push_back(p);
        }
    }
    printf("%lu\n",ans.size());
    for(int a: ans)
    {
        printf("%d ",a);
    }
    printf("\n");
    return 0;
}
