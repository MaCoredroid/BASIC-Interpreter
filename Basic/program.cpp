/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
#include"parser.h"
#include "../StanfordCPPLib/tokenscanner.h"
using namespace std;

Program::Program() {
	
   // Replace this stub with your own code
}

Program::~Program() {
   // Replace this stub with your own code
}


void Program::addSourceLine(int lineNumber, string line) {
	if (souceline.find(lineNumber) == souceline.end())
	{
		souceline.insert(make_pair(lineNumber,line));
	}
	else
	{
		souceline[lineNumber] = line;
	}
}

void Program::removeSourceLine(int lineNumber) {
	souceline.erase(lineNumber);
}

string Program::getSourceLine(int lineNumber) {
	

	if (souceline.find(lineNumber) != souceline.end())
	{
		
		return souceline[lineNumber];
	}
	else
	{
		error("SYNTAX ERROR");
	}
}

void Program::setParsedStatement(int lineNumber, std::string line) {
	
	    if (line == " ")
	    {
			ENDStatement *temp = new ENDStatement();
			ParsedStatement[lineNumber] = temp;
			return;
		}
	   
		TokenScanner scanner;
		scanner.ignoreWhitespace();
		scanner.scanNumbers();
		scanner.setInput(line);
		string firstToken = scanner.nextToken();
		
		if (firstToken == "REM")
		{
			int i = scanner.getPosition();
			REMStatement *temp = new REMStatement(line.substr(i));
			ParsedStatement[lineNumber] = temp;
			return;
		}
		if (firstToken == "PRINT")
		{
			int i = scanner.getPosition();
			PRINTStatement *temp = new PRINTStatement(line.substr(i));
			ParsedStatement[lineNumber] = temp;
			return;
		}
		if (firstToken == "LET")
		{
			int i = scanner.getPosition();
			LETStatement *temp = new LETStatement(line.substr(i));
			ParsedStatement[lineNumber] = temp;
			return;

		}
		if (firstToken == "INPUT")
		{
			int i = scanner.getPosition();
			INPUTStatement *temp=new INPUTStatement(line.substr(i));
			ParsedStatement[lineNumber] = temp;
			return;

		}
		if (firstToken == "IF")
		{
			string t1;
			string t2;
			string tempExpression;
			string temp;
			while ((temp = scanner.nextToken()) != "=" && temp != ">" && temp != "<" && scanner.hasMoreTokens()) {
				tempExpression += temp;
			}
			t1 = tempExpression;
			

			
			char op = temp[0];
			tempExpression = "";
			while ((temp = scanner.nextToken()) != "THEN") {
				tempExpression += temp;
			}
			t2 = tempExpression;
			string tempLine = scanner.nextToken();
			
			
			int num= atoi(tempLine.c_str());
			
			IFStatement *temp2=new IFStatement(t1,t2, op,num);
			ParsedStatement[lineNumber] = temp2;
			return;
			
		}
		if (firstToken == "GOTO")
		{
			string tempLine = scanner.nextToken();
			if (scanner.hasMoreTokens() || scanner.getTokenType(tempLine) != NUMBER)
				error("INVALID NUMBER");
			for (auto it = tempLine.begin(); it != tempLine.end(); it++)
				if (*it < '0' || *it > '9')
					error("INVALID NUMBER");
			int num = atoi(tempLine.c_str());
			GOTOStatement *temp=new GOTOStatement(num);
			ParsedStatement[lineNumber] = temp;
			return;
		}
		if (firstToken == "END")
		{
			ENDStatement *temp= new ENDStatement;
			ParsedStatement[lineNumber] = temp;
			return;
		}

	
}

Statement *Program::getParsedStatement(int lineNumber) {
	if (ParsedStatement.find(lineNumber) == ParsedStatement.end())
	{

	}
	else
	{
		return ParsedStatement[lineNumber];
	}
}

int Program::getFirstLineNumber() {
	return souceline.begin()->first;
}

int Program::getNextLineNumber(int lineNumber) {
	if (++souceline.find(lineNumber) == souceline.end())
	{
		
		return 0;
	}
	map<int, string>::iterator it = ++souceline.find(lineNumber);
	return it->first;
}

void Program::run(EvalState &state)
{
	int linenum = getFirstLineNumber();
	bool flag = 1;
	do
	{
		
		if (linenum == 0)
		{
			return;
		}
		int temp = linenum;
		if (ParsedStatement.find(linenum) != ParsedStatement.end())
		{
			ParsedStatement[linenum]->execute(state, linenum);
		}
		else
		{
			cout << "LINE NUMBER ERROR" << endl;
			return;
		}
		if (temp == linenum)
		{
			linenum = getNextLineNumber(linenum);
		}
		
		


		
	} while (linenum != 0);
	
	
}
