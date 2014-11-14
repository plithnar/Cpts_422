
#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
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

		TEST_METHOD(ConstructorSetsBlankToSpace)
		{
			Tape* testTape = new Tape();
			Assert::AreEqual(testTape->BlankCharacter(), ' ');
		};

		TEST_METHOD(MovingRightMovesToNextCell)
		{
			Tape* testTape = new Tape();
			testTape->Initialize("1234");
			testTape->Update('1', 'R');
			Assert::AreEqual(testTape->CurrentCharacter(), '2');
		};

		TEST_METHOD(ProperlyDisplaysIDToTheRight)
		{
			Tape* testTape = new Tape();
			testTape->Initialize("1234");
			string returned =  testTape->Right(1);
			Assert::AreEqual(returned.compare("1>"), 0);
		};

		TEST_METHOD(MovingRightMovesToPreviousCell)
		{
			Tape* testTape = new Tape();
			testTape->Initialize("1234");
			testTape->Update('1', 'R');
			testTape->Update('2', 'L');
			Assert::AreEqual(testTape->CurrentCharacter(), '1');
		};

		TEST_METHOD(ProperlyDisplaysIDToTheLeft)
		{
			Tape* testTape = new Tape();
			testTape->Initialize("1234");
			testTape->Update('1', 'R');
			string returned = testTape->Left(1);
			Assert::AreEqual(returned.compare("1"), 0);
		};

	};
}
