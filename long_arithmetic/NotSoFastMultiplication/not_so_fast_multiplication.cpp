#include <cstdio>
#include <vector>
#include <cstdint>

int GetLength(const char *a)
{
    int len_a = 0;
    while (a[len_a++] > 0)
        ;
    return len_a - 1;
}

std::vector<int64_t> GetProduct(const std::vector<int64_t> &a, const std::vector<int64_t> &b, int radix_)
{
    std::vector<int64_t> res(a.size() + b.size());
    for (size_t i = 0; i < a.size(); ++i)
    {
        int64_t da = a[i];
        for (size_t j = 0; j < b.size(); ++j)
        {
            int64_t db = b[j];
            int64_t t = da * db + res[i + j];
            res[i + j] = t % radix_;
            res[i + j + 1] += t / radix_;
        }
    }
    return std::move(res);
}

std::vector<int64_t> ToDigitVector(const char *a, int radix_, int digit_len_)
{
    std::vector<int64_t> digits_;
    int len = GetLength(a);
    digits_.resize((len + digit_len_ - 1) / digit_len_);
    int64_t c = 1;
    for (int i = 0; i < len; ++i)
    {
        digits_[i / digit_len_] += (a[len - 1 - i] - '0') * c;
        c = (c * 10) == radix_ ? 1 : c * 10;
    }
    return std::move(digits_);
}

class BigInteger
{
  public:
    BigInteger(const std::vector<int64_t> &a) : digits_(a)
    {
    }
    BigInteger(const char *a): digits_(ToDigitVector(a,radix_,digit_len_))
    {
    }
    BigInteger operator*(const BigInteger &other) const
    {
        return BigInteger(GetProduct(digits_, other.digits_, radix_));
    }
    std::vector<char> ToCharVector() const
    {
        std::vector<char> res;
        int num_digits = digits_.size();
        for (int i = 0; i < num_digits; ++i)
        {
            int c = radix_;
            int64_t num = digits_[num_digits - 1 - i];
            for (int j = 0; j < digit_len_; ++j)
            {
                c /= 10;
                char t = num / c + '0';
                if (!res.empty() || t > '0')
                {
                    res.push_back(t);
                }
                num %= c;
            }
        }
        if (res.empty())
        {
            res.push_back('0');
        }
        res.push_back(0);
        return std::move(res);
    }
  private:
    const int radix_ = 1000000000;
    const int digit_len_ = 9;
    std::vector<int64_t> digits_;
};

int main()
{
    const int max_num_len = 10001;
    int num_test_cases = 0;
    scanf("%d", &num_test_cases);
    for (int t = 0; t < num_test_cases; ++t)
    {
        char a[max_num_len] = {};
        char b[max_num_len] = {};
        scanf("%s", a);
        scanf("%s", b);
        auto res = BigInteger(a) * BigInteger(b);
        auto string = res.ToCharVector();
        printf("%s\n", string.data());
    }
    return 0;
}
