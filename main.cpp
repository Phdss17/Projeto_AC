#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> // Para std::setw e std::left

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

int main(int argc, char* argv[]){
    vector<string> argumentos;

    if(argc < 2 ){
        std::cerr << "Erro: Numero incorreto de argumentos." << std::endl;
        return 1; 
    }

    string in = argv[1];


    ifstream entrada(in);

    if (!entrada) {
        throw runtime_error("Não foi possível abrir o arquivo para leitura.");
    }

    string conteudo;

    while (getline(entrada, conteudo)) {
        UnicodeString aux = UnicodeString::fromUTF8(conteudo);
        
        vector<UnicodeString> individual_words = split_words(aux.toLower());
        
        for(UnicodeString str : individual_words){

        }  
    }
    entrada.close();
        
    ofstream saida("results");
    
    if (!saida) {
        throw runtime_error("Não foi possível criar o arquivo.");
    }

    saida.close();

}