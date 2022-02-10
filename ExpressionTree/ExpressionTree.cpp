// ExpressionTree.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ExpressionTree.h"
map<string, int> priority;

// helper methods
bool isDigit(char c)
{
	if ('0' <= c && c <= '9')
	{
		return 1;
	}
	return 0;
}

int toInt(string s)
{
	int num = 0;
	if (s[0] != '-')
	{
		for (unsigned int i = 0; i < s.length(); i++)
			num = num * 10 + (int(s[i]) - 48);
	}
	else
	{
		for (unsigned int i = 1; i < s.length(); i++)
		{
			num = num * 10 + (int(s[i]) - 48);
		}
		num = num * -1;
	}
	return num;
}

void postorder(Tree<string>* root)
{
	if (root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("%s", root->value.c_str());
	}
}
void ExpressionTree::SetPriority()
{
	priority["("] = 1;
	priority["*"] = 2;
	priority["/"] = 2;
	priority["-"] = 3;
	priority["+"] = 3;
}
void ExpressionTree::MakeNode(stack<string> &oprtr, stack<Tree<string> *> &tree)
{
	Tree<string> *root = new Tree<string>(oprtr.top());

	oprtr.pop();
	root->right = tree.top();
	tree.pop();
	root->left = tree.top();
	tree.pop();
	tree.push(root);

}

Tree<string>* ExpressionTree::BuildExpressionTree(string s)
{
	stack<Tree<string> *> tree;
	stack<string> operators;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ')
			continue;
		else if (s[i] == '(')
		{
			operators.push("(");
		}
		else if (isDigit(s[i]) ||
			(s[i] == '-' && i + 1 < s.length() && isDigit(s[i + 1])))
		{
			string num = "";
			num += s[i];
			while (i + 1 < s.length() && isDigit(s[i + 1]))
			{
				num += s[i + 1];
				i++;
			}
			Tree<string> *node = new Tree<string>(num);
			tree.push(node);
		}
		else if (s[i] == ')')
		{
			while (operators.top() != "(" && (tree.size() > 1))
			{
				MakeNode(operators, tree);
			}

			operators.pop();
		}
		else
		{
			string oprtr = "";
			oprtr += s[i];

			while (!operators.empty() && priority[operators.top()] >= priority[oprtr]
				&& (tree.size() > 1))
			{
				MakeNode(operators, tree);
			}

			operators.push(oprtr);
		}
	}

	while (tree.size() > 1)
	{
		MakeNode(operators, tree);
	}

	return tree.top();
}

int ExpressionTree::Evaluate(Tree<string>* root)
{
	// empty tree
	if (!root)
		return 0;

	// leaf node
	if (!root->left && !root->right)
		return toInt(root->value);

	int l_val = Evaluate(root->left);

	int r_val = Evaluate(root->right);

	if (root->value == "+")
		return l_val + r_val;

	if (root->value == "-")
		return l_val - r_val;

	if (root->value == "*")
		return l_val * r_val;

	return l_val / r_val;
}

int ExpressionTree::GetValFromExpressionTree(string inputExpr)
{
	SetPriority();
	Tree<string>* result = BuildExpressionTree(inputExpr);

	postorder(result);

	int value = Evaluate(result);
	return value;
}

//int main()
//{
//	// setting priority based on BODMAS
//	priority["("] = 1;
//	priority["*"] = 2;
//	priority["/"] = 2;
//	priority["-"] = 3;
//	priority["+"] = 3;
//	ExpressionTree exprTree;
//	string inputExpr = "((15 / (7 - (1 + 1) ) ) * -3 ) - (2 + (1 + 1))";
//
//	int value = exprTree.GetValFromExpressionTree(inputExpr);
//	return 0;
//}


