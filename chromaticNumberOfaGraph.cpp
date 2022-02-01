#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class rijesi
{
public:
   int n;
   vector<vector<int>> matrix;
   vector<int> x;
   int m;
   rijesi(int n, vector<vector<int>> matrix, vector<int> x, int m) : n(n), matrix(matrix), x(x), m(m) {}

   bool boja(int k)
   {
      if (k == n)
         return true;
      for (int c = 1; c <= m; c++)
      {
         if (moze(k, c))
         {
            x[k] = c;
            if (boja(k + 1))
               return true;

            x[k] = 0;
         }
      }
      return false;
   }
   bool moze(int k, int c)
   {
      for (int i = 0; i < n; i++)
      {
         if (matrix[k][i] == 1 && c == x[i])
         {
            return false;
         }
      }
      return true;
   }
};

int main(void)
{
   int n, s;
   vector<vector<int>> matrix;
   string file, contents;
   vector<string> prebaci;
   vector<int> content;
   vector<int> boje;
   ifstream myfile;
   cout << "Unesite ime datoteke: ";
   cin >> file;
   myfile.open(file);
   if (myfile.is_open())
   {
      while (myfile.good())
      {
         myfile >> contents;
         prebaci.push_back(contents);
      }
   }
   myfile.close();
   n = stoi(prebaci[0]);
   s = stoi(prebaci[1]);
   for (int i = 2; i < prebaci.size(); i++)
      content.push_back(stoi(prebaci[i]));

   for (int i = 0; i < n; i++)
   {
      vector<int> pom;
      for (int j = 0; j < n; j++)
      {
         pom.push_back(0);
      }
      matrix.push_back(pom);
   }
   for (int i = 0; i < n; i++)
   {
      boje.push_back(0);
      for (int j = 0; j < n; j++)
      {
         for (int k = 0; k < s; k++)
            if (content[k] == abs(i - j))
               matrix[i][j] = 1;
      }
   }
   for (int i = 1; i < 21; i++)
   {
      rijesi a = rijesi(n, matrix, boje, i);
      if (a.boja(0))
      {
         cout << "Kromatski broj zadanog grafa je " << i;
         break;
      }
   }

   return 0;
}