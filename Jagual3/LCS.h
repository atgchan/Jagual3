#pragma once
#include <string>

using namespace std;

class LCS
{
public:
	LCS() {}
	~LCS() {}

	void Run()
	{
		string str1 = "ABCBDAB";
		string str2 = "BDCABA";

		cout << "Recursion Result : " << RunRecursion(str1, str1.size(), str2, str2.size()) << endl;

		int solM[8][7];

		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 7; ++j)
			{
				solM[i][j] = -1;
			}
		}

		cout << "Memoization Result : " << RunMemoization(str1, str1.size(), str2, str2.size(), solM) << endl;

		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 7; ++j)
			{
				solM[i][j] = -1;
			}
		}

		cout << "BottomUp Result : " << RunBottomUp(str1, str2, solM) << endl;
	}

	int RunRecursion(string &str1, int str1SubLen, string &str2, int str2SubLen)
	{
		int lcsLen, subseqLen;

		if (str1SubLen == 0 || str2SubLen == 0) return 0;

		if (str1[str1SubLen] == str2[str2SubLen])
			lcsLen = RunRecursion(str1, str1SubLen - 1, str2, str2SubLen - 1) + 1;
		else
			lcsLen = max(RunRecursion(str1, str1SubLen, str2, str2SubLen - 1), 
						RunRecursion(str1, str1SubLen - 1, str2, str2SubLen));

		return lcsLen;
	}

	int RunMemoization(string &str1, int str1SubLen, string &str2, int str2SubLen, int solM[][7])
	{
		int lcsLen, subseqLen;

		if (solM[str1SubLen][str2SubLen] != -1) return solM[str1SubLen][str2SubLen];

		if (str1SubLen == 0 || str2SubLen == 0)
		{
			solM[str1SubLen][str2SubLen] = 0;
			return 0;
		}

		if (str1[str1SubLen] == str2[str2SubLen])
			lcsLen = RunRecursion(str1, str1SubLen - 1, str2, str2SubLen - 1) + 1;
		else
			lcsLen = max(RunRecursion(str1, str1SubLen, str2, str2SubLen - 1),
				RunRecursion(str1, str1SubLen - 1, str2, str2SubLen));

		solM[str1SubLen][str2SubLen] = lcsLen;

		return lcsLen;
	}

	int RunBottomUp(string &str1, string &str2, int solM[][7])
	{
		for (int i = 0; i < str1.size(); ++i)
		{
			solM[i][0] = 0;
		}

		for (int i = 0; i < str2.size(); ++i)
		{
			solM[0][i] = 0;
		}

		for (int i = 1; i <= str1.size(); ++i)
		{
			for (int j = 1; j <= str2.size(); ++j)
			{
				if (str1[i] == str2[j])
				{
					solM[i][j] = solM[i - 1][j - 1] + 1;
				}
				else
				{
					solM[i][j] = max(solM[i][j - 1], solM[i - 1][j]);
				}
			}
		}

		return solM[str1.size()][str2.size()];
	}

};