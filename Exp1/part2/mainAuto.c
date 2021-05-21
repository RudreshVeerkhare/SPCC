#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int lineNo = 1;
char lexeme[5000];
FILE *fp;
/*  
    -1  - end of file
    -2  - error
    0   - init state/ clean state
    1** - Regular Expression
    2** - keywords
    9   - identifier
    5** - operators
    6** - seperators   
*/

typedef struct SymbolTable{
    char *name;
    char *val;
}SymbolTable;

SymbolTable table[100];
int indexId = 0;
int add(char *val, char *type){
    if(strcmp(type, "keyword") != 0 && strcmp(type, "identifier") != 0)
        return -1;
    for (int i = 0; i<indexId; i++){
        if(strcmp(val, table[i].val) == 0){
            return i;
        }
    }
    char *strVal = (char*) calloc(strlen(val), sizeof(char));
    char *strType = (char*) calloc(strlen(type), sizeof(char));
    strcpy(strVal, val);
    strcpy(strType, type);
    table[indexId].name = strType;
    table[indexId].val = strVal;

    return indexId++;
}

void printTable(){
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("\n==========================================\nType\t\tId\tValue\n==========================================\n");
    for(int i=0; i<indexId; i++){
        setvbuf(stdout, NULL, _IONBF, 0);
        printf("%s    \t| %d\t|%s\n", table[i].name, i, table[i].val);
        printf("------------------------------------------\n");
    }

}

char getNextChar(){
    char c = fgetc(fp);
    // setvbuf(stdout, NULL, _IONBF, 0);
    // printf("%c", c);
    if(c == '\n') lineNo++;
    return c;
}

void append(char curr){
    sprintf(lexeme, "%s%c", lexeme, curr);
}

void resetLexeme(char *type){
    setvbuf(stdout, NULL, _IONBF, 0);
    int id = add(lexeme, type);
    printf("[%d] <%s, %s, %d >\n", lineNo, type, lexeme, id);
    memset(lexeme, '\0', sizeof(lexeme));
}

