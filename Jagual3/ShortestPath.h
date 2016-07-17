#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class ShortestPath
{
public:
	ShortestPath() {};
	~ShortestPath() {};
	
	struct Vertex
	{
		Vertex(int i)
		{
			id = i;
		}

		int id;
		vector <pair<Vertex*, int>> nears;
	};

	struct Graph
	{
		vector<Vertex*> vertexes;
	};

	void Run()
	{
		cout << "-- Shortest Path With Cycle Algorithm Starts --" << endl;

		Graph graph;
		Vertex s(0);
		Vertex v1(1);
		Vertex v2(2);
		Vertex v3(3);

		s.nears.push_back(make_pair(&v1, 5));
		v1.nears.push_back(make_pair(&v2, 4));
		v1.nears.push_back(make_pair(&v3, 1));
		v2.nears.push_back(make_pair(&v3, 10));
		v3.nears.push_back(make_pair(&v1, 2));
		v3.nears.push_back(make_pair(&s, 3));

		graph.vertexes.push_back(&s);
		graph.vertexes.push_back(&v1);
		graph.vertexes.push_back(&v2);
		graph.vertexes.push_back(&v3);

		int pathWeight[4][4];
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
				pathWeight[i][j] = INT_MAX;
		}

		RunMemoization();
		cout << "Memoization Result : "  << endl;


		RunBottomUp(&graph, pathWeight, &s);
		cout << "Bottom-Up Result : ";
		for (int i = 0; i < 4; ++i)
		{
			cout << pathWeight[i][3] << " ";
		}
		cout << endl;
	}

	void RunMemoization()
	{

	}
	
	void RunBottomUp(Graph* graph, int pathWeight[][4], Vertex* source)
	{
		int maxlen = graph->vertexes.size();
		pathWeight[0][source->id] = 0;

		for (int k = 0; k < maxlen - 1; ++k)
		{
			for (int i = 0; i < maxlen; ++i)
			{
				if (pathWeight[i][k] != INT_MAX)
				{
					Vertex* v = graph->vertexes[i];
					for (auto& near : v->nears)
					{
						if (pathWeight[i][k] == INT_MAX) continue;
						pathWeight[i][k + 1] = pathWeight[i][k];
						if (pathWeight[near.first->id][k + 1] > pathWeight[i][k] + near.second)
						{
							pathWeight[near.first->id][k + 1] = pathWeight[i][k] + near.second;
						}
					}
				}
			}
		}

	}
};