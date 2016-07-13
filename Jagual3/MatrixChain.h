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
		int rowNum;
		int colNum;
	};

	void Run()
	{

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

			if (cost > minCost) minCost = cost;
		}

		return minCost;
	}
};