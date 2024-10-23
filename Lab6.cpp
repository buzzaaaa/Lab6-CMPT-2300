#include <iostream>
#include <string>
#include <vector>

std::string in2postfix(std::string); //doesn't work for bracket
std::string pre2infix(std::string);

template <class T>
class Stack
{
private:
    std::vector<T >stackVector;
public:
    void push(T);
    T pop();
    bool isEmpty() const;
    void display() const;
    T top();
    void copy(std::string &);
};
template <class T>
void Stack<T>::push(T input)
{
    stackVector.push_back(input);
}
template <class T>
T Stack<T>::pop()
{
    if (isEmpty()) {
        std::cout << "Stack is empty. Cannot pop.\n";
        return -1;
    }
    T top = stackVector.back();
    stackVector.pop_back();
    //std::cout << "Popped: " << top << '\n';
    return top;
}
template <class T>
T Stack<T>::top()
{
    if (isEmpty()) {
        std::cout << "Stack is empty. No top element.\n";
        return -1;
    }
    return stackVector.back();
}
template <class T>
bool Stack<T>::isEmpty() const{
    return stackVector.empty();
}
template <class T>
void Stack<T>::display() const
{
    if (isEmpty())
        std::cout << "The stack is empty.\n";
    else {
        for (auto i = stackVector.begin(); i != stackVector.end(); ++i) {
            std::cout << *i << " ";
        }
        std::cout << '\n';
    }
}
template <class T>
void Stack<T>::copy(std::string &input)
{
    int j = 0;
    for (auto i = stackVector.begin(); i != stackVector.end(); ++i, j++) {
        input[j] = *i;
    }
}
int main()
{
    std::string test = "A+B*C-E";
    std::string test2 = "X%D+Y-C";
    //std::cout << test.length() << '\n';
    in2postfix(test);
    in2postfix(test2);
    //for (int i = 0; i < test.length(); i++)
    //{
    //    std::cout << test[i] << " ";
    //}
    //Stack<char> testString;
    //testString.push('a');
    //testString.push('b');
    //testString.push('c');
    //test.display();
    //testString.top();
}
std::string in2postfix(std::string inputInfix) {
    Stack<char> postfix;
    Stack<char> operatorStack;
    char op;
    std::string output;
    size_t length = inputInfix.length();
    for (unsigned int i = 0; i < length; i++) {
        std::cout << inputInfix[i];
    }
    std::cout << '\n';
    for (unsigned int i = 0; i < length; i++)
    {
        if (isalpha(inputInfix[i])) {
            std::cout << "operand detected: '" << inputInfix[i] << "' push into postfix" << '\n';
            postfix.push(inputInfix[i]);
            std::cout << "-------------------------------" << '\n';
            std::cout << "postfix stack: ";
            postfix.display();
            std::cout << "-------------------------------" << '\n';
        }
        else if (inputInfix[i] == '+'
            || inputInfix[i] == '-'
            || inputInfix[i] == '*'
            || inputInfix[i] == '/'
            || inputInfix[i] == '%')
        {
            std::cout << "operator '" << inputInfix[i] << "' detected!" << '\n';
            if (operatorStack.isEmpty())
            {
                operatorStack.push(inputInfix[i]);
                std::cout << "list empty, push '" << inputInfix[i] << "' into operator stack" << '\n';
                std::cout << "-------------------------------" << '\n';
                std::cout << "operator stack: ";
                operatorStack.display();
                std::cout << "-------------------------------" << '\n';
            }
            else if ((operatorStack.top() == '*' || operatorStack.top() == '/' || operatorStack.top() == '%') && (inputInfix[i] == '+' || inputInfix[i] == '-'))//stack has more precedence than operator
            {
                std::cout << "top stack has more precedence than operator, pop operator stack and push into postfix" << '\n';
                while (!(operatorStack.isEmpty()))
                {
                    postfix.push(operatorStack.top());
                    std::cout << "-------------------------------" << '\n';
                    std::cout << "postfix stack: ";
                    postfix.display();
                    std::cout << "-------------------------------" << '\n';
                    std::cout << "poping: " << operatorStack.top() << '\n';
                    operatorStack.pop();
                }
                std::cout << "push '" << inputInfix[i] << "' into operator stack" << '\n';
                operatorStack.push(inputInfix[i]);
                std::cout << "-------------------------------" << '\n';
                std::cout << "operator stack: ";
                operatorStack.display();
                std::cout << "-------------------------------" << '\n';
            }
            else if ((inputInfix[i] == '*' || inputInfix[i] == '/' || inputInfix[i] == '%') && (operatorStack.top() == '+' || operatorStack.top() == '-')) 
            {//stack has less precedence than operator
                std::cout << "top stack has less precedence than operator, push '" << inputInfix[i] << "' into operator stack" << '\n';
                operatorStack.push(inputInfix[i]);
                std::cout << "-------------------------------" << '\n';
                std::cout << "operator stack: ";
                operatorStack.display();
                std::cout << "-------------------------------" << '\n';
            }
            else
            { //the top operator stack has the same precedence as the operator
                postfix.push(operatorStack.top());
                std::cout << "-------------------------------" << '\n';
                std::cout << "postfix stack: ";
                postfix.display();
                std::cout << "-------------------------------" << '\n';
                std::cout << "poping: " << operatorStack.top() << '\n';
                operatorStack.pop();
                operatorStack.push(inputInfix[i]);
                std::cout << "-------------------------------" << '\n';
                std::cout << "operator stack: ";
                operatorStack.display();
                std::cout << "-------------------------------" << '\n';
            }
        }
        if (i + 1 == length) {
            std::cout << "loop ended, pop all the operator stack, and push it into postfix" << '\n';
            while (!(operatorStack.isEmpty()))
            {
                postfix.push(operatorStack.top());
                std::cout << "poping: " << operatorStack.top() << '\n';
                operatorStack.pop();
            }
        }
    }
    std::cout << "displaying postfix: ";
    postfix.display();
    postfix.copy(output);
    return output;
}
