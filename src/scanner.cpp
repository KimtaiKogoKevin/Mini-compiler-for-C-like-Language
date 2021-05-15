///Designing a lexical analyzer in C

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "symtb.hpp"

// SymbolTable st;
// string check;


// // Function to modify an identifier
// bool SymbolTable::modify(string id, string s,
//                          string t, int l)
// {
//     int index = hashf(id);
//     Node* start = head[index];
  
//     if (start == NULL)
//         return "-1";
  
//     while (start != NULL) {
//         if (start->identifier == id) {
//             start->scope = s;
//             start->type = t;
//             start->lineNo = l;
//             return true;
//         }
//         start = start->next;
//     }
  
//     return false; // id not found
// }

 
// // Function to delete an identifier
// bool SymbolTable::deleteRecord(string id)
// {
//     int index = hashf(id);
//     Node* tmp = head[index];
//     Node* par = head[index];
  
//     // no identifier is present at that index
//     if (tmp == NULL) {
//         return false;
//     }
//     // only one identifier is present
//     if (tmp->identifier == id && tmp->next == NULL) {
//         tmp->next = NULL;
//         delete tmp;
//         return true;
//     }
  
//     while (tmp->identifier != id && tmp->next != NULL) {
//         par = tmp;
//         tmp = tmp->next;
//     }
//     if (tmp->identifier == id && tmp->next != NULL) {
//         par->next = tmp->next;
//         tmp->next = NULL;
//         delete tmp;
//         return true;
//     }
	
  
//     // delete at the end
//     else {
//         par->next = NULL;
//         tmp->next = NULL;
//         delete tmp;
//         return true;
//     }
//     return false;
// }
// // Function to find an identifier
// string SymbolTable::find(string id)
// {
//     int index = hashf(id);
//     Node* start = head[index];
  
//     if (start == NULL)
//         return "-1";
  
//     while (start != NULL) {
  
//         if (start->identifier == id) {
//             start->print();
//             return start->scope;
//         }
  
//         start = start->next;
//     }
  
//     return "-1"; // not found
// }
  
// // Function to insert an identifier
// bool SymbolTable::insert(string id, string scope,
//                          string Type, int lineno)
// {
//     int index = hashf(id);
//     Node* p = new Node(id, scope, Type, lineno);
  
//     if (head[index] == NULL) {
//         head[index] = p;
//         cout << "\n"
//              << id << " inserted" << endl ;
  
//         return true;
//     }
  
//     else {
//         Node* start = head[index];
//         while (start->next != NULL)
//             start = start->next;
  
//         start->next = p;
//         cout << "\n"
//              << id << " inserted" << endl;
  
//         return true;
//     }
  
//     return false;
// }
// int SymbolTable::hashf(string id)
// {
//     int asciiSum = 0;
  
//     for (int i = 0; i < id.length(); i++) {
//         asciiSum = asciiSum + id[i];
//     }
  
//     return (asciiSum % 100);
// }

/// Returns 'true' if the character : DELIMITER.
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
				printf("'%s' : Not accepted by small c \n \n", subStr);
			left = right;
		}
	}
	return;
}

// DRIVER FUNCTION
int main()
{

	FILE *ptr_file;
	char buf[1000];

	ptr_file = fopen("text.txt", "r");
	if (!ptr_file)
		return 1;

	while (fgets(buf, 1000, ptr_file) != NULL)
		scan(buf);
	fclose(ptr_file);

	//find and print 'number'
    //check = st.find("k");
    // if (check != "-1")
    //     cout << "Identifier Is present\n";
    // else
    //     cout << "\nIdentifier Not Present";
  

	return 0;

	return (0);
}
