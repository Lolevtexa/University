#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int main()
{
    vector<int> vec = {1, 2, 3, 5, -10};
    int n = vec.size();
    int min = 0;  
  int buf = 0; 
  for (int i = 0; i < n; i++) 
  { 
   min = i; 
   for (int j = i + 1; j < n; j++) 
    min = (vec[j] < vec[min]) ? j : min; 
   if (i != min) 
   { 
    buf = vec[i]; 
    vec[i] = vec[min]; 
    vec[min] = buf; 
   } 
  } 
  cout << "\nПосле сортировки: "; 
 
  for (int i = 0; i < n; i++) { 
   cout << vec[i] << " "; 
  } 
    
}
