
#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "../inputAlphabet.h"
#include "../tapeAlphabet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tmTester
{
	TEST_CLASS(AlphabetTester)
	{
	public:

		TapeAlphabet* tapeAlpha = new TapeAlphabet();
		InputAlphabet* inputAlpha = new InputAlphabet();

		TEST_METHOD(ReturnsCorrectSizeOfAlphabet)
		{
			vector<char> alpha;
			alpha.push_back('1');
			alpha.push_back('2');
			inputAlpha->Alphabet(alpha);
			alpha.push_back('3');
			tapeAlpha->Alphabet(alpha);

			Assert::AreEqual(tapeAlpha->Size(), 3);
			Assert::AreEqual(inputAlpha->Size(), 2);
		}

		TEST_METHOD(ReturnsElementAtCorrectIndex)
		{
			vector<char> tapeAlph;
			vector<char> inputAlph;
			tapeAlph.push_back('1');
			inputAlph.push_back('2');
			tapeAlph.push_back('3');
			inputAlph.push_back('1');
			tapeAlpha->Alphabet(tapeAlph);
			inputAlpha->Alphabet(inputAlph);

			Assert::AreEqual(tapeAlpha->Element(0), '1');
			Assert::AreEqual(inputAlpha->Element(0), '2');
			Assert::AreEqual(tapeAlpha->Element(1), '3');
			Assert::AreEqual(inputAlpha->Element(1), '1');
		}

		TEST_METHOD(AccuratelyFindsMembersOfAlphabet)
		{
			vector<char> tapeAlph;
			vector<char> inputAlph;
			tapeAlph.push_back('1');
			inputAlph.push_back('2');
			tapeAlpha->Alphabet(tapeAlph);
			inputAlpha->Alphabet(inputAlph);

			Assert::AreEqual(tapeAlpha->IsElement('1'), true);
			Assert::AreEqual(inputAlpha->IsElement('2'), true);

			// Shouldn't find elements of other alphabet
			Assert::AreEqual(tapeAlpha->IsElement('2'), false);
			Assert::AreEqual(inputAlpha->IsElement('1'), false);
		}
	};
}
