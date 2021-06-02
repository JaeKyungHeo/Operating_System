#include <iostream>
#include <queue>
using namespace std;

struct PCB {
	string Name = "";
	string PID = "";//Process number
	string Pointer = "";//다음 프로세스의 주소저장
	string Process_Status = "";
};

void Admitted(PCB& state) {
	state.Process_Status = "Ready";
	state.Pointer = "";
}

void Dispatch(PCB& state){
	state.Process_Status = "Running";
	state.Pointer = "";
}

void Wait(PCB& state){
	state.Process_Status = "Waiting";
	state.Pointer = "";
}

void Completion(PCB& state) {
	state.Process_Status = "Ready";
	state.Pointer = "";
}

void Exit(PCB& state){
	state.Process_Status = "Terminated";
	state.Pointer = "";
}

int Process() {
	int N;
	cout << "1. Admitted." << "\n";
	cout << "2. Dispatch." << "\n";
	cout << "3. I/O or Event Occurrence." << "\n";
	cout << "4. I/O or Event Completion." << "\n";
	cout << "5. Exit." << "\n";
	cin >> N;
	cout << "\n";
	return N;
}

int main() {
	queue<PCB>CPU, Job_Queue, SubJob_Queue, Ready_Queue, Device_Queue, Sub;
	PCB PCB1, PCB3, PCB4;
	PCB1.Name = "PCB1", PCB1.PID = "001",PCB1.Pointer = "001", PCB3.Name = "PCB3", PCB3.PID = "003", PCB3.Pointer = "003", PCB4.Name = "PCB4", PCB4.PID = "004", PCB4.Pointer = "004";
	Job_Queue.push(PCB1);
	Job_Queue.push(PCB3);
	Job_Queue.push(PCB4);
	SubJob_Queue.push(PCB1);
	SubJob_Queue.push(PCB3);
	SubJob_Queue.push(PCB4);

	cout << ">>Start \n";
	while (!CPU.empty() || !Job_Queue.empty() || !Ready_Queue.empty() || !Device_Queue.empty()) {

		//현재 전체 프로세스상황 출력 -> 각각의PCB(PCB 포인터가 가리키는 주소의 PCB 표시) 형태로 나타난다.
		cout << "CPU(Running) : ";
		while (!CPU.empty()) {
			Sub.push(CPU.front());
			cout << CPU.front().Name << "(" << CPU.front().Pointer << ")" << " ";
			CPU.pop();
		}
		while (!Sub.empty()) {
			CPU.push(Sub.front());
			Sub.pop();
		}
		cout << "\n";
		cout << "Ready Queue(Ready) : ";
		while (!Ready_Queue.empty()) {
			Sub.push(Ready_Queue.front());
			cout << Ready_Queue.front().Name << "(" << Ready_Queue.front().Pointer << ")" << " ";
			Ready_Queue.pop();
		}
		while (!Sub.empty()) {
			Ready_Queue.push(Sub.front());
			Sub.pop();
		}
		cout << "\n";
		cout << "Device Queue(Wait) : ";
		while (!Device_Queue.empty()) {
			Sub.push(Device_Queue.front());
			cout << Device_Queue.front().Name << "(" << Device_Queue.front().Pointer << ")" << " ";
			Device_Queue.pop();
		}
		while (!Sub.empty()) {
			Device_Queue.push(Sub.front());
			Sub.pop();
		}
		cout << "\n";
		cout << "Job Queue : ";
		while (!SubJob_Queue.empty()) {
			Sub.push(SubJob_Queue.front());
			cout << SubJob_Queue.front().Name << "(" << SubJob_Queue.front().Pointer << ")" << " ";
			SubJob_Queue.pop();
		}
		while (!Sub.empty()) {
			SubJob_Queue.push(Sub.front());
			Sub.pop();
		}
		cout << "\n\n";

		//현재 수행할 과정입력
		int ans = Process();
		if (ans == 1) {
			if (!Job_Queue.empty()) {
				if(!Ready_Queue.empty())
					Ready_Queue.back().Pointer = Job_Queue.front().PID;
				Admitted(Job_Queue.front());
				cout << "#" << Job_Queue.front().Name << "-PID" << Job_Queue.front().PID << " " << Job_Queue.front().Process_Status << "\n";
				Ready_Queue.push(Job_Queue.front());
				Job_Queue.pop();
			}
		}
		else if (ans == 2) {
			if (!CPU.empty()) {
				cout << ">>CPU is performing." << "\n";
				continue;
			}
			if (!Ready_Queue.empty()) {
				Dispatch(Ready_Queue.front());
				cout << "#" << Ready_Queue.front().Name << "-PID" << Ready_Queue.front().PID << " " << Ready_Queue.front().Process_Status << "\n";
				CPU.push(Ready_Queue.front());
				Ready_Queue.pop();
				if (!Ready_Queue.empty())
					CPU.front().Pointer = Ready_Queue.front().PID;
				else
					CPU.front().Pointer = "";
			}
		}
		else if (ans == 3) {
			if (!CPU.empty()) {
				if (!Device_Queue.empty())
					Device_Queue.back().Pointer = CPU.front().PID;
				Wait(CPU.front());
				cout << "#" << CPU.front().Name << "-PID" << CPU.front().PID << " " << CPU.front().Process_Status << "\n";
				Device_Queue.push(CPU.front());
				CPU.pop();
			}
			cout << ">>CPU is empty." << "\n";
		}
		else if (ans == 4) {
			if (!Device_Queue.empty()) {
				Completion(Device_Queue.front());
				cout << "#" << Device_Queue.front().Name << "-PID" << Device_Queue.front().PID << " " << Device_Queue.front().Process_Status << "\n";
				if (!Ready_Queue.empty())
					Ready_Queue.back().Pointer = Device_Queue.front().PID;
				else
					Ready_Queue.back().Pointer = "";
				Ready_Queue.push(Device_Queue.front());
				Device_Queue.pop();
			}
		}
		else {
			if (!CPU.empty()) {
				Exit(CPU.front());
				while (!SubJob_Queue.empty()) {
					if(CPU.front().Name != SubJob_Queue.front().Name)
						Sub.push(SubJob_Queue.front());
					SubJob_Queue.pop();
				}
				while (!Sub.empty()) {
					SubJob_Queue.push(Sub.front());
					Sub.pop();
				}
				cout << "#" << CPU.front().Name << "-PID" << CPU.front().PID << " " << CPU.front().Process_Status << "\n";
				CPU.pop();
			}
		}
	}
	cout << "Completed all Process!";

	return 0;
}