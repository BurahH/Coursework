#pragma once

#include "Queue.h"

void list_empty(string entered, ListQueue& Queue);
void postfix_transformation(ListQueue& infix, ListQueue& postfix);
double expression_calculation(ListQueue& postfix);
