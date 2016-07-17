#pragma once

#include <string>
#include <iostream>

using namespace std;

class MatrixChain
{
public:
	MatrixChain() {};
	~MatrixChain() {};

	struct matrix_t
	{
		matrix_t(int row, int col)
		{
			rowNum = row;
			colNum = col;
		}

		int rowNum;
		int colNum;
	};

	void Run()
	{
		cout << "-- Matirx Chain Algorithm Starts --" << endl;

		matrix_t matrix[4] = {matrix_t(3, 4), matrix_t(4, 2), matrix_t(2, 5), matrix_t(5, 6)};

		int resMatrix[4][4];
		int cutPos[4][4];
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				resMatrix[i][j] = -1;
				cutPos[i][j] = -1;
			}
		}

		cout << "Recursive Result : " << RunRecursive(matrix, 0, 3) << endl;
		cout << "Memoization Result : " << RunMemoization(matrix, 0, 3, resMatrix) << endl;
		cout << "BottomUp Result : " << RunBottomUp(matrix, 4) << endl;
		cout << "BottomUpWithCutPos Result : " << RunBottomUpWithCutPos(matrix, 4, cutPos) << endl;
		//PrintOptimalPranthesis(cutPos, 0 , 4);
		cout << endl;
	}

	int RunRecursive(matrix_t* matrixChain, int firstMatrixId, int lastMatrixId)
	{
		int minCost, cost;

		if (firstMatrixId == lastMatrixId) return 0;

		minCost = RunRecursive(matrixChain, firstMatrixId + 1, lastMatrixId) 
										+ ( matrixChain[firstMatrixId].rowNum 
										* matrixChain[firstMatrixId].colNum 
										* matrixChain[lastMatrixId].colNum );

		for (int endOfFirstSeq = firstMatrixId + 1; endOfFirstSeq < lastMatrixId; ++endOfFirstSeq)
		{
			cost = RunRecursive(matrixChain, firstMatrixId, endOfFirstSeq)
					+ RunRecursive(matrixChain, endOfFirstSeq + 1, lastMatrixId)
					+ ( matrixChain[firstMatrixId].rowNum
					* matrixChain[endOfFirstSeq].colNum
					* matrixChain[lastMatrixId].colNum );

			if (cost < minCost) minCost = cost;
		}

		return minCost;
	}

	int RunMemoization(matrix_t* matrixChain, int firstMatrixId, int lastMatrixId, int resMatrix[][4])
	{
		int cost;

		if (resMatrix[firstMatrixId][lastMatrixId] != -1) return resMatrix[firstMatrixId][lastMatrixId];

		if (firstMatrixId == lastMatrixId)
		{
			resMatrix[firstMatrixId][lastMatrixId] = 0;
			return 0;
		}

		resMatrix[firstMatrixId][lastMatrixId] = RunRecursive(matrixChain, firstMatrixId + 1, lastMatrixId)
			+ (matrixChain[firstMatrixId].rowNum
				* matrixChain[firstMatrixId].colNum
				* matrixChain[lastMatrixId].colNum);

		for (int endOfFirstSeq = firstMatrixId + 1; endOfFirstSeq < lastMatrixId; ++endOfFirstSeq)
		{
			cost = RunRecursive(matrixChain, firstMatrixId, endOfFirstSeq)
				+ RunRecursive(matrixChain, endOfFirstSeq + 1, lastMatrixId)
				+ (matrixChain[firstMatrixId].rowNum
					* matrixChain[endOfFirstSeq].colNum
					* matrixChain[lastMatrixId].colNum);

			if (cost < resMatrix[firstMatrixId][lastMatrixId]) resMatrix[firstMatrixId][lastMatrixId] = cost;
		}

		return resMatrix[firstMatrixId][lastMatrixId];
	}

	int RunBottomUp(matrix_t* matrixChain, int num)
	{
		int cost, minCost, eId;
		int resMatrix[4][4];

		for (int sId = 0; sId < num; ++sId)
			resMatrix[sId][sId] = 0;

		for (int diff = 1; diff < num; ++diff)
		{
			for (int sId = 0; sId < num - diff; ++sId)
			{
				eId = sId + diff;
				
				resMatrix[sId][eId] = resMatrix[sId + 1][eId] 
									+ matrixChain[sId].rowNum * matrixChain[sId].colNum * matrixChain[eId].colNum;

				for (int endOfFirst = sId + 1; endOfFirst < eId; ++endOfFirst)
				{
					cost = resMatrix[sId][endOfFirst] + resMatrix[endOfFirst + 1][eId]
						+ matrixChain[sId].rowNum * matrixChain[endOfFirst].colNum * matrixChain[eId].colNum;

					if (cost < resMatrix[sId][eId])
						resMatrix[sId][eId] = cost;
				}
			}
		}

		return resMatrix[0][num - 1];
	}

	int RunBottomUpWithCutPos(matrix_t* matrixChain, int num, int cutPos[][4])
	{
		int cost, minCost, eId;
		int resMatrix[4][4];

		for (int sId = 0; sId < num; ++sId)
			resMatrix[sId][sId] = 0;

		for (int diff = 1; diff < num; ++diff)
		{
			for (int sId = 0; sId < num - diff; ++sId)
			{
				eId = sId + diff;

				resMatrix[sId][eId] = resMatrix[sId + 1][eId]
					+ matrixChain[sId].rowNum * matrixChain[sId].colNum * matrixChain[eId].colNum;

				cutPos[sId][eId] = sId;

				for (int endOfFirst = sId + 1; endOfFirst < eId; ++endOfFirst)
				{
					cost = resMatrix[sId][endOfFirst] + resMatrix[endOfFirst + 1][eId]
						+ matrixChain[sId].rowNum * matrixChain[endOfFirst].colNum * matrixChain[eId].colNum;

					if (cost < resMatrix[sId][eId])
					{
						resMatrix[sId][eId] = cost;
						cutPos[sId][eId] = endOfFirst;
					}
				}
			}
		}

		return resMatrix[0][num - 1];
	}

	void PrintOptimalPranthesis(int cutPos[][4], int sId, int eId)
	{
		if (sId > eId) return;
		if (sId == eId) cout << "A" << sId;
		else
		{
			cout << "(";
			PrintOptimalPranthesis(cutPos, sId, cutPos[sId][eId]);
			PrintOptimalPranthesis(cutPos, cutPos[sId][eId] + 1, eId);
			cout << ")";
		}
	}
};