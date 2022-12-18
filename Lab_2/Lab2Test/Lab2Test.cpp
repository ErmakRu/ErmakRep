#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab 2\HeadeArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab2Test
{

	TEST_CLASS(UnitTests)
	{
	public:
		TEST_METHOD(DefaultConstructorTest)
		{
			ArrayClass<int> obj;
			Assert::IsTrue(obj.data() != nullptr);
			Assert::IsTrue(obj.size() == 0);
			Assert::IsTrue(obj.capacity() == obj.defaultCapacity());
		}
		TEST_METHOD(ParameterConstructorTest)
		{
			int capacity = 5;
			ArrayClass<std::string> obj(capacity);
			Assert::IsTrue(obj.data() != nullptr);
			Assert::IsTrue(obj.size() == 0);
			Assert::IsTrue(obj.capacity() == capacity);
		}
		TEST_METHOD(CopyConstructorTest)
		{
			ArrayClass<int> obj1;
			obj1.insert(10);
			obj1.insert(11);
			obj1.insert(12);
			ArrayClass<int> obj2 = obj1;
			Assert::IsTrue(obj2.data() != obj1.data());
			Assert::IsTrue(obj2.size() == obj1.size());
			Assert::IsTrue(obj2.capacity() == obj1.capacity());
			for (int i = 0; i < obj2.size(); i++)
			{
				Assert::IsTrue(obj2.data()[i] == obj1.data()[i]);
			}
		}

		TEST_METHOD(InsertTest)
		{
			ArrayClass<int> obj;
			int a = 10;
			Assert::IsTrue(obj[obj.insert(a)] == a);
			Assert::IsTrue(obj.size() == 1);
		}

		TEST_METHOD(InsertMiddleTest)
		{
			ArrayClass<int> obj(3);
			obj.insert(0);
			obj.insert(1);
			obj.insert(2);
			obj.insert(1, 10);
			Assert::IsTrue(obj[0] == 0);
			Assert::IsTrue(obj[1] == 10);
			Assert::IsTrue(obj[2] == 1);
			Assert::IsTrue(obj[3] == 2);
			Assert::IsTrue(obj.size() == 4);
		}
		TEST_METHOD(CopyOperatorTest)
		{
			ArrayClass<std::string> obj1;
			obj1.insert("A");
			obj1.insert("B");
			obj1.insert("C");
			ArrayClass<std::string> obj2;
			obj2 = obj1;
			Assert::IsTrue(obj2.data() != obj1.data());
			Assert::IsTrue(obj2.size() == obj1.size());
			Assert::IsTrue(obj2.capacity() == obj1.capacity());
			for (int i = 0; i < obj2.size(); i++)
			{
				Assert::IsTrue(obj2.data()[i] == obj1.data()[i]);
			}
		}

		TEST_METHOD(InsertAndRemoveString)
		{
			ArrayClass<std::string> obj(4);
			obj.insert("One");
			obj.insert("Two");
			obj.insert("Three");
			obj.insert(2, "Four");
			Assert::IsTrue(obj[2] == "Four");
			obj.insert(0, "Five");
			Assert::IsTrue(obj[0] == "Five");
			Assert::IsTrue(obj[3] == "Four");
			obj.remove(3);
			obj.remove(2);
			Assert::IsTrue(obj[0] == "Five");
			Assert::IsTrue(obj[1] == "One");
			Assert::IsTrue(obj[2] == "Three");
		}

		TEST_METHOD(RemoveStringTest)
		{
			ArrayClass<std::string> obj;
			obj.insert("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
			obj.insert("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB");
			obj.insert("CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");
			obj.remove(1);
			Assert::IsTrue(obj[0] == "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
			Assert::IsTrue(obj[1] == "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");
			Assert::IsTrue(obj.size() == 2);
		} 
		TEST_METHOD(RemoveAndIteratorTest)
		{
			ArrayClass<std::string> obj;
			obj.insert("A");
			obj.insert("B");
			obj.insert("C");
			obj.insert("D");
			obj.insert("E");
			obj.remove(1);
			obj.remove(3);
			int i = 0;
			for (auto it = obj.iterator(); it.hasCurrent(); it.next())
			{
				Assert::IsTrue(it.get() == obj[i]);
				i++;
			}
			Assert::IsTrue(obj.size() == 3);
		}		
	};
}
