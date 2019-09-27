#include <iostream>

int main()
{
    int n;
    scanf("%d",&n);
    bool up = false;
    int prev = n;
    int num_lm = 0;
    int prev_lm_idx = 0;
    int idx = 0;
    int min_dist = 0;
    while(n)
    {
        if(n > prev)
        {
            up = true;
        }
        else if (n < prev)
        {
            if(up) // local max
            {
                ++num_lm;
                if(num_lm == 2)
                {
                    min_dist = idx - prev_lm_idx;
                }
                else if (num_lm != 1) // > 2
                {
                    if(idx - prev_lm_idx < min_dist)
                        min_dist= idx-prev_lm_idx;
                }
                prev_lm_idx = idx;
            }
            up = false;
        }
        else
        {
            up = false;
        }
        prev = n;
        scanf("%d",&n);
        ++idx;
    }
    printf("%d\n",min_dist);
    return 0;
}
