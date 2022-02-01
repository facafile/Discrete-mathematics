#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> napuni(int n, int a, int b)
{
   vector<vector<int>> matrix(n, vector<int>(n));
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < n; j++)
      {
         if (i == j)
            matrix[i][j] = 0;
         else if (i < j)
            matrix[i][j] = (a * (i + 1) + b * (j + 1)) * (a * (i + 1) + b * (j + 1)) + 1;
         else
            matrix[i][j] = (a * (j + 1) + b * (i + 1)) * (a * (j + 1) + b * (i + 1)) + 1;
      }
   }
   return matrix;
}

int bruteforce(vector<vector<int>> matrix, int n)
{
   int source = 0;
   vector<int> nodes;
   for (int i = 0; i < n; i++)
   {
      if (i != source)
      {
         nodes.push_back(i);
      }
   }
   int m = nodes.size();
   int shortest_path = INT_MAX;
   while (next_permutation(nodes.begin(), nodes.end()))
   {
      int path_weight = 0;

      int j = source;
      for (int i = 0; i < m; i++)
      {
         path_weight += matrix[j][nodes[i]];
         j = nodes[i];
      }
      path_weight += matrix[j][source];

      shortest_path = min(shortest_path, path_weight);
   }
   return shortest_path;
}
int greedyA(vector<vector<int>> matrix)
{
   int sum = 0;
   int i, j;
   int mini = INT_MAX;
   int arr[matrix.size()];

   for (int x = 0; x < matrix.size(); x++)
      arr[x] = 0;

   for (int x = 0; x < matrix.size(); x++)
   {
      for (int y = 0; y < matrix[x].size(); y++)
      {
         if (matrix[x][y] < mini && x != y)
         {
            mini = matrix[x][y];
            i = x;
            j = y;
         }
      }
   }
   arr[i] = 1;
   arr[j] = 1;
   sum += mini;

   for (int x = 0; x < matrix.size() - 2; x++)
   {
      int a = 0;
      int b = 0;
      int min1 = INT_MAX;
      int min2 = INT_MAX;
      for (int y = 0; y < matrix[0].size(); y++)
      {
         if (arr[y] != 0)
            continue;
         if (i != y)
         {
            if (matrix[i][y] < min1)
            {
               min1 = matrix[i][y];
               a = y;
            }
         }
         if (j != y)
         {
            if (matrix[j][y] < min2)
            {
               min2 = matrix[j][y];
               b = y;
            }
         }
      }

      if (min1 <= min2)
      {
         i = a;
         arr[i] = 1;
         sum += min1;
      }
      else
      {
         j = b;
         arr[j] = 1;
         sum += min2;
      }
   }
   sum += matrix[i][j];
   return sum;
}
int main()
{
   int a, b, n, brute, greedy;
   cout << "Unesite redom, odvojene razmakom, parametre n, a i b: ";
   cin >> n >> a >> b;
   cout << "\n";
   vector<vector<int>> matrix = napuni(n, a, b);

   brute = bruteforce(matrix, n);
   greedy = greedyA(matrix);

   cout << "Pohlepni algoritam nalazi ciklus duljine " << greedy << endl;
   cout << "Iscrpni algoritam nalazi ciklus duljine " << brute << endl;
   cout << "\n";
   if (greedy <= brute)
      cout << "Pohlepni algoritam na ovom grafu daje optimalno rjesenje!\n ";
   else
      cout << "Pohlepni algoritam na ovom grafu ne daje optimalno rjesenje! \n";
   cout << "\n";
   return 0;
}