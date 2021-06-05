#include <iostream>
#include <queue>
using namespace std;

struct process {
	string name;
	int Max_A;
	int Max_B;
	int Max_C;
	int Max_D;
	int Al_A;
	int Al_B;
	int Al_C;
	int Al_D;
};

struct available {
	int A;
	int B;
	int C;
	int D;
};

bool Is_safe_state(queue<process> pro, available Ava, queue<string>& complete) {
	int count = 0;
	int max;
	while (!pro.empty()) {
		max = pro.size();
		process temp = pro.front();
		pro.pop();
		if (temp.Max_A - temp.Al_A - Ava.A <= 0 && temp.Max_B - temp.Al_B - Ava.B <= 0 && temp.Max_C - temp.Al_C - Ava.C <= 0 && temp.Max_D - temp.Al_D - Ava.D <= 0) {
			complete.push(temp.name);
			Ava.A += temp.Al_A;
			Ava.B += temp.Al_B;
			Ava.C += temp.Al_C;
			Ava.D += temp.Al_D;
			count = 0;
		}
		else {
			pro.push(temp);
			count++;
		}
		if (count == max) return false;
	}
	return true;
}

void request(process& p, available& Ava, int a, int b, int c, int d) {
	p.Al_A += a;
	p.Al_B += b;
	p.Al_C += c;
	p.Al_D += c;
	Ava.A -= a;
	Ava.B -= b;
	Ava.C -= c;
	Ava.D -= d;
}

int main() {
	queue<string> complete;
	queue<process> pro;

	available Ava = { 3,2,1,1 };
	process P0 = { "P0",6,0,1,2,4,0,0,1 };
	process P1 = { "P1",1,7,5,0,1,1,0,0 };
	process P2 = { "P2",2,3,5,6,1,2,5,4 };
	process P3 = { "P3",1,6,5,3,0,6,3,3 };
	process P4 = { "P4",1,6,5,6,0,2,1,2 };

	pro.push(P0);
	pro.push(P1);
	pro.push(P2);
	pro.push(P3);
	pro.push(P4);
	
	cout << "Term_Project3_1" << endl;

	if (Is_safe_state(pro, Ava, complete) == true) {
		cout << "The System is safe state." << endl;
		cout << "Safe squence : ";
		while (!complete.empty()) {
			if (complete.size() != 1)
				cout << complete.front() << " -> ";
			else
				cout << complete.front();
			complete.pop();
		}
	}
	else {
		cout << "The System is unsafe state." << endl;
	}
	cout << endl << endl;

	cout << "Term_Project3_2(request for (1,2,0,0) by P4)" << endl;

	request(P4, Ava, 1, 2, 0, 0);

	pro.push(P0);
	pro.push(P1);
	pro.push(P2);
	pro.push(P3);
	pro.push(P4);

	if (Is_safe_state(pro, Ava, complete) == true) {
		cout << "The System is safe state." << endl;
		cout << "Safe squence : ";
		while (!complete.empty()) {
			if (complete.size() != 1)
				cout << complete.front() << " -> ";
			else
				cout << complete.front();
			complete.pop();
		}
	}
	else {
		cout << "The System is unsafe state." << endl;
	}

	return 0;
}