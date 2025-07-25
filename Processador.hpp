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
#include <stdexcept>
#include "decode.hpp"
#include <iomanip>
#include <sstream>

using namespace std;

/**
 * @brief Classe que implementa uma simulacao de um processador RISC
 *      
 */
class Processador {
public:
    Processador() {
        regs.resize(16, 0);
        mem.resize(32769, 0);
        regs[14] = 32768;
        IR = 0;
        Z = C = false; 
    }

    string run(vector<string> instrucoes){
        while(true){
            IR = regs[15];
            string opcode = instrucoes[IR].substr(0, 4);
            if(opcode == "0000"){
                JMP(instrucoes[IR].substr(4, 16)); 
            }else if(opcode  == "0001"){
                string cond = instrucoes[IR].substr(4, 2);
                if(cond == "00"){
                    if(Z){
                        JMP(instrucoes[IR].substr(5, 10));
                    }
                }else if(cond == "01"){
                    if(!Z){
                        JMP(instrucoes[IR].substr(5, 10));
                    }
                }if(cond == "10"){
                    if(!Z && C){
                        JMP(instrucoes[IR].substr(5, 10));
                    }
                }else if(cond == "11"){
                    if(Z && !C){
                        JMP(instrucoes[IR].substr(5, 10));
                    }
                }
            }else if(opcode == "0010"){  
                LDR(instrucoes[IR].substr(4, 8));
            }else if(opcode == "0011"){
                STR(instrucoes[IR].substr(8, 8));
            }else if(opcode == "0100"){
                MOV(instrucoes[IR].substr(4, 12));
            }else if(opcode == "0101"){     
                ADD(instrucoes[IR].substr(4, 12));
            }else if(opcode == "0110"){
                ADDI(instrucoes[IR].substr(4, 12));
            }else if(opcode == "0111"){   
                SUB(instrucoes[IR].substr(4, 12));
            }else if(opcode == "1000"){       
                SUBI(instrucoes[IR].substr(4, 12));
            }else if(opcode == "1001"){             
                AND(instrucoes[IR].substr(4, 12));
            }else if(opcode == "1010"){                
                OR(instrucoes[IR].substr(4, 12));
            }else if(opcode == "1011"){              
                SHR(instrucoes[IR].substr(4, 12));
            }else if(opcode == "1100"){           
                SHL(instrucoes[IR].substr(4, 12));
            }else if(opcode == "1101"){              
                CMP(instrucoes[IR].substr(8, 8));
            }else if(opcode == "1110"){      
                PUSH(instrucoes[IR].substr(12, 4));
            }else if(opcode == "1111"){
                if(instrucoes[IR].substr(4, 12) == "111111111111"){
                    return NOP();
                }
                POP(instrucoes[IR].substr(4, 12));
            }
            regs[15]++;
        } 
        return NOP();
    } 

private:
    vector<int> regs;
    vector<int> mem;
    size_t IR;
    bool Z;
    bool C;
    vector<int> positions;

    void JMP(string instruction){
        int jmp;
        if(instruction.at(0) == '1'){
            instruction = twoComplement(instruction);
            jmp = biToDec(instruction) * (-1);
        }else{
            jmp = biToDec(instruction);
        }
        
        if(jmp == 0){
            cout << NOP();
        }else{
            regs[15] += jmp;
        }
    }

    void LDR(string instruction){
        int destine = biToDec(instruction.substr(0, 4));
        int adress_mem =  biToDec(instruction.substr(4, 4));

        if(mem[adress_mem] = 61440){
            char c;
            cin >> c;
            regs[destine] = static_cast<int>(c);
        }else if(mem[adress_mem] = 61441){
            int n;
            cin >> n;
            regs[destine] = n;
        }else{
            regs[destine] = mem[adress_mem];
        }
    }

    void STR(string instruction){
        int adress_mem =  biToDec(instruction.substr(0, 4));
        int value = biToDec(instruction.substr(4, 4));
        if(regs[value] == 61442){
            cout << static_cast<char>(regs[adress_mem]);
        }else if(regs[value] == 61443){
            cout << regs[adress_mem];
        }else{
            mem[regs[adress_mem]] = regs[value];
            positions.push_back(regs[adress_mem]);
        }
    }

    void MOV(string instruction){
        int reg =  biToDec(instruction.substr(0, 4));
        int value = biToDec(instruction.substr(4, 8));

        regs[reg] = value;
    }

    void ADD(string instruction){
        int destino = biToDec(instruction.substr(0, 4));
        int saida1 = biToDec(instruction.substr(4, 4));
        int saida2 = biToDec(instruction.substr(8, 4));

        regs[destino] = regs[saida1] + regs[saida2];
    }

