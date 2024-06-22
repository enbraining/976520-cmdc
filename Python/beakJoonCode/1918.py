import sys


def convert_infix_expression_to_postfix_expression(infix_expression):
    stack = list()

    for i in range(len(infix_expression) - 1):
        if (infix_expression[i] == "("):
            stack.append(infix_expression[i])
        elif (infix_expression[i] == "+" or infix_expression[i] == "-"):
            while(stack and stack[-1]!='('):
                print(stack.pop(), end="")
            stack.append(infix_expression[i])
        elif (infix_expression[i] == "*" or infix_expression[i] == "/"):
            while (stack and stack[-1] != '(' and (stack[-1] == "*" or stack[-1] =='/')):
                print(stack.pop(), end="")
            stack.append(infix_expression[i])
        elif (infix_expression[i] == ")"):
            while (stack and stack[-1] != '('):
                print(stack.pop(), end="")
            stack.pop()
        elif (infix_expression[i] >= 'A' and infix_expression[i] <= 'Z'):
            print(infix_expression[i], end="")

    if (len(stack) > 0):
        for i in range(len(stack)):
            print(stack.pop(), end="")


if __name__ == '__main__':
    infix_expression = sys.stdin.readline()
    convert_infix_expression_to_postfix_expression(infix_expression)
