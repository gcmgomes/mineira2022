#include <iostream>
#include <string>

using namespace std;

char check(int g, string s){
    int calc = 0;
    int maxD = 0;
    int maxE = 0;
    
    for(int i=0; i<s.size(); i++){
      if(s[i] == 'D') calc += g;
      else calc -= g;
      
      maxD = max(maxD, calc);
      maxE = min(maxE, calc);
      if(maxD+abs(maxE)>=360) return 'S';
    }
    
    return 'N';
}

int main()
{
  int g;
  string s;
  
  cin >> g >> s;

  cout << check(g, s) << endl;

  return 0; 
        
}