// 第一次作业第一题：编写程序使用Eratosthenes筛法打印1 000 000内所有素数及个数，效果如图所示. （ 思考：a.对比筛法与普通算法的性能差异；b.递归调用该算法求更大范围素数进行优化；c.求更大的素数（如 数量级）该方法是否适用？会引入哪些新的问题？）
#include <iostream>
#include <cmath>
using namespace std;
bool if_vegetable(int n)
{ // 判断是否为素数
    if (n <= 1)
        return false;
    else
    {
        bool flag = true;
        for (int i = 2; i < n; i++)
        {
            if (n % i == 0)
                flag = false;
        }
        return flag;
    }
}
void Eratosthenes(int n)
{
    bool *a = new bool[n]; // 下标是否是素数的bool类型数组
    int count = 0;         // 素数个数
    for (int i = 2; i < n; i++)
    {
        a[i] = true;
    }
    for (int i = 2; i < sqrt(n); i++)
    {
        if (if_vegetable(i))
        { // 是素数
            for (int j = 2; i * j <= n; j++)
            { // 去掉其所有整数倍数，设置为false
                a[i * j] = false;
            }
        }
    }
    for (int i = 2; i < n; i++)
    {
        if (a[i])
        {
            cout << i << " ";
            count++;
        }
    }
    cout << endl;
    cout << "Total:" << count << endl;
    return;
}
int main()
{
    int n;
    cin >> n;
    Eratosthenes(n);
    return 0;
}