#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool isDelimiter(char ch)
{
	if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
		ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
		ch == '[' || ch == ']' || ch == '{' || ch == '}')
		return (true);
	return (false);
}
bool isblankspace(char ch)
{
	if (ch == ' ')
		return (true);
	return (false);
}

bool isempty(char ch)
{
	if (ch == '\0')
		return (true);
	return (false);
}

/// Returns 'true' if the character :OPERATOR.
bool isOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == '>' || ch == '<' ||
		ch == '=')
		return (true);
	return (false);
}

/// Returns 'true' if the string : VALID IDENTIFIER.
bool validIdentifier(char *str)
{
	if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
		str[0] == '3' || str[0] == '4' || str[0] == '5' ||
		str[0] == '6' || str[0] == '7' || str[0] == '8' ||
		str[0] == '9' || isDelimiter(str[0]) == true || str[0] == '\0' || str[0] == '\n')
		return (false);
	return (true);
}

/// Returns 'true' if the string : KEYWORD.
bool isKeyword(char *str)
{
	if (!strcmp(str, "if") || !strcmp(str, "else") ||
		 !strcmp(str, "int") || !strcmp(str, "float") || !strcmp(str, "return"))
		return (true);
	return (false);
}

///Returns 'true' if the string :INTEGER.
bool isInteger(char *str)
{
	int i, len = strlen(str);

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++)
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
			return (false);
	}
	return (true);
}

///Returns 'true' if the string : REAL NUMBER.
bool isDecimal(char *str)
{
	int i, len = strlen(str);
	bool hasDecimal = false;

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++)
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.' ||
			(str[i] == '-' && i > 0))
			return (false);
		if (str[i] == '.')
			hasDecimal = true;
	}
	return (hasDecimal);
}

/// Extracts the SUBSTRING.
char *subString(char *str, int left, int right)
{
	int i;
	char *subStr = (char *)malloc(
		sizeof(char) * (right - left + 2));

	for (i = left; i <= right; i++)
		subStr[i - left] = str[i];
	subStr[right - left + 1] = '\0'; //inserts null at end of sunstr
	return (subStr);
}

/// scanning the input FILE.
void scan(char *str) //str pointer parameter stores address of character array
{
	int left = 0, right = 0;
	int len = strlen(str);

	while (right <= len && left <= right)
	{

		if (isDelimiter(str[right]) == false)
			right++;

		if (isDelimiter(str[right]) == true && left == right)
		{
			if (isOperator(str[right]) == true)
			{
				printf("'%c' :operater \n \n", str[right]);
				// if (st.insert(str, "local", "operater", 3))
				// {
				// 	// printf("inserted to symbol table \n");
				// }
				// else
				// {
				// 	printf("we have an error boss");
				// }
			}
			else if (isblankspace(str[right]) == true)
				printf("'%c' : blank space \n \n", str[right]);

			else if (isDelimiter(str[right]) == true)
			{
				printf("'%c' : Delimiter \n \n", str[right]);
				// if (st.insert(str, "local", "delimiter", 4))
				// {
				// 	// printf("inserted to symbol table \n");
				// }
				// else
				// {
				// 	printf("we have an error boss");
				// }
			}

			right++;
			left = right;
		}

		else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right))
		{
			char *subStr = subString(str, left, right - 1); //call to substring extractor function

			if (isKeyword(subStr) == true)
			{
				printf("'%s' : keyword\n \n", subStr);
				// if (st.insert(subStr, "local", "keyword", 4))
				// {
				// 	// printf("inserted to symbol table \n");
				// }
				// else
				// {
				// 	printf("we have an error ");
				// }
			}

			else if (isInteger(subStr) == true)
			{
				
				printf("'%s' : integer\n \n", subStr);
				// if (st.insert(subStr, "local", "number", 4))
				// {
				// 	// printf("inserted to symbol table \n");
				// }
				// else
				// {
				// 	printf("we have an error boss");
				// }
			}
			else if (isDecimal(subStr) == true)
			{
				printf("'%s' : floating point no \n \n", subStr);
				// if (st.insert(subStr, "local", "decimalno \n", 4))
				// {
				// 	printf("inserted to symbol table");
				// }
				// else
				// {
				// 	printf(" error ");
				// }
			}
			else if (validIdentifier(subStr) == true && isDelimiter(str[right - 1]) == false)
			{    
				
				printf("'%s' : accepted identifier \n \n", subStr);

			//	check =st.find(subStr);

				

				
				// if (st.insert(subStr, "local", "identifier", 9))
				// {
				// 	// printf("inserted to symbol table \n");
				// }
				// else
				// {
				// 	printf(" an error ");
				// }
			}
			else if (validIdentifier(subStr) == false && isDelimiter(str[right - 1]) == false)
				printf("'%s' : New line character \n \n", subStr);
			left = right;
		}
	}
	return;

}
