#pragma once

class ListStack {
private:
	class Stack {
	public:
		string symbol;
		double number;
		Stack* next;
		Stack(string newsymbol, double data)
		{
			this->number = data;
			this->symbol = newsymbol;
			this->next = NULL;
		}
		~Stack() {}
	};
	Stack* head;
	size_t size;
public:
	ListStack();
	~ListStack();
	bool Empty();
	void add_item(string newsymbol, double  data);
	void delete_item();
	string get_first_string();
	double get_first_double();
};