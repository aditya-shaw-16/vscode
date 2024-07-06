#include <iostream>
using namespace std;
int main()
{
    int m, n, i, j, k;
    n = 4;
    m = 3;

    int alloc[4][3] = {{1, 2, 3},
                       {0, 3, 4},
                       {2, 4, 6},
                       {3, 5, 7}};

    int max[4][3] = {{5, 6, 7},
                     {3, 5, 7},
                     {6, 7, 8},
                     {7, 8, 9}};

    int available[3] = {8, 8, 9};
    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++)
    {
        f[k] = 0;
    }
    int need[n][m];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }                                                                                                                                                                                                            
    int y = 0;
    for (k = 0; k < 4; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {

                int flag = 0;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        available[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    int flag = 1;

    for (int i = 0; i < n; i++)
    {
        if (f[i] == 0)
        {
            flag = 0;
            cout<<"The given sequence is not safe";
            break;
        }
    }

    if (flag == 1)
    {
        cout << "The following sequence is safe: "<<endl;
        for (i = 0; i < n - 1; i++)
        cout <<" P"<<ans[i]<<" -> ";
        cout <<" P"<<ans[n - 1]<<endl;
    }

    return (0);
}
 