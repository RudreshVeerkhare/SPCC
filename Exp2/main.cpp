#include <bits/stdc++.h>
using namespace std;

/*
* NAME: RUDRESH VEERKHARE
* UID: 2018130061
* BATCH: D
*
* INPUT FORMAT =>
* ex.
*    3          <= Non Terminal Symbols count
*    S A B      <= Non Terminal Symbols
*    2          <= Terminal Symbol count
*    a b        <= Terminal Symbols
*    3          <= Productions count
*    S=>AB      <=} 
*    A=>BS|b    <=} all productions
*    B=>SS|a    <=}
* 
* USAGE =>
*   make TARGET=<filename>
*       - TARGET -- optional input filename if not provided "input.grammer" is used
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
        static Symbol* epsilon;

        // normal
        string name; // name of the Symbol ex. A, a, A'
        deque<deque<Symbol*>> productions; // to store productions 
        bool isTerminal; // flag to determine terminal symbols
    
    // Constructor
        Symbol(string name, bool isTerminal){
            this->name = name;
            this->isTerminal = isTerminal;

            // adding to global list
            if(isTerminal)
                Symbol::terminals.push_back(this);
            else
                Symbol::nonTerminals.push_back(this);
        }


    // Methods
        // Static
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
            Symbol *S1 = new Symbol(this->name + "'", false);

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
        NT = new Symbol(name, false);// new non terminal symbol
    }

    // Terminals
    Symbol* T;
    file >> tCount;// count of terminal symbols
    for (int i=0; i<tCount; i++){
        // all T symbols
        string name;
        file >> name;
        T = new Symbol(name, true);
    }

    // Productions
    file >> prodCount; // production count
    for (int i=0; i<prodCount; i++){
        string line;
        file >> line; // take whole production input

        int dil = line.find("=>");
        Symbol* S = Symbol::getSymbol(line.substr(0, dil)); // get LHS Symbol

        deque<Symbol*> newProd;
        for (auto ch: line.substr(dil+2)){
            if(ch == '|'){
                S->addProduction(newProd);
                newProd.clear();
                continue;
            }

            string s(1, ch);
            Symbol* symb = Symbol::getSymbol(s);
            newProd.push_back(symb);
        }

        if(!newProd.empty()){
            S->addProduction(newProd);
            newProd.clear();
        }


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

void printOriginal(string fileName){
    ifstream file(fileName);
    if(!file.is_open())
        throw runtime_error("Could not open file!");
        
    cout << "Original Grammer : " << endl;
    int count;
    file >> count;
    for (int i=0; i<count; i++){
        string temp;
        file >> temp;
    }
    file >> count;
    for (int i=0; i<count; i++){
        string temp;
        file >> temp;
    }

    // prods
    file >> count;
    for (int i=0; i<count; i++){
        string temp;
        file >> temp;
        cout << temp << endl;
    }

    cout << endl;

}

void printProductions(){
    for (auto symb: Symbol::nonTerminals){
        symb->print();
    }
}

vector<Symbol*> Symbol::terminals;
vector<Symbol*> Symbol::nonTerminals;
Symbol* Symbol::epsilon = new Symbol("ε", true);

int main(int argc, char **argv){
    string inputFile = "input.grammer";
    if(argc == 2)
        inputFile = string(argv[1]);

    printOriginal(inputFile);
    processGrammer(inputFile);
    cout << endl; // just seperation
    cout << "Grammer after removing Left recursion : " << endl;
    printProductions();
    return 0;
}