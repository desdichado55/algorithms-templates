#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<int> path;
//���� n ��������� � ������ ����������� � ������� a. ����������, �� ����� ������������ ��� ����� ������� ��������� � ������ ����������� ���� W .
int task_rukzak(vector<int> a, int w)
{
    //w - ������� ��������� ������� ������
    //a - ������ ����� ���������
    int n = a.size();
    vector<vector<bool>> dp(n, vector<bool>(w + 1, false));
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
    vector<int> dp(n + 1);
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
    return dp[n];
}


//1 51 25
/*�������� �������� n ����� ������ ���������.������������ ����� ����� ����� S.���� ��� ��������, 
���������� ������� ������ �����(���������� ����� ������ ���� ���������� ���������), ������� ���� ������ �����, ����� ���� ��������, ��� ������ ����������.*/



//������� ������ ����������
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