#include <iostream>
#include <string>

using namespace std;

int solve(string s){
    int carga = 1, result = 0;
    bool pulando = false;
  
    for(int i=0; i<s.size(); i++){
      
      if(!pulando){
        if(s[i] == 'x') carga++;
        else{ 
            carga--;
            pulando = true;
            result++;
        }
      }
      else{
          if(s[i] == 'x'){
              carga = 1;
              pulando = false;
          }
          else carga--;
      }
      
      if(carga<0) return -1;
  }
   return result;
}

int main()
{
  int n;
  string s;
  cin >> n >> s;
  
  if(s[0]=='.') cout << "-1" << endl;
  else cout << solve(s) << endl;
  
  return 0; 
        
}