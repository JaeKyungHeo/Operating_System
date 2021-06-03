#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef struct
{
	int Arrival;
	int Burst;
	string Name;
}Process;

bool compare1(Process a, Process b) {
	if (a.Arrival == b.Arrival) {
		return a.Burst < b.Burst;
	}
	else {
		return a.Arrival < b.Arrival;
	}
}

bool compare2(Process a, Process b) {
	if (a.Arrival<0 && b.Arrival<0) {
		return a.Burst < b.Burst;
	}
	else if (a.Arrival >= 0 && b.Arrival >= 0) {
		if (a.Arrival == b.Arrival) {
			return a.Burst < b.Burst;
		}
		else {
			return a.Arrival < b.Arrival;
		}
	}
	else {
		return a.Arrival < b.Arrival;
	}
}

void FCFS(vector<Process> Process, queue<string>& Progress, float& AWT) {
	sort(Process.begin(), Process.end(), compare1);
	float total = 0, ans = 0;
	for (int i = 0; i < Process.size(); i++) {
		Progress.push(Process[i].Name);
		if(total - Process[i].Arrival>0)
			ans += total - Process[i].Arrival;
		total += Process[i].Burst;
	}
	AWT = ans / Process.size();
}

void SJF(vector<Process> Pro, queue<string>& Progress, float& AWT) {
	int complete_count = 0, Process_num = Pro.size(), total = 0;
	sort(Pro.begin(), Pro.end(), compare1);
	string pre = Pro[0].Name;
	Progress.push(pre);
	while (complete_count != Process_num) {
		for (int i = 0; i < Pro.size(); i++) {
			Pro[i].Arrival--;
		}
		for (int i = 0; i < Pro.size(); i++) {
			if (Pro[i].Arrival < 0)
				total++;
		}
		total--;//현재 수행중인 것 하나 빼줌
		sort(Pro.begin(), Pro.end(), compare2);
		Pro[0].Burst--;
		if (Pro[0].Name != pre) {
			pre = Pro[0].Name;
			Progress.push(pre);
		}
		//burst time이 끝난 프로세스 빼주기
		if (Pro[0].Burst == 0) {
			Pro.erase(Pro.begin());
			complete_count++;
		}
	}
	AWT = 1.0 * total / Process_num;
}

void RR(vector<Process> Pro, queue<string>& Progress, float& AWT) {
	int complete_count = 0, Process_num = Pro.size(), total_wait = 0;
	sort(Pro.begin(), Pro.end(), compare1);
	string pre = Pro[0].Name;
	queue<Process>ready, wait;
	Progress.push(pre);
	ready.push(Pro[0]);
	while (complete_count != Process_num) {
		for (int k = 0; k < 3; k++) {
			for (int i = 0; i < Pro.size(); i++) {
				Pro[i].Arrival--;
			}
			for (int i = 0; i < Pro.size(); i++) {
				if (Pro[i].Arrival == 0)
					ready.push(Pro[i]);
				if (Pro[i].Arrival < 0) {
					total_wait++;
				}
			}
			total_wait--;
			if (wait.empty()&&!ready.empty()) {
				wait.push(ready.front());
				ready.pop();
				if (wait.front().Name != pre) {
					pre = wait.front().Name;
					Progress.push(pre);
				}
			}
			bool check = false;
			for (int i = 0; i < Pro.size(); i++) {
				if (wait.front().Name == Pro[i].Name) {
					Pro[i].Burst--;
					if (Pro[i].Burst == 0) {//예외처리
						Pro.erase(Pro.begin() + i);
						complete_count++;
						wait.pop();
						check = true;
						break;

					}
				}
			}
			if (check)
				break;
		}
		if (!wait.empty()) {
			ready.push(wait.front());
			wait.pop();
		}
	}
	AWT = 1.0 * total_wait / Process_num;
}


int main() {
	float AWT_FCFS, AWT_SJF, AWT_RR;
	queue<string> Progress_FCFS, Progress_SJF, Progress_RR;
	Process P[6];
	vector<Process> Process;

	P[0].Name = "P1";
	P[0].Arrival = 0;
	P[0].Burst = 10;
	P[1].Name = "P2";
	P[1].Arrival = 3;
	P[1].Burst = 12;
	P[2].Name = "P3";
	P[2].Arrival = 7;
	P[2].Burst = 4;
	P[3].Name = "P4";
	P[3].Arrival = 10;
	P[3].Burst = 6;
	P[4].Name = "P5";
	P[4].Arrival = 14;
	P[4].Burst = 8;
	P[5].Name = "P6";
	P[5].Arrival = 15;
	P[5].Burst = 7;

	for (int i = 0; i < 6; i++)
		Process.push_back(P[i]);
	//FCFS
	FCFS(Process, Progress_FCFS, AWT_FCFS);
	cout << "FCFS" << "\n";
	cout << "Process Progress : ";
	while (!Progress_FCFS.empty()) {
		cout << Progress_FCFS.front() << " ";
		Progress_FCFS.pop();
	}
	cout << "\n";
	cout << "Average Waiting Time : " << AWT_FCFS << "\n\n";
	//SJF
	SJF(Process, Progress_SJF, AWT_SJF);
	cout << "SJF" << "\n";
	cout << "Process Progress : ";
	while (!Progress_SJF.empty()) {
		cout << Progress_SJF.front() << " ";
		Progress_SJF.pop();
	}
	cout << "\n";
	cout << "Average Waiting Time : " << AWT_SJF << "\n\n";
	//RR
	RR(Process, Progress_RR, AWT_RR);
	cout << "RR" << "\n";
	cout << "Process Progress : ";
	while (!Progress_RR.empty()) {
		cout << Progress_RR.front() << " ";
		Progress_RR.pop();
	}
	cout << "\n";
	cout << "Average Waiting Time : " << AWT_RR << "\n\n";

	return 0;
}