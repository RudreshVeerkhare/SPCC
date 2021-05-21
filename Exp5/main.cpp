#include <bits/stdc++.h>
#define dhr(x) for(int _=0; _<x; _++) cout << "="; cout << endl;
#define hr(x) for(int _=0; _<x; _++) cout << "-"; cout << endl;
using namespace std;

/*
* NAME: RUDRESH VEERKHARE
* UID: 2018130061
* BATCH: D
* 
* INPUT FORMAT =>
*       abc$-*+ --> [a + b * -c] 
*           use $<operator> for unary operator
*
* USAGE =>
*       g++ -o run main.cpp && ./run
*/


set<string> op;

// checks if given string is digit or not
bool isOperator(string s){
    if(op.find(s) == op.end()) 
        return false;
    
    return true;
}

void postfixTo3Addr(string _input){
    
    int tempState = 0;
    stack<string> st;
    vector<vector<string>> table; // [[operator, result, arg1, arg2], ...]


    // handle unary operators 
    // iterate over input string and evaluate all 
    // convert input into vector of string for processing 
    vector<string> input;
    for(int i=0; i < _input.size(); i++){
        
        if (_input[i] == '$'){
            string res = "$";
            res += _input[++i];

            input.push_back(res);
        } else{
            string s(1, _input[i]);
            input.push_back(s);
        }
    }

    // iterate input
    // if it's operator pop last 2 entires and evaluate
    for (auto s: input){

        // this is for unary operator
        if (s[0] == '$'){
            string op(1, s[1]);
            string res = "t";
            res += to_string(tempState++);

            string arg1 = st.top(); st.pop();
            
            table.push_back({op, res, arg1, ""});

            st.push(res);
        }

        // this is for binary operator
        else if (isOperator(s)){
            string arg2 = st.top(); st.pop();
            string arg1 = st.top(); st.pop();

            // put in table
            string res = "t";
            res += to_string(tempState++);
            
            table.push_back({s, res, arg1, arg2});
            
            // push evaluted exp to stack
            st.push(res);
        } 
        
        // for an operand
        else
            st.push(s);
    }

    // printing table
    cout << endl;
    cout << "Quadruple representation ==> " << endl;
    
    dhr(40);
    cout << "#\tOperator Arg1\tArg2\tResult" << endl;
    dhr(40);

    for(int i=0; i < table.size(); i++){
        cout << i << "\t";
        
        cout << table[i][0] << '\t';
        cout << table[i][2] << '\t';
        cout << table[i][3] << '\t';
        cout << table[i][1] << '\t';
        
        cout << endl;
    }

    hr(40);
    cout << "\n\n";

    
}

int main(){
    
    // defining list of operators
    op.insert("+");
    op.insert("/");
    op.insert("*");
    op.insert("%");
    op.insert("!");
    op.insert("^");
    op.insert("&");
    op.insert("-");
    op.insert("|");

    // print instructions
    hr(80);
    cout << "Postfix Expression to 3 Address Instruction format Converter\n" << endl;
    cout << "Note : \n--> to use unary operator in postfix notation, add '$' before the operator" << endl;
    cout << "--> Enter 'exit' to terminate" << endl;
    hr(80);

    while (true){
        // input buffer
        string input;
        // print options 
        cout << "Enter postfix notation : ";
        cin >> input;
        
        // Terminate if empty string is given
        if (input == "exit") break;
        
        // convert postfix epression to 3 address form
        postfixTo3Addr(input);

    }
    
    return 0;
}