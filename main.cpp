#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Processador.hpp"
#include "decode.hpp"
#include <stdexcept>

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

        if(word != ":" && word != "," && word != "#" && word != " " && word != "[" && word != "]"){
            words.push_back(word);
        }
        
        start = end;
        end = wordIterator->next();
    }
    delete wordIterator;
    return words;
}


int main(int argc, char* argv[]){
    vector<string> argumentos;

    if( argc < 3 ){
        std::cerr << "Erro: Numero incorreto de argumentos." << std::endl;
        return 1; 
    }

    string in = argv[1];
    bool ishexa;
    string hexa = argv[2];
    ishexa = (hexa == "h");
    
    ifstream entrada(in);

    if (!entrada) {
        throw runtime_error("Não foi possível abrir o arquivo para leitura.");
    }

    string indice;
    string valor;
    vector<vector<UnicodeString>> instrucoes;
    
    while (getline(entrada, indice)) {
        UnicodeString aux = UnicodeString::fromUTF8(indice);
        
        vector<UnicodeString> individual_words = split_words(aux);
        
        if(ishexa){ 
            hex_treat(individual_words);
            hex_binary(individual_words); 
        }else{
            assembly_treat(individual_words); 
            assembly_binary(individual_words);
        }
        instrucoes.push_back(individual_words);
    }

    Processador proc;
    try{
        proc.run(instrucoes);
    }catch(const std::exception& e){
        cerr << e.what() << endl;
    }

    entrada.close();
        
    ofstream saida("results");

    if (!saida) {
        throw runtime_error("Não foi possível criar o arquivo.");
    }

    saida.close();
}