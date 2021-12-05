#pragma once

bool number(char symbol);
bool sign(char symbol);
bool point(char symbol);
bool brackets(char symbol);
double check_const(string entered, int& count);
string check_function(string entered, int& count);
bool check_unary(string entered, int count);
void check_correct_brackets(string entered);
void check_correct_input(string entered);
void check_correct_function(string entered);
void check_correct_point(string entered);
void check_sign(string entered);
void check_last_sign(string entered);
void check_brackets_sign(string entered);