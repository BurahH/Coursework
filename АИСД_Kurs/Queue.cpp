#include <iostream>

using namespace std;

#include "Queue.h"

ListQueue::ListQueue()
{
	head = NULL;
	last = NULL;
	size = 0;
}
ListQueue::~ListQueue()
{
	while (size)
		delete_item();
}
void ListQueue::add_item(string newsymbol, double number)
{
	if (head == NULL)
	{
		Queue* temp = new Queue(newsymbol,number);
		head = temp;
		last = temp;
	}
	else
	{
		Queue* temp = new Queue(newsymbol,number);
		last->next = temp;
		last = temp;
	}
	size++;
}
void ListQueue::delete_item()
{
	if (head != NULL)
	{
		Queue* current;
		current = head->next;
		delete(head);
		head = current;
		if (head == NULL)
			last = NULL;
		size--;
	}
	else
	{
		throw out_of_range("deletion isn't possible, the list is empty");  //Exception if list is empty
	}
}

string ListQueue::get_first_string()
{
	if (head != NULL)
		return head->symbol;
	else
		throw out_of_range("The stack is empty");
}

double ListQueue::get_first_double()
{
	if (head != NULL)
		return head->number;
	else
		throw out_of_range("The stack is empty");
}

bool ListQueue::Empty()
{
	return head == NULL;
}