int resetState(char curr){
    // also handles the " "/EOL
    // also handles if "curr" has to be appended at the end of lexeme or not
    char _curr = tolower(curr);
    switch (_curr){

        // spaces and newline
        case EOF:
            return -1;

        case '\n':
            return 0;

        case ' ':
            return 0;
        
        case '\t':
            return 0;

        // comments
        case '/':
            append(curr);
            return 100;
        
        case '{':
            append(curr);
            return 103;

        // string
        case '\'':
            append(curr);
            return 104;
        
        // digits
        case '0':
            append(curr);
            return 105;
        case '1':
            append(curr);
            return 105;
        case '2':
            append(curr);
            return 105;
        case '3':
            append(curr);
            return 105;
        case '4':
            append(curr);
            return 105;
        case '5':
            append(curr);
            return 105;
        case '6':
            append(curr);
            return 105;
        case '7':
            append(curr);
            return 105;
        case '8':
            append(curr);
            return 105;
        case '9':
            append(curr);
            return 105;
        
        // keywords initial

        case 'a':
                strncat(lexeme, &curr, 1);
                return 201;

        case 'b':
                strncat(lexeme, &curr, 1);
                return 210;

        case 'c':
                strncat(lexeme, &curr, 1);
                return 219;

        case 'd':
                strncat(lexeme, &curr, 1);
                return 244;

        case 'e':
                strncat(lexeme, &curr, 1);
                return 266;

        case 'f':
                strncat(lexeme, &curr, 1);
                return 284;

        case 'g':
                strncat(lexeme, &curr, 1);
                return 313;

        case 'i':
                strncat(lexeme, &curr, 1);
                return 317;

        case 'l':
                strncat(lexeme, &curr, 1);
                return 364;

        case 'm':
                strncat(lexeme, &curr, 1);
                return 375;

        case 'n':
                strncat(lexeme, &curr, 1);
                return 378;

        case 'o':
                strncat(lexeme, &curr, 1);
                return 385;

        case 'p':
                strncat(lexeme, &curr, 1);
                return 403;

        case 'r':
                strncat(lexeme, &curr, 1);
                return 426;

        case 's':
                strncat(lexeme, &curr, 1);
                return 440;

        case 't':
                strncat(lexeme, &curr, 1);
                return 453;

        case 'u':
                strncat(lexeme, &curr, 1);
                return 472;

        case 'v':
                strncat(lexeme, &curr, 1);
                return 482;

        case 'w':
                strncat(lexeme, &curr, 1);
                return 485;

        case 'x':
                strncat(lexeme, &curr, 1);
                return 493;        
        
        case 'h':
                append(curr);
                return 9;
        case 'j':
                append(curr);
                return 9;
        case 'k':
                append(curr);
                return 9;
        case 'q':
                append(curr);
                return 9;
        case 'y':
                append(curr);
                return 9;
        case 'z':
                append(curr);
                return 9;
        


        // operators initial

        case '.':
                strncat(lexeme, &curr, 1);
                return 501;
        case '[':
                strncat(lexeme, &curr, 1);
                return 503;
        case ']':
                strncat(lexeme, &curr, 1);
                return 504;
        case ':':
                strncat(lexeme, &curr, 1);
                return 505;
        case '+':
                strncat(lexeme, &curr, 1);
                return 507;
        case '-':
                strncat(lexeme, &curr, 1);
                return 508;
        case '*':
                strncat(lexeme, &curr, 1);
                return 509;
        case '%':
                strncat(lexeme, &curr, 1);
                return 511;
        case '&':
                strncat(lexeme, &curr, 1);
                return 512;
        case '|':
                strncat(lexeme, &curr, 1);
                return 513;
        case '!':
                strncat(lexeme, &curr, 1);
                return 514;
        case '<':
                strncat(lexeme, &curr, 1);
                return 515;
        case '>':
                strncat(lexeme, &curr, 1);
                return 517;
        case '~':
                strncat(lexeme, &curr, 1);
                return 519;
        case '=':
                strncat(lexeme, &curr, 1);
                return 521;


        case ')':
                append(curr);
                return 600;
        case '(':
                append(curr);
                return 601;
        case ';':
                append(curr);
                return 602;
        case ',':
                append(curr);
                return 603;   

        default:
            break;
    }

    return -2;
}

int isSeperator(char curr){
    // check if it's a seperating char ==> operators/' '/seperators/'\n'
    // 1 - seperator
    // 0 - not seperator
    switch (curr){

        case EOF:
            return 1;

        case '\n':
            return 1;

        case ' ':
            return 1;
        
        case '\t':
            return 1;

        // comments
        case '/':
            return 1;
        
        case '{':
            return 1;

        // operators initial
        case '.':
                return 1;
        case '[':
                return 1;
        case ']':
                return 1;
        case ':':
                return 1;
        case '+':
                return 1;
        case '-':
                return 1;
        case '*':
                return 1;
        case '%':
                return 1;
        case '&':
                return 1;
        case '|':
                return 1;
        case '!':
                return 1;
        case '<':
                return 1;
        case '>':
                return 1;
        case '~':
                return 1;
        case '=':
                return 1;


        case ')':
                return 1;
        case '(':
                return 1;
        case ';':
                return 1;
        case ',':
                return 1;
    
    default:
        break;
    }
    return 0;
}

