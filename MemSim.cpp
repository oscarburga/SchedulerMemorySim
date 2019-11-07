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
/*
struct pag{};
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
*/
int cap, fault, hit;
queue<int> ids;

void read()
{
	cin >> cap;
	int aux;
	while (cin >> aux) ids.push(aux);
}

#define its(v) v.begin(), v.end()
bool compnru(pii a, pii b) { return a.second<b.second; }
void updnru(int &id, map<int, int>&m){
	if (m.count(id)){	
		cout << "Hit (ID: " << id << ") || H: " << ++hit << " - F: " << fault <<"\n";
		for(auto&p:m) {
			if (p.first == id) p.second = 1;
			else p.second++;
		}
	} else {
		cout << "Fault (ID: " << id << ") || H: " << hit << " - F: " << ++fault <<"\n";
		if (m.size()>=cap) {
				auto it = max_element(m.begin(), m.end(), compnru);
				cout << "Erasing oldest element (ID: " << (*it).first << " - Age: " << (*it).second << ")\n";
				m.erase((*it).first);
			}
			m[id] = 0;
			for(auto&p:m) p.second++;
	}
	cout << "Current IDs with ages:\n";
	for(auto&p:m) cout << "\tID: " << p.first << " - Age: " << p.second << "\n";
		cout << "\n";
}
void nru() {
	cout << "***NOT RECENTLY USED***\n";
	map<int, int> m;
	
	int id;
	int last =-123;
	while(ids.size()) {
		id = ids.front();
		ids.pop();
		if (id == last) {
			cout << "Hit (ID: " << id << ") || H: " << ++hit << " - F: " << fault << " - Same ID as last\n";
			cout << "\tNo changes.\n\n";
			continue;
		} else updnru(id, m);
		last = id;
	}
}
void fifo(){
	
}
void lru() {
	map<int, pii> m;


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
	read();
	if (opt == "NRU") nru();
	else if (opt == "FIFO") fifo();
	else if (opt == "LRU") lru();
	else cout << "INVALID OPTION";
	return 0;
}