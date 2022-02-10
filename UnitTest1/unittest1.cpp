#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\ExpressionTree\ExpressionTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestEvaluateExpr)
		{
			ExpressionTree exprTree;
			string inputExpr = "((15 / (7 - (1 + 1) ) ) * -3 ) - (2 + (1 + 1))";

			int value = exprTree.GetValFromExpressionTree(inputExpr);

			Assert::AreEqual(value, -13);
		}

	};
}