void router(){
    // all states inside
    int state = 0;
    char curr, _curr;

    while(1){
        switch (state){
        
        case -1:
            // end of file
            printTable();
            exit(0);

        case -2:
            // error
            setvbuf(stdout, NULL, _IONBF, 0);
            printf("Unexpected symbol '%c' detected on line no %d\n", curr, lineNo);
            exit(1);

    /*=====================================Start Regular Expressions==========================================*/
        case 0:
            // this is a init state
            curr = getNextChar();
            state = resetState(curr);
            break;

        case 9:
            // identifier
            curr = getNextChar();
            if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
            }
            break;

        // comment ==> //comment
        case 100:
            // "/"
            curr = getNextChar();
            if (curr == '/'){
                // this is comment then
                state = 101;
                append(curr);
            } else {
                // it's '/' divide operator then
                resetLexeme("operator");
                state = resetState(curr);
            }
            break;
        
        case 101:
            // "// .*"
            curr = getNextChar();
            append(curr);
            // go till end of the line
            while (curr != '\n'){
                curr = getNextChar();
                append(curr);
            }
            resetLexeme("comment");
            // curr = getNextChar();
            state = resetState(curr);
            break;

        // comment ==> "{ comment }"
        case 103:
            // "{"
            curr = getNextChar();
            append(curr);
            // go till '}'
            while (curr != '}'){
                curr = getNextChar();
                append(curr);
            }
            resetLexeme("comment");
            curr = getNextChar();
            state = resetState(curr);
            break;
        
        // string 
        case 104:
            // '
            curr = getNextChar();
            append(curr);
            // go till '}'
            while (curr != '\''){
                curr = getNextChar();
                append(curr);
            }

            // append(curr);
            resetLexeme("string");
            curr = getNextChar();
            state = resetState(curr);
            break;

        // digits
        case 105:
            // '0' - one digit is already there
            curr = getNextChar();
            if('0' <= curr && curr <= '9'/* if digit */){
                append(curr);
                // state will be same
            } else if (isSeperator(curr)) {
                resetLexeme("digit");
                state = resetState(curr);
            } else {
                // error
                state = -2;
            }

            break;
        
    /*=====================================End Regular Expressions==========================================*/
    
    
    /*=====================================Start Keywords==========================================*/
    
        case 201: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 202; // <===
            }
            else if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 204; // <===
            }
            else if (_curr == 's'){
                strncat(lexeme, &curr, 1);
                state = 208; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 202: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'd'){
                strncat(lexeme, &curr, 1);
                state = 203; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 204: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 205; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 208: // s
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'm'){
                strncat(lexeme, &curr, 1);
                state = 209; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 203: // d
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 205: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 206; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 209: // m
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 206: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'y'){
                strncat(lexeme, &curr, 1);
                state = 207; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 207: // y
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 210: // b
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 211; // <===
            }
            else if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 215; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 211: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'g'){
                strncat(lexeme, &curr, 1);
                state = 212; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 215: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 216; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 212: // g
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 213; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 216: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 217; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 213: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 214; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 217: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'k'){
                strncat(lexeme, &curr, 1);
                state = 218; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 214: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 218: // k
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 219: // c
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 220; // <===
            }
            else if (_curr == 'l'){
                strncat(lexeme, &curr, 1);
                state = 223; // <===
            }
            else if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 227; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 220: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 's'){
                strncat(lexeme, &curr, 1);
                state = 221; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 223: // l
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 224; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 227: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 228; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 221: // s
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 222; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 224: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 's'){
                strncat(lexeme, &curr, 1);
                state = 225; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 228: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 's'){
                strncat(lexeme, &curr, 1);
                state = 229; // <===
            }
            else if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 239; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 222: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 225: // s
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 's'){
                strncat(lexeme, &curr, 1);
                state = 226; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 229: // s
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 230; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 239: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 240; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 226: // s
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 230: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 231; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 240: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 241; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 231: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 232; // <===
            }
            else if (_curr == 'u'){
                strncat(lexeme, &curr, 1);
                state = 234; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 241: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'u'){
                strncat(lexeme, &curr, 1);
                state = 242; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 232: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'f'){
                strncat(lexeme, &curr, 1);
                state = 233; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 234: // u
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'c'){
                strncat(lexeme, &curr, 1);
                state = 235; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 242: // u
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 243; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 233: // f
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 235: // c
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 236; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 243: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 236: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 237; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 237: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 238; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 238: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 244: // d
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 245; // <===
            }
            else if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 254; // <===
            }
            else if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 261; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 245: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 's'){
                strncat(lexeme, &curr, 1);
                state = 246; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 254: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 's'){
                strncat(lexeme, &curr, 1);
                state = 255; // <===
            }
            else if (_curr == 'v'){
                strncat(lexeme, &curr, 1);
                state = 260; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 261: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'w'){
                strncat(lexeme, &curr, 1);
                state = 262; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 246: // s
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 247; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 255: // s
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'p'){
                strncat(lexeme, &curr, 1);
                state = 256; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 260: // v
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 262: // w
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 263; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 247: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 248; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 256: // p
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 257; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 263: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 264; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 248: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'u'){
                strncat(lexeme, &curr, 1);
                state = 249; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 257: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 's'){
                strncat(lexeme, &curr, 1);
                state = 258; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 264: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 265; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 249: // u
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'c'){
                strncat(lexeme, &curr, 1);
                state = 250; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 258: // s
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 259; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 265: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 250: // c
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 251; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 259: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 251: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 252; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 252: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 253; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 253: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 266: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'l'){
                strncat(lexeme, &curr, 1);
                state = 267; // <===
            }
            else if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 270; // <===
            }
            else if (_curr == 'x'){
                strncat(lexeme, &curr, 1);
                state = 272; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 267: // l
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 's'){
                strncat(lexeme, &curr, 1);
                state = 268; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 270: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'd'){
                strncat(lexeme, &curr, 1);
                state = 271; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 272: // x
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'c'){
                strncat(lexeme, &curr, 1);
                state = 273; // <===
            }
            else if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 277; // <===
            }
            else if (_curr == 'p'){
                strncat(lexeme, &curr, 1);
                state = 279; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 268: // s
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 269; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 271: // d
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 273: // c
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 274; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 277: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 278; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 279: // p
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 280; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 269: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 274: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'p'){
                strncat(lexeme, &curr, 1);
                state = 275; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 278: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 280: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 281; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 275: // p
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 276; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 281: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 282; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 276: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 282: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 's'){
                strncat(lexeme, &curr, 1);
                state = 283; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 283: // s
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 284: // f
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 285; // <===
            }
            else if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 289; // <===
            }
            else if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 304; // <===
            }
            else if (_curr == 'u'){
                strncat(lexeme, &curr, 1);
                state = 306; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 285: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'l'){
                strncat(lexeme, &curr, 1);
                state = 286; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 289: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'l'){
                strncat(lexeme, &curr, 1);
                state = 290; // <===
            }
            else if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 292; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 304: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 305; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 306: // u
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 307; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 286: // l
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 's'){
                strncat(lexeme, &curr, 1);
                state = 287; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 290: // l
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 291; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 292: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 293; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 305: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 307: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'c'){
                strncat(lexeme, &curr, 1);
                state = 308; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 287: // s
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 288; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 291: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 293: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'l'){
                strncat(lexeme, &curr, 1);
                state = 294; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 308: // c
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 309; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 288: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 294: // l
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 295; // <===
            }
            else if (_curr == 'l'){
                strncat(lexeme, &curr, 1);
                state = 302; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 309: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 310; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 295: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'z'){
                strncat(lexeme, &curr, 1);
                state = 296; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 302: // l
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'y'){
                strncat(lexeme, &curr, 1);
                state = 303; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 310: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 311; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 296: // z
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 297; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 303: // y
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 311: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 312; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 297: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 298; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 312: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 298: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 299; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 299: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 300; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 300: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 301; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 301: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 313: // g
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 314; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 314: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 315; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 315: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 316; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 316: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 317: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'f'){
                strncat(lexeme, &curr, 1);
                state = 318; // <===
            }
            else if (_curr == 'm'){
                strncat(lexeme, &curr, 1);
                state = 319; // <===
            }
            else if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 332; // <===
            }
            else if (_curr == 's'){
                strncat(lexeme, &curr, 1);
                state = 363; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 318: // f
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 319: // m
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'p'){
                strncat(lexeme, &curr, 1);
                state = 320; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 332: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'h'){
                strncat(lexeme, &curr, 1);
                state = 333; // <===
            }
            else if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 340; // <===
            }
            else if (_curr == 'l'){
                strncat(lexeme, &curr, 1);
                state = 352; // <===
            }
            else if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 356; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 363: // s
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 320: // p
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'l'){
                strncat(lexeme, &curr, 1);
                state = 321; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 333: // h
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 334; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 340: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 341; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 352: // l
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 353; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 356: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 357; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 321: // l
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 322; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 334: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 335; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 341: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 342; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 353: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 354; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 357: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 358; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 322: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'm'){
                strncat(lexeme, &curr, 1);
                state = 323; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 335: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 336; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 342: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 343; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 354: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 355; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 358: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'f'){
                strncat(lexeme, &curr, 1);
                state = 359; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 323: // m
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 324; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 336: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 337; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 343: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'l'){
                strncat(lexeme, &curr, 1);
                state = 344; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 355: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 359: // f
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 360; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 324: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 325; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 337: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 338; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 344: // l
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 345; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 360: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'c'){
                strncat(lexeme, &curr, 1);
                state = 361; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 325: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 326; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 338: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'd'){
                strncat(lexeme, &curr, 1);
                state = 339; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 345: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'z'){
                strncat(lexeme, &curr, 1);
                state = 346; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 361: // c
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 362; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 326: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 327; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 339: // d
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 346: // z
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 347; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 362: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 327: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 328; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 347: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 348; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 328: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 329; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 348: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 349; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 329: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 330; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 349: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 350; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 330: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 331; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 350: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 351; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 331: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 351: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 364: // l
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 365; // <===
            }
            else if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 369; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 365: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'b'){
                strncat(lexeme, &curr, 1);
                state = 366; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 369: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'b'){
                strncat(lexeme, &curr, 1);
                state = 370; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 366: // b
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 367; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 370: // b
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 371; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 367: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'l'){
                strncat(lexeme, &curr, 1);
                state = 368; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 371: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 372; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 368: // l
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 372: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 373; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 373: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'y'){
                strncat(lexeme, &curr, 1);
                state = 374; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 374: // y
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 375: // m
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 376; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 376: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'd'){
                strncat(lexeme, &curr, 1);
                state = 377; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 377: // d
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 378: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 379; // <===
            }
            else if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 381; // <===
            }
            else if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 383; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 379: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'w'){
                strncat(lexeme, &curr, 1);
                state = 380; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 381: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'l'){
                strncat(lexeme, &curr, 1);
                state = 382; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 383: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 384; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 380: // w
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 382: // l
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 384: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 385: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'b'){
                strncat(lexeme, &curr, 1);
                state = 386; // <===
            }
            else if (_curr == 'f'){
                strncat(lexeme, &curr, 1);
                state = 391; // <===
            }
            else if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 392; // <===
            }
            else if (_curr == 'p'){
                strncat(lexeme, &curr, 1);
                state = 393; // <===
            }
            else if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 400; // <===
            }
            else if (_curr == 'u'){
                strncat(lexeme, &curr, 1);
                state = 401; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 386: // b
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'j'){
                strncat(lexeme, &curr, 1);
                state = 387; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 391: // f
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 392: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 393: // p
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 394; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 400: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 401: // u
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 402; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 387: // j
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 388; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 394: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 395; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 402: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 388: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'c'){
                strncat(lexeme, &curr, 1);
                state = 389; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 395: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 396; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 389: // c
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 390; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 396: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 397; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 390: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 397: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 398; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 398: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 399; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 399: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 403: // p
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 404; // <===
            }
            else if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 409; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 404: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'c'){
                strncat(lexeme, &curr, 1);
                state = 405; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 409: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 410; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 405: // c
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'k'){
                strncat(lexeme, &curr, 1);
                state = 406; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 410: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'c'){
                strncat(lexeme, &curr, 1);
                state = 411; // <===
            }
            else if (_curr == 'g'){
                strncat(lexeme, &curr, 1);
                state = 417; // <===
            }
            else if (_curr == 'p'){
                strncat(lexeme, &curr, 1);
                state = 421; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 406: // k
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 407; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 411: // c
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 412; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 417: // g
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 418; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 421: // p
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 422; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 407: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'd'){
                strncat(lexeme, &curr, 1);
                state = 408; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 412: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'd'){
                strncat(lexeme, &curr, 1);
                state = 413; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 418: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 419; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 422: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 423; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 408: // d
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 413: // d
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'u'){
                strncat(lexeme, &curr, 1);
                state = 414; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 419: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'm'){
                strncat(lexeme, &curr, 1);
                state = 420; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 423: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 424; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 414: // u
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 415; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 420: // m
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 424: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'y'){
                strncat(lexeme, &curr, 1);
                state = 425; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 415: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 416; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 425: // y
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 416: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 426: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 427; // <===
            }
            else if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 431; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 427: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 428; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 431: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'c'){
                strncat(lexeme, &curr, 1);
                state = 432; // <===
            }
            else if (_curr == 'p'){
                strncat(lexeme, &curr, 1);
                state = 436; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 428: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 's'){
                strncat(lexeme, &curr, 1);
                state = 429; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 432: // c
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 433; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 436: // p
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 437; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 429: // s
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 430; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 433: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 434; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 437: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 438; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 430: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 434: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'd'){
                strncat(lexeme, &curr, 1);
                state = 435; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 438: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 439; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 435: // d
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 439: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 440: // s
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 441; // <===
            }
            else if (_curr == 'h'){
                strncat(lexeme, &curr, 1);
                state = 445; // <===
            }
            else if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 448; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 441: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'l'){
                strncat(lexeme, &curr, 1);
                state = 442; // <===
            }
            else if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 444; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 445: // h
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'l'){
                strncat(lexeme, &curr, 1);
                state = 446; // <===
            }
            else if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 447; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 448: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 449; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 442: // l
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'f'){
                strncat(lexeme, &curr, 1);
                state = 443; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 444: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 446: // l
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 447: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 449: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 450; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 443: // f
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 450: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 451; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 451: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'g'){
                strncat(lexeme, &curr, 1);
                state = 452; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 452: // g
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 453: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'h'){
                strncat(lexeme, &curr, 1);
                state = 454; // <===
            }
            else if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 464; // <===
            }
            else if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 465; // <===
            }
            else if (_curr == 'y'){
                strncat(lexeme, &curr, 1);
                state = 469; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 454: // h
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 455; // <===
            }
            else if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 457; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 464: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 465: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'u'){
                strncat(lexeme, &curr, 1);
                state = 466; // <===
            }
            else if (_curr == 'y'){
                strncat(lexeme, &curr, 1);
                state = 468; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 469: // y
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'p'){
                strncat(lexeme, &curr, 1);
                state = 470; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 455: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 456; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 457: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 458; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 466: // u
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 467; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 468: // y
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 470: // p
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 471; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 456: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 458: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 459; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 467: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 471: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 459: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'd'){
                strncat(lexeme, &curr, 1);
                state = 460; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 460: // d
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'v'){
                strncat(lexeme, &curr, 1);
                state = 461; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 461: // v
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 462; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 462: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 463; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 463: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 472: // u
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'n'){
                strncat(lexeme, &curr, 1);
                state = 473; // <===
            }
            else if (_curr == 's'){
                strncat(lexeme, &curr, 1);
                state = 479; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 473: // n
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 474; // <===
            }
            else if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 476; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 479: // s
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 480; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 474: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 475; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 476: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 477; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 480: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 's'){
                strncat(lexeme, &curr, 1);
                state = 481; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 475: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 477: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'l'){
                strncat(lexeme, &curr, 1);
                state = 478; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 481: // s
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 478: // l
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 482: // v
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'a'){
                strncat(lexeme, &curr, 1);
                state = 483; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 483: // a
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 484; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 484: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 485: // w
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'h'){
                strncat(lexeme, &curr, 1);
                state = 486; // <===
            }
            else if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 490; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 486: // h
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'i'){
                strncat(lexeme, &curr, 1);
                state = 487; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 490: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 't'){
                strncat(lexeme, &curr, 1);
                state = 491; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 487: // i
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'l'){
                strncat(lexeme, &curr, 1);
                state = 488; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 491: // t
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'h'){
                strncat(lexeme, &curr, 1);
                state = 492; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 488: // l
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'e'){
                strncat(lexeme, &curr, 1);
                state = 489; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 492: // h
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 489: // e
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 493: // x
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'o'){
                strncat(lexeme, &curr, 1);
                state = 494; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 494: // o
            curr = getNextChar();
            _curr = tolower(curr);

            if (_curr == 'r'){
                strncat(lexeme, &curr, 1);
                state = 495; // <===
            }
            else if (isSeperator(_curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;
        case 495: // r
            curr = getNextChar();
            _curr = tolower(curr);

            if (isSeperator(_curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                strncat(lexeme, &curr, 1);
                state = 9; // <===
            }
            break;

        
    /*=====================================End Keywords==========================================*/
    
    /*=====================================Start Operators==========================================*/

        case 501: // .
            curr = getNextChar();

            if (curr == '.'){
                strncat(lexeme, &curr, 1);
                state = 502; // <===
            }
            else {
                // resetLexeme("operator");
                // state = resetState(curr);
                state = -2;
            }
            break;
        case 502: // .
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 503: // [
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 504: // ]
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 505: // :
            curr = getNextChar();

            if (curr == '='){
                strncat(lexeme, &curr, 1);
                state = 506; // <===
            }
            else {
                resetLexeme("operator");
                state = resetState(curr);
            }
            break;
        case 506: // =
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 507: // +
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 508: // -
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 509: // *
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 510: // /
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 511: // %
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 512: // &
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 513: // |
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 514: // !
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 515: // <
            curr = getNextChar();

            if (curr == '<'){
                strncat(lexeme, &curr, 1);
                state = 516; // <===
            }
            else if (curr == '='){
                strncat(lexeme, &curr, 1);
                state = 520; // <===
            }
            else if (curr == '>'){
                strncat(lexeme, &curr, 1);
                state = 525; // <===
            }
            else {
                resetLexeme("operator");
                state = resetState(curr);
            }
            break;
        case 516: // <
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 520: // =
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 525: // >
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 517: // >
            curr = getNextChar();

            if (curr == '>'){
                strncat(lexeme, &curr, 1);
                state = 518; // <===
            }
            else if (curr == '='){
                strncat(lexeme, &curr, 1);
                state = 524; // <===
            }
            else {
                resetLexeme("operator");
                state = resetState(curr);
            }
            break;
        case 518: // >
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 524: // =
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 519: // ~
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 521: // =
            curr = getNextChar();

            if (curr == '<'){
                strncat(lexeme, &curr, 1);
                state = 522; // <===
            }
            else if (curr == '>'){
                strncat(lexeme, &curr, 1);
                state = 523; // <===
            }
            else {
                resetLexeme("operator");
                state = resetState(curr);
            }
            break;
        case 522: // <
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 523: // >
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;


    /*=====================================End Operators==========================================*/
    /* "(" ")" ";" "," ":" */
    /*=====================================Start Seperators==========================================*/
    
        case 600:
            // (
            curr = getNextChar();
            resetLexeme("seperator");
            state = resetState(curr);
            break;
        
        case 601:
            // )
            curr = getNextChar();
            resetLexeme("seperator");
            state = resetState(curr);
            break;
        
        case 602:
            // ;
            curr = getNextChar();
            resetLexeme("seperator");
            state = resetState(curr);
            break;
        
        case 603:
            // ,
            curr = getNextChar();
            resetLexeme("seperator");
            state = resetState(curr);
            break;
        
        
        
        
        
    
    /*=====================================End Seperators==========================================*/
    

    
        default:
            break;
        }
    }
}

int main(int argc, char **argv){
    if(argc < 2){
        printf("NO file provided!!");
        return 1;
    }
    if(argc > 2){
        printf("Only 1 file expected!!");
        return 1;
    }
    fp = fopen(argv[1],"r");
    router();
    return 0;
}
