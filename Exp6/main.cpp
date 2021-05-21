#include <bits/stdc++.h>
#define lli long long int
#define dhl(x) for(int _=0; _<x; _++) cout << "="; cout << endl;
#define hl(x) for(int _=0; _<x; _++) cout << "-"; cout << endl;
using namespace std;

/*
* NAME: RUDRESH VEERKHARE
* UID: 2018130061
* BATCH: D
*
* 
* USAGE =>
*   USAGE =>
*   make INPUT=<filename> INTERM=<filename>
*       - INPUT -- optional input filename if not provided "input.asm" is used
*       - INTERM -- optional output filename for intermediate data
                     if not provided "intermediate.data" is used

*/

class SICAssembler {

    /*
    * This class encapsulates all the stages of 
    * 2 pass SIC assembler till object code output
    */

    public:
    // Attrinutes
        // class
        map<string, lli> SYMTAB; // symbol table
        map<string, lli> OPTAB; // opcode table
        lli LOCCTR; // Location Counter


    // Methods

        // Static Methods
        /*
        * converts hex string to long long int
        */
        static lli hexStringToInt(string num){
            stringstream ss;
            lli res;
            
            // hex to int
            ss << hex << num;
            ss >> res;
            
            return res;
        }

        /*
        * converts long long int to hex string
        */
        static string intToHexString(lli num, int len = 4){
            stringstream ss;
            string res;
            
            // int to hex
            ss << hex << num;
            string temp = ss.str();
            
            // pad with zeros to get required size
            if (temp.size() < len){
                for(int _=0; _<(len-temp.size()); _++) res += '0';
            }
            res += temp;
            return res;
        }


        // Class Methods

        /*
        * To add Symbol to SYMTAB
        * return false if symb already exists 
        * else returns true
        */
        bool addSymbol(string symb, lli addr){
            // check if symbol exists
            if(this->SYMTAB.find(symb) != this->SYMTAB.end())
                return false;

            // else add symbol to table
            this->SYMTAB[symb] = addr;
            return true;
        }

        /* 
        * To add Opcodes to OPTABLE
        */
        void addOp(string op, string hexOpcode){
            this->OPTAB[op] = SICAssembler::hexStringToInt(hexOpcode);
        }    

        /* 
        * Sets Location Counter
        */
        void setLocation(lli loc){
            this->LOCCTR = loc;
        }

        /*
        * Perform pass 1
        * takes input vector<tuple<string, string, string>> 
        *     [['Label', 'Mnemonics', 'Operands'], ...]
        * returns vector<tuple<lli, string, string, string>> 
        *     [['Location', 'Label', 'Mnemonics', 'Operands'], ...]
        */
        vector<tuple<lli, string, string, string>> 
        passOne(vector<tuple<string, string, string>> input){
            // for storing result
            vector<tuple<lli, string, string, string>> res;
            lli startAddr;

            /*--------------------------------START----------------------------------------*/
            // check for first input for START instruction
            if(get<1>(input[0]) != "START")
                throw runtime_error("Expected START intruction!");
            // get start address
            startAddr = SICAssembler::hexStringToInt(get<2>(input[0]));
            this->LOCCTR = startAddr;
            // add this to intermediate file
            res.push_back(make_tuple(startAddr, get<0>(input[0]), get<1>(input[0]), get<2>(input[0])));



            // itrerate over all inputs 
            for (lli i=1; i<input.size()-1; i++){
                auto x = input[i];

                // unload tuple
                string label = get<0>(x); // Label
                string instr = get<1>(x); // instruction
                string oprnd = get<2>(x); // operand

                // result vars
                lli addr;
                string opcode;

                // check if Label is given
                if (label != ""){
                    // check if label exists in SYMTAB
                    if (this->SYMTAB.find(label) != this->SYMTAB.end()){
                        // Same Label is used more than once
                        throw runtime_error("Label used more than once! (" + label + ")");
                    }
                    // add label to symbol table
                    this->SYMTAB[label] = this->LOCCTR;
                }
            

                // check if intruction exists in OPTAB
                if (this->OPTAB.find(instr) != this->OPTAB.end()){
                    // if operator exists in table
                    // increment current address by 3 bytes
                    addr = this->LOCCTR;
                    this->LOCCTR += 3;
                } 
                // checks if it's a pseudo instruction
                else if (instr == "WORD"){
                    // then add 3 bytes to curr location
                    addr = this->LOCCTR;
                    this->LOCCTR += 3;
                } else if (instr == "RESW"){
                    // then add 3 * Operand to curr location
                    lli val = stoll(oprnd);
                    addr = this->LOCCTR;
                    this->LOCCTR += 3 * val;
                } else if (instr == "RESB"){
                    // add Operand to curr location
                    lli val = stoll(oprnd);
                    addr = this->LOCCTR;
                    this->LOCCTR += val;
                } else if (instr == "BYTE"){
                    lli len;
                    // find length of constant
                    // if it's a char rep
                    // ex. C'EOF'
                    if (oprnd[0] == 'C'){
                        len = oprnd.size() - 3;
                    }
                    // if it's hex rep
                    // ex. X'D8' 
                    else if (oprnd[0] == 'X'){
                        len = oprnd.size() - 3;
                        len = (len / 2) + (len & 1);
                    }
                    // else not recognized
                    else 
                        throw runtime_error("constant format invalid (" + oprnd + ")");
                    
                    // add len to curr address
                    addr = this->LOCCTR;
                    this->LOCCTR += len;
                }
                // else not known instruction encountered
                else
                    throw runtime_error("Invalid intruction (" + instr + ")");

                // add output to intermediate file
                res.push_back(make_tuple(addr, label, instr, oprnd));
                

            }

            /*------------------------------------END------------------------------------*/
            // check if last instruction is END or not
            lli _n = input.size() - 1;
            if(get<1>(input[_n]) != "END")
                // error: last intruction is not END
                throw runtime_error("Incomplete Code! END instruction not detected!");
            // save last address as total size of the program
            lli programSize = this->LOCCTR - startAddr;
            // add to intermediate code
            res.push_back(make_tuple(this->LOCCTR, get<0>(input[_n]), get<1>(input[_n]), get<2>(input[_n])));


            // return intermediate code
            return res;
        }


