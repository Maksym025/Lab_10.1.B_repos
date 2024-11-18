#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_10.1.B/Lab_10.1.B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			int N = 3;
			Student* students = new Student[N];
			students[1].fizyka = 4;
			students[2].fizyka = 2;
			students[3].fizyka = 5;
			double exp = PercentHighPhysics(students, N);
			Assert::AreEqual(exp, 33.3, 0.1);
		}
	};
}
