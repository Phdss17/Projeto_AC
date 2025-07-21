#ifndef DECODE_HPP
#define DECODE_HPP

#include <iostream>
#include <vector>
#include <unicode/uchar.h>
#include <unicode/unistr.h> 
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <stdexcept>

using namespace std;
using namespace icu;


void hex_treat(vector<UnicodeString>& hexWords){
    UnicodeString auxs = hexWords[1];
    hexWords.clear();
    for(int i = 2; i < auxs.length(); i++){
        UChar32 auxc = auxs.charAt(i);
        hexWords.push_back(UnicodeString(auxc));
    }
}

void assembly_treat(vector<UnicodeString>& assemblyWords){
    for(int i = 1; i < assemblyWords.size(); i++){
        if(assemblyWords[i].charAt(0) == 'R'){
            UnicodeString aux = assemblyWords[i].charAt(1); 
            assemblyWords[i] = aux;
        }
    }
}

void charToBi(UnicodeString& aux){
    if(aux == "A"){
        aux = "1010";
    }else if(aux == "B"){
        aux = "1011";
    }else if(aux == "C"){
        aux = "1100";
    }else if(aux == "D"){
        aux = "1101";
    }else if(aux == "E"){
        aux = "1110";
    }else if(aux == "F"){
        aux = "1111";
    }
}

void numHexToBi(UnicodeString& aux){
    if(aux == "0"){
        aux = "0000";   
    }else if(aux == "1"){
        aux = "0001";       
    }else if(aux == "2"){ 
        aux = "0010";
    }else if(aux == "3"){
        aux = "0011";
    }else if(aux == "4"){
        aux = "0100";
    }else if(aux == "5"){
        aux = "0101";
    }else if(aux == "6"){
        aux = "0110";
    }else if(aux == "7"){
        aux = "0111";
    }else if(aux == "8"){
        aux = "1000";
    }else if(aux == "9"){
        aux = "1001";
    }
}

void decToBi(string& num){
    int aux;
    try{
        aux = stoi(num);
    }catch (const std::out_of_range& e) {
        cerr << "Erro: Número fora do intervalo - " << e.what() << std::endl;
    }
    stack<char> stack;
    while(aux != 0 ){
        stack.push((aux%2 == 0 ? '0' : '1'));
        aux /= 2;
    }
    num = "";
    if(stack.size() < 4){
        for(int i = 0; i+stack.size() < 4; i++){
            num += '0';
        }
    }
    while(!stack.empty()){
        num += stack.top();
        stack.pop();
    }
}

size_t biToDec(string num){
    queue<char> queue;
    for(int i = num.length()-1; i > 0; i--){
        queue.push(num.at(i));
    }
    int aux;
    size_t result = 0;
    for(int i = 0; i < queue.size(); i++){
        if(queue.front() == '0'){ aux = 0; }else{ aux = 1; }
        queue.pop();
        result += aux * (pow(2, i));
    }
    return result;
} 

string decToHex(size_t num){
    stack<int> stack;
    while(num != 0){
        stack.push(num % 16);
        num /= 16;
    }
    string out = "";
    while(!stack.empty()){
        int aux = stack.top();
        stack.pop();
        if(aux == 10){
            out += "A";
        }else if(aux == 11){
            out += "B";
        }else if(aux == 12){
            out += "C";
        }else if(aux == 13){
            out += "D"; 
        }else if(aux == 14){
            out += "E"; 
        }else if(aux == 15){
            out += "F";
        }else{
            out += to_string(aux);
        }
    }
    return out;
}

void assembly_binary(vector<UnicodeString>& toBinary){
    if(toBinary[0] == "JMP"){
        toBinary[0] = "0000";   
    }else if(toBinary[0] == "JEQ" || toBinary[0] == "JNQ" || toBinary[0] == "JLT" || toBinary[0] == "JGE"){
        toBinary[0] = "0001";       
    }else if(toBinary[0] == "LDR"){ 
        toBinary[0] = "0010";
    }else if(toBinary[0] == "STR"){
        toBinary[0] = "0011";
    }else if(toBinary[0] == "MOV"){
        toBinary[0] = "0100";
    }else if(toBinary[0] == "ADD"){
        toBinary[0] = "0101";
    }else if(toBinary[0] == "ADDI"){
        toBinary[0] = "0110";
    }else if(toBinary[0] == "SUB"){
        toBinary[0] = "0111";
    }else if(toBinary[0] == "SUBI"){
        toBinary[0] = "1000";
    }else if(toBinary[0] == "AND"){
        toBinary[0] = "1001";
    }else if(toBinary[0] == "OR"){
        toBinary[0] = "1010";
    }else if(toBinary[0] == "SHR"){
        toBinary[0] = "1011";
    }else if(toBinary[0] == "SHL"){
        toBinary[0] = "1100";
    }else if(toBinary[0] == "CMP"){
        toBinary[0] = "1101";
    }else if(toBinary[0] == "PUSH"){
        toBinary[0] = "1110";
    }else if(toBinary[0] == "POP"  || toBinary[0] == "HALT"){
        toBinary[0] = "1111";
    }else{
        throw invalid_argument("Instrução fora do escopo");
    }
    for(int i = 1; i < toBinary.size(); i++){
        string utf;
        toBinary[i].toUTF8String(utf);
        decToBi(utf);
        toBinary[i] = UnicodeString::fromUTF8(utf);
    }
}

void hex_binary(vector<UnicodeString>& toBinary){
    for(int i = 0; i < toBinary.size(); i++){
        numHexToBi(toBinary[i]);
        charToBi(toBinary[i]);
    }
}

#endif