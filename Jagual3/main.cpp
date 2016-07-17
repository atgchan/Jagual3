#include <iostream>
#include <string>

#include "RodCutting.h"
#include "ShortestPath.h"
#include "MatrixChain.h"
#include "ActivitySelection.h"

using namespace std;

int main()
{
	string input;
	RodCutting* rodCutting = new RodCutting();
	ShortestPath* shortestPath = new ShortestPath();
	MatrixChain* matrixChain = new MatrixChain();
	ActivitySelection* activitySelection = new ActivitySelection();

	cout << "0: Exit" << endl;
	cout << "1: Rod - Cutting " << endl;
	cout << "2: Shortest Path With Cycle Algorithm" << endl;
	cout << "3: Matrix Chain Algorithm" << endl;
	cout << "5: Activity Selction Algorithm" << endl;

	while (1)
	{
		getline(cin, input);

		if (input == "") continue;

		switch (stoi(input))
		{
		case 0:
			return 0;
			break;

		case 1:
			rodCutting->Run();
			break;

		case 2:
			shortestPath->Run();
			break;

		case 3:
			matrixChain->Run();
			break;

		case 5:
			activitySelection->Run();
			break;

		default:
			cout << "Invalid Index Input" << endl;
			break;
		}
	}

	getchar();

	delete(rodCutting);
}