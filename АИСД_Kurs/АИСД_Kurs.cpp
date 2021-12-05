#include <iostream>
#include <string>

using namespace std;

#include "Queue.h"
#include "function.h"
#include "input_definition.h";

int main()
{
    double result;
    string into;
    int buff = 0;
    int temp = 0;
    int count = 0;
    char counter;
    ListQueue entered_string, postfix;
    cout << "Entered an expression. Enter \"end\" to exit\n";
    while (into != "end")
    {
        getline(cin, into);
        for (int count = 0; count < into.length(); count++) 
        {
            if (into[count] == ' ') 
            {
                into.erase(count, 1);
                count--;
            }
        }
        if(into != "end")
        try {
            check_correct_brackets(into);
            check_correct_input(into);
            check_correct_function(into);
            check_correct_point(into);
            check_last_sign(into);
            check_brackets_sign(into);
            check_sign(into);
            list_empty(into, entered_string);
            postfix_transformation(entered_string, postfix);
            result = expression_calculation(postfix);
            cout << " = " << result<< endl;
        }
        catch (const char* expection)
        {
            cout << "Error: " << expection << endl;
        }
        catch (const out_of_range expection)
        {
            cout << expection.what() << endl;
        }
        catch (int expection)
        {
            cout << "Error: Incorrect data entered starting from the symbol number - " << expection << endl;
            count = 0;
            while (count < expection)
            {
                cout << into[count];
                count++;
            }
            cout << " Error:";
            while (into[count] != NULL)
            {
                cout << into[count];
                count++;
            }
            cout << endl;
        }
        catch (unsigned long long expection)
        {
            cout << "Error: A closing parenthesis has been encountered that does not have an opening number on the symbol  - " << expection - 1 << endl;
            count = 0;
            while (count < expection - 1)
            {
                cout << into[count];
                count++;
            }
            cout << " Error:";
            while (into[count] != NULL)
            {
                cout << into[count];
                count++;
            }
            cout << endl;
        }
        catch (long int expection)
        {
            cout << "Error: There is no parenthesis after the function, or there is no number in parentheses . Place of error starting from symbol number - " << expection << endl;
            count = 0;
            while (count < expection)
            {
                cout << into[count];
                count++;
            }
            cout << " !Error! ";
            while (into[count] != NULL)
            {
                cout << into[count];
                count++;
            }
            cout << endl;
        }
        catch (unsigned int expection)
        {
            cout << "Error: Incorrect dot/comma location. Point symbol number - " << expection + 1 << endl;
            count = 0;
            while (count < expection-2)
            {
                cout << into[count];
                count++;
            }
            cout << " !Error!";
            while (into[count] != NULL)
            {
                cout << into[count];
                count++;
            }
            cout << endl;
        }
        catch (long unsigned int expection)
        {
            cout << "Error: Met the second sign in a row. Place error symbol number - " << expection << endl;
            count = 0;
            while (count < expection)
            {
                cout << into[count];
                count++;
            }
            cout << " Error:";
            while (into[count] != NULL)
            {
                cout << into[count];
                count++;
            }
            cout << endl;
        }
    }
}
