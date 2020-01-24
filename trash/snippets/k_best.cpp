#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool ExistsK(const vector<int> &v, const vector<int> &w, vector<double> &tmp, int n, int k, double x)
{
    for (int i = 0; i < n; ++i)
    {
        tmp[i] = v[i] - x * w[i];
    }
    sort(tmp.begin(), tmp.end());
    double sum = 0.0;
    for (int i = 0; i < k; ++i)
    {
        sum += *(tmp.rbegin() + i);
    }
    return sum >= 0.0;
}

double BinarySearch(const vector<int> &v, const vector<int> &w, vector<double> &tmp, int n, int k)
{
    double l = 0;              // f(l) = 1
    double r = 100000000000.0; // f(r) = 0
    for (int i = 0; i < 100; ++i)
    {
        double x = (r - l) / 2;
        if (ExistsK(v, w, tmp, n, k, x))
        {
            x = l;
        }
        else
        {
            x = r;
        }
    }
    return l;
}

int main()
{
    freopen("input.txt","r",stdin);
    int n, k;
    scanf("%d%d", &n, &k);
    vector<int> values(n);
    vector<int> weights(n);
    vector<double> tmp(n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", &values[i], &weights[i]);
    }
    double x = BinarySearch(values, weights, tmp, n, k);
    vector<int> ids(n);
    for (int i = 0; i < n; ++i)
    {
        ids[i] = i;
    }
    sort(ids.begin(), ids.end(), [&](int i, int j) { return (values[i] - x * weights[i]) > (values[j] - x * weights[j]); });
    int value_sum = 0;
    int weight_sum = 0;
    for (int i = 0; i < k; ++i)
    {
        printf("%d\n", ids[i] + 1);
        value_sum  += values[ids[i]];
        weight_sum += weights[ids[i]];
    }
    printf("%f\n", static_cast<double>(value_sum)/weight_sum);

    return 0;
}