/**
 * @file Processador.hpp
 * @author Paulo Henrique (phenriquedss@alu.ufc.br)
 * @brief Uma simulacao de um processador RISC
 * Estrutura de dados avancada - 2025.1
 * @version 0.1
 * @date 2025-07-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef PROCESSADOR_HPP
#define PROCESSADOR_HPP

#include <vector>
#include <utility>
#include <stdexcept>
#include "decode.hpp"

using namespace std;

/**
 * @brief Classe que implementa uma simulacao de um processador RISC
 *      
 */
class Processador {
public:
    Processador() {
        regs.resize(16, 0);
        mem.resize(8001, 0);
        regs[14] = 8000;
        IR = 0;
        Z = C = false; 
    }

    void run(vector<string> instrucoes){
        // for(int i = 0; i < instrucoes.size(); i = regs[15]){
        //     if( == "0000"){
        //         JMP(individual_instructions); 
        //     }else if(individual_instructions[0] == "LDR"){

        //     }else if(individual_instructions[0] == "0011"){
                
        //     }else if(individual_instructions[0] == "MOV"){
            
        //     }else if(individual_instructions[0] == "ADD"){
            
        //     }else if(individual_instructions[0] == "ADDI"){
            
        //     }else if(individual_instructions[0] == "SUB"){
            
        //     }else if(individual_instructions[0] == "SUBI"){
            
        //     }else if(individual_instructions[0] == "AND"){
            
        //     }else if(individual_instructions[0] == "OR"){
            
        //     }else if(individual_instructions[0] == "SHR"){
            
        //     }else if(individual_instructions[0] == "SHL"){
            
        //     }else if(individual_instructions[0] == "CMP"){
            
        //     }else if(individual_instructions[0] == "PUSH"){
            
        //     }else if(individual_instructions[0] == "POP"){
            
        //     }else{
            
        //     }
        // }  
    } 

private:
    vector<size_t> regs;
    vector<size_t> mem;
    size_t IR;
    bool Z;
    bool C;
    vector<int> positions;

    void JMP(vector<string>& instruction){
        IR = regs[15];
        if(instruction[1] == "0000" && instruction[2] == "0000" && instruction[3] == "0000"){
            NOP();
            regs[15]++;
        }else{
            size_t jmp = 0;
            for(int i = 1; i < instruction.size(); i++){
                jmp += biToDec(instruction[i]);
                if(jmp > 4095){
                    throw runtime_error("limite do imediato excedido");
                }
            }
            regs[15] = jmp;
        }
    }

    void NOP(){
        string out = "REGISTRADORES:\n";
        for(int i = 0; i < 14; i++){
            out += "R" + to_string(i) + ":     0x" + decToHex(regs[i]) + "\n";
        }
        out += "SP:     0x" + to_string(regs[14]) + "\n";
        out += "PC:     0x" + to_string(regs[15]) + "\n\n";
        // if(){
        //     out += "Memoria de Dados:\n";
        // }

    }

};

#endif