#include <iostream>
#include <string>

using namespace std;

#include "input_definition.h"

bool number(char symbol)
{
	if ((symbol == '0') || (symbol == '1') || (symbol == '2') || (symbol == '3') || (symbol == '4') || (symbol == '5') || (symbol == '6') || (symbol == '7') || (symbol == '8') || (symbol == '9'))
	{
		return true;
	}
	else
		return false;
}

bool sign(char symbol)
{
	if ((symbol == '+') || (symbol == '-') || (symbol == '*') || (symbol == '/') || (symbol == '^'))
	{
		return true;
	}
	else
		return false;
}

bool point(char symbol)
{
	if ((symbol == '.') || (symbol == ','))
	{
		return true;
	}
	else
		return false;
}

bool brackets(char symbol)
{
	if ((symbol == ')') || (symbol == '('))
	{
		return true;
	}
	else
		return false;
}

double check_const(string entered, int& count)
{
	if ((entered[count] == 'e'))
	{
		return 2.7182818284;
	}
	else if ((entered[count] == 'p') && (entered[count + 1] == 'i'))
	{
		count++;
		return 3.1415926535;
	}
	else
		return 0;
}

string check_function(string entered, int& count)
{
	if ((entered[count] == 'c') && (entered[count + 1] == 'o') && (entered[count + 2] == 's'))
	{
		count = count + 2;
		return "cos";
	}
	else if ((entered[count] == 's') && (entered[count + 1] == 'i') && (entered[count + 2] == 'n'))
	{
		count = count + 2;
		return "sin";
	}
	else if ((entered[count] == 't') && (entered[count + 1] == 'g'))
	{
		count = count + 1;
		return "tg";
	}
	else if ((entered[count] == 'c') && (entered[count + 1] == 't') && (entered[count + 2] == 'g'))
	{
		count = count + 2;
		return "ctg";
	}
	else if ((entered[count] == 'l') && (entered[count + 1] == 'n'))
	{
		count = count + 1;
		return "ln";
	}
	else if ((entered[count] == 'l') && (entered[count + 1] == 'o') && (entered[count + 2] == 'g'))
	{
		count = count + 2;
		return "log";
	}
	else if ((entered[count] == 's') && (entered[count + 1] == 'q') && (entered[count + 2] == 'r') && (entered[count + 3] == 't'))
	{
		count = count + 3;
		return "sqrt";
	}
	else if ((entered[count] == 'a') && (entered[count + 1] == 'b') && (entered[count + 2] == 's'))
	{
		count = count + 2;
		return "abs";
	}
	return "-";
}

bool check_unary(string entered, int count)
{
	if (count == 0)
		return true;
	else if (entered[count - 1] == '(')
		return true;
	else if ((entered[count - 1] == ' ') && (entered[count - 2] == '('))
		return true;
	else
		return false;
}

void check_correct_brackets(string entered)
{
	int amount = 0, count = 0;
	unsigned long long temp;
	while ((entered[count] != NULL) && (amount >= 0))
	{
		if (entered[count] == ')')
			amount--;
		if (entered[count] == '(')
			amount++;
		count++;
	}
	if (amount < 0)
	{
		temp = count;
		throw temp;
	}
	if (amount != 0)
		throw "closing parenthesis missing, retype";
}

void check_correct_input(string entered)
{
	int count = 0;
	while (entered[count] != NULL)
	{
		if ((number(entered[count]) == false) && (sign(entered[count]) == false) && (point(entered[count]) == false) && (brackets(entered[count]) == false) && (entered[count] != ' ') && (check_function(entered, count) == "-") && (check_const(entered, count) == 0))
			throw count;
		count++;
	}
}

void check_correct_function(string entered)
{
	int count = 0;
	long int temp;
	while (entered[count] != NULL)
	{
		if (check_function(entered, count) != "-")
		{
			count++;
			if (entered[count] != '(')
			{
				temp = count;
				throw temp;
			}
			else
			{
				count++;
				if ((number(entered[count]) != true) && ((entered[count] != '-') && (number(entered[count + 1]) != true)) && (check_const(entered, count) == 0) && ((entered[count] != '-') && (check_const(entered, count) == 0)))
				{
					temp = count;
					throw temp;
				}
			}
		}
		count++;
	}
}

void check_correct_point(string entered)
{
	int count = 0, point_count;
	unsigned int temp;
	while (entered[count] != NULL)
	{
		point_count = 0;
		if (point(entered[count]))
		{
			temp = count;
			throw temp;
		}
		if(number(entered[count]))
			while(((number(entered[count])) || (point(entered[count]))) && (entered[count] != NULL))
			{
				if (point(entered[count]))
					point_count++;
				count++;
			}
		if (point_count > 1)
		{
			temp = count;
			throw temp;
		}
		if(entered[count] != NULL)
		    count++;
	}
}

void check_sign(string entered)
{
	int count = 0;
	long unsigned int temp;
	while (entered[count] != NULL)
	{
		if (sign(entered[count]))
		{
			count++;
			while (entered[count] == ' ')
				count++;
			if (sign(entered[count]))
			{
				temp = count;
				throw temp;
			}
		}
		count++;
	}
}

void check_last_sign(string entered)
{
	int count = 0;
	while (entered[count] != NULL)
		count++;
	count--;
	while (entered[count] == ' ')
		count--;
	while (entered[count] == ')')
		count--;
	if (sign(entered[count]))
		throw "The expression cannot end with a sign";
}

void check_brackets_sign(string entered)
{
	int count = 0;
	while (entered[count] != NULL)
	{
		if (entered[count] == '(')
		{
			count++;
			if((entered[count] == '+') || (entered[count] == '*') || (entered[count] == '^') || (entered[count] == '/'))
				throw "There can be no sign after the open parenthesis";
		}
		count++;
	}
}
