#include "pch.h"
#include "CppUnitTest.h"
#include "../lab2_7/Account.h"
#include "../lab2_7/Account.cpp"
#include "../lab2_7/Money.h"
#include "../lab2_7/Money.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Money m(123.45);
			Assert::AreEqual(123.45, m.getTotal(), 0.001);
		}
	};
}
