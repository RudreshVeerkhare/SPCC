#include <bits/stdc++.h>
using namespace std;

/*
* NAME: RUDRESH VEERKHARE
* UID: 2018130061
* BATCH: D
*
* GRAMMER FORMAT =>
* ex.
*   3                       <= Non Terminal count
*   D L T                   <= Non terminal symbols
*   6                       <= Terminal Symbol count
*   id ; : integer real ,   <= Terminal Symbols
*   3                       <= Production Count
*   D=>id_L_;               }
*   L=>,_id_L|:_T           } productions with symbol seperated by _
*   T=>integer|real         }
*
* SAMPLE FORMAT =>
* 6                         <= count of terminal symbols
* id , id : real ;          <= terminal symbols to parse
* USAGE =>
*   make TARGET=<filename> GRAMMER=<filename>
*       - TARGET -- optional input filename if not provided "smaple.txt" is used
*       - GRAMMER -- optional grammer filename if not provided "input.grammer" is used
*/

class Symbol {

    /* 
    * this is class representing Symbols
    * It can be both Terminal and Non-Terminal
    */

    public:
    // Attributes
        // static
        static vector<Symbol*> terminals; // all terminal symbols
        static vector<Symbol*> nonTerminals; // all non-terminal symbols
        static Symbol *epsilon, *dollar;

        // normal
        string name; // name of the Symbol ex. A, a, A'
        deque<deque<Symbol*>> productions; // to store productions 
        bool isTerminal; // flag to determine terminal symbols
        bool isStart;
    
    // Constructor
        Symbol(string name, bool isTerminal, bool isStart){
            this->name = name;
            this->isTerminal = isTerminal;
            this->isStart = isStart;

            // adding to global list
            if(isTerminal)
                Symbol::terminals.push_back(this);
            else
                Symbol::nonTerminals.push_back(this);
        }


    // Methods
        // Static
        /*
        * retruns if NonTerminal with given name is initialized or not
        * */
        static bool isPresent(string name){
            for(auto symb: Symbol::nonTerminals){
                if (symb->name == name && symb->productions.size() > 0){
                    return true;
                }
            }
            return false;
        }

        /*
        * Returns pointer to the given Symbol if present
        */
        static Symbol* getSymbol(string name){
            for(auto symb: Symbol::nonTerminals){
                if (symb->name == name){
                    return symb;
                }
            }

            for(auto symb: Symbol::terminals){
                if (symb->name == name){
                    return symb;
                }
            }
            return NULL;
        }

        /*
        * This method will find out the first of the symbol
        * returns map of <string, production>
        * 
        */
        map<string, deque<Symbol*>> first(){

            // first not applicable for terminal symbols
            if (this->isTerminal)
                throw runtime_error("Could not open file!");

            map<string, deque<Symbol*>> firsts;
            // iterate over productions
            for(auto prod: this->productions){
                Symbol* leftSym = prod.front();

                if(leftSym->isTerminal)
                    firsts[leftSym->name] = prod;
                else{
                    // get firsts of this symbol and then all it to firsts
                    map<string, deque<Symbol*>> temp = leftSym->first();
                    for(auto item: temp){
                        firsts[item.first] = item.second;
                    }
                }
            }

            return firsts;
        }

