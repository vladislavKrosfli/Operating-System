#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include "..//funk_lab2/Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			vector<int> arr = {3, 2, 6, 7, 4, 8};
			int min = 2, max = 8, average = 5;

			vector<int> arrT = { 3, 2, 6, 7, 4, 8 };
			int minT, maxT, averageT;
			
			lab2 lb;
			lb.min_max(arrT, minT, maxT);
			lb.average(arrT, averageT);
			lb.change_arr(arrT, averageT, minT, maxT);

			Assert::AreEqual(min, minT);
			Assert::AreEqual(max, maxT);
			Assert::AreEqual(average, averageT);
		}
	};
}
