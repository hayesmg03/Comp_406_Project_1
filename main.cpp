#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

unsigned char PC = 0;
unsigned char memory[256];
unsigned char registers[4];
unsigned char program[21] = {0xff,0xfe,0x23,0x15,0xc8,0xcb,0xcd,0xcd,0x49,0x5f,0x74,0xcc,0xcd,0x1b,0xcc,0xde,0x5f,0xff,0xff,0x37,0x01};

string doInstruction(unsigned char instruction, unsigned char &A, unsigned char &B, unsigned char &C, unsigned char &D)
{
    //bytes indexed from 0, right to left
    unsigned char opcode = (instruction >> 4) & 15;
    unsigned char rd = (instruction >> 2) & 3;
    unsigned char rs = instruction & 3;
    unsigned char imm = (opcode & 3) + rs;


//    int regd = rd;
//    int opcodeInt = opcode;
//    cout << rd << "\n";
//    cout << regd << "\n";
//    cout << opcode << "\n";
//    cout << opcodeInt << "\n";

//  HALT
    if(instruction == 0x01)
    {
        cout << "HALT";
        exit(0);
    }
//  SLI
    if(opcode >> 2 == 3)
    {

    }

    return "no instruction";
}

int main()
{

//  references to corresponding registers arr
    unsigned char &A=registers[0],  &B=registers[1], &C=registers[2], &D=registers[3];

//  set each register to 0
    A = 0;
    B = 0;
    C = 0;
    D = 0;


    int i = 0;
    for(unsigned char & step : program)
    {
        memory[i] = step;
        i++;
    }

    memory[0xfe] = 2;

    for(unsigned char & step : program)
    {
        unsigned char instruction = memory[PC];

        doInstruction(instruction, A, B, C, D);

        PC++;
    }





    //cout << memory[0xff];



    return 0;
}













