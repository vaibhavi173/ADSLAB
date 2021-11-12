#include <bits/stdc++.h>
using namespace std;

class Disjointsets
{
     
    vector<int> rank, parent;
    int n;
     
    public:
    Disjointsets(int n)
    {
        rank.resize(n);
        parent.resize(n);
        this->n = n;
        makeSet();
    }
 
    void makeSet()
    {
      
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
 
    
    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x]=find(parent[x]);
        }
 
        return parent[x];
    }
 
    
    void Union(int x, int y)
    {
        
        int xR = find(x);
        int yR = find(y);
 
     
        if (xR == yR)
            return;
 
        if (rank[xR] < rank[yR])
            parent[xR] = yR;
 
        else if (rank[yR] < rank[xR])
            parent[yR] = xR;
 
        else 
        {
            parent[yR] = xR;
            rank[xR] = rank[xR] + 1;
        }
    }
};
 

int countIslands(vector<vector<int>>a)
{
    int n = a.size();
    int m = a[0].size();
 
    Disjointsets *dus = new Disjointsets(n * m);
 
    for (int j = 0; j < n; j++)
    {
        for (int k = 0; k < m; k++)
        {
            
            if (a[j][k] == 0)
                continue;
 
            
            if (j + 1 < n && a[j + 1][k] == 1)
                dus->Union(j * (m) + k,
                          (j + 1) * (m) + k);
            if (j - 1 >= 0 && a[j - 1][k] == 1)
                dus->Union(j * (m) + k,
                          (j - 1) * (m) + k);
            if (k + 1 < m && a[j][k + 1] == 1)
                dus->Union(j * (m) + k,
                          (j) * (m) + k + 1);
            if (k - 1 >= 0 && a[j][k - 1] == 1)
                dus->Union(j * (m) + k,
                          (j) * (m) + k - 1);
            if (j + 1 < n && k + 1 < m &&
                    a[j + 1][k + 1] == 1)
                dus->Union(j * (m) + k,
                          (j + 1) * (m) + k + 1);
            if (j + 1 < n && k - 1 >= 0 &&
                    a[j + 1][k - 1] == 1)
                dus->Union(j * m + k,
                          (j + 1) * (m) + k - 1);
            if (j - 1 >= 0 && k + 1 < m &&
                     a[j - 1][k + 1] == 1)
                dus->Union(j * m + k,
                          (j - 1) * m + k + 1);
            if (j - 1 >= 0 && k - 1 >= 0 &&
                     a[j - 1][k - 1] == 1)
                dus->Union(j * m + k,
                          (j - 1) * m + k - 1);
        }
    }
 

    int *dup = new int[n * m];
    int noIslands = 0;
    for (int j = 0; j < n; j++)
    {
        for (int k = 0; k < m; k++)
        {
            if (a[j][k] == 1)
            {
                int x = dus->find(j * m + k);
 
                
                if (dup[x] == 0)
                {
                    noIslands++;
                    dup[x]++;
                }
 
                else
                    dup[x]++;
            }
        }
    }
    return noIslands;
}
 

int main()
{   
    int size;
    cout << "Enter the size of 2D matrix : " ;
    cin >> size;
    vector<vector<int>>a;
    for(int i=0 ; i<size; i++)
    { 
      vector<int> v1;
      for(int j=0; j<size; j++)
      {
        v1.push_back()
      }
    }
    vector<vector<int>>a = {{1, 1, 0, 0, 0},
                            {0, 1, 0, 0, 1},
                            {1, 0, 0, 1, 1},
                            {0, 0, 0, 0, 0},
                            {1, 0, 1, 0, 1}};
    cout << "Number of Islands is: "
         << countIslands(a) << endl;
    
    return 0;
}
 
