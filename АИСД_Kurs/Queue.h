#pragma once

class ListQueue {
private:
	class Queue {
	public:
		double number;
		string symbol;
		Queue* next;
		Queue(string newsymbol, double number)
		{
			this->number = number;
			this->symbol = newsymbol;
			this->next = NULL;
		}
		~Queue() {}
	};
	Queue* head;
	Queue* last;
	size_t size;
public:
	ListQueue();
	~ListQueue();
	bool Empty();
	void add_item(string newsymbol, double number);
	void delete_item();
	string get_first_string();
	double get_first_double();
};