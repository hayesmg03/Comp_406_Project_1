#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

unsigned char PC = 1;
unsigned char memory[256];
unsigned char registers[4];
//  references to corresponding registers arr
unsigned char &A=registers[0], &B=registers[1], &C=registers[2], &D=registers[3];
unsigned char testProgram[21] = {0xff,0xfe,0x23,0x15,0xc8,0xcb,0xcd,0xcd,0x49,0x5f,0x74,0xcc,0xcd,0x1b,0xcc,0xde,0x5f,0xff,0xff,0x37,0x01};
bool halted = false;


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
    if(opcode == 0 && rs == 1)
    {
        halted = true;
    }
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
        } else if(rs == 1){
            A += B;
        } else if(rs == 2){
            A += C;
        } else if(rs == 3){
            A += D;
        }
        cout << "ADD ";

    }   else if(opcode == 7 && rd == 1)
    {
        if(rs == 0) {
            B += A;
        } else if(rs == 1){
            B += B;
        } else if(rs == 2){
            B += C;
        } else if(rs == 3){
            B += D;
        }
        cout << "ADD ";

    }   else if(opcode == 7 && rd == 2)
    {
        if(rs == 0) {
            C += A;
        } else if(rs == 1){
            C += B;
        } else if(rs == 2){
            C += C;
        } else if(rs == 3){
            C += D;
        }
        cout << "ADD ";

    }   else if(opcode == 7 && rd == 3) {
        if (rs == 0) {
            D += A;
        } else if (rs == 1) {
            D += B;
        } else if (rs == 2) {
            D += C;
        } else if (rs == 3) {
            D += D;
        }
        cout << "ADD ";

    }
    //  SUB
    else if(opcode == 1 && rd == 0)
    {
        if(rs == 0) {
            A -= A;
        } else if(rs == 1){
            A -= B;
        } else if(rs == 2){
            A -= C;
        } else if(rs == 3){
            A -= D;
        }
        cout << "SUB ";

    }   else if(opcode == 1 && rd == 1)
    {
        if(rs == 0) {
            B -= A;
        } else if(rs == 1){
            B -= B;
        } else if(rs == 2){
            B -= C;
        } else if(rs == 3){
            B -= D;
        }
        cout << "SUB ";

    }   else if(opcode == 1 && rd == 2)
    {
        if(rs == 0) {
            C -= A;
        } else if(rs == 1){
            C -= B;
        } else if(rs == 2){
            C -= C;
        } else if(rs == 3){
            C -= D;
        }
        cout << "SUB ";

    }   else if(opcode == 1 && rd == 3)
    {
        if(rs == 0) {
            D -= A;
        } else if(rs == 1){
            D -= B;
        } else if(rs == 2){
            D -= C;
        } else if(rs == 3){
            D -= D;
        }
        cout << "SUB ";

    }
//  LOAD
    else if(opcode == 2 && rd == 0)
    {
        cout << "LOAD ";
        if(rs == 0)
        {
            A = memory[A];
        } else if(rs == 1) {
            A = memory[B];
        } else if(rs == 2){
            A = memory[C];
        } else if(rs == 3){
            A = memory[D];
        }
    }
    if(opcode == 2 && rd == 1)
    {
        cout << "LOAD ";

        if(rs == 0)
        {
            B = memory[A];
        } else if(rs == 1) {
            B = memory[B];
        } else if(rs == 2){
            B = memory[C];
        } else if(rs == 3){
            B = memory[D];
        }
    }
    if(opcode == 2 && rd == 2)
    {
        cout << "LOAD ";

        if(rs == 0)
        {
            C = memory[A];
        } else if(rs == 1) {
            C = memory[B];
        } else if(rs == 2){
            C = memory[C];
        } else if(rs == 3){
            C = memory[D];
        }
    }
    if(opcode == 2 && rd == 3)
    {
        cout << "LOAD ";
        if(rs == 0)
        {
            D = memory[A];
        } else if(rs == 1) {
            D = memory[B];
        } else if(rs == 2){
            D = memory[C];
        } else if(rs == 3){
            D = memory[D];
        }
    }
