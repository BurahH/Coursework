#include <iostream>
#include <string>
#include <math.h>

using namespace std;

#include "Queue.h"
#include "function.h"
#include "input_definition.h"
#include "Stack.h"

void list_empty(string entered, ListQueue& Queue)
{
	string temp_string;
	int count = 0, transform = 0;
	double data = 0, pass = 0;
	bool minus;
	char temp;
	while (entered[count] != NULL)
	{
		if (number(entered[count]))
		{
			minus = false;
			if(count > 0)
			    if(entered[count - 1] == '-')
			         minus = check_unary(entered, count-1);
			if(count > 1)
			    if ((entered[count - 1] == ' ') && (entered[count - 2] == '-'))
				    minus = check_unary(entered, count - 2);
			data = 0;
			while (number(entered[count]))
			{
				transform = entered[count] - '0';
				data = data * 10 + transform;
				count++;
			}
			if (point(entered[count]))
			{
				count++;
				pass = 0.1;
				while (number(entered[count]))
				{
					transform = entered[count] - '0';
					data = data + (transform * pass);
					count++;
					pass = pass * 0.1;
				}
			}
			if (minus)
				data = -data;
			Queue.add_item("NULL", data);
		}
		if (sign(entered[count]))
		{
			if (entered[count] != '-')
			{
				temp_string = entered[count];
				Queue.add_item(temp_string, 0);
			}
			else
			{
				if (check_unary(entered, count) != true)
				{
					temp_string = entered[count];
					Queue.add_item(temp_string, 0);
				}
			}
			count++;
		}
		if (brackets(entered[count]))
		{
			temp_string = entered[count];
			Queue.add_item(temp_string, 0);
			count++;
		}
		data = check_const(entered, count);
		if (data != 0)
		{
			Queue.add_item("NULL", data);
			count++;
		}
		temp_string = check_function(entered, count);
		if (temp_string != "-")
		{
			Queue.add_item(temp_string, 0);
			count++;
		}
		if (entered[count] == ' ')
			count++;
	}
}

void postfix_transformation(ListQueue& infix, ListQueue& postfix)
{
	ListStack Stack;
	int priority_stack, priority_infix, temp;
	while (infix.Empty() != true)
	{
		priority_stack = 10;
		priority_infix = 0;
		temp = 0;
		if (infix.get_first_string() == "NULL")
			postfix.add_item("NULL", infix.get_first_double());
		else if (infix.get_first_string() == "(")
			Stack.add_item("(", 0);
		else if (infix.get_first_string() == ")")
		{
			while (Stack.get_first_string() != "(")
			{
				postfix.add_item(Stack.get_first_string(), 0);
				Stack.delete_item();
			}
			Stack.delete_item();
		}
		else if ((sign(infix.get_first_string()[0])) || (check_function(infix.get_first_string(), temp = 0) != "-"))
		{
			if (check_function(infix.get_first_string(), temp = 0) != "-")
				priority_infix = 1;
			if (infix.get_first_string() == "^")
				priority_infix = 1;
			if ((infix.get_first_string() == "*") || (infix.get_first_string() == "/"))
				priority_infix = 2;
			if ((infix.get_first_string() == "+") || (infix.get_first_string() == "-"))
				priority_infix = 3;
			if (Stack.Empty() != true)
			{
				if (check_function(Stack.get_first_string(), temp = 0) != "-")
					priority_stack = 1;
				else if (Stack.get_first_string() == "^")
					priority_stack = 1;
				else if ((Stack.get_first_string() == "*") || (Stack.get_first_string() == "/"))
					priority_stack = 2;
				else if ((Stack.get_first_string() == "+") || (Stack.get_first_string() == "-"))
					priority_stack = 3;
				else
					priority_stack = 10;
			}
			else
				priority_stack = 10;
			if (priority_stack <= priority_infix)
			{
				postfix.add_item(Stack.get_first_string(), 0);
				Stack.delete_item();
				Stack.add_item(infix.get_first_string(), 0);
			}
			else 
				Stack.add_item(infix.get_first_string(), 0);
		}
		infix.delete_item();
	}
	while (Stack.Empty() != true)
	{
		postfix.add_item(Stack.get_first_string(), 0);
		Stack.delete_item();
	}
}


double expression_calculation(ListQueue& postfix)
{
	int count;
	string function;
	double result, operand1, operand2;
	ListStack Stack;
	while (postfix.Empty() != true)
	{
		count = 0;
		if (postfix.get_first_string() == "NULL")
		{
			Stack.add_item("NULL", postfix.get_first_double());
		}
		if (sign(postfix.get_first_string()[0]))
		{
			operand2 = Stack.get_first_double();
			Stack.delete_item();
			operand1 = Stack.get_first_double();
			Stack.delete_item();
			if ((postfix.get_first_string() == "+"))
				result = operand1 + operand2;
			else if ((postfix.get_first_string() == "-"))
				result = operand1 - operand2;
			else if ((postfix.get_first_string() == "*"))
				result = operand1 * operand2;
			else if ((postfix.get_first_string() == "/"))
			{
				if (operand2 == 0)
					throw "trying to divide by zero";
				result = operand1 / operand2;
			}
			else if ((postfix.get_first_string() == "^"))
				result = pow(operand1, operand2);
			Stack.add_item("NULL", result);
		}
		function = check_function(postfix.get_first_string(), count);
		if (function != "-")
		{
			operand1 = Stack.get_first_double();
			Stack.delete_item();
			if ((function == "cos"))
				result = cos(operand1);
			else if ((function == "sin"))
				result = sin(operand1);
			else if ((function == "tg"))
			{
				result = tan(operand1);
			}
			else if ((function == "ctg"))
				result = 1.0/tan(operand1);
			else if ((function == "ln"))
			{
				if (operand1 < 0)
					throw "Attempting to enter a negative number into a logarithm function";
				result = log(operand1);
			}
			else if ((function == "log"))
			{
				if (operand1 < 0)
					throw "Attempting to enter a negative number into a logarithm function";
				result = log10(operand1);
			}
			else if ((function == "sqrt"))
			{
				if (operand1 < 0)
					throw "Attempting to enter a negative number at the root";
				result = sqrt(operand1);
			}
			else if ((function == "abs"))
			{
				if (operand1 < 0)
					operand1 = -operand1;
				result = operand1;
			}
			Stack.add_item("NULL", result);
		}
		if (postfix.get_first_string() == "NULL")
		{
			if ((3.1415926535 != postfix.get_first_double()) && (2.7182818284 != postfix.get_first_double()))
				cout << postfix.get_first_double() << " ";
			if (3.1415926535 == postfix.get_first_double())
				cout << "pi" << " ";
			if (2.7182818284 == postfix.get_first_double())
				cout << "e" << " ";
		}
		else 
		    cout << postfix.get_first_string() << " ";
		postfix.delete_item();

	}
	return Stack.get_first_double();
}