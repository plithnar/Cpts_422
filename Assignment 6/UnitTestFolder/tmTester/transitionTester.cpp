
#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "../transition.h"
#include "../transitionFunction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tmTester
{
	TEST_CLASS(TransitionTester)
	{
	public:
		Transition* RightTrans = new Transition("S1", '1', "S2", '2', 'R');
		Transition* LeftTrans = new Transition("S2", '2', "S1", '1', 'L');
		TransitionFunction* transitions = new TransitionFunction();
		


		TEST_METHOD(ShouldAccuratelyReturnDataForTransition)
		{
			transitions->Add(*RightTrans);

			Assert::AreEqual(transitions->SourceState(0).compare("S1"), 0);
			Assert::AreEqual(transitions->DestinationState(0).compare("S2"), 0);
			Assert::AreEqual(transitions->ReadCharacter(0), '1');
			Assert::AreEqual(transitions->WriteCharacter(0), '2');
		}

		TEST_METHOD(ShouldFindDefinedTransitions)
		{
			transitions->Add(*RightTrans);

			string dest;
			char write;
			Direction move;

			Assert::AreEqual(transitions->IsDefinedTransition("S1", '1', dest, write, move), true);
		}

		TEST_METHOD(ShouldNotFindNotDefinedTransition)
		{
			string dest;
			char write;
			Direction move;

			Assert::AreEqual(transitions->IsDefinedTransition("S1", '1', dest, write, move), false);
		}

		TEST_METHOD(ShouldFindDefinedSourceState)
		{
			transitions->Add(*RightTrans);

			Assert::AreEqual(transitions->IsSourceState("S1"), true);
		}

		TEST_METHOD(ShouldNotFindNotDefinedSourceState)
		{
			Assert::AreEqual(transitions->IsSourceState("S1"), false);
		}
	};
}
