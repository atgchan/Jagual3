#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class ActivitySelection
{
public:
	ActivitySelection() {};
	~ActivitySelection() {};

	struct act_t // [start, end)
	{
		act_t(int start, int end)
		{
			startTime = start;
			endTime = end;
		};
		int startTime;
		int endTime;
	};

	void Run()
	{
		cout << "-- Activity Algorithm Starts --" << endl;

		int len = 11;
		act_t* acts[11] = {	new act_t(1, 4), new act_t(3, 5), new act_t(0, 6), new act_t(5, 7), 
							new act_t(3, 9), new act_t(5, 9), new act_t(6, 10), new act_t(8, 11), 
							new act_t(8, 12), new act_t(2, 14), new act_t(12, 16) };

		SortActs(acts, len);

		cout << "Recursive Result : " << RunRecursive(acts, len, 0, 0) << endl;

		cout << "Iterative Result : " << RunIterative(acts, len) << endl;
	}

	void SortActs(act_t** acts, int len)
	{
		vector<act_t*> tmpVector;
		tmpVector.assign(acts, acts + len);
		sort(tmpVector.begin(), tmpVector.end(), [](act_t* first, act_t* second) {
			return first->endTime < second->endTime;
		});
		
		for (int i = 0; i < len; ++i)
		{
			acts[i]->startTime = tmpVector[i]->startTime;
			acts[i]->endTime = tmpVector[i]->endTime;
		}
	}

	int RunRecursive(act_t** acts, int len, int startIndex, int lastEndTime)
	{
		if (startIndex >= len) return 0;

		for (int i = startIndex; i < len; ++i)
		{
			if (acts[i]->startTime >= lastEndTime)
				return 1 + RunRecursive(acts, len, i + 1, acts[i]->endTime);
		}

		return 0;
	}

	int RunIterative(act_t** acts, int len)
	{
		int maxNum, lastInstertedActId;

		if (len <= 0) return 0;

		maxNum = 1;
		lastInstertedActId = 0;
		for (int i = 1; i < len; ++i)
		{
			if (acts[i]->startTime >= acts[lastInstertedActId]->endTime)
			{
				++maxNum;
				lastInstertedActId = i;
			}
		}

		return maxNum;
	}
};