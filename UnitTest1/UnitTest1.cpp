#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB_12.12S/LAB_12.12S.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestAddEmployee)
		{
			LinkedList phoneBook;
			Employee emp("Doe", "12345", "101");

			phoneBook.addEmployee(emp);

			Assert::IsNotNull(phoneBook.searchByPhoneNumber("12345"));
		}

		TEST_METHOD(TestDeleteEmployee)
		{
			LinkedList phoneBook;
			Employee emp("Doe", "12345", "101");
			phoneBook.addEmployee(emp);

			phoneBook.deleteEmployee("12345");

			Assert::IsNull(phoneBook.searchByPhoneNumber("12345"));
		}
	};
}
