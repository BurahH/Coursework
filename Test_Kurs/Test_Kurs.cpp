#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std;

#include <iostream>
#include <string>

#include "../АИСД_Kurs/function.h"
#include "../АИСД_Kurs/input_definition.h"
#include "../АИСД_Kurs/Queue.h"
#include "../АИСД_Kurs/Stack.h"

namespace TestKurs
{
	TEST_CLASS(Test_input_definition)
	{
	public:
		
		TEST_METHOD(Test_number)
		{
			Assert::AreEqual(number('0'), true);
			Assert::AreEqual(number('1'), true);
			Assert::AreEqual(number('2'), true);
			Assert::AreEqual(number('3'), true);
			Assert::AreEqual(number('4'), true);
			Assert::AreEqual(number('5'), true);
			Assert::AreEqual(number('6'), true);
			Assert::AreEqual(number('7'), true);
			Assert::AreEqual(number('8'), true);
			Assert::AreEqual(number('9'), true);
			Assert::AreEqual(number('+'), false);
			Assert::AreEqual(number('v'), false);
			Assert::AreEqual(number('.'), false);
		}
		TEST_METHOD(Test_sign)
		{
			Assert::AreEqual(sign('+'), true);
			Assert::AreEqual(sign('-'), true);
			Assert::AreEqual(sign('^'), true);
			Assert::AreEqual(sign('*'), true);
			Assert::AreEqual(sign('/'), true);
			Assert::AreEqual(sign('5'), false);
			Assert::AreEqual(sign('v'), false);
			Assert::AreEqual(sign('.'), false);
		}
		TEST_METHOD(Test_point)
		{
			Assert::AreEqual(point('.'), true);
			Assert::AreEqual(point(','), true);
			Assert::AreEqual(point('5'), false);
			Assert::AreEqual(point('v'), false);
			Assert::AreEqual(point('+'), false);
		}
		TEST_METHOD(Test_brackets)
		{
			Assert::AreEqual(brackets('('), true);
			Assert::AreEqual(brackets(')'), true);
			Assert::AreEqual(brackets('5'), false);
			Assert::AreEqual(brackets('v'), false);
			Assert::AreEqual(brackets('+'), false);
		}
		TEST_METHOD(Test_check_const)
		{
			int count = 0;
			Assert::AreEqual(check_const("e",count), 2.7182818284);
			count = 0;
			Assert::AreEqual(check_const("pi", count), 3.1415926535);
			count = 0;
			Assert::AreEqual(check_const("cos", count), 0.0);
			count = 0;
			Assert::AreEqual(check_const("tg", count), 0.0);
		}
		TEST_METHOD(Test_check_function)
		{
			int count = 0;
			string temp;
			bool show;
			if (check_function("e", count) == "-")
				show = true;
			Assert::AreEqual(show, true);
			count = 0;
			show = false;
			if (check_function("pi", count) == "-")
				show = true;
			Assert::AreEqual(show, true);
			count = 0;
			show = false;
			if (check_function("cos", count) == "cos")
				show = true;
			Assert::AreEqual(show, true);
			count = 0;
			show = false;
			if (check_function("sin", count) == "sin")
				show = true;
			Assert::AreEqual(show, true);
			count = 0;
			show = false;
			if (check_function("ln", count) == "ln")
				show = true;
			Assert::AreEqual(show, true);
			count = 0;
			show = false;
			if (check_function("tg", count) == "tg")
				show = true;
			Assert::AreEqual(show, true);
			count = 0;
			show = false;
		}
		TEST_METHOD(Test_check_unary)
		{
			int count = 5;
			Assert::AreEqual(check_unary("5 + (-3)", count), true);
			count = 0;
			Assert::AreEqual(check_unary("-3 + 1", count), true);
			count = 2;
			Assert::AreEqual(check_unary("5 - 3", count), false);
			count = 8;
			Assert::AreEqual(check_unary("cos(30) - 1", count), false);
		}
		TEST_METHOD(Test_check_correct_brackets)
		{
			string String = "(5-1))";
			try {
				check_correct_brackets(String);
			}
			catch (const char* s)
			{
				Assert::AreEqual(s, "closing parenthesis missing, retype");
			}
			String = "(5-1)+(5+1)";
			try {
				check_correct_brackets(String);
			}
			catch (const char* s)
			{
				Assert::AreEqual(false, true);
			}
		}
		TEST_METHOD(Test_check_correct_input)
		{
			string String = "cis(90) - cos(60)";
			try {
				check_correct_input(String);
			}
			catch (const int s)
			{
				Assert::AreEqual(true, true);
			}
			String = "5+1+2 - cos(30) + tg(pi/4) - ln(60)";
			try {
				check_correct_input(String);
			}
			catch (const int s)
			{
				Assert::AreEqual(false, true);
			}
		}
		TEST_METHOD(Test_check_correct_function)
		{
			string String = "cos90 - cos(60)";
			try {
				check_correct_function(String);
			}
			catch (const long int s)
			{
				Assert::AreEqual(true, true);
			}
			String = "cos(30) + tg(pi/4) - ln(60)";
			try {
				check_correct_function(String);
			}
			catch (const long int s)
			{
				Assert::AreEqual(false, true);
			}
		}
		TEST_METHOD(Test_check_correct_point)
		{
			string String = "3.98.1 - 3.543";
			try {
				check_correct_point(String);
			}
			catch (const unsigned int s)
			{
				Assert::AreEqual(true, true);
			}
			String = "cos(30) + 2.112 + 3.443";
			try {
				check_correct_point(String);
			}
			catch (const unsigned int s)
			{
				Assert::AreEqual(false, true);
			}
		}
		TEST_METHOD(Test_check_sign)
		{
			string String = "5 + 4 -+ 1";
			try {
				check_sign(String);
			}
			catch (const long unsigned int s)
			{
				Assert::AreEqual(true, true);
			}
			String = "cos(30) + 2.112 + 3.443";
			try {
				check_sign(String);
			}
			catch (const long unsigned int s)
			{
				Assert::AreEqual(false, true);
			}
		}
		TEST_METHOD(Test_check_last_sign)
		{
			string String = "5 + 4 +";
			try {
				check_last_sign(String);
			}
			catch (const char* s)
			{
				Assert::AreEqual(s, "The expression cannot end with a sign");
			}
			String = "cos(30) + 2.112 + 3.443";
			try {
				check_last_sign(String);
			}
			catch (const char* s)
			{
				Assert::AreEqual(false, true);
			}
		}
		TEST_METHOD(Test_check_brackets_sign)
		{
			string String = "5 + 4 +";
			try {
				check_brackets_sign(String);
			}
			catch (const char* s)
			{
				Assert::AreEqual(s, "The expression cannot end with a sign");
			}
			String = "cos(30) + 2.112 + 3.443";
			try {
				check_brackets_sign(String);
			}
			catch (const char* s)
			{
				Assert::AreEqual(false, true);
			}
		}
	};
	TEST_CLASS(Test_function)
	{
	public:

		TEST_METHOD(Test_list_empty)
		{
			ListQueue Queue;
			string String = "5 + 3 * 10 - cos(90)";
			bool show;
			list_empty(String, Queue);
			Assert::AreEqual(Queue.get_first_double(), 5.0);
			Queue.delete_item();
			show = false;
			if (Queue.get_first_string() == "+")
				show = true;
			Assert::AreEqual(show, true);
			Queue.delete_item();
			Assert::AreEqual(Queue.get_first_double(), 3.0);
			Queue.delete_item();
			show = false;
			if (Queue.get_first_string() == "*")
				show = true;
			Assert::AreEqual(show, true);
			Queue.delete_item();
			Assert::AreEqual(Queue.get_first_double(), 10.0);
			Queue.delete_item();
			show = false;
			if (Queue.get_first_string() == "-")
				show = true;
			Assert::AreEqual(show, true);
			Queue.delete_item();
			show = false;
			if (Queue.get_first_string() == "cos")
				show = true;
			Assert::AreEqual(show, true);
			Queue.delete_item();
			show = false;
			if (Queue.get_first_string() == "(")
				show = true;
			Assert::AreEqual(show, true);
			Queue.delete_item();
			Assert::AreEqual(Queue.get_first_double(), 90.0);
			Queue.delete_item();
			show = false;
			if (Queue.get_first_string() == ")")
				show = true;
			Assert::AreEqual(show, true);
		}

		TEST_METHOD(Test_postfix_transformation)
		{
			ListQueue infix, postfix;
			string String = "(5+3)*(4+1)";
			bool show;
			list_empty(String, infix);
			postfix_transformation(infix, postfix);
			Assert::AreEqual(postfix.get_first_double(), 5.0);
			postfix.delete_item();
			Assert::AreEqual(postfix.get_first_double(), 3.0);
			postfix.delete_item();
			show = false;
			if (postfix.get_first_string() == "+")
				show = true;
			Assert::AreEqual(show, true);
			postfix.delete_item();
			postfix_transformation(infix, postfix);
			Assert::AreEqual(postfix.get_first_double(), 4.0);
			postfix.delete_item();
			Assert::AreEqual(postfix.get_first_double(), 1.0);
			postfix.delete_item();
			show = false;
			if (postfix.get_first_string() == "+")
				show = true;
			Assert::AreEqual(show, true);
			postfix.delete_item();
			show = false;
			if (postfix.get_first_string() == "*")
				show = true;
			Assert::AreEqual(show, true);
			postfix.delete_item();
		}

		TEST_METHOD(Test_expression_calculation)
		{
			ListQueue infix, postfix,infix2, postfix2,infix3, postfix3;
			string String = "5 + 3 * 10 + 6";
			list_empty(String, infix);
			postfix_transformation(infix, postfix);
			Assert::AreEqual(expression_calculation(postfix), 41.0);
			String = "cos(0) + 4^2 - 10 - (-10) + sqrt(4) * 2";
			list_empty(String, infix2);
			postfix_transformation(infix2, postfix2);
			Assert::AreEqual(expression_calculation(postfix2), 21.0);
			String = "(1/2+1/4+1/8)^2+log(100)+abs(-100)";
			list_empty(String, infix3);
			postfix_transformation(infix3, postfix3);
			Assert::AreEqual(expression_calculation(postfix3), 102.765625);
		}
	};
	TEST_CLASS(Test_Queue)
	{
	public:

		TEST_METHOD(Test_queue)
		{
			ListQueue Queue;
			bool show;
			Queue.add_item("qwerty", 10);
			Queue.add_item("asdfgh", 6);
			Queue.add_item("zxcvb", 55);
			Assert::AreEqual(Queue.Empty(), false);
			Assert::AreEqual(Queue.get_first_double(), 10.0);
			show = false;
			if (Queue.get_first_string() == "qwerty")
				show = true;
			Assert::AreEqual(show, true);
			Queue.delete_item();
			Assert::AreEqual(Queue.get_first_double(), 6.0);
			show = false;
			if (Queue.get_first_string() == "asdfgh")
				show = true;
			Assert::AreEqual(show, true);
			Queue.delete_item();
			Assert::AreEqual(Queue.get_first_double(), 55.0);
			show = false;
			if (Queue.get_first_string() == "zxcvb")
				show = true;
			Assert::AreEqual(show, true);
			Queue.delete_item();
			Assert::AreEqual(Queue.Empty(), true);
		}
	};
	TEST_CLASS(Test_Stack)
	{
	public:
		TEST_METHOD(Test_queue)
		{
			ListStack Stack;
			bool show;
			Stack.add_item("qwerty", 10);
			Stack.add_item("asdfgh", 6);
			Stack.add_item("zxcvb", 55);
			Assert::AreEqual(Stack.Empty(), false);
			Assert::AreEqual(Stack.get_first_double(), 55.0);
			show = false;
			if (Stack.get_first_string() == "zxcvb")
				show = true;
			Assert::AreEqual(show, true);
			Stack.delete_item();
			Assert::AreEqual(Stack.get_first_double(), 6.0);
			show = false;
			if (Stack.get_first_string() == "asdfgh")
				show = true;
			Assert::AreEqual(show, true);
			Stack.delete_item();
			Assert::AreEqual(Stack.get_first_double(), 10.0);
			show = false;
			if (Stack.get_first_string() == "qwerty")
				show = true;
			Assert::AreEqual(show, true);
			Stack.delete_item();
			Assert::AreEqual(Stack.Empty(), true);
		}
	};
}
