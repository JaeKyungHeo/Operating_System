#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

int LRU(queue<int> req) {
	int used_frame = 0;//프레임 수 확인용
	int page_fault = 0;
	bool check[10];//들어가있는 사용된 페이지번호 확인용
	int num[10];//누적된 수가 클수록 오래된 것임.
	memset(check, false, sizeof(check));
	memset(num, 0, sizeof(num));

	while (!req.empty()) {
		int page_num = req.front();
		for (int i = 0; i < 10; i++)
			num[i]++;
		num[page_num] = 0;
		if (check[page_num] == true) {
			req.pop();
			continue;
		}
		else if (used_frame == 4 && check[page_num] == false) {
			page_fault++;
			int max = -1;
			int index;
			for (int i = 0; i < 10; i++) {
				if (check[i] == true) {
					if (max < num[i]) {
						max = num[i];
						index = i;
					}
				}
			}
			check[index] = false;
			check[page_num] = true;
		}
		else if (used_frame < 4 && check[page_num] == false) {
			check[page_num] = true;
			used_frame++;
			page_fault++;

		}
		req.pop();
	}
	return page_fault;
}

int Optimal(vector<int> Opt) {
	int used_frame = 0;//프레임 수 확인용
	int page_fault = 0;
	bool check[10];//들어가있는 사용된 페이지번호 확인용
	int num[10];//누적된 수가 클수록 오래된 것임.

	memset(check, false, sizeof(check));
	memset(num, 0, sizeof(num));

	for(int i = 0;i<Opt.size();i++){
		int page_num = Opt[i];
		if (check[page_num] == true) {
			continue;
		}
		else if (used_frame == 4 && check[page_num] == false) {
			page_fault++;
			int max = -1;
			int index;
			for (int k = Opt.size()-1; i < k; k--) {
				for (int j = 0; j < 10; j++)
					num[j]++;
				num[Opt[k]] = 0;
			}
			for (int p = 0; p < 10; p++) {
				if (check[p] == true) {
					if (max < num[p]) {
						max = num[p];
						index = p;
					}
				}
			}
			check[index] = false;
			check[page_num] = true;
		}
		else if (used_frame < 4 && check[page_num] == false) {
			check[page_num] = true;
			used_frame++;
			page_fault++;

		}
	}
	return page_fault;
}

int main() {
	queue<int>  req;
	vector<int> Opt;
	req.push(1);
	req.push(2);
	req.push(1);
	req.push(4);
	req.push(5);
	req.push(6);
	req.push(3);
	req.push(4);
	req.push(6);
	req.push(3);
	req.push(7);
	req.push(3);
	req.push(1);
	req.push(5);
	req.push(3);
	req.push(7);
	req.push(3);
	req.push(4);
	req.push(2);
	req.push(4);
	req.push(1);
	req.push(4);
	req.push(5);
	req.push(1);

	int k = req.size();

	for (int i = 0; i < k; i++) {
		Opt.push_back(req.front());
		req.push(req.front());
		req.pop();
	}


	cout<< "(LRU Algorithm) number of page fault : " << LRU(req) << endl;

	cout<< "(Optimal Algorithm) number of page fault : " << Optimal(Opt) << endl;

	return 0;
}