        /*
        * This method will find out the follow of the symbol
        * returns map of <string, production>
        */
        map<string, deque<Symbol*>> follow(){

            // follow not applicable for terminal symbols
            if (this->isTerminal) 
                throw runtime_error("Could not open file!");

            map<string, deque<Symbol*>> follows, temp;
            if (this->isStart){
                deque<Symbol*> dollarProd;
                dollarProd.push_back(Symbol::dollar);
                follows["$"] = dollarProd;
            }
            // iterate over all Non Terminal Symbols
            for(auto &symb: Symbol::nonTerminals){
                // iterate through it's all productions
                for(auto prod: symb->productions){
                    // check if it contains current symbol (this->name)
                    // i.e iterate through production
                    for(int i=0; i<prod.size(); i++){
                        
                        // if found curr symbol
                        if(prod[i]->name == this->name){
                            
                            // if last symbol
                            if(i+1 == prod.size()){
                                // check if LHS is same as this
                                if(symb->name == this->name)
                                    continue; // continue so as to avoid Right Recursion
                                
                                // get follow of LHS and add it to follows
                                temp.clear();
                                temp = symb->follow();
                                for(auto item: temp){
                                    follows[item.first] = item.second;
                                }
                                continue;
                            }

                            Symbol* next = prod[i+1];
                            // if terminal add to follow 
                            // note - this won't be epsilon
                            if (next->isTerminal)
                                follows[next->name] = prod;
                            // if Non Terminal symbol
                            else{
                                // get first of given symbol
                                
                                int index = 1; // next ==> i + index
                                bool isEpsilon = true; // if epsilon in the first of next; init from true to start while loop
                                while(isEpsilon){
                                    // check if index is out of bound
                                    if (i+index == prod.size()){
                                        // then append follow of LHS
                                    
                                        // check if LHS is same as this
                                        if(symb->name == this->name){
                                            isEpsilon = false;
                                            continue; // continue so as to avoid Right Recursion
                                        }
                                            
                                        
                                        // get follow of LHS and add it to follows
                                        temp = symb->follow();
                                        for(auto item: temp){
                                            follows[item.first] = item.second;
                                        }
                                    }
                                    
                                    // reassigning next
                                    next = prod[i + index];

                                    // if not index out of bound
                                    temp.clear();
                                    temp = next->first();
                                    isEpsilon = false;
                                    for(auto item: temp){
                                        if(item.first == Symbol::epsilon->name){
                                            isEpsilon = true;
                                            continue;
                                        }
                                        // append it to the follows
                                        follows[item.first] = item.second;
                                    }

                                    // increment index
                                    index++;

                                }

                            }
                        }
                    }
                }
            }

            return follows;
        }

        /*
        * This method will add new production to the symbol
        * args - 
        *   prod - 
        *       vector of Symbols prod => order is important
        */
        void addProduction(deque<Symbol*> prod){
            // just adding new prod to the back
            productions.push_back(prod);
        }

        /*
        * Checks for left recusion present or not, 
        * while doing that, it would substitue all Non-Terminals if NT is first
        * 
        * if YES returns true else false
        */
        bool isLeftRecusion(){
            // go through all prods
            int countChecked = 0;
            bool isPresent = false;
            while (countChecked < productions.size()){

                deque<Symbol*> prod = productions.front();
                Symbol *first = prod.front(); // left most symbol
                productions.pop_front();

                // if first is Non-terminal then skip
                // if it's left recusion, leave it to be handled by 'removeDirectLeftRecursion'
                if (first->isTerminal || first->name == this->name || !Symbol::isPresent(first->name)){
                    if(first->name == this->name)
                        isPresent = true;
                    countChecked++;
                    productions.push_back(prod);
                    continue;
                }

                // remove first NT from that prod
                prod.pop_front();


                for (auto firstProds: first->productions){
                    // generating new prods
                    deque<Symbol*> newProd;
                    for (auto symb: firstProds){
                        newProd.push_back(symb);
                    }
                    for (auto symb: prod){
                        newProd.push_back(symb);
                    }

                    productions.push_back(newProd);
                }
                
            }
            return isPresent;
        }

        /*
        * Removes direct left recursion if present
        * ( This function assumes that there is a left recusrsion in production )
        */
        void removeDirectLeftRecursion(){
            
            // new Symbol
            Symbol *S1 = new Symbol(this->name + "'", false, false);

            // scan all preds for left recusion
            int countChecked = 0;
            while(countChecked < productions.size()){
                
                // get production at front
                auto prod = productions.front();
                productions.pop_front();

                // left most symbol
                Symbol *first = prod[0];

                // if not a direct left recursion then put 'beta S1'
                if (first->name != this->name){
                    countChecked++;
                    prod.push_back(S1);
                    productions.push_back(prod);
                    continue;
                }

                // create new prod to add in S1
                deque<Symbol*> newProd;
                prod.pop_front(); // after this there is alpha in prod
                for (auto symb: prod){
                    newProd.push_back(symb);
                }
                // add S1 at the end
                newProd.push_back(S1);
                
                // add newProd to S1
                S1->addProduction(newProd);

            }

            // add epsilon at the end of S1
            deque<Symbol*> epProd;
            epProd.push_back(epsilon);
            S1->addProduction(epProd);
            epProd.clear();

        }
        /* prints the all producton rules of given symbol */
        void print(){
            cout << this->name << "=>";
            for(auto prod: this->productions){
                for(auto s: prod){
                    cout << s->name;
                }
                cout << "|";
            }
            cout << endl;
        }

};