    void ADDI(string instruction){
        int destino = biToDec(instruction.substr(0, 4));
        int saida = biToDec(instruction.substr(4, 4));
        int im = biToDec(instruction.substr(8, 4));

        regs[destino] = regs[saida] + im;
    }

    void SUB(string instruction){
        int destino = biToDec(instruction.substr(0, 4));
        int saida1 = biToDec(instruction.substr(4, 4));
        int saida2 = biToDec(instruction.substr(8, 4));

        regs[destino] = regs[saida1] - regs[saida2];
        if(regs[destino] < 0){
            regs[destino] = regs[destino] * (-1);
        }
    }

    void SUBI(string instruction){
        int destino = biToDec(instruction.substr(0, 4));
        int saida = biToDec(instruction.substr(4, 4));
        int im = biToDec(instruction.substr(8, 4));

        regs[destino] = regs[saida] - im;
    }

    void AND(string instruction){
        int destino = biToDec(instruction.substr(0, 4));
        int op1 = regs[biToDec(instruction.substr(4, 4))];
        int op2 = regs[biToDec(instruction.substr(8, 4))];
        
        regs[destino] = op1 & op2;
    }

    void OR(string instruction){
        int destino = biToDec(instruction.substr(0, 4));
        int op1 = regs[biToDec(instruction.substr(4, 4))];
        int op2 = regs[biToDec(instruction.substr(8, 4))];
        
        regs[destino] = op1 | op2;
    }    

    void SHR(string instruction){
        int destino = biToDec(instruction.substr(0, 4));
        int saida = biToDec(instruction.substr(4, 4));
        int im = biToDec(instruction.substr(8, 4));
        string aux = to_string(regs[saida]);
        decToBi(aux);

        string result = aux.substr(0, im);
        aux = "";
        for(int i = 0; i < im; i++){
            aux += "0";
        }

        result += aux + result;
        regs[destino] = biToDec(result);
    }

    void SHL(string instruction){
        int destino = biToDec(instruction.substr(0, 4));
        int saida = biToDec(instruction.substr(4, 4));
        int im = biToDec(instruction.substr(8, 4));
        string aux = to_string(regs[saida]);
        decToBi(aux);

        string result = aux.substr(aux.length() - im, aux.length());
        aux = "";
        for(int i = 0; i < im; i++){
            aux += "0";
        }
        result += result + aux;
        regs[destino] = biToDec(result);
    }

    void CMP(string instruction){
        string cmp1 = instruction.substr(0, 4);
        string cmp2 = instruction.substr(4, 4);
        int a = regs[biToDec(cmp1)]; 
        int b = regs[biToDec(cmp2)];

        if(a == b){
            Z = true;
        }else{
            Z = false;
        }

        if(a < b){
            C = true;
        }else{
            C = false;
        }
    }

    void PUSH(string instruction){
        regs[14]--;
        mem[regs[14]] = regs[biToDec(instruction)];
    }

    void POP(string instruction){
       int destino = biToDec(instruction.substr(0, 4));

       regs[destino] = mem[regs[14]];
       regs[14]++;
    }

    string NOP(){
        std::stringstream out;
    
        out << "Registradores:\n";
        for(int i = 0; i < 14; i++) {
            out << "R" << i << ":" << std::setw(10 - std::to_string(i).size()) 
                << "0x" << hexFormat(decToHex(regs[i])) << "\n";
        }
    
        out << "SP:" << std::setw(9) << "0x" << hexFormat(decToHex(regs[14])) << "\n"
            << "PC:" << std::setw(9) << "0x" << hexFormat(decToHex(regs[15])) << "\n\n";
    
        if(!positions.empty()) {
            out << "Memoria de Dados:\n";
            for(auto position : positions) {
                out << hexFormat(decToHex(position)) << ":" << std::setw(8)
                    << "0x" << hexFormat(decToHex(mem[position])) << "\n";
            }
            out << "\n";
        }
 
        if(regs[14] != 32768) {
            out << "Pilha: \n";
            for(int i = regs[14]; i < 32768; i++) {
                out << hexFormat(decToHex(i)) << ":" << std::setw(8)
                    << "0x" << hexFormat(decToHex(mem[i])) << "\n";
            }
            out << "\n";
        }

            out << "Flags: \n"
            << "Z = " << (Z ? "1" : "0") << "\n"
            << "C = " << (C ? "1" : "0") << "\n";
    
        return out.str();
    }
};

#endif