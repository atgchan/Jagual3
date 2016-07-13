#pragma once

#include <string>
#include <iostream>

using namespace std;

class RodCutting
{
public:
	RodCutting() {};
	~RodCutting() {};

	void Run()
	{
		cout << "-- Rod Cutting Algorithm Starts --" << endl;

		int pieceValue[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
		int len = 9;

		cout << "Recursive Result : " << RunRecursive(pieceValue, len) << endl;

		// Memoization을 위한 결과 저장 배열 초기화
		int* resValue;
		resValue = new int[len + 1];
		for (int i = 0; i <= len; ++i)
		{
			resValue[i] = -1;
		}

		cout << "Memoization Result : " << RunMemoization(pieceValue, len, resValue) << endl;
		delete(resValue);

		cout << "Bottom-Up Result : " << RunBottomUp(pieceValue, len) << endl;

		// Print solution 을 위한 자른 위치 저장 배열 초기화
		int* firstCutForLength;
		firstCutForLength = new int[len + 1];
		for (int i = 0; i <= len; ++i)
		{
			firstCutForLength[i] = -1;
		}

		cout << "Extended Bottom-Up Result : " << RunExtendedBottomUp(pieceValue, len, firstCutForLength) << endl;

		PrintSolution(firstCutForLength, len);

		cout << endl;
	}

	int RunRecursive(int* pieceValue, int len)
	{
		int maxValue;
		int value;

		if (len == 0) return 0;

		maxValue = -1;

		for (int firstPieceLen = 1; firstPieceLen <= len; ++firstPieceLen)
		{
			value = pieceValue[firstPieceLen] + RunRecursive(pieceValue, len - firstPieceLen);

			if (value > maxValue) maxValue = value;
		}

		return maxValue;
	}

	int RunMemoization(int* pieceValue, int len, int* resValue)
	{
		int maxValue;
		int value;

		if (resValue[len] != -1) return resValue[len];

		if (len == 0) return 0;

		maxValue = -1;

		for (int cutPos = 1; cutPos <= len; ++cutPos)
		{
			value = pieceValue[cutPos] + RunMemoization(pieceValue, len - cutPos, resValue);

			if (value > maxValue) maxValue = value;
		}

		resValue[len] = maxValue;

		return maxValue;
	}

	int RunBottomUp(int* pieceValue, int totalLen)
	{
		int value;
		int subMaxValue;
		int maxValue;
		int* resValue = new int[totalLen + 1];

		resValue[0] = 0;

		for (int len = 1; len <= totalLen; ++len)
		{
			subMaxValue = -1;
			for (int subLen = 1; subLen <= len; ++subLen)
			{
				value = pieceValue[subLen] + resValue[len - subLen];
				if (value > subMaxValue) subMaxValue = value;
			}
			resValue[len] = subMaxValue;
		}

		maxValue = resValue[totalLen];

		delete(resValue);

		return maxValue;
	}

	int RunExtendedBottomUp(int* pieceValue, int totalLen, int* firstCutForLength)
	{
		int value;
		int subMaxValue;
		int maxValue;
		int* resValue = new int[totalLen + 1];

		resValue[0] = 0;
		firstCutForLength[0] = 0;

		for (int len = 1; len <= totalLen; ++len)
		{
			subMaxValue = -1;
			for (int subLen = 1; subLen <= len; ++subLen)
			{
				value = pieceValue[subLen] + resValue[len - subLen];
				if (value > subMaxValue)
				{
					subMaxValue = value;
					firstCutForLength[len] = subLen;
				}
			}
			resValue[len] = subMaxValue;
		}
		maxValue = resValue[totalLen];

		delete[] resValue;

		return maxValue;
	}

	void PrintSolution(int* firstCutForLength, int totalLen)
	{
		int len;

		cout << "Sulution : ";

		len = totalLen;
		while (len > 0)
		{
			cout << firstCutForLength[len] << " ";
			len -= firstCutForLength[len];
		}

		cout << endl;
	}
};