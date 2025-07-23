#ifndef DECODE_HPP
#define DECODE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <stdexcept>

using namespace std;

void hex_treat(vector<string>& hexWords){
    string auxs = hexWords[1];
    hexWords.clear();
    for(int i = 0; i < auxs.length(); i++){
        string str = "";
        str += auxs.at(i);
        hexWords.push_back(str);
    }
}

void assembly_treat(vector<string>& assemblyWords){
    string aux = "";
    for(int i = 1; i < assemblyWords.size(); i++){
        for(int j = 0; j < assemblyWords[i].length(); j++){
            if(assemblyWords[i].at(j) != 'R'){
                aux += assemblyWords[i].at(j);
            }
        }
        assemblyWords[i] = aux;
        aux = "";
    }
}

void toPadronize(vector<string>& toPadronize){
    if(toPadronize.size() < 4){
        if(toPadronize[0] == "2"){
            toPadronize.push_back("1");
        }else if(toPadronize[0] == "3" || toPadronize[0] == "D"){
            string aux = toPadronize[1];
            toPadronize[1] = "0";
            toPadronize.push_back(aux);
        }else if(toPadronize[0] == "E"){
            string aux = toPadronize[1];
            toPadronize[1] = toPadronize[2] = "0";
            toPadronize.push_back(aux);
        }else if(toPadronize[0] == "F"){
            int i;
            string aux;
            if(toPadronize.size() == 1){ 
                i = 0; 
                aux = "F"; 
            }else{ 
                i = 1; 
                aux = "0"; 
            }
            for(i; i < 3; i++){
                toPadronize.push_back(aux);
            }
        }else{
            if(toPadronize[0] == "0" || toPadronize[0] == "1"){
                if(toPadronize[1].length() < 3){
                    int i = 3 - toPadronize[1].length();
                    for(int j = 1; j <= i; j++){
                        string aux = toPadronize[j];
                        toPadronize[j] = "0";
                        toPadronize.push_back(aux);
                    }
                }else if(toPadronize[1].length() > 3){
                    throw invalid_argument("Instrução fora do escopo");
                }
            }else{
                if(toPadronize[2].length() < 2){
                    string aux = toPadronize[2];
                    toPadronize[2] = "0";
                    toPadronize.push_back(aux);
                }else if(toPadronize[2].length() > 2){
                    throw invalid_argument("Instrução fora do escopo");
                }
            }
        }
    }
}

void charToBi(string& aux){
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

void numHexToBi(string& aux){
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
    for(int i = num.length()-1; i >= 0; i--){
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
    if(num == 0){
        return "0";
    }
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

void assembly_Hex(vector<string>& toHex){
    if(toHex[0] == "JMP"){
        toHex[0] = "0";   
    }else if(toHex[0] == "JEQ" || toHex[0] == "JNQ" || toHex[0] == "JLT" || toHex[0] == "JGE"){
        toHex[0] = "1";       
    }else if(toHex[0] == "LDR"){ 
        toHex[0] = "2";
    }else if(toHex[0] == "STR"){
        toHex[0] = "3";
    }else if(toHex[0] == "MOV"){
        toHex[0] = "4";
    }else if(toHex[0] == "ADD"){
        toHex[0] = "5";
    }else if(toHex[0] == "ADDI"){
        toHex[0] = "6";
    }else if(toHex[0] == "SUB"){
        toHex[0] = "7";
    }else if(toHex[0] == "SUBI"){
        toHex[0] = "8";
    }else if(toHex[0] == "AND"){
        toHex[0] = "9";
    }else if(toHex[0] == "OR"){
        toHex[0] = "A";
    }else if(toHex[0] == "SHR"){
        toHex[0] = "B";
    }else if(toHex[0] == "SHL"){
        toHex[0] = "C";
    }else if(toHex[0] == "CMP"){
        toHex[0] = "D";
    }else if(toHex[0] == "PUSH"){
        toHex[0] = "E";
    }else if(toHex[0] == "POP"  || toHex[0] == "HALT"){
        toHex[0] = "F";
    }else{
        throw invalid_argument("Instrução fora do escopo");
    }
    for(int i = 1; i < toHex.size(); i++){
        toHex[i] = decToHex(stoi(toHex[i]));
    }
}

string hex_binary(vector<string> toBinary){
    for(int i = 0; i < toBinary.size(); i++){
        numHexToBi(toBinary[i]);
        charToBi(toBinary[i]);
    }
    string aux = "";
    for(int i = 0; i < toBinary.size(); i++){
        aux += toBinary[i];
    }
    return aux;
}

#endif