void processGrammer(string fileName){
    
    string line;
    ifstream file(fileName);

    if(!file.is_open())
        throw runtime_error("Could not open file!");
    
    int ntCount, tCount, prodCount;
    
    
    // Non-Terminal 
    Symbol* NT;
    file >> ntCount; // first line will be NT count
    for (int i=0; i<ntCount; i++){
        // get all NT symbols
        string name;
        file >> name;
        bool isStart = (i == 0);
        NT = new Symbol(name, false, isStart);// new non terminal symbol
    }

    // Terminals
    Symbol* T;
    file >> tCount;// count of terminal symbols
    for (int i=0; i<tCount; i++){
        // all T symbols
        string name;
        file >> name;
        T = new Symbol(name, true, false);
    }
    cout << "Original Grammer : " << endl;
    // Productions
    file >> prodCount; // production count
    for (int i=0; i<prodCount; i++){
        string line;
        file >> line; // take whole production input
        
        int dil = line.find("=>");
        Symbol* S = Symbol::getSymbol(line.substr(0, dil)); // get LHS Symbol

        deque<Symbol*> newProd;
        string name = "";
        for (auto ch: line.substr(dil+2)){
            if(ch == '|'){
                Symbol* symb = Symbol::getSymbol(name);
                newProd.push_back(symb);
                name = "";
                S->addProduction(newProd);
                newProd.clear();
                continue;
            }
            
            if(ch == '_'){
                Symbol* symb = Symbol::getSymbol(name);
                newProd.push_back(symb);
                name = "";
                continue;
            }

            string s(1, ch);
            name += s;
        }

        if(name != ""){
            Symbol* symb = Symbol::getSymbol(name);
            newProd.push_back(symb);
            name = "";
        }

        if(!newProd.empty()){
            S->addProduction(newProd);
            newProd.clear();
        }

        S->print();

        // Check of LEFT Recursion
        bool isLeft = S->isLeftRecusion();
        if (isLeft){
            cout << "Left Recusion Detected at " << S->name << endl;
            // remove left recursion if present
            S->removeDirectLeftRecursion();
        }

    }

    file.close();

}

/*
* This function will analyse the given file 
* with provided parse table
*/
void syntaxAnalysis(string filename, map<string, map<string, deque<Symbol*>>> &parseTable){
    deque<Symbol*> stack;
    deque<string> buffer;

    // add $ to stack and buffer
    stack.push_back(Symbol::dollar);
    

    //load file into buffer
    ifstream file(filename);
    if(!file.is_open())
        throw runtime_error("Could not open file!");
    string input;
    int count;
    file >> count;
    for(int i=0; i<count; i++){
        file >> input;
        buffer.push_back(input);
    }   
    buffer.push_back("$");
    file.close();

    // push start symbol to stack
    for(auto &symb: Symbol::nonTerminals){
        if(symb->isStart){
            stack.push_back(symb);
            break;
        }
    }

    // syntax analysis
    while(!stack.empty() && !buffer.empty()){
        Symbol *stackTop = stack.back();
        string bufferPtr = buffer.front();

        // print stack and buffer
        cout << "Stack => ";
        for(auto x: stack) cout << x->name << " ";
        cout << endl;
        cout << "Buffer => ";
        for(auto x: buffer) cout << x << " ";
        cout << endl << endl;


        //if both are same
        if(stackTop->name == bufferPtr){
            stack.pop_back();
            buffer.pop_front();
            continue;
        }

        // check if production is there in parsetable
        if(parseTable[stackTop->name][bufferPtr].empty()){
            cout << "Invalid Syntax, failed to parse" << endl;
            exit(1);
        }

        auto prod = parseTable[stackTop->name][bufferPtr];
        stack.pop_back();
        reverse(prod.begin(), prod.end());
        for(auto &symb: prod)
            stack.push_back(symb);

    }

    // check if stack and buffer are empty or not
    if(!stack.empty() || !buffer.empty()){
        cout << "Invalid Syntax, failed to parse" << endl;
        exit(1);
    }

    cout << "Correct Syntax, parsing completed" << endl;
    return;
}

