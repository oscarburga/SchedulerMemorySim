#include <bits/stdc++.h>
#define forn(i, n) for (int i = 0; i<(int)n; ++i)
#define forr(i, t, n) for (int i = t; i<n; ++i)
#define rmod(x, y) (((x%y)+y)%y)
using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

//STRUCTS AND OPERATORS
//struct pag {int id, age;};
bool operator>(pag a, pag b) {
	if (a.r and not b.r) return true;
	else if (b.r and not a.r) return false;
	else return a.age>b.age;
}
bool operator<(pag a, pag b) {
	if (b.r and not a.r) return true;
	else if (a.r and not b.r) return false;
	else return a.age>b.age;
}

int cap, fs, hs;
queue<int> ids;
map<int, int> v;
void read()
{
	cin >> cap;
	int aux;
	while (cin >> aux) ids.push(aux);
}

#define its(v) v.begin(), v.end()
void updnru(int &id){
	for(auto&p:v) {
		if (p.first == id) p.second = 1;
		else p.second++;
	}
}
void nru() {
	cout << "***NOT RECENTLY USED***\n";
	int id;
	int last =-123;
	while(ids.size())
	{
		id = ids.front();
		ids.pop();
		if (id == last) continue;
		last = aux.id;
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	#ifndef LOCAL
		cout << "WARNING: Wrong input format causes undefined behavior.\n";
		cout << "WARNING: Wrong file name  causes undefined behavior.\n";
		cout << "Input file name (include file ext, no spaces allowed):\n";
		cout << "Example: input.txt\nFile name: ";
		string fl;
		cin >> fl;
		freopen(fl.c_str(), "r", stdin);
		freopen("MEMORY_OUTPUT.TXT", "w", stdout);
	#endif
	string opt;
	cin >> opt;
	if (opt == "NRU") nru();
	else if (opt == "FIFO") fifo();
	else if (opt == "LRU") lru();
	else cout << "INVALID OPTION";
	return 0;
}