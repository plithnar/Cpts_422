#include "stdafx.h"
#include "CppUnitTest.h"
#include "../tape.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tmTester
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(IsFirstCellAfterInitialize)
		{
			//
			// TODO: Add test logic here
			//
			Tape* testTape = new Tape();
			testTape->Initialize("aabb");

			Assert::AreEqual(testTape->IsFirstCell(), true);
		};

	};
}