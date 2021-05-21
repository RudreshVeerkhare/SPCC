#include <bits/stdc++.h>

using namespace std;

/*
* NAME: RUDRESH VEERKHARE
* UID: 2018130061
* BATCH: D
*
* GRAMMER FORMAT =>
* ex.
*   1       <= NonTerminal Count
*   E       {  NonTerminal Symbols
*   3       <= Terminal Count
*   i & |   {  NonTerminal Symbols
*   3       <= Productions Count
*   E=>E|E  {
*   E=>E&E  {  Productions
*   E=>i    {
*   4       <= f function table length
*   i 4     {
*   & 4     {   f table values
*   | 2     {
*   $ 0     {
*   4       <= g table length
*   i 5     {
*   & 3     {   g table values
*   | 1     {
*   $ 0     {
*   1       <= errors 
*   i i     { error comparisions
*
*
*   make GRAMMER=<filename>
*       - GRAMMER -- optional grammer filename if not provided "grammer.txt" is used
*/

int main(int argc, char const *argv[]){

    // this is a reverse mapping between symbol and productions 
    // for reduction
    map<string, string> productions;
    map<string, int> f, g; // function table
    map<string, map<string, bool>> isError; // to counter error pairs
    set<string> terminals;
    set<string> nonTerminals;

    // take input grammer from file
    ifstream gFile("grammer.txt");
    if (!gFile.is_open())
        throw runtime_error("Could not open file to read grammer!");

    int count;

    // Non-Terminals
    gFile >> count; // count of Non-Terminal symbols
    for(int i=0; i<count; i++){
        string symb;
        gFile >> symb;

        // adding to list of Non-Terminals
        nonTerminals.insert(symb);
    }

    // Terminals
    gFile >> count; // count of Terminal symbols
    for(int i=0; i<count; i++){
        string symb;
        gFile >> symb;

        // adding to list of Terminals
        terminals.insert(symb);
    }

    // Productions
    gFile >> count; // count of productions
    for(int i=0; i<count; i++){
        string line;
        // get full line as a input
        gFile >> line;

        int dil = line.find("=>");
        string lhs = line.substr(0, dil); // get LHS Symbol
        
        // adding production
        productions[line.substr(dil+2)] = lhs;

    }

    // function table "f"
    gFile >> count;
    for(int i=0; i<count; i++){
        string symb;
        gFile >> symb;
        int val;
        gFile >> val;

        f[symb] = val;
    }

    // function table "g"
    gFile >> count;
    for(int i=0; i<count; i++){
        string symb;
        gFile >> symb;
        int val;
        gFile >> val;

        g[symb] = val;
    }

    // errors 
    gFile >> count;
    for(int i=0; i<count; i++){
        string s1, s2;
        gFile >> s1 >> s2;
        isError[s1][s2] = true;
    }


    // getting user input
    string input;
    cout << "Enter string for systax analysis : ";
    cin >> input;
    input += "$";

    // start of syntax analysis
    deque<string> stack;
    stack.push_back("$");
    int lookAhead = 0;
    
    // print table header
    cout << "------------------------------------------" << endl;
    cout << "Stack\t\tBuffer\t\tOperation" << endl;
    cout << "------------------------------------------" << endl;

    while (lookAhead < input.size()){
        
        // get top of stack and front of the buffer
        string sTop = stack.back();
        string bFront(1, input[lookAhead]);
        
        // print stack and buffer
        for(auto x: stack) cout << x; cout << "\t\t";
        cout << input.substr(lookAhead) << "\t\t";

        //check if bFront is in g
        if(g.find(bFront) == g.end()){
            throw runtime_error("Invalid Symbol!!");
        }

        // get sTop or sTop-1 if sTop is Non-Terminal Symbol
        if(nonTerminals.find(sTop) != nonTerminals.end()){
            if(stack.size() < 2){
                throw runtime_error("Error!");
            }
            sTop = stack[stack.size() - 2];
        }

        if(sTop == "$" && bFront == "$"){
            cout << "Accepted!" << endl;
            return 0;
        }

        //check if sTop in f
        if(f.find(sTop) == f.end()){
            throw runtime_error("Invalid Symbol!!");
        }

        // check if sTop and bFront is valid comparison or not
        if(isError[sTop][bFront] || isError[bFront][sTop]){
            throw runtime_error("Invalid Comparison!");
        }

        // Shift operation
        if (f[sTop] <= g[bFront]){
            // push in stack
            string temp(1, input[lookAhead]);
            stack.push_back(temp);
            // printing opration
            cout << "Shift" << endl;
            lookAhead++;
        }

        // Reduction operation
        else {
            // if stack top is identifier
            if(terminals.find(stack.back()) != terminals.end()){
                string handle = "";
                handle += stack.back();
                stack.pop_back();

                // check if production exists
                if(productions.find(handle) == productions.end()){
                    throw runtime_error("Invalid Handle!");
                }

                // push back to stack
                stack.push_back(productions[handle]);

                // printing opration
                cout << "Reduce : " << handle << "=>" << productions[handle] << endl;
            }

            // if stack top is not identifier
            else if (nonTerminals.find(stack.back()) != nonTerminals.end()) {
                string handle = "";
                if(stack.size() < 3)
                    throw runtime_error("Error!");

                // get last 3 symbols from stack
                for(int i=0; i<3; i++){
                    handle += stack.back();
                    stack.pop_back();
                }

                // check if production exists
                if(productions.find(handle) == productions.end()){
                    throw runtime_error("Invalid Handle!");
                }

                // push back
                stack.push_back(productions[handle]);

                // printing opration
                cout << "Reduce : " << handle << "=>" << productions[handle] << endl;
            }

            else 
                throw runtime_error("Invalid Symbol!");

        }

    }

    return 0;
}
