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
struct pr { int id, bt, at;}; // FIFO, SJF
struct prr { //RR
	int id, bt, at, wt = -1, ct = -1;
	void WT(int time) { if (wt == -1) wt = time; }
	void CT(int time) { if (bt == 0 and ct == -1) ct = time; }
};
bool operator>(pr a, pr b){	return a.bt>b.bt;}
bool operator<(pr a, pr b){ return a.bt<b.bt;}
bool operator>(prr a, prr b){ return a.bt>b.bt; }
bool operator<(prr a, prr b){ return a.bt<b.bt; }
bool atcompFF(pr a, pr b){ return a.at>b.at;}
bool atcompRR(prr a, prr b){ return a.at>b.at;}
bool atcompSJF(pr a, pr b) {
	if (a.at==b.at)	return a.bt>b.bt;
	else return a.at>b.at;
}
ostream& operator << (ostream &out, pr& a) {
	out << "ID: " << a.id << " - BT: " << a.bt << " - AT: " << a.at << " ";
	return out;
}
ostream& operator << (ostream &out, prr& a) {
	out << "ID: " << a.id << " - BT: " << a.bt << " - AT: " << a.at << " ";
	return out;
}


//GLOBALS
vector<pr> procesos;
int timer, awt, act, tat, tq;

//FUNCTIONS
void read() {
	int a, b, id = 1;
	while (cin >> a >> b)
	 	procesos.push_back({id++, abs(a), abs(b)});
}
void printp(pr& aux, int& timer) { //FIFO, SJF
	cout << aux << "\n\t Starts at: " << timer;
	timer+= aux.bt;
	cout << " - Ends at: " << timer;
	cout << "\n\n";
}
void printpp(prr &aux, int& timer, int tq) { //RR
	cout << aux << "\n\t Starts at: " << timer;
	aux.WT(timer);
	if (tq>aux.bt) {
		timer+= aux.bt;
		aux.bt = 0;
	}
	else {
		timer+= tq;
		aux.bt-=tq;
	}
	cout << " - Ends at: " << timer << " - Remaining: " << aux.bt;
	aux.CT(timer);
	cout << "\n\n";
}

void fifo() {
	cout << "***FIRST IN FIRST OUT***\n\n";
	read();
	pr aux;
	priority_queue<pr, vector<pr>, function<bool(pr, pr)>> arriving(atcompFF);
	for(auto&p: procesos) {
		if (p.at == 0) {
				awt+=timer;
				printp(p, timer);
				act+=timer;
			}
		else arriving.push(p);
	}
	while (arriving.size())	{
		aux = arriving.top();
		if (aux.at>timer)timer=aux.at;
		awt+=(timer-aux.at);
		printp(aux, timer);
		act+=(timer-aux.at);
		arriving.pop();
	}
	cout << "AWT: " << double(awt/(procesos.size()*1.00))  << "\n";
	cout << "ACT: " << double(act/(procesos.size()*1.00));
}
void sjf() {
	cout << "***SHORTEST JOB FIRST***\n\n";
	read();
	pr aux;
	priority_queue<pr, vector<pr>, function<bool(pr, pr)>> arriving(atcompSJF);
	priority_queue<pr, vector<pr>, greater<pr>> procs;
	for(auto&p:procesos) {
			if (p.at == 0) procs.push(p);
			else arriving.push(p);
		}
	while (procs.size() or arriving.size())	{
		while (procs.size()) {
			aux = procs.top();
			procs.pop();
			printp(aux, timer);
			while (arriving.size() and arriving.top().at<=timer) {
				procs.push(arriving.top());
				arriving.pop();
			}
		}
		if (arriving.size() and not procs.size()) {
			procs.push(arriving.top());
			if (arriving.top().at>timer) timer = arriving.top().at; 
			arriving.pop();
		}
	}
}
void rr() {
	cout << "***ROUND ROBIN - FIXED TIME QUANTUM***\n";
	cin >> tq;
	cout << "***\t\t   TIME QUANTUM: " << tq << "\t\t   ***\n\n";
	read();
	prr aux;
	priority_queue<prr, vector<prr>, function<bool(prr, prr)>> arriving(atcompRR);
	queue<prr> procs, next;
	vector<prr> finished;
	int round = 1;
	for(auto&p: procesos) {
		if (p.at == 0) procs.push({p.id, p.bt, p.at});
		else arriving.push({p.id, p.bt, p.at});
	}
	while (procs.size() or arriving.size())	{
		while (procs.size()) {
			aux = procs.front();
			procs.pop();
			printpp(aux, timer, tq);
			if (aux.bt>0) next.push(aux);
			else finished.emplace_back(aux);
			while (arriving.size() and arriving.top().at<=timer) {
				procs.push(arriving.top());
				arriving.pop();
			}
		}
		while (next.size())	{
			procs.push(next.front());
			next.pop();
		}
		cout << "***END OF ROUND " << round << "***\n\n";
		round++;
		if ((not procs.size()) and arriving.size() and arriving.top().at > timer) {
			procs.push(arriving.top());
			timer = arriving.top().at;
			arriving.pop();
		}  
	}
	for(auto&p: finished) {
		awt+= p.wt-p.at;
		act+= p.ct-p.at;
	}
	cout << "AWT: " << double(awt/(procesos.size()*1.00))  << "\n";
	cout << "ACT: " << double(act/(procesos.size()*1.00));
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
		freopen("SCHEDULER_OUTPUT.TXT", "w", stdout);
	#endif
	string opt;
	cin >> opt;
	if (opt == "SJF") sjf();
	else if (opt == "FIFO") fifo();
	else if (opt == "RR") rr();
	else cout << "INVALID OPTION";
	return 0;
}