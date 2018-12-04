/*
 * File: Basic.cpp
 * ---------------
 * Name: [ÂíÖÂÔ¶]
 * Section: [ÂíÖÂÔ¶]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
   
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cerr << "Error: " << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state) 
{
	
        TokenScanner scanner;
		scanner.ignoreWhitespace();
		scanner.scanNumbers();
		scanner.setInput(line);
		string firstToken = scanner.nextToken();
		if (scanner.getTokenType(firstToken) == NUMBER)
		{
					if (scanner.hasMoreTokens())
					{   
						
						int i = scanner.getPosition();
						if (i > 0 && i < line.size())
						{
							program.addSourceLine(atoi(firstToken.c_str()), line.substr(i));
							program.setParsedStatement(atoi(firstToken.c_str()), line.substr(i));
						}
						else
						{
							program.addSourceLine(atoi(firstToken.c_str())," ");
							program.setParsedStatement(atoi(firstToken.c_str()), " ");
						}
					}
				    else
                    {
						program.removeSourceLine(atoi(firstToken.c_str()));
                    }
		}
		else
		{
			if (firstToken == "QUIT")
			{
				exit(0);
			}
			if (firstToken == "RUN")
			{
				program.run(state);
				
			}
			if (firstToken == "LIST")
			{
				int linenum = program.getFirstLineNumber();
				do
				{
					cout << linenum << " " << program.getSourceLine(linenum) << endl;
					linenum = program.getNextLineNumber(linenum);
				} while (linenum != 0);
			}
			if (firstToken == "CLEAR")
			{
				program.clear();
				state.clear();
			}
			
			if(firstToken=="LET")
			{
				if (scanner.hasMoreTokens())
				{
						string temp = line.substr(3);
						
						TokenScanner scanner1;
						scanner1.ignoreWhitespace();
						scanner1.scanNumbers();
						scanner1.setInput(temp);
						Expression *exp = parseExp(scanner1);
						int value = exp->eval(state);
						
					
				}
			}
			if(firstToken=="PRINT")
			{
				if (scanner.hasMoreTokens())
				{
					int i = scanner.getPosition();
					string temp = line.substr(5);
					TokenScanner scanner1;
					scanner1.ignoreWhitespace();
					scanner1.scanNumbers();
					scanner1.setInput(temp);
					Expression *exp = parseExp(scanner1);
					int value = exp->eval(state);
					if (value == 1224)
					{

					}
					else
					{
						cout << value << endl;
					}

				}
				
			}
			if(firstToken=="INPUT")
			{
				string variable = scanner.nextToken();
		        int flag = 1;
				bool flag2 = 0;
		        string tempLine;

		        while (flag2==0) 
				{
			
				cout << " ? ";
				getline(cin, tempLine);
				TokenScanner tempScanner(tempLine);
				flag2 = 1;
				tempLine = tempScanner.nextToken();
				if (tempLine == "-"){
					flag = -1;
					tempLine = tempScanner.nextToken();
				}
				if (tempScanner.hasMoreTokens() || tempScanner.getTokenType(tempLine) != NUMBER)
				{
					cout << "INVALID NUMBER" << endl;
					flag2 = 0;
					continue;
				}
				for (auto it = tempLine.begin(); it != tempLine.end(); it++)
				{
					if (*it < '0' || *it > '9')
					{
						cout << "INVALID NUMBER" << endl;
						flag2 = 0;
						break;
					}
				}
			
		        }
		     state.setValue(variable, flag * atoi(tempLine.c_str()));
		
			}

		}
	
	


}

