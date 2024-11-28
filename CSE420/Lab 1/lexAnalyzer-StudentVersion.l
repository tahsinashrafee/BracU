%option noyywrap

%{
#include<bits/stdc++.h>
using namespace std;

ofstream yyoutlog; //output filestream for log file

string loglist = ""; //list of tokens along with line numbers

// define necessary c++ variables and functions here (if any)
int lines = 1;

%}

/* Regular Definitions */

delim	 [ \t\v\r]

/* write regular expressions for whitespace and newline */
ws      [ \t]+		 

newline \n 

letter_	 [A-Za-z_]
digit	 [0-9]

/* write regular expressions for id, float and integers */
id      [a-zA-Z_][a-zA-Z0-9_]*	
int_const  [0-9]+
float_const [0-9]*\.[0-9]+([eE][-+]?[0-9]+)?


%%
{ws} { /* ignore whitespace */ }

{newline} { lines++; }

{id} {
    if (strcmp(yytext, "if") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <IF> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "else") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <ELSE> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "for") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <FOR> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "while") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <WHILE> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "do") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <DO> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "break") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <BREAK> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "int") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <INT> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "char") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <CHAR> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "float") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <FLOAT> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "double") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <DOUBLE> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "void") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <VOID> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "return") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <RETURN> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "switch") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <SWITCH> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "case") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <CASE> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "default") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <DEFAULT> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "continue") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <CONTINUE> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "goto") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <GOTO> Lexeme " + string(yytext) + " found\n";
    else if (strcmp(yytext, "printf") == 0)
        loglist = "Line no " + to_string(lines) + ": Token <PRINTF> Lexeme " + string(yytext) + " found\n";
    else
        loglist = "Line no " + to_string(lines) + ": Token <ID> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

{int_const} {
    loglist = "Line no " + to_string(lines) + ": Token <CONST_INT> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

{float_const} {
    loglist = "Line no " + to_string(lines) + ": Token <CONST_FLOAT> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

"+"|"-" {
    loglist = "Line no " + to_string(lines) + ": Token <ADDOP> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

"*"|"/"|"%" {
    loglist = "Line no " + to_string(lines) + ": Token <MULOP> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

"++"|"--" {
    loglist = "Line no " + to_string(lines) + ": Token <INCOP> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

"<"|">"|"=="|"<="|">="|"!=" {
    loglist = "Line no " + to_string(lines) + ": Token <RELOP> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

"=" {
    loglist = "Line no " + to_string(lines) + ": Token <ASSIGNOP> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

"&&"|"||" {
    loglist = "Line no " + to_string(lines) + ": Token <LOGICOP> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

"!" {
    loglist = "Line no " + to_string(lines) + ": Token <NOT> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

"(" {
    loglist = "Line no " + to_string(lines) + ": Token <LPAREN> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

")" {
    loglist = "Line no " + to_string(lines) + ": Token <RPAREN> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

"{" {
    loglist = "Line no " + to_string(lines) + ": Token <LCURL> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

"}" {
    loglist = "Line no " + to_string(lines) + ": Token <RCURL> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

"[" {
    loglist = "Line no " + to_string(lines) + ": Token <LTHIRD> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

"]" {
    loglist = "Line no " + to_string(lines) + ": Token <RTHIRD> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

"," {
    loglist = "Line no " + to_string(lines) + ": Token <COMMA> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

":" {
    loglist = "Line no " + to_string(lines) + ": Token <COLON> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

";" {
    loglist = "Line no " + to_string(lines) + ": Token <SEMICOLON> Lexeme " + string(yytext) + " found\n";
    yyoutlog << loglist;
}

.|\n {
    /* Ignore unrecognized characters */
}

%%





int main(int argc, char *argv[])
{

	if(argc != 2) //check if file name is given
	{
		cout<<"Please input file name"<<endl;
		return 0;
	}

	yyin = fopen(argv[1], "r"); //the file to be read must be assigned to yyin

	yyoutlog.open("my_log.txt", ios::trunc); // remember to rename the log file as mentioned in the spec
	
	if(yyin == NULL) // file does not exist
	{
		// print error message and exit
	}
	
	yylex(); // start reading the input file in a loop
	
	//print total number of lines found in the input file
	
	yyoutlog.close();  // close the log file
	
	fclose(yyin); // close the input file
}
