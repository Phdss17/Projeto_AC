#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Processador.hpp"
#include "decode.hpp"
#include <stdexcept>

using namespace std;

vector<string> split_words(string txt){
    vector<string> words;
    string word = "";
    for(int i = 0; i < txt.length(); i++){
        char aux = txt.at(i);
        if(aux != ' ' && aux != 'R' && aux != ':' && aux != '#' && aux != '[' && aux != ']' && aux != ','){
            if(aux == 'x'){ word = ""; }else{ word += aux; }
        }else{
            if(word != ""){ words.push_back(word); }
            word = "";
        }
    }
    words.push_back(word);
        
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

    string line;
    vector<vector<string>> instrucoes;
    
    while (getline(entrada, line)) {
        vector<string> individual_words = split_words(line);
        
        if(ishexa){ 
            hex_treat(individual_words);
            hex_binary(individual_words); 
        }else{
            assembly_binary(individual_words);
        }
        instrucoes.push_back(individual_words);
    }
       

    // Processador proc;
    // try{
    //     proc.run(instrucoes);
    // }catch(const std::exception& e){
    //     cerr << e.what() << endl;
    // }

    entrada.close();
        
    ofstream saida("results");
    
    if (!saida) {
        throw runtime_error("Não foi possível criar o arquivo.");
    }

    saida.close();
}