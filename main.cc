/*
Easy Parser Regex Project

@author: Joe Insalaco
@author: Will Zheng
@author: Bernard Tran
*/

#include <iostream>
#include <stdio.h>
#include <regex>
#include <string>
#include <fstream>

using namespace std::regex_constants;
using namespace std;

class easyParser {
private:
    string source;
    smatch ans;

    regex identifier = regex("[a-zA-Z_][a-zA-Z_0-9]*[\t\r\n ]*");
    regex intConst = regex("-?[0-9]+[\t\r\n ]*");
    regex longConst = regex("-?[0-9]+L[\t\r\n ]*");
    regex floatConst = regex("-?([0-9]+[.])[0-9]+[\t\r\n ]*");
    regex whitespace = regex("[\\s ]+");
    regex keyword = regex("if|else|while|do|for|break|continue|try|catch|void|int|float|double|char|string|const[\t \r \n ]*"); 

public:

    easyParser(){
        string source;
    }
    
    ~easyParser(){
        
    }

    //void foundIdentifier(uint32_t start, uint32_t end) 
    void foundIdentifier(string s){
        auto words_begin = sregex_iterator(s.begin(), s.end(), identifier);
        auto words_end = sregex_iterator();
        for(sregex_iterator i = words_begin; i != words_end; ++i){
            ans = *i;
            std::cout << "Found Identifier: " << endl;
            std::cout << "    " << ans.str() << endl;
        }
    }

    //void foundIntConst(uint32_t start, uint32_t end) 
    void foundIntConst(string s){
        auto words_begin = sregex_iterator(s.begin(), s.end(), intConst);
        auto words_end = sregex_iterator();
        for(sregex_iterator i = words_begin; i != words_end; ++i){
            ans = *i;
            std::cout << "Found IntConst: " << endl;
            std::cout << "    " << ans.str() << endl;
        }

    }
    
    //void foundLongConst(uint32_t start, uint32_t end) 
    void foundLongConst(string s){
        auto words_begin = sregex_iterator(s.begin(), s.end(), longConst);
        auto words_end = sregex_iterator();
        for(sregex_iterator i = words_begin; i != words_end; ++i){
            ans = *i;
            std::cout << "Found Long Const: " << endl;
            std::cout << "    " << ans.str() << endl;
        }
    }
    
    //void foundFloatConst(uint32_t start, uint32_t end) 
    void foundFloatConst(string s){
        auto words_begin = sregex_iterator(s.begin(), s.end(), floatConst);
        auto words_end = sregex_iterator();
        for(sregex_iterator i = words_begin; i != words_end; ++i){
            ans = *i;
            std::cout << "Found Float Const: " << endl;
            std::cout << "    " << ans.str() << endl;
        }
    }

    //void foundWhitespace(uint32_t start, uint32_t end) 
    void foundWhitespace(string s){
        auto words_begin = sregex_iterator(s.begin(), s.end(), whitespace);
        auto words_end = sregex_iterator();
        for(sregex_iterator i = words_begin; i != words_end; ++i){
            ans = *i;
            std::cout << "Found Whitespace at position: " << ans.position() << endl;
            //std::cout << "    " << ans.str() << endl;
        }
    }

    //void foundKeyword(uint32_t start, uint32_t end) 
    void foundKeyword(string s){
        auto words_begin = sregex_iterator(s.begin(), s.end(), keyword);
        auto words_end = sregex_iterator();
        for(sregex_iterator i = words_begin; i != words_end; ++i){
            ans = *i;
            std::cout << "Found Keyword: " << endl;
            std::cout << "    " << ans.str() << endl;
        }
    }

    void parseRegex(string regexString) {
        source = regexString;
        //for(int i = 0; i < input.length(); i++) 
        //{
            foundIdentifier(source);
            foundIntConst(source);
            foundLongConst(source);
            foundFloatConst(source);
            foundWhitespace(source);
            foundKeyword(source);
        //}
    }

};

int main() {
    easyParser start;
    string regexInput, fileString;
    int index = 0;

    ifstream readFile;
    readFile.open("test1.txt");

    if (!readFile) {
	    cout << "No file" << endl;

        cout << "Input REGEX string: " << endl;
        //cin >> regexInput;
        //cin >> noskipws >> regexInput;
        getline(cin, regexInput);
        start.parseRegex(regexInput);
    }
	else {
		char fileInput;

		while (1) 
        {
            readFile >> noskipws;
			readFile >> fileInput;
            fileString += fileInput;
			if (readFile.eof())
				break;
		}

        cout << fileString << endl;

        start.parseRegex(fileString);
	}
    readFile.close();

    return 0;
}

/*
Easy Parser Project
Parsing is overly complicated using current tools like lex and yacc.
Focus on the lexical analysis problem of identifying a token and executing code.
First, implement a regular expression engine that can identify all the standard features.
Then, create a hierarchical engine that will in a single operation read a token and execute the appropriate function.

For example:

Regex identifier(“[a-zA-Z_][a-zA-Z_0-9]*”);
Regex intConst(“-?[0-9]+”);
Regex longConst(“-?[0-9]+L”);
Regex floatConst(“...”); // your job, big and complicated!
Regex whitespace([ \\t\\r\\n]+); // a sequence of at least one space
Regex keyword(“if|else|while|do|for|break|continue|try|catch|...”);
etc.

Now imagine reading in a line.
Your code should read in the next token, and identify which of these (and potentially many more) regular expressions match.
There is no easy way to do this in the regex engine.
You could match one pattern with everything, and then check which pattern matches it, or you could iterate trying multiple patterns.
Instead, write code which identifies which and executes a matching function. The syntax should be simple and easy.

The following is only an example:


identifier	[a-zA-Z_][a-zA-Z_0-9]*				foundIdentifier
intConst	-?[0-9]+						foundIntConst
longConst	-?[0-9]+L						foundLongConst
floatConst	[+\-]?[0-9]+...						foundFloatConst
whitespace	[ \\t\\r\\n]+						foundWhiteSpace
keyword	if|else|while|do|for|break|continue|try|catch|...	foundKeyWord

Ideally, a user of your parser would create a class like LexicalParser or Compiler
and each of the functions specifiedin the lexical file above would be methods in the user’s class.
In order to achieve very high speed, don’t allocate new memory for the string found, just identify the position and length within the file being parsed.
Here is a sample of what a class might look like in C++.
Try to make it very clean and easy to use.
If we want complex and ugly, we can always use lex!

class Compiler {
private:
  std::string source; // the text of the code
public:
  void foundIdentifier(uint32_t start, uint32_t end); 
  void foundIntConst(uint32_t start, uint32_t end); 
  void foundLongConst(uint32_t start, uint32_t end); 
  void foundFloatConst(uint32_t start, uint32_t end); 
  ...
};
*/