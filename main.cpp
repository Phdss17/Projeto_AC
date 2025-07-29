#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Processador.hpp"
#include "decode.hpp"
#include <stdexcept>

using namespace std;

int loop;
int count;

vector<string> split_words(string txt){
    vector<string> words;
    string word = "";
    for(int i = 0; i < txt.length(); i++){
        char aux = txt.at(i);
        if(aux != ' ' && aux != ':' && aux != '#' && aux != '[' && aux != ']' && aux != ','){
            if(aux == 'x'){ word = ""; }else{ word += aux; }
        }else{
            if(word != ""){
            if(word == "loop"){
                loop = count;
            }else if(word != "main"){
                words.push_back(word);
            }
            }
            word = "";
        }
    }
    if(word != ""){
        words.push_back(word);
    }
        
    return words;
}

int main(int argc, char* argv[]){
    vector<string> argumentos;

    if( argc < 2 ){
        std::cerr << "Erro: Numero incorreto de argumentos." << std::endl;
        return 1; 
    }

    string in = argv[1];
    bool ishexa;
    count = 0;
    
    ifstream entrada(in);

    if (!entrada) {
        throw runtime_error("Não foi possível abrir o arquivo para leitura.");
    }

    string line;
    vector<string> instrucoes;
    
    while (getline(entrada, line)) {
        vector<string> individual_words = split_words(line);
        if(line.at(0) == '0' && count == 0){
            ishexa = true;
        }
        string instrucao;
        if(!ishexa){ 
            if(individual_words[0].at(0) == 'J'){
                individual_words[1] = to_string(count - loop);
            }
            assembly_treat(individual_words);
            assembly_Hex(individual_words);
            toPadronize(individual_words);
        }else{
            hex_treat(individual_words);
        }
        instrucao = hex_binary(individual_words);
        instrucoes.push_back(instrucao);
        count++;
    }
    entrada.close();

    Processador proc;
    proc.run(instrucoes, in);
}