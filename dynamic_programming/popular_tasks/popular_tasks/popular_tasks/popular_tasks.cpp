#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<int> path;
//Даны n предметов с весами хранящимися в массиве a. Определите, на какой максимальный вес можно набрать предметов в рюкзак вместимости веса W .
int task_rukzak(vector<int> a, int w)
{
    //w - сколько предметов вмещвет рюкзак
    //a - список весов предметов
    int n = a.size();
    vector<vector<bool>> dp(n, vector<bool>(w + 1, false));
    //dp[pref][w] - можно ли рассмотреть первые pref предметов и набрать вес W в рюкзаке (true/false)
    dp[0][0] = true;
    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j <= w; ++j)
        {
            dp[i][j] = dp[i - 1][j]; //Мы рассмотрели предмет, но в рюкзак его не положили, поэтому вес рюкзака остался тот же что и в i - 1 строчке массива dp
            if (a[i] <= j && dp[i - 1][j - a[i]]) //проверяем что i-ый предмет в массиве a весит не больше веса j (вес который на данной итерации мы рассматриваем) и проверяем можем ли мы набрать вес j - a[i] рассмотрев i - 1 предметов
            {
                dp[i][j] = true;
            }

        }
    }

    int ans = 0;

    int ans_i = 0;
    int i = n - 1;
    for (int j = 0; j <= w; ++j)
    {
        if (j > ans && dp[i][j] == true) //Ответом будет максимальный j в строке n - 1(т.е. последней) (вес, который можем набрать в рюкзаке), такой чтобы dp[i][j] = true
        {
            ans = j;
            ans_i = i;
        }
    }

    //восстановление ответа
    int j = ans;
    while (j > 0)
    {
        if (dp[i - 1][j])
        {
            i--;
        }
        else {
            path.push_back(i);
            j -= a[i];
            i--;
        }
    }

    return ans;
}


//Перечислены предметы с весами хранящимися в массиве a. Определите, на какой максимальный вес можно набрать предметов в рюкзак вместимости веса W, если каждый предмет можно брать по многу раз
int task_rukzak2(vector<int> a, int w)
{
    int n = a.size();
    vector<int> dp(n + 1);
    dp[0] = true;
    for (int i = 1; i < n; ++i) // итерируемся по массиву предметов
    {
        for (int j = 0; j <= w; ++j) // перебираем значения веса который может выдержать рюкзак
        {
            if (j - a[i] >= 0)
            {
                dp[j] |= dp[j - a[i]];
            }
        }
    }
    return dp[n];
}


//1 51 25
/*банкомат содержит n купюр разных номиналов.Пользователь хочет снять сумму S.Если это возможно, 
необходимо вывести список купюр(количество купюр должно быть минимально возможным), которые дают нужную сумму, иначе надо написать, что выдача невозможна.*/



//Решение жадным алгоритмом
vector<int> bancomat(vector<int> a, int s)
{
    int cur = 0;
    int n = a.size();
    vector<int> ans;
    vector<bool> ind_used(n, 0);
    while (cur < s)
    {
        for (int i = 0; i < n; ++i)
        {
            if (cur + a[i] <= s && (!(ind_used[i])))
            {
                ans.push_back(a[i]);
                cur += a[i];
                ind_used[i] = true;
            }
        }
    }
    return ans;
}



int main()
{
    vector<int> k = { 1000, 800, 500, 100, 100, 100 };
    int s = 1300;
    vector<int> a = bancomat(k, s);
    for (auto elem : a)
    {
        cout << elem << " ";
    }
}