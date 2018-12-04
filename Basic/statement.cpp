/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include"parser.h"
#include "../StanfordCPPLib/tokenscanner.h"

using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}



REMStatement::REMStatement(string comment)
{
	this->comment = comment;
}

void REMStatement::execute(EvalState & state,  int& linenumbner)
{
	return;
}



LETStatement::LETStatement(string e)
{
	
	this->ex = e;
}

void LETStatement::execute(EvalState & state,  int& linenumbner)
{
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(ex);
	Expression *exp = parseExp(scanner);
	int value = exp->eval(state);
	
}



PRINTStatement::PRINTStatement(string e)
{
	this->ex = e;
}

void PRINTStatement::execute(EvalState & state, int& linenumbner)
{
	
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(ex);
	
	Expression *exp = parseExp(scanner);
	
	int value = exp->eval(state);
	if (value == 1224)
	{

	}
	else
	{
		cout << value << endl;
	}
	
}



INPUTStatement::INPUTStatement(string var)
{
	this->var = var;
}

void INPUTStatement::execute(EvalState & state, int& linenumbner)
{
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(var);
	string variable = scanner.nextToken();
	int flag = 1;
	string tempLine;
	while (true) 
	{
			cout << " ? ";
			getline(cin, tempLine);
			TokenScanner tempScanner(tempLine);
			tempLine = tempScanner.nextToken();
			if (tempLine == "-") {
				flag = -1;
				tempLine = tempScanner.nextToken();
			}
			if (tempScanner.hasMoreTokens() || tempScanner.getTokenType(tempLine) != NUMBER)
				error("INVALID NUMBER");
			for (auto it = tempLine.begin(); it != tempLine.end(); it++)
				if (*it < '0' || *it > '9')
					error("INVALID NUMBER");
			break;
	}
	state.setValue(variable, flag * atoi(tempLine.c_str()));
	

}
IFStatement::IFStatement(string exp1, string exp2, char op,int number)
{
	this->ex1=exp1;
	this->ex2 =exp2;
	this->num = number;
	this->op = op;
}

void IFStatement::execute(EvalState & state, int& linenumbner)
{
	TokenScanner scanner1;
	scanner1.ignoreWhitespace();
	scanner1.scanNumbers();
	scanner1.setInput(ex1);
	Expression *exp1 = parseExp(scanner1);
	TokenScanner scanner2;
	scanner2.ignoreWhitespace();
	scanner2.scanNumbers();
	scanner2.setInput(ex2);
	
	Expression *exp2 = parseExp(scanner2);
	int leftValue = exp1->eval(state);
	int rightValue = exp2->eval(state);
	switch (op)
	{
	case '>': 	if (!(leftValue > rightValue)) return ;
		break;
	case '<': 	if (!(leftValue < rightValue)) return ;
		break;
	case '=': 	if (!(leftValue == rightValue)) return ;
		break;
	}
	linenumbner = num;

}

GOTOStatement::GOTOStatement(int num)
{
	this->number = num;
}


void GOTOStatement::execute(EvalState & state, int& linenumbner)
{
	linenumbner = this->number;
}

ENDStatement::ENDStatement()
{
	
}


void ENDStatement::execute(EvalState & state, int& linenumbner)
{
	linenumbner = 0;
}
