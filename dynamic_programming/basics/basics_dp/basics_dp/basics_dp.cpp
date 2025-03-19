// dynamic_programming1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include <iostream>
using namespace std;

#define f false

//Наивная рекурсия, числа фибоначи
int fib1(int n)
{
    if (n < 0)
    {
        return 0;
    }
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else {
        return fib1(n - 1) + fib1(n - 2);
    }
}




//Рекурсия с мемоизацией или ленивая динамика
int fib2(int n, vector<int> dp)
{
    if (dp[n] == -1)
    {
        dp[n] = fib2(n - 1, dp) + fib2(n - 2, dp);
    }
    return dp[n];
}


/*Кузнечик прыгает на 1 или 2 кочки. Сколько способов добраться до кончки n?*/
int cricket(int n)
{
    vector<int> dp(n, -1);
    dp[0] = 1, dp[1] = 1;
    for (int i = 2; i < n; ++i)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n - 1];
}


vector<int> path;
//Даны n предметов с весами хранящимися в массиве a. Определите, на какой максимальный вес можно набрать предметов в рюкзак вместимости веса W .
int task_rukzak(vector<int> a, int w)
{
    //w - сколько предметов вмещвет рюкзак
    //a - список весов предметов
    int n = a.size();
    vector<vector<bool>> dp(n, vector<bool> (w+1, f));
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
    vector<int> dp(n+1);
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
}


int main()
{
    
    vector<int> a = { 0, 3, 4, 2, 1 };
    int w = 8;
    cout << task_rukzak(a, w) << endl;
    for (int i = 0; i < path.size(); ++i)
    {
        cout << path[i] << endl;
    }
    
}
