#include <iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

vector<int> arr[10010];
vector<int> longest;
vector<int> temp;
int n;

bool isSmall() {
    for (int i = 0; i < min(longest.size(), temp.size()); i++)
    {
        if (temp[i] < longest[i])return true;
    }
    return false;
}

void dfs(int idx, int cnt)
{
    if (idx >= n)return;
    if (arr[idx].size() == 0)//结束条件
    {
        if (cnt > longest.size())
        {
            longest = temp;
        }
        else if (cnt == longest.size() && isSmall())
        {
            longest = temp;
        }
        return;
    }

    for (int i = 0; i < arr[idx].size(); i++)
    {
        temp.push_back(arr[idx][i]);
        dfs(arr[idx][i], cnt + 1);
        temp.pop_back();
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        while (k--)
        {
            int t;
            cin >> t;
            arr[i].push_back(t);
        }

    }

    for (int i = 0; i < n; i++)
    {
        temp.clear();
        temp.push_back(i);
        dfs(i, 1);
    }

    cout << longest.size()<<endl;
    for (int i = 0; i < longest.size(); i++)
    {
        cout << longest[i] << " ";
    }

    return 0;
}