//  SKIPNZ
    else if(opcode == 4 && rd == 0 && A != 0 && rs == 1)
    {
        PC += 1;
        cout << "SKIPNZ ";
    }   else if(opcode == 4 && rd == 1 && B != 0 && rs == 1)
    {
        PC += 1;
        cout << "SKIPNZ ";

    }   else if(opcode == 4 && rd == 2 && C != 0 && rs == 1)
    {
        PC += 1;
        cout << "SKIPNZ ";

    }   else if(opcode == 4 && rd == 3 && D != 0 && rs == 1)
    {
        PC += 1;
        cout << "SKIPNZ ";

    }
//  JALR
    else if(opcode == 5 && rd == 0)
    {
        cout << "JALR ";

        if(rs == 0)
        {
            unsigned char temp = PC + 1;
            PC = A;
            A = temp;
        }  else if(rs == 1) {
            A = PC + 1;
            PC = B;
        }  else if(rs == 2) {
            A = PC + 1;
            PC = C;
        }  else if(rs == 3) {
            A = PC + 1;
            PC = D;
        }
    }
    else if(opcode == 5 && rd == 1)
    {
        cout << "JALR ";

        if(rs == 0)
        {
            B = PC + 1;
            PC = A;
        }  else if(rs == 1) {
            unsigned char temp = PC + 1;
            PC = B;
            B = temp;
        }  else if(rs == 2) {
            B = PC + 1;
            PC = C;
        }  else if(rs == 3) {
            B = PC + 1;
            PC = D;
        }
    }else if(opcode == 5 && rd == 2)
    {
        cout << "JALR ";

        if(rs == 0)
        {
            C = PC + 1;
            PC = A;
        }  else if(rs == 1) {
            C = PC + 1;
            PC = B;
        }  else if(rs == 2) {
            unsigned char temp = PC + 1;
            PC = C;
            C = temp;

        }  else if(rs == 3) {
            C = PC + 1;
            PC = D;
        }
    }else if(opcode == 5 && rd == 3)
    {
        cout << "JALR ";
        if(rs == 0)
        {
            D = PC + 1;
            PC = A;
        }  else if(rs == 1) {
            D = PC + 1;
            PC = B;
        }  else if(rs == 2) {
            D = PC + 1;
            PC = C;
        }  else if(rs == 3) {
            unsigned char temp = PC + 1;
            PC = D;
            D = temp;
        }
    }
//  STORE
    if(opcode == 3 && rd == 0)
    {
        cout << "STORE ";
        if(rs == 0)
        {
            memory[A] = A;
        } else if (rs == 1) {
            memory[B] = A;
        }else if (rs == 2) {
            memory[C] = A;
        }else if (rs == 3) {
            memory[D] = A;
        }
    } else if(opcode == 3 && rd == 1)
    {
        cout << "STORE ";

        if(rs == 0)
        {
            memory[A] = B;
        } else if (rs == 1) {
            memory[B] = B;
        }else if (rs == 2) {
            memory[C] = B;
        }else if (rs == 3) {
            memory[D] = B;
        }
    }if(opcode == 3 && rd == 2)
    {
        cout << "STORE ";

        if(rs == 0)
        {
            memory[A] = C;
        } else if (rs == 1) {
            memory[B] = C;
        }else if (rs == 2) {
            memory[C] = C;
        }else if (rs == 3) {
            memory[D] = C;
        }
    }if(opcode == 3 && rd == 3)
    {
        cout << "STORE ";

        if(rs == 0)
        {
            memory[A] = D;
        } else if (rs == 1) {
            memory[B] = D;
        }else if (rs == 2) {
            memory[C] = D;
        }else if (rs == 3) {
            memory[D] = D;
        }
    }

    return "no instruction";
}

int main()
{




//  set each register to 0
    A = 0, B = 0, C = 0, D = 0;

//  set the item in index 0xfe of memory to 2
    memory[0xfe] = 2;

//  copies the program into the memory array
    int i = 0;
    for(unsigned char & step : testProgram)
    {
        memory[i] = step;
        i++;
    }

    i = 0;
//  main loop that iterates through the program and executes each instruction
    while(!halted)
    {

        unsigned char instruction = memory[PC - 1];

        doInstruction(instruction);

        printf( "%i, PC=%x, inst=%x, A=%x, B=%x, C=%x, D=%x\n", i, PC, instruction, A, B, C, D);

        PC++;
        i++;
    }



    cout << memory[0xff];



    return 0;
}













