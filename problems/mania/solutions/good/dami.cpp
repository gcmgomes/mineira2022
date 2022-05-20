#include <iostream>
#include <string>

using namespace std;

int main(){
	
	int g, dir = 0, max_d = 0, min_e = 0;
	string s;
	
	cin >> g >> s;
	
	for(int i=0; i<s.size(); i++){
		if(s[i] == 'D'){
			dir += g;
			max_d = max(dir, max_d);
		}
		else{
			dir -= g;
			min_e = min(dir, min_e);
		}
	}
	
	if(abs(min_e) + max_d >= 360) cout << "S\n";
	else cout << "N\n";
	
	return 0;
}
