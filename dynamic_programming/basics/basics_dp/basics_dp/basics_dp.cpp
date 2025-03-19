// dynamic_programming1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include <iostream>
using namespace std;

#define f false

//������� ��������, ����� ��������
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




//�������� � ����������� ��� ������� ��������
int fib2(int n, vector<int> dp)
{
    if (dp[n] == -1)
    {
        dp[n] = fib2(n - 1, dp) + fib2(n - 2, dp);
    }
    return dp[n];
}


/*�������� ������� �� 1 ��� 2 �����. ������� �������� ��������� �� ������ n?*/
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
//���� n ��������� � ������ ����������� � ������� a. ����������, �� ����� ������������ ��� ����� ������� ��������� � ������ ����������� ���� W .
int task_rukzak(vector<int> a, int w)
{
    //w - ������� ��������� ������� ������
    //a - ������ ����� ���������
    int n = a.size();
    vector<vector<bool>> dp(n, vector<bool> (w+1, f));
    //dp[pref][w] - ����� �� ����������� ������ pref ��������� � ������� ��� W � ������� (true/false)
    dp[0][0] = true;
    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j <= w; ++j)
        {
            dp[i][j] = dp[i - 1][j]; //�� ����������� �������, �� � ������ ��� �� ��������, ������� ��� ������� ������� ��� �� ��� � � i - 1 ������� ������� dp
            if (a[i] <= j && dp[i - 1][j - a[i]]) //��������� ��� i-�� ������� � ������� a ����� �� ������ ���� j (��� ������� �� ������ �������� �� �������������) � ��������� ����� �� �� ������� ��� j - a[i] ���������� i - 1 ���������
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
        if (j > ans && dp[i][j] == true) //������� ����� ������������ j � ������ n - 1(�.�. ���������) (���, ������� ����� ������� � �������), ����� ����� dp[i][j] = true
        {
            ans = j;
            ans_i = i;
        }
    }
    
    //�������������� ������
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


//����������� �������� � ������ ����������� � ������� a. ����������, �� ����� ������������ ��� ����� ������� ��������� � ������ ����������� ���� W, ���� ������ ������� ����� ����� �� ����� ���
int task_rukzak2(vector<int> a, int w)
{
    int n = a.size();
    vector<int> dp(n+1);
    dp[0] = true;
    for (int i = 1; i < n; ++i) // ����������� �� ������� ���������
    {
        for (int j = 0; j <= w; ++j) // ���������� �������� ���� ������� ����� ��������� ������
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
