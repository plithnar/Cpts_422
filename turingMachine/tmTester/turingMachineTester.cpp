
#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "../turingMachine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tmTester
{
	TEST_CLASS(TuringMachineTester)
	{
	public:
		TuringMachine* tm = new TuringMachine("../fullValidTm.def");

		TEST_METHOD(InitializingTuringMachineShouldSetDefaults)
		{
			tm->Initialize("aabb");

			//All stuff should be set to 
			Assert::AreEqual(tm->InputString().compare("aabb"), 0);
			Assert::AreEqual(tm->TotalNumberOfTransitions(), 0);
			Assert::AreEqual(tm->IsAcceptedInputString(), false);
			Assert::AreEqual(tm->IsOperating(), true);
			Assert::AreEqual(tm->IsRejectedInputString(), false);
			Assert::AreEqual(tm->IsUsed(), true);			
		};
		
		TEST_METHOD(TuringMachineShouldRunForAppropriateNumberOfTransitions)
		{
			tm->Initialize("aabb");
			tm->PerformTransitions(2);
			Assert::AreEqual(tm->TotalNumberOfTransitions(), 2);

			tm->Initialize("aabb");
			tm->PerformTransitions(10);
			Assert::AreEqual(tm->TotalNumberOfTransitions(), 10);
		}

		TEST_METHOD(TuringMachineShouldShowStringAccepted)
		{
			tm->Initialize("ab");
			tm->PerformTransitions(20);
			Assert::AreEqual(tm->IsAcceptedInputString(), true);
		}

		TEST_METHOD(TuringMachineShouldShowStringRejected)
		{
			tm->Initialize("abb");
			tm->PerformTransitions(20);
			Assert::AreEqual(tm->IsRejectedInputString(), true);
		}

		TEST_METHOD(TuringMachineShouldShowNotOperatingWhenTerminatedMidwayThrough)
		{
			tm->Initialize("aabb");
			tm->PerformTransitions(2);
			tm->TerminateOperation();
			Assert::AreEqual(tm->IsOperating(), false);
		}

		TEST_METHOD(TuringMachineShouldShowRecognizeInvalidStrings)
		{
			Assert::AreEqual(tm->IsValidInputString("aabb"), true);
			Assert::AreEqual(tm->IsValidInputString("aabbc"), false);
		}

	};
}
