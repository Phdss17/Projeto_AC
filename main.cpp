#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Processador.hpp"

// ICU 
#include <unicode/unistr.h> 
#include <unicode/brkiter.h>
#include <unicode/uchar.h>

using namespace std; 
using namespace icu;

vector<UnicodeString> split_words(const UnicodeString txt){
    Locale locale("pt", "BR");
    UErrorCode status = U_ZERO_ERROR;

    BreakIterator* wordIterator = BreakIterator::createWordInstance(locale, status);
    vector<UnicodeString> words;

    if(U_FAILURE(status)) {
        std::cerr << "Erro ao criar BreakIterator: " << u_errorName(status) << std::endl;
        return words;
    }

    wordIterator->setText(txt);
    int32_t start = wordIterator->first();
    int32_t end = wordIterator->next();
    
    while(end != BreakIterator::DONE) {
        UnicodeString word;
        txt.extractBetween(start, end, word);

        words.push_back(word);
        
        start = end;
        end = wordIterator->next();
    }
    delete wordIterator;
    return words;
}

void hex_treat(vector<UnicodeString>& hexWords){
    UnicodeString aux = hexWords[1];
    hexWords.clear();

    switch(aux.charAt(2)){
        case '0':
        case '1':
        hexWords.push_back("JMP");
        break;
        case '2':
        hexWords.push_back("LDR");
        break;
        case '3':
        hexWords.push_back("STR");
        break;
        case '4':
        hexWords.push_back("MOV");
        break;
        case '5':
        hexWords.push_back("ADD");
        break;
        case '6':
        hexWords.push_back("ADDI");
        break;
        case '7':
        hexWords.push_back("SUB");
        break;
        case '8':
        hexWords.push_back("SUBI");
        break;
        case '9':
        hexWords.push_back("AND");
        break;
        case 'A':
        hexWords.push_back("OR");
        break;
        case 'B':
        hexWords.push_back("SHR");
        break;
        case 'C':
        hexWords.push_back("SHL");
        break;
        case 'D':
        hexWords.push_back("CMP");
        break;
        case 'E':
        hexWords.push_back("PUSH");
        break;
        case 'F':
        hexWords.push_back("POP");
        break;
        default:
        throw out_of_range("OPcode fora do escopo");
    }

    for(int i = 3; i < aux.length(); i++){
        UChar32 char_code_point = aux.charAt(i);
        hexWords.push_back(UnicodeString(char_code_point));
    }
}

// bool isHexa(UnicodeString word){
//     UChar ch = word.charAt(1);
//     if(isdigit(ch)){
//         return true;
//     }
//     return false;
// }

int main(int argc, char* argv[]){
    vector<string> argumentos;

    if( argc < 3 ){
        std::cerr << "Erro: Numero incorreto de argumentos." << std::endl;
        return 1; 
    }

    string in = argv[1];
    bool ishexa;
    if(argv[2] == "h"){ ishexa = true; }else{ ishexa = false; }

    ifstream entrada(in);

    if (!entrada) {
        throw runtime_error("Não foi possível abrir o arquivo para leitura.");
    }

    string conteudo;
    Processador proc;


    while (getline(entrada, conteudo)) {
        UnicodeString aux = UnicodeString::fromUTF8(conteudo);
        
        vector<UnicodeString> individual_words = split_words(aux);
        if(ishexa){ hex_treat(individual_words); }

        
    }

    entrada.close();
        
    ofstream saida("results");
    
    if (!saida) {
        throw runtime_error("Não foi possível criar o arquivo.");
    }

    saida.close();

}