#pragma once
#include <iostream>
#include <stack>
#include <map>
using namespace std;

template <typename T>
class Tree
{
public:
	T value;
	Tree<T> *left;
	Tree<T> *right;

	Tree(T value) {
		this->value = value;
		left = NULL;
		right = NULL;
	}
};

class ExpressionTree
{
public:
	__declspec(dllexport) int GetValFromExpressionTree(string s);
private:
	void MakeNode(stack<string> &oprtr, stack<Tree<string> *> &tree);
	Tree<string>* BuildExpressionTree(string s);
	int Evaluate(Tree<string>* root);
	void SetPriority();
};