        /*
        * Perform pass 2
        * takes input vector<tuple<lli, string, string, string>> 
        *     [['Location', 'Label', 'Mnemonics', 'Operands'], ...]
        * returns vector<tuple<lli, string, string, string, string>> 
        *     [['Location', 'Label', 'Mnemonics', 'Operands', 'Opcode'], ...]
        */
        vector<tuple<lli, string, string, string, string>> 
        passTwo(vector<tuple<lli, string, string, string>> input){
            // for storing result
            vector<tuple<lli, string, string, string, string>> res;

            /*--------------------------------START----------------------------------------*/
            // check for first input for START instruction
            if(get<2>(input[0]) != "START")
                throw runtime_error("Expected START intruction!");
            // add this to result file
            res.push_back(make_tuple(get<0>(input[0]), get<1>(input[0]), get<2>(input[0]), get<3>(input[0]), ""));



            // itrerate over all inputs 
            for (lli i=1; i<input.size()-1; i++){
                auto x = input[i];

                // unload tuple
                string label = get<1>(x); // Label
                string instr = get<2>(x); // instruction
                string oprnd = get<3>(x); // operand

                // result vars
                string opcode;


                // check if intruction exists in OPTAB
                if (this->OPTAB.find(instr) != this->OPTAB.end()){
                    // if operator exists in table
                    // then add hex opcode to opcode string
                    string temp = SICAssembler::intToHexString(this->OPTAB[instr], 2);
                    opcode += temp;

                    if (this->SYMTAB.find(oprnd) == this->SYMTAB.end())
                        throw runtime_error("Label not found! (" + oprnd + ")");
                    // add address of specified label
                    opcode += SICAssembler::intToHexString(this->SYMTAB[oprnd]);
                } 
                // checks if it's a pseudo instruction
                else if (instr == "WORD"){
                    // then get size of that word
                    if(oprnd.size() < 6){
                        // make it if size 3 bytes i.e 1 word
                        for(int _=0; _<(6 - oprnd.size()); _++){
                            opcode += '0';
                        }
                    }
                    opcode += oprnd;

                } else if (instr == "BYTE"){
                    // find length of constant
                    // if it's a char rep
                    // ex. C'EOF'
                    if (oprnd[0] == 'C'){
                        // convert to hex
                        for (int i=2; i<oprnd.size()-1; i++){
                            opcode += SICAssembler::intToHexString((lli)oprnd[i], 2);
                        }
                    }
                    // if it's hex rep
                    // ex. X'D8' 
                    else if (oprnd[0] == 'X'){
                        // add it to opcode
                        for (int i=2; i<oprnd.size()-1; i++){
                            opcode += oprnd[i];
                        }
                    }
                    // else not recognized
                    else 
                        throw runtime_error("constant format invalid (" + oprnd + ")");
                    
                }
                

                // add output to result
                res.push_back(make_tuple(get<0>(input[i]), get<1>(input[i]), get<2>(input[i]), get<3>(input[i]), opcode));

            }

            /*------------------------------------END------------------------------------*/
            // check if last instruction is END or not
            lli _n = input.size() - 1;
            if(get<2>(input[_n]) != "END")
                // error: last intruction is not END
                throw runtime_error("Incomplete Code! END instruction not detected!");
            // add to result
            res.push_back(make_tuple(get<0>(input[_n]), get<1>(input[_n]), get<2>(input[_n]), get<3>(input[_n]), ""));


            // return intermediate code
            return res;
        }

