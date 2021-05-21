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
    4** - operators
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
                append(curr);
                return 201;

        case 'b':
                append(curr);
                return 208;

        case 'c':
                append(curr);
                return 213;

        case 'd':
                append(curr);
                return 221;

        case 'e':
                append(curr);
                return 229;

        case 'f':
                append(curr);
                return 235;

        case 'g':
                append(curr);
                return 248;

        case 'i':
                append(curr);
                return 252;

        case 'l':
                append(curr);
                return 255;

        case 'm':
                append(curr);
                return 260;

        case 'n':
                append(curr);
                return 263;

        case 'o':
                append(curr);
                return 268;

        case 'p':
                append(curr);
                return 270;

        case 'r':
                append(curr);
                return 288;

        case 's':
                append(curr);
                return 298;

        case 't':
                append(curr);
                return 301;

        case 'u':
                append(curr);
                return 309;

        case 'v':
                append(curr);
                return 317;

        case 'w':
                append(curr);
                return 320;
        
        
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
        case 'x':
                append(curr);
                return 9;
        case 'y':
                append(curr);
                return 9;
        case 'z':
                append(curr);
                return 9;
        


        // operators initial

        case ':':
                append(curr);
                return 401;
        case '+':
                append(curr);
                return 403;
        case '-':
                append(curr);
                return 404;
        case '*':
                append(curr);
                return 405;
        case '%':
                append(curr);
                return 407;
        case '&':
                append(curr);
                return 408;
        case '|':
                append(curr);
                return 409;
        case '!':
                append(curr);
                return 410;
        case '<':
                append(curr);
                return 411;
        case '>':
                append(curr);
                return 413;
        case '~':
                append(curr);
                return 415;
        case '=':
                append(curr);
                return 417;


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
    char curr;

    while(1){
        switch (state){
        
        case -1:
            // end of file
            printTable();
            exit(0);

        case -2:
            // error
            setvbuf(stdout, NULL, _IONBF, 0);
            printf("Invalid symbol '%c' detected on line no %d\n", curr, lineNo);
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

            if (curr == 'n'){
                append(curr);
                state = 202; // <===
            }
            else if (curr == 'r'){
                append(curr);
                state = 204; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 202: // n
            curr = getNextChar();

            if (curr == 'd'){
                append(curr);
                state = 203; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 204: // r
            curr = getNextChar();

            if (curr == 'r'){
                append(curr);
                state = 205; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 203: // d
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 205: // r
            curr = getNextChar();

            if (curr == 'a'){
                append(curr);
                state = 206; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 206: // a
            curr = getNextChar();

            if (curr == 'y'){
                append(curr);
                state = 207; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 207: // y
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 208: // b
            curr = getNextChar();

            if (curr == 'e'){
                append(curr);
                state = 209; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 209: // e
            curr = getNextChar();

            if (curr == 'g'){
                append(curr);
                state = 210; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 210: // g
            curr = getNextChar();

            if (curr == 'i'){
                append(curr);
                state = 211; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 211: // i
            curr = getNextChar();

            if (curr == 'n'){
                append(curr);
                state = 212; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 212: // n
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 213: // c
            curr = getNextChar();

            if (curr == 'a'){
                append(curr);
                state = 214; // <===
            }
            else if (curr == 'o'){
                append(curr);
                state = 217; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 214: // a
            curr = getNextChar();

            if (curr == 's'){
                append(curr);
                state = 215; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 217: // o
            curr = getNextChar();

            if (curr == 'n'){
                append(curr);
                state = 218; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 215: // s
            curr = getNextChar();

            if (curr == 'e'){
                append(curr);
                state = 216; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 218: // n
            curr = getNextChar();

            if (curr == 's'){
                append(curr);
                state = 219; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 216: // e
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 219: // s
            curr = getNextChar();

            if (curr == 't'){
                append(curr);
                state = 220; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 220: // t
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 221: // d
            curr = getNextChar();

            if (curr == 'i'){
                append(curr);
                state = 222; // <===
            }
            else if (curr == 'o'){
                append(curr);
                state = 224; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 222: // i
            curr = getNextChar();

            if (curr == 'v'){
                append(curr);
                state = 223; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 224: // o
            curr = getNextChar();

            if (curr == 'w'){
                append(curr);
                state = 225; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 223: // v
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 225: // w
            curr = getNextChar();

            if (curr == 'n'){
                append(curr);
                state = 226; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 226: // n
            curr = getNextChar();

            if (curr == 't'){
                append(curr);
                state = 227; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 227: // t
            curr = getNextChar();

            if (curr == 'o'){
                append(curr);
                state = 228; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 228: // o
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 229: // e
            curr = getNextChar();

            if (curr == 'l'){
                append(curr);
                state = 230; // <===
            }
            else if (curr == 'n'){
                append(curr);
                state = 233; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 230: // l
            curr = getNextChar();

            if (curr == 's'){
                append(curr);
                state = 231; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 233: // n
            curr = getNextChar();

            if (curr == 'd'){
                append(curr);
                state = 234; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 231: // s
            curr = getNextChar();

            if (curr == 'e'){
                append(curr);
                state = 232; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 234: // d
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 232: // e
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 235: // f
            curr = getNextChar();

            if (curr == 'i'){
                append(curr);
                state = 236; // <===
            }
            else if (curr == 'o'){
                append(curr);
                state = 239; // <===
            }
            else if (curr == 'u'){
                append(curr);
                state = 241; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 236: // i
            curr = getNextChar();

            if (curr == 'l'){
                append(curr);
                state = 237; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 239: // o
            curr = getNextChar();

            if (curr == 'r'){
                append(curr);
                state = 240; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 241: // u
            curr = getNextChar();

            if (curr == 'n'){
                append(curr);
                state = 242; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 237: // l
            curr = getNextChar();

            if (curr == 'e'){
                append(curr);
                state = 238; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 240: // r
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 242: // n
            curr = getNextChar();

            if (curr == 'c'){
                append(curr);
                state = 243; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 238: // e
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 243: // c
            curr = getNextChar();

            if (curr == 't'){
                append(curr);
                state = 244; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 244: // t
            curr = getNextChar();

            if (curr == 'i'){
                append(curr);
                state = 245; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 245: // i
            curr = getNextChar();

            if (curr == 'o'){
                append(curr);
                state = 246; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 246: // o
            curr = getNextChar();

            if (curr == 'n'){
                append(curr);
                state = 247; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 247: // n
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 248: // g
            curr = getNextChar();

            if (curr == 'o'){
                append(curr);
                state = 249; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 249: // o
            curr = getNextChar();

            if (curr == 't'){
                append(curr);
                state = 250; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 250: // t
            curr = getNextChar();

            if (curr == 'o'){
                append(curr);
                state = 251; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 251: // o
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 252: // i
            curr = getNextChar();

            if (curr == 'f'){
                append(curr);
                state = 253; // <===
            }
            else if (curr == 'n'){
                append(curr);
                state = 254; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 253: // f
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 254: // n
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 255: // l
            curr = getNextChar();

            if (curr == 'a'){
                append(curr);
                state = 256; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 256: // a
            curr = getNextChar();

            if (curr == 'b'){
                append(curr);
                state = 257; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 257: // b
            curr = getNextChar();

            if (curr == 'e'){
                append(curr);
                state = 258; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 258: // e
            curr = getNextChar();

            if (curr == 'l'){
                append(curr);
                state = 259; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 259: // l
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 260: // m
            curr = getNextChar();

            if (curr == 'o'){
                append(curr);
                state = 261; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 261: // o
            curr = getNextChar();

            if (curr == 'd'){
                append(curr);
                state = 262; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 262: // d
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 263: // n
            curr = getNextChar();

            if (curr == 'i'){
                append(curr);
                state = 264; // <===
            }
            else if (curr == 'o'){
                append(curr);
                state = 266; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 264: // i
            curr = getNextChar();

            if (curr == 'l'){
                append(curr);
                state = 265; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 266: // o
            curr = getNextChar();

            if (curr == 't'){
                append(curr);
                state = 267; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 265: // l
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 267: // t
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 268: // o
            curr = getNextChar();

            if (curr == 'f'){
                append(curr);
                state = 269; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 269: // f
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 270: // p
            curr = getNextChar();

            if (curr == 'a'){
                append(curr);
                state = 271; // <===
            }
            else if (curr == 'r'){
                append(curr);
                state = 276; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 271: // a
            curr = getNextChar();

            if (curr == 'c'){
                append(curr);
                state = 272; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 276: // r
            curr = getNextChar();

            if (curr == 'o'){
                append(curr);
                state = 277; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 272: // c
            curr = getNextChar();

            if (curr == 'k'){
                append(curr);
                state = 273; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 277: // o
            curr = getNextChar();

            if (curr == 'c'){
                append(curr);
                state = 278; // <===
            }
            else if (curr == 'g'){
                append(curr);
                state = 284; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 273: // k
            curr = getNextChar();

            if (curr == 'e'){
                append(curr);
                state = 274; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 278: // c
            curr = getNextChar();

            if (curr == 'e'){
                append(curr);
                state = 279; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 284: // g
            curr = getNextChar();

            if (curr == 'r'){
                append(curr);
                state = 285; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 274: // e
            curr = getNextChar();

            if (curr == 'd'){
                append(curr);
                state = 275; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 279: // e
            curr = getNextChar();

            if (curr == 'd'){
                append(curr);
                state = 280; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 285: // r
            curr = getNextChar();

            if (curr == 'a'){
                append(curr);
                state = 286; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 275: // d
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 280: // d
            curr = getNextChar();

            if (curr == 'u'){
                append(curr);
                state = 281; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 286: // a
            curr = getNextChar();

            if (curr == 'm'){
                append(curr);
                state = 287; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 281: // u
            curr = getNextChar();

            if (curr == 'r'){
                append(curr);
                state = 282; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 287: // m
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 282: // r
            curr = getNextChar();

            if (curr == 'e'){
                append(curr);
                state = 283; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 283: // e
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 288: // r
            curr = getNextChar();

            if (curr == 'e'){
                append(curr);
                state = 289; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 289: // e
            curr = getNextChar();

            if (curr == 'c'){
                append(curr);
                state = 290; // <===
            }
            else if (curr == 'p'){
                append(curr);
                state = 294; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 290: // c
            curr = getNextChar();

            if (curr == 'o'){
                append(curr);
                state = 291; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 294: // p
            curr = getNextChar();

            if (curr == 'e'){
                append(curr);
                state = 295; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 291: // o
            curr = getNextChar();

            if (curr == 'r'){
                append(curr);
                state = 292; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 295: // e
            curr = getNextChar();

            if (curr == 'a'){
                append(curr);
                state = 296; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 292: // r
            curr = getNextChar();

            if (curr == 'd'){
                append(curr);
                state = 293; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 296: // a
            curr = getNextChar();

            if (curr == 't'){
                append(curr);
                state = 297; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 293: // d
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 297: // t
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 298: // s
            curr = getNextChar();

            if (curr == 'e'){
                append(curr);
                state = 299; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 299: // e
            curr = getNextChar();

            if (curr == 't'){
                append(curr);
                state = 300; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 300: // t
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 301: // t
            curr = getNextChar();

            if (curr == 'h'){
                append(curr);
                state = 302; // <===
            }
            else if (curr == 'o'){
                append(curr);
                state = 305; // <===
            }
            else if (curr == 'y'){
                append(curr);
                state = 306; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 302: // h
            curr = getNextChar();

            if (curr == 'e'){
                append(curr);
                state = 303; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 305: // o
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 306: // y
            curr = getNextChar();

            if (curr == 'p'){
                append(curr);
                state = 307; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 303: // e
            curr = getNextChar();

            if (curr == 'n'){
                append(curr);
                state = 304; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 307: // p
            curr = getNextChar();

            if (curr == 'e'){
                append(curr);
                state = 308; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 304: // n
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 308: // e
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 309: // u
            curr = getNextChar();

            if (curr == 's'){
                append(curr);
                state = 310; // <===
            }
            else if (curr == 'n'){
                append(curr);
                state = 313; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 310: // s
            curr = getNextChar();

            if (curr == 'e'){
                append(curr);
                state = 311; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 313: // n
            curr = getNextChar();

            if (curr == 't'){
                append(curr);
                state = 314; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 311: // e
            curr = getNextChar();

            if (curr == 's'){
                append(curr);
                state = 312; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 314: // t
            curr = getNextChar();

            if (curr == 'i'){
                append(curr);
                state = 315; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 312: // s
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 315: // i
            curr = getNextChar();

            if (curr == 'l'){
                append(curr);
                state = 316; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 316: // l
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 317: // v
            curr = getNextChar();

            if (curr == 'a'){
                append(curr);
                state = 318; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 318: // a
            curr = getNextChar();

            if (curr == 'r'){
                append(curr);
                state = 319; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 319: // r
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 320: // w
            curr = getNextChar();

            if (curr == 'h'){
                append(curr);
                state = 321; // <===
            }
            else if (curr == 'i'){
                append(curr);
                state = 325; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 321: // h
            curr = getNextChar();

            if (curr == 'i'){
                append(curr);
                state = 322; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 325: // i
            curr = getNextChar();

            if (curr == 't'){
                append(curr);
                state = 326; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 322: // i
            curr = getNextChar();

            if (curr == 'l'){
                append(curr);
                state = 323; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 326: // t
            curr = getNextChar();

            if (curr == 'h'){
                append(curr);
                state = 327; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 323: // l
            curr = getNextChar();

            if (curr == 'e'){
                append(curr);
                state = 324; // <===
            }
            else if (isSeperator(curr)){
                resetLexeme("identifier");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 327: // h
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;
        case 324: // e
            curr = getNextChar();

            if (isSeperator(curr)){
                resetLexeme("keyword");
                state = resetState(curr);
            } else {
                // identifier
                append(curr);
                state = 9; // <===
            }
            break;


        
    /*=====================================End Keywords==========================================*/
    
    /*=====================================Start Operators==========================================*/

        case 401: // :
            curr = getNextChar();

            if (curr == '='){
                append(curr);
                state = 402; // <===
            }
            else {
                resetLexeme("seperator");
                state = resetState(curr);
            }
            break;
        case 402: // =
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 403: // +
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 404: // -
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 405: // *
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 406: // /
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 407: // %
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 408: // &
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 409: // |
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 410: // !
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 411: // <
            curr = getNextChar();

            if (curr == '<'){
                append(curr);
                state = 412; // <===
            }
            else if (curr == '='){
                append(curr);
                state = 416; // <===
            }
            else if (curr == '>'){
                append(curr);
                state = 421; // <===
            }
            else {
                resetLexeme("operator");
                state = resetState(curr);
            }
            break;
        case 412: // <
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 416: // =
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 421: // >
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 413: // >
            curr = getNextChar();

            if (curr == '>'){
                append(curr);
                state = 414; // <===
            }
            else if (curr == '='){
                append(curr);
                state = 420; // <===
            }
            else {
                resetLexeme("operator");
                state = resetState(curr);
            }
            break;
        case 414: // >
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 420: // =
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 415: // ~
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 417: // =
            curr = getNextChar();

            if (curr == '<'){
                append(curr);
                state = 418; // <===
            }
            else if (curr == '>'){
                append(curr);
                state = 419; // <===
            }
            else {
                resetLexeme("operator");
                state = resetState(curr);
            }
            break;
        case 418: // <
            curr = getNextChar();

            resetLexeme("operator");
            state = resetState(curr);

            break;
        case 419: // >
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
