
#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include <fstream>
#include <iostream>
#include "../turingMachine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tmTester
{
	TEST_CLASS(DefinitionTester)
	{
	public:

		TEST_METHOD(CompleteValidDefinition)
		{
			TuringMachine tm("../tmTester/tmDefTestFiles/test1.def");
			Assert::IsTrue(tm.IsValidDefinition());
		};
		TEST_METHOD(CompleteValidDefinitionWithWhiteSpace)
		{
			TuringMachine tm("../tmTester/tmDefTestFiles/test2.def");
			Assert::IsTrue(tm.IsValidDefinition());
		};
		TEST_METHOD(DefinitionIncorrectHeadingOrder)
		{
			TuringMachine tm("../tmTester/tmDefTestFiles/test3.def");
			Assert::IsFalse(tm.IsValidDefinition());
		};
		TEST_METHOD(ReservedCharacterInStates)
		{
			TuringMachine tm("../tmTester/tmDefTestFiles/test5.def");
			Assert::IsFalse(tm.IsValidDefinition());
		};
		TEST_METHOD(DuplicateCharacterInStates)
		{
			TuringMachine tm("../tmTester/tmDefTestFiles/test6.def");
			Assert::IsFalse(tm.IsValidDefinition());
		};
		TEST_METHOD(StringInInputAlphabet)
		{
			std::ifstream file("../tmTester/tmDefTestFiles/test7.def");
			std::string consumeHeader;
			file >> consumeHeader;
			bool valid = true;
			InputAlphabet inputAlphabet;
			inputAlphabet.Load(file, valid);
			Assert::IsFalse(valid);
		};
		/*TEST_METHOD(EmptyInputAlphabet)
		{
			std::ifstream file("../tmTester/tmDefTestFiles/test8.def");
			std::string consumeHeader;
			file >> consumeHeader;
			bool valid = true;
			InputAlphabet inputAlphabet;
			inputAlphabet.Load(file, valid);
			Assert::IsFalse(valid);
		};*/
		TEST_METHOD(ReservedCharacterInInputAlphabet)
		{
			std::ifstream file("../tmTester/tmDefTestFiles/test9.def");
			std::string consumeHeader;
			file >> consumeHeader;
			bool valid = true;
			InputAlphabet inputAlphabet;
			inputAlphabet.Load(file, valid);
			Assert::IsFalse(valid);
		};
		TEST_METHOD(BlankCharacterInTapeAlphabet)
		{
			std::ifstream file("../tmTester/tmDefTestFiles/test10.def");
			std::string consumeHeader;
			file >> consumeHeader;
			bool valid = true;
			TapeAlphabet tapeAlphabet;
			tapeAlphabet.Load(file, valid);
			Assert::IsTrue(valid);
		};
		TEST_METHOD(ReservedCharacterInTapeAlphabet)
		{
			std::ifstream file("../tmTester/tmDefTestFiles/test11.def");
			std::string consumeHeader;
			file >> consumeHeader;
			bool valid = true;
			TapeAlphabet tapeAlphabet;
			tapeAlphabet.Load(file, valid);
			Assert::IsFalse(valid);
		};
		/*TEST_METHOD(EmptyTapeAlphabet)
		{
			std::ifstream file("../tmTester/tmDefTestFiles/test12.def");
			std::string consumeHeader;
			file >> consumeHeader;
			bool valid = true;
			TapeAlphabet tapeAlphabet;
			tapeAlphabet.Load(file, valid);
			Assert::IsFalse(valid);
		};*/
		TEST_METHOD(MultipleInitialStates)
		{
			TuringMachine tm("../tmTester/tmDefTestFiles/test13.def");
			Assert::IsFalse(tm.IsValidDefinition());
		};
		TEST_METHOD(EmptyInitialState)
		{
			TuringMachine tm("../tmTester/tmDefTestFiles/test14.def");
			Assert::IsFalse(tm.IsValidDefinition());
		};
		TEST_METHOD(NoBlankCharacter)
		{
			TuringMachine tm("../tmTester/tmDefTestFiles/test15.def");
			Assert::IsFalse(tm.IsValidDefinition());
		};
		TEST_METHOD(ReservedCharacterInFinalStates)
		{
			TuringMachine tm("../tmTester/tmDefTestFiles/test16.def");
			Assert::IsFalse(tm.IsValidDefinition());
		};
		TEST_METHOD(UndeclaredStateInFinalStates)
		{
			TuringMachine tm("../tmTester/tmDefTestFiles/test17.def");
			Assert::IsFalse(tm.IsValidDefinition());
		};
		TEST_METHOD(HeadingAfterFinalStates)
		{
			TuringMachine tm("../tmTester/tmDefTestFiles/test18.def");
			Assert::IsFalse(tm.IsValidDefinition());
		};
	};
}