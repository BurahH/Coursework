#include <iostream>

using namespace std;

#include "Stack.h"

ListStack::ListStack()
{
	head = NULL;
	size = 0;
}
ListStack::~ListStack()
{
	while (size)
		delete_item();
}
void ListStack::add_item(string newsymbol, double  data)
{
	if (head == NULL)
		head = new Stack(newsymbol, data);
	else
	{
		Stack* temp = new Stack(newsymbol, data);
		temp->next = head;
		head = temp;
	}
	size++;
}
void ListStack::delete_item()
{
	if (head != NULL)
	{
		Stack* current;
		current = head->next;
		delete(head);
		head = current;
		size--;
	}
	else
	{
		throw out_of_range("deletion isn't possible, the list is empty");
	}
}

string ListStack::get_first_string()
{
	if (head != NULL)
		return head->symbol;
	else
		throw out_of_range("The stack is empty");
}

double ListStack::get_first_double()
{
	if (head != NULL)
		return head->number;
	else
		throw out_of_range("The stack is empty");
}

bool ListStack::Empty()
{
	return head == NULL;
}