        /*
        * This function converts output of pass 2 into the object code
        * takes input [['Location', 'Label', 'Mnemonics', 'Operands', 'Opcode'], ...]
        * returns ex,  [["H", "WRREC", "00105D", ...], ["T", "00105D", "1C", ...], ...]
        */
        vector<vector<string>> convertToObjectCode(vector<tuple<lli, string, string, string, string>> input){
            
            vector<vector<string>> objCode;

            // handle HEADER section
            // length of the program
            // is at the end instruction of program
            string programLen = SICAssembler::intToHexString(get<0>(input[input.size() - 1]), 6);
            objCode.push_back({"H", get<1>(input[0]), SICAssembler::intToHexString(get<0>(input[0]), 6), programLen});

            // iterate over full table 
            // also keep track of each row
            vector<string> row;
            lli index = 0;
            for(int i=1; i<input.size()-1; i++){

                // unpack
                lli addr = get<0>(input[i]);
                string label = get<1>(input[i]);
                string instr = get<2>(input[i]);
                string oprnd = get<3>(input[i]);
                string opcode = get<4>(input[i]);

                if (opcode.size() + index > 70){
                    // capacity full
                    // complete the row
                    // add length
                    
                    string programSize = SICAssembler::intToHexString((index - 10)/2, 2);
                    row[2] = programSize;
                    // add this row to objCode
                    objCode.push_back(row);
                    // reset row
                    row.clear();
                    index = 0;
                }

                if(row.size() == 0){
                    // new row
                    // add "T"
                    row.push_back("T"); index++;
                    // add start address
                    row.push_back(SICAssembler::intToHexString(addr, 6));
                    index += 6;
                    // add empty str as length and update it at the end
                    row.push_back("");
                    index += 2;
                }

                row.push_back(opcode);
                index += opcode.size();

            }

            // check if last row is finished
            if (row.size() > 0){
                // data exausted
                // complete the row
                // add length
                
                string programSize = SICAssembler::intToHexString((index - 10)/2, 2);
                row[2] = programSize;
                // add this row to objCode
                objCode.push_back(row);
                // reset row
                row.clear();
                index = 0;
            }

            // handle END record
            objCode.push_back({"E", SICAssembler::intToHexString(get<0>(input[0]), 6)});
            
            // return object code 
            return objCode;
        }

};


vector<tuple<string, string, string>> readAsm(string filename){

    // for storing data
    vector<tuple<string, string, string>> res;

    // load file
    ifstream file(filename);
    if(!file.is_open())
        throw runtime_error("Could not open file! (" + filename + ")");

    string label, instr, oprnd;
    while(file >> label >> instr >> oprnd){
        if(label == "**") label = "";
        if(instr == "**") instr = "";
        if(oprnd == "**") oprnd = "";

        res.push_back(make_tuple(label, instr, oprnd));
    }

    return res;
}

void writeInterm(vector<tuple<lli, string, string, string>> interm, string filename, bool verbose = true){
    
    // open file to write
    ofstream file(filename);
    if(!file.is_open())
        throw runtime_error("Could not open file! (" + filename + ")");

    if(verbose){
        cout << "Intermediate Data => " << endl;
        dhl(35);
        cout << "Address\tLabel\tMnemonic Operand" << endl;
        dhl(35);
    }
    for(auto x: interm){
        file << hex << get<0>(x) << "\t" << get<1>(x) << "\t" << get<2>(x) << "\t" << get<3>(x) << endl; 

        if(verbose)
            cout << hex << get<0>(x) << "\t" << get<1>(x) << "\t" << get<2>(x) << "\t" << get<3>(x) << endl; 
    }


    if(verbose) {
        hl(35);
        cout << endl;
    }
    
}


int main(int argc, char **argv){

    string inputFile = "input.asm", intermediateFile = "intermediate.data";
    if(argc == 2)
        inputFile = string(argv[1]);
    if(argc == 3){
        inputFile = string(argv[1]);
        intermediateFile = string(argv[2]);
    }  

    // reading from file
    auto input = readAsm(inputFile); 

    // creating object of assembler 
    SICAssembler assm;
    // adding operands and opcodes
    assm.addOp("LDA", "00");
    assm.addOp("LDX", "04");
    assm.addOp("LDT", "74");
    assm.addOp("TD", "E0");
    assm.addOp("JEQ", "30");
    assm.addOp("WD", "DC");
    assm.addOp("TIX", "2C");
    assm.addOp("JLT", "38");
    assm.addOp("TD", "E0");
    assm.addOp("STA", "0C");
    assm.addOp("LDCH", "50");
    assm.addOp("STCH", "54");
    
    //performing pass 1 
    // getting intermedeate data
    auto intermediate = assm.passOne(input);
    // writing intermediate data
    writeInterm(intermediate, intermediateFile);


    // performing pass 2
    auto res = assm.passTwo(intermediate);
    // printing pass 2 output
    cout << "Final Table =>" << endl;
    dhl(40);
    cout << "Address\tLabel\tMnemonic Operand ObjCode" << endl;
    dhl(40);
    for(auto x: res){
        cout << hex << get<0>(x) << "\t" << get<1>(x) << "\t" << get<2>(x) << "\t" << get<3>(x) << "\t" << get<4>(x) << endl; 
    }
    hl(40);
    cout << endl;

    
    cout << "Object code =>" << endl;
    auto objCode = assm.convertToObjectCode(res);
    for (auto x: objCode){
        for (auto s: x){
            cout << s << " ";
        }
        cout << endl;
    }
    

    return 0;
}