#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

unsigned char PC = 0;
unsigned char memory[256];
unsigned char registers[4];
unsigned char &A=registers[0], &B=registers[1], &C=registers[2], &D=registers[3];
unsigned char testProgram[21] = {0xff,0xfe,0x23,0x15,0xc8,0xcb,0xcd,0xcd,0x49,0x5f,0x74,0xcc,0xcd,0x1b,0xcc,0xde,0x5f,0xff,0xff,0x37,0x01};



string doInstruction(unsigned char instruction)
{
    //bytes indexed from 0, right to left

    //bitshift right 4 places then take last 4 bits
    unsigned char opcode = (instruction >> 4) & 15;
    //bitshift right 2 places then take last 2 bits
    unsigned char rd = (instruction >> 2) & 3;
    //take last 2 bits
    unsigned char rs = instruction & 3;
    //take last 2 bits of opcode and add rs
    unsigned char imm = ((opcode & 3) << 2) + rs;



//  HALT
//    if(instruction == 0x01)
//    {
//        cout << "HALT";
//        exit(0);
//    }
//  SLI
    if(opcode >> 2 == 3)
    {
        cout << "SLI ";
        if(rd == 0)
        {
            A = (A << 4) + imm;
        }
        if(rd == 1)
        {
            B = (B << 4) + imm;
        }
        if(rd == 2)
        {
            C = (C << 4) + imm;
        }
        if(rd == 3)
        {
            D = (D << 4) + imm;
        }
    }
//  ADD
    else if(opcode == 7 && rd == 0)
    {
        if(rs == 0) {
            A += A;
        } else if(rs == 0){
            A += B;
        } else if(rs == 0){
            A += C;
        } else if(rs == 0){
            A += D;
        }
        cout << "ADD ";

    }   else if(opcode == 7 && rd == 1)
    {
        if(rs == 1) {
            B += A;
        } else if(rs == 0){
            B += B;
        } else if(rs == 0){
            B += C;
        } else if(rs == 0){
            B += D;
        }
        cout << "ADD ";

    }   else if(opcode == 7 && rd == 2)
    {
        if(rs == 2) {
            C += A;
        } else if(rs == 0){
            C += B;
        } else if(rs == 0){
            C += C;
        } else if(rs == 0){
            C += D;
        }
        cout << "ADD ";

    }   else if(opcode == 7 && rd == 3)
    {
        if(rs == 3) {
            D += A;
        } else if(rs == 0){
            D += B;
        } else if(rs == 0){
            D += C;
        } else if(rs == 0){
            D += D;
        }
        cout << "ADD ";

    }
//  LOAD
    if(opcode == 2 && rd == 0)
    {
        cout << "LOAD ";
        if(rs == 0)
        {
            A += memory[A];
        } else if(rs == 1) {
            A += memory[B];
        } else if(rs == 2){
            A += memory[C];
        } else if(rs == 3){
            A += memory[D];
        }
    }
    if(opcode == 2 && rd == 1)
    {
        cout << "LOAD ";

        if(rs == 0)
        {
            B += memory[A];
        } else if(rs == 1) {
            B += memory[B];
        } else if(rs == 2){
            B += memory[C];
        } else if(rs == 3){
            B += memory[D];
        }
    }
    if(opcode == 2 && rd == 2)
    {
        cout << "LOAD ";

        if(rs == 0)
        {
            C += memory[A];
        } else if(rs == 1) {
            C += memory[B];
        } else if(rs == 2){
            C += memory[C];
        } else if(rs == 3){
            C += memory[D];
        }
    }
    if(opcode == 2 && rd == 3)
    {
        cout << "LOAD ";
        if(rs == 0)
        {
            D += memory[A];
        } else if(rs == 1) {
            D += memory[B];
        } else if(rs == 2){
            D += memory[C];
        } else if(rs == 3){
            D += memory[D];
        }
    }

    return "no instruction";
}

int main()
{

//  references to corresponding registers arr


//  set each register to 0
    A = 0, B = 0, C = 0, D = 0;

   unsigned char f = 0x66;

    cout << f << "\n";

    memory[0xfe] = 2;

    int i = 0;
    for(unsigned char & step : testProgram)
    {
        memory[i] = step;

        unsigned char instruction = memory[PC];

        doInstruction(instruction);

        printf("PC=%x, inst=%x, A=%x, B=%x, C=%x, D=%x\n", PC, instruction, A, B, C, D);

        PC++;
        i++;
    }



    //cout << memory[0xfe];



    return 0;
}