/*
* creates a parsing table
* returns map<string, map<string, production>>
*/
map<string, map<string, deque<Symbol*>>> createParseTable(bool print=true){
    map<string, map<string, deque<Symbol*>>> table;
    // traverse all non terminal
    for(auto &symb: Symbol::nonTerminals){
        // getting first and follow
        map<string, deque<Symbol*>> first = symb->first();

        // add production on parse table
        bool isEpsilon = false;
        deque<Symbol*> epsilonProd;
        for (auto &item: first){
            //check for epsilon
            if(item.first == Symbol::epsilon->name){
                isEpsilon = true;
                epsilonProd = item.second;
                continue;
            }

            table[symb->name][item.first] = item.second;
        }

        if(!isEpsilon)
            continue;


        // if epsilon was in fisrt then use follow also
        map<string, deque<Symbol*>> follow = symb->follow();
        for(auto &item: follow){
            table[symb->name][item.first] = epsilonProd;
        }
        
    }

    if(print){
        for(auto map1: table){
            cout << map1.first << " =>";
            for(auto item: map1.second){
                cout << "\t" << item.first << " => ";
                for(auto s: item.second)
                    cout << s->name;
                cout << endl;
            }
        }
    }

    return table;

}


void printFirsts(){
    // iterate through all of the NT symbols
    for(auto &symb: Symbol::nonTerminals){
        auto first = symb->first();
        cout << symb->name << " ==> ";
        for(auto item: first){
            cout << "\t{ " << item.first << "|";
            for(auto s: item.second){
                cout << s->name;
            }
            cout << " }"<< endl;
        }
    }
}

void printFollow(){
    // iterate through all of the NT symbols
    for(auto &symb: Symbol::nonTerminals){
        auto first = symb->follow();
        cout << symb->name << " ==> ";
        for(auto item: first){
            cout << "\t{ " << item.first << "|";
            for(auto s: item.second){
                cout << s->name;
            }
            cout << " }"<< endl;
        }
    }
}


void printProductions(){
    for (auto symb: Symbol::nonTerminals){
        symb->print();
    }
}

vector<Symbol*> Symbol::terminals;
vector<Symbol*> Symbol::nonTerminals;
Symbol* Symbol::epsilon = new Symbol("ε", true, false);
Symbol* Symbol::dollar = new Symbol("$", true, false);

int main(int argc, char **argv){
    string inputFile = "input.grammer", targetFile = "sample.txt";
    if(argc == 2)
        inputFile = string(argv[1]);
    if(argc == 3){
        inputFile = string(argv[1]);
        targetFile = string(argv[2]);
    }
    cout << endl; // just seperation
    processGrammer(inputFile);
    cout << endl; // just seperation
    cout << "Grammer after removing Left recursion : " << endl;
    printProductions();
    cout << endl; // just seperation
    cout << "Firsts : " << endl;
    printFirsts();
    cout << endl; // just seperation
    cout << "Follow : " << endl;
    printFollow();
    cout << endl; // just seperation
    cout << "Pasrsing Table : " << endl;
    map<string, map<string, deque<Symbol*>>> parsingTable = createParseTable();
    cout << endl; // just seperation
    cout << "Syntax Check : " << endl;
    syntaxAnalysis(targetFile, parsingTable);
    return 0;
} 