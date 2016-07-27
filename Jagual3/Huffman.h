#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

class Huffman
{
public:
	Huffman() {};
	~Huffman() {};

	struct node_t
	{
		node_t(char character, int frequency)
		{
			c = character;
			freq = frequency;
		}
		int freq;
		char c;
		node_t* left;
		node_t* right;
	};

	void Run()
	{
		cout << "-- Huffman Code Algorithm Starts --" << endl;
		vector<node_t*> list;

		node_t n1('f', 5);
		node_t n2('e', 9);
		node_t n3('c', 12);
		node_t n4('b', 13);
		node_t n5('d', 16);
		node_t n6('a', 45);

		list.push_back(&n1);
		list.push_back(&n2);
		list.push_back(&n3);
		list.push_back(&n4);
		list.push_back(&n5);
		list.push_back(&n6);

		node_t* root = HuffmanCode(list);

		cout << "Huffman Code Reuslt : " << root->freq << endl;
	}

	node_t* HuffmanCode(vector<node_t*> &list)
	{
		auto cmp = [](node_t* n1, node_t* n2) {
			return n1->freq < n2->freq;
		};

		int n = list.size();
		priority_queue<node_t*, vector<node_t*>, decltype(cmp)> q(cmp);
		for (auto &node : list)
		{
			q.push(node);
		}

		for (int i = 1; i < n; ++i)
		{
			node_t* left = q.top();
			q.pop();
			node_t* right = q.top();
			q.pop();
			node_t* z = new node_t('\0', left->freq + right->freq);
			z->left = left;
			z->right = right;

			q.push(z);
		}

		return q.top();
	}
};