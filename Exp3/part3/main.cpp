# include <bits/stdc++.h>

using namespace std;

/*
* NAME    : RUDRESH VEERKHARE
* UID     : 2018130061
* ROLL No : 66
* BATCH   : D
*
* USAGE =>
*   make
*      -- program will ask for input to user and parse it.
*/

int main() {

    // defining grammer
    map<string, string> productions;
    vector<string> terminals, nonTerminals;

    terminals.push_back("+");
    terminals.push_back("*");
    terminals.push_back("a");
    terminals.push_back("b");
    terminals.push_back("$");

    terminals.push_back("E");
    terminals.push_back("T");
    terminals.push_back("F");

    // putting productions in reverse order
    // so that it'll be easy to retrive
    productions["E+T"] = "E";
    productions["T"] = "E";

    productions["TF"] = "T";
    productions["F"] = "T";

    productions["F*"] = "F";
    productions["a"] = "F";
    productions["b"] = "F";

    // to get production from index number
    map<int, string> index;
    index[1] = "E+T";
    index[2] = "T";
    index[3] = "TF";
    index[4] = "F";
    index[5] = "F*";
    index[6] = "a";
    index[7] = "b";

    // SLR parsing table
    map<int, map<string, string>> table;

    // adding rules to the table
    table[0]["a"] = "S4";
    table[0]["b"] = "S5";
    table[0]["E"] = "S1";
    table[0]["T"] = "S2";
    table[0]["F"] = "S3";

    table[1]["+"] = "S6";
    table[1]["$"] = "ACPT";

    table[2]["+"] = "R2";
    table[2]["a"] = "S4";
    table[2]["b"] = "S5";
    table[2]["$"] = "R2";
    table[2]["F"] = "S7";

    table[3]["+"] = "R4";
    table[3]["*"] = "S8";
    table[3]["a"] = "R4";
    table[3]["b"] = "R4";
    table[3]["$"] = "R4";

    table[4]["+"] = "R6";
    table[4]["*"] = "R6";
    table[4]["a"] = "R6";
    table[4]["b"] = "R6";
    table[4]["$"] = "R6";

    table[5]["+"] = "R7";
    table[5]["*"] = "R7";
    table[5]["a"] = "R7";
    table[5]["b"] = "R7";
    table[5]["$"] = "R7";

    table[6]["a"] = "S4";
    table[6]["b"] = "S5";
    table[6]["T"] = "S9";
    table[6]["F"] = "S3";

    table[7]["+"] = "R3";
    table[7]["*"] = "S8";
    table[7]["a"] = "R3";
    table[7]["b"] = "R3";
    table[7]["$"] = "R3";

    table[8]["+"] = "R5";
    table[8]["*"] = "R5";
    table[8]["a"] = "R5";
    table[8]["b"] = "R5";
    table[8]["$"] = "R5";

    table[9]["+"] = "R1";
    table[9]["a"] = "S4";
    table[9]["b"] = "S5";
    table[9]["$"] = "R1";
    table[9]["F"] = "S7";
   
    // printing production 
    cout << "Productions => " << endl;
    for(auto x: productions){
        cout << x.second << "->" << x.first << endl;
    }
    cout << endl;
    // printing LR table
    cout << "LR table => " << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    cout << '|' << "states\t";
    for (auto x: terminals) cout << '|' << x << "\t";
    cout << '|' << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    for (int i = 0; i < table.size(); i++){
        cout << '|' << i << "\t";
        for (auto x: terminals){
            if(table[i].find(x) == table[i].end()){
                cout << '|' << ' ' << '\t';
            } else {
                cout << '|' << table[i][x] << "\t";
            }
        }
        cout << '|' << endl;
    }

    cout << "-------------------------------------------------------------------------" << endl;

    // taking input string to parse
    string buffer;
    cout << "Enter a string input to parse : ";
    cin >> buffer;
    // add $ at the end of buffer
    buffer += '$';

    // stacks for symbol and it's corresponding state
    deque<string> symbls;
    deque<int> states;
    
    states.push_back(0); // init state

    int i = 0; // index to iterate buffer

    cout << "-------------------------------------------------------------" << endl;
    cout << "Symbols Stack" << "\t";
    cout << "States Stack" << "\t";
    cout << "Buffer" << "\t\t";
    cout << "Action" << endl;
    cout << "--------------------------------------------------------------" << endl;

    while (true){
        string symb(1, buffer[i]);
        int state = states.back();

        if(table[state].find(symb) == table[state].end()){
            cout << "Error!" << endl;
            exit(1);
        }

        if (table[state][symb] == "ACPT"){
            cout << "Accepted!" << endl;
            break;
        }

        string action = table[state][symb];

        if(action[0] == 'S'){
            // Shifting
            int _state = action[1] - '0';
            symbls.push_back(symb);
            states.push_back(_state);
            // print status of buffer and stack;

            // symbols stack
            for(auto _s: symbls) cout << _s;

            cout << "\t\t";

            // state stack
            for(auto _s: states) cout << _s;

            cout << "\t\t";

            // buffer
            cout << buffer.substr(i);

            cout << "\t\t";

            // action 
            cout << "Shift"<< endl;
            i++;
        } else if (action[0] == 'R'){
            // Reduction
            int _idx = action[1] - '0';
            string prod = index[_idx];
            string rprod = prod;
            reverse(rprod.begin(), rprod.end());
            for(auto _x: rprod){
                string x(1, _x);
                if (x == symbls.back()){
                    symbls.pop_back();
                    states.pop_back();
                } else {
                    cout << "Error!" << endl;
                    exit(1);
                }
            }

            string lhs = productions[prod];
            if(table[states.back()].find(lhs) == table[states.back()].end()){
                cout << "Error!" << endl;
                exit(1);
            }

            int _state = table[states.back()][lhs][1] - '0';
            states.push_back(_state);
            symbls.push_back(lhs);

            // print status of buffer and stack;

            // symbols stack
            for(auto _s: symbls) cout << _s;

            cout << "\t\t";

            // state stack
            for(auto _s: states) cout << _s;

            cout << "\t\t";

            // buffer
            cout << buffer.substr(i);

            cout << "\t\t";

            // action 
            cout << "Reduce: " << lhs << "->" << prod << endl;
            
        }


    }


    return 0;
}