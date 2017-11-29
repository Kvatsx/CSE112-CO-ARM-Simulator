/*
The project is developed as part of Computer Architecture class
Project Name: Functional Simulator for subset of ARM Processor
Developer's Name: Kaustav Vats, Shravika Mittal, Meghna Gupta.
*/
#include <stdio.h>
#include <stdlib.h>

// Registers
static int R[16];
// Instructions Memory
static char MEM[4000];

// Intermediate Datapath.
static unsigned int rn;
static unsigned int op2;
static unsigned int inst;
static unsigned int rd;
static unsigned int immediate;
static int Instruction_Type;
static unsigned int opcode;
static int Binary[32];
static unsigned int R_All[16][1024];
unsigned int result;
unsigned int *updated_register;
static int offset;
static unsigned int f;
static int carry;
static int negate;
static int equate;
static unsigned int cond;

void reset_proc();
void load_program_memory(char *file_name);
int read_word(char *mem, unsigned int address);
void Run_ARMSim();
void Fetch();
void Decode();
void Execute();
void Memory();
void Write_Back();
void swi_exit();
void write_word(char *mem, unsigned int address, unsigned int data);
void write_data_memory();
int read_word(char *mem, unsigned int address);


int main()
{
	reset_proc();
	load_program_memory("input.mem");
	Run_ARMSim();
	return 0;
}
// Resets all Arrays & Variables to 0.
void reset_proc()
{
	for ( int i=0; i<16; i++ )
	{
		R[i] = 0;
	}
	for ( int i=0; i<4000; i++ )
	{
		MEM[i] = '0';
	}
	for ( int i=0; i<32; i++ )
	{
		Binary[i] = 0;
	}
	rn = 0;
	op2 = 0;
	Instruction_Type = -1;
	negate = 0;
	equate = 0;
	carry = 0;
}
void Run_ARMSim()
{
	while( 1 )
	{
		Fetch();
		Decode();
		Execute();
		Memory();
		Write_Back();
	}
}
void print_Decode_Imm1(char *s, unsigned int a, unsigned int b, unsigned int c, unsigned int d, int e)
{
	printf("DECODE: Operation is %s, First Operand is R%d, (immediate) second Operand is %d, Destination Register is R%d\n Read Registers: R%d = %d\n", s, a, b, c, d, e);
}

void print_Decode(char *s, unsigned int a, unsigned int b, unsigned int c, unsigned int d, int e, unsigned int f, int g)
{
	printf("DECODE: Operation is %s, First Operand is R%d, Second Operand is R%d, Destination Register is R%d\n Read Registers: R%d = %d, R%d = %d\n", s, a, b, c, d, e, f, g);
}
void Fetch()
{
	inst = read_word(MEM, R[15]);
	printf("Fetch: Instruction 0x%x from Address 0x%x\n", inst, R[15]);
	R[15] = R[15] + 4;
}
void Decode()
{
	unsigned int a = (inst>>26);
	a = (a<<30);
	a = (a>>30);
	f = a ;
	cond = (inst>>28); // check
	if(f==0)
	{
		unsigned int b = (inst<<6);
		immediate = (b>>31);
		unsigned int c = (inst<<7);
		opcode = (c>>28);
		rn = (inst>>16)&(0xF);
		unsigned int e = (inst<<16);
		rd = (e>>28);
		if(immediate == 0)
		{
			op2 = ((inst)&(0xF));
			switch(opcode)
			{
				case 4:
				print_Decode("ADD", rn, op2, rd, rn, R[rn], op2, R[op2]);
				break;
				case 2:
				print_Decode("SUB", rn, op2, rd, rn, R[rn], op2, R[op2]);
				break;
				case 1:
				print_Decode("XOR", rn, op2, rd, rn, R[rn], op2, R[op2]);
				break;
				case 15:
				print_Decode("MNV", rn, op2, rd, rn, R[rn], op2, R[op2]);
				break;
				case 13:
				print_Decode("MOV", rn, op2, rd, rn, R[rn], op2, R[op2]);
				break;
				case 10:
				print_Decode("CMP", rn, op2, rd, rn, R[rn], op2, R[op2]);
				break;
				case 5:
				print_Decode("ADC", rn, op2, rd, rn, R[rn], op2, R[op2]);
				break;
				case 12:
				print_Decode("ORR", rn, op2, rd, rn, R[rn], op2, R[op2]);
				break;
				case 0:
				print_Decode("AND", rn, op2, rd, rn, R[rn], op2, R[op2]);
				break;
				case 3:
				print_Decode("RSB", rn, op2, rd, rn, R[rn], op2, R[op2]);
				break;
				case 6:
				print_Decode("SBC", rn, op2, rd, rn, R[rn], op2, R[op2]);
				break;
				case 7:
				print_Decode("SRC", rn, op2, rd, rn, R[rn], op2, R[op2]);
				break;
				case 14:
				print_Decode("BIC", rn, op2, rd, rn, R[rn], op2, R[op2]);
				break;
			}
		}
		else if(immediate == 1)
		{
			op2 = ((inst)&(0xFF));
			switch(opcode)
			{
				case 4:
				print_Decode_Imm1("ADD", rn, op2, rd, rn, R[rn]);
				break;
				case 2:
				print_Decode_Imm1("SUB", rn, op2, rd, rn, R[rn]);
				break;
				case 1:
				print_Decode_Imm1("XOR", rn, op2, rd, rn, R[rn]);
				break;
				case 15:
				print_Decode_Imm1("MNV", rn, op2, rd, rn, R[rn]);
				break;
				case 13:
				print_Decode_Imm1("MOV", rn, op2, rd, rn, R[rn]);
				break;
				case 10:
				print_Decode_Imm1("CMP", rn, op2, rd, rn, R[rn]);
				break;
				case 5:
				print_Decode_Imm1("ADC", rn, op2, rd, rn, R[rn]);
				break;
				case 12:
				print_Decode_Imm1("ORR", rn, op2, rd, rn, R[rn]);
				break;
				case 0:
				print_Decode_Imm1("AND", rn, op2, rd, rn, R[rn]);
				break;
				case 3:
				print_Decode_Imm1("RSB", rn, op2, rd, rn, R[rn]);
				break;
				case 6:
				print_Decode_Imm1("SBC", rn, op2, rd, rn, R[rn]);
				break;
				case 7:
				print_Decode_Imm1("SRC", rn, op2, rd, rn, R[rn]);
				break;
				case 14:
				print_Decode_Imm1("BIC", rn, op2, rd, rn, R[rn]);
				break;
			}
		}
	}

	// ldr str - Data Transfer
	else if(f==1)
	{
		unsigned int a = (inst<<6);
		opcode = (a>>26);
		if(opcode == 25)
		{
			rn = (inst>>16)&(0xF);
			unsigned int e = (inst<<16);
			rd = (e>>28);
			op2 = ((inst)&(0xFFF));
			printf("DECODE: Operation is LDR, Base Register is R%d, Offset is %d, Destination Register is R%d\n",rn, op2, rd);
		}
		else if(opcode == 24)
		{
			rn = (inst>>16)&(0xF);
			unsigned int e = (inst<<16);
			rd = (e>>28);
			op2 = ((inst)&(0xFFF));
			printf("DECODE: Operation is STR, Base Register is R%d, Offset is %d, Destination Register is R%d\n",rn, op2, rd);
		}
	}

	// branch
	else if(f==2)
	{
		unsigned int a = (inst<<6);
		opcode = (a>>30);
		offset = (inst&(0xFFFFFF));
		if(opcode == 2)
		{
			switch (cond) {
				case 0:
				printf("DECODE: Operation is Branch Equals\n");
				break;
				case 13:
				printf("DECODE: Operation is Branch less than Equals\n");
				break;
				case 10:
				printf("DECODE: Operation is Branch greater than Equals\n");
				break;
				case 1:
				printf("DECODE: Operation is Branch Not Equals\n");
				break;
				case 14:
				printf("DECODE: Operation is Branch and Link\n");
				break;
				case 12:
				printf("DECODE: Operation is Branch Greater Than\n");
				break;
				case 11:
				printf("DECODE: Operation is Branch Less Than\n");
				break;
			}
		}
	}
}
void Execute()
{
	updated_register = 0;
	result = 0;
	if(f == 0)
	{
		if(immediate == 0)
		{
			switch (opcode) {
				case 4:
				result = R[rn] + R[op2];
				printf("EXECUTE: ADD %d and %d\n",R[rn], R[op2]);
				break;
				case 2:
				result = R[rn] - R[op2];
				printf("EXECUTE: SUB %d and %d\n",R[rn], R[op2]);
				break;
				case 1:
				result = R[rn] ^ R[op2];
				printf("EXECUTE: XOR %d and %d\n",R[rn], R[op2]);
				break;
				case 15:
				result = ~R[op2];
				printf("EXECUTE: MNV not of R%d in R%d\n",op2, rd);
				break;
				case 13:
				result = R[op2];
				printf("EXECUTE: MOV value R%d in R%d\n",op2, rd);
				break;
				case 5:
				result = R[rn] + R[op2];
				printf("EXECUTE: ADC %d and %d\n",R[rn], R[op2]);
				carry = 1;
				break;
				case 12:
				result = R[rn] | R[op2];
				printf("EXECUTE: ORR %d and %d\n",R[rn], R[op2]);
				break;
				case 0:
				result = R[rn] & R[op2];
				printf("EXECUTE: AND %d and %d\n",R[rn], R[op2]);
				break;
				case 3:
				result = R[op2] - R[rn];
				printf("EXECUTE: RSB %d and %d\n",R[rn], R[op2]);
				break;
				case 6:
				result = R[rn] - R[op2];
				printf("EXECUTE: SBC %d and %d\n",R[rn], R[op2]);
				carry = 1;
				break;
				case 7:
				result = R[op2] - R[rn];
				printf("EXECUTE: SRC %d and %d\n",R[rn], R[op2]);
				carry = 1;
				break;
				case 14:
				result = 0;
				printf("EXECUTE: BIC R%d\n",op2);
				break;
				case 10:
				if(R[rn] < R[op2])
				{
					result = -1;
					negate = 1;
				}
				else if(R[rn] > R[op2])
				{
					result = 1;
				}
				else
				{
					result = 0;
					equate = 1;
				}
				printf("EXECUTE: CMP %d and %d\n",R[rn], R[op2]);
				break;
			}
		}
		else  if(immediate == 1)
		{
			switch (opcode) {
				case 4:
				result = R[rn] + op2;
				printf("EXECUTE: ADD %d and %d\n",R[rn], op2);
				break;
				case 2:
				result = R[rn] - op2;
				printf("EXECUTE: SUB %d and %d\n",R[rn], op2);
				break;
				case 1:
				result = R[rn] ^ op2;
				printf("EXECUTE: XOR %d and %d\n",R[rn], op2);
				break;
				case 15:
				result = ~op2;
				printf("EXECUTE: MNV not of %d in R%d\n",op2, rd);
				break;
				case 13:
				result = op2;
				printf("EXECUTE: MOV value %d in R%d\n",op2, rd);
				break;
				case 5:
				result = R[rn] + op2;
				printf("EXECUTE: ADC %d and %d\n",R[rn], op2);
				carry = 1;
				break;
				case 12:
				result = R[rn] | op2;
				printf("EXECUTE: ORR %d and %d\n",R[rn], op2);
				break;
				case 0:
				result = R[rn] & op2;
				printf("EXECUTE: AND %d and %d\n",R[rn], op2);
				break;
				case 3:
				result = op2 - R[rn];
				printf("EXECUTE: RSB %d and %d\n",R[rn], op2);
				break;
				case 6:
				result = R[rn] - op2;
				printf("EXECUTE: SBC %d and %d\n",R[rn], op2);
				carry = 1;
				break;
				case 7:
				result = op2 - R[rn];
				printf("EXECUTE: SRC %d and %d\n",R[rn], op2);
				carry = 1;
				break;
				case 14:
				result = 0;
				printf("EXECUTE: BIC R%d\n",op2);
				break;
				case 10:
				if(R[rn] < op2)
				{
					result = -1;
					negate = 1;
				}
				else if(R[rn] > op2)
				{
					result = 1;
				}
				else
				{
					result = 0;
					equate = 1;
				}
				printf("EXECUTE: CMP %d and %d\n",R[rn], op2);
				break;
			}
		}
	}
	else if(f == 1)
	{
		if(opcode == 25)
		{
			int index = (op2/4); // else would store at 4, 8, 12, ...
			for(int j = 0 ; j<=15 ; j++)
			{
				if(j == rn)
				{
					result = R_All[j][index];
					printf("EXECUTE Load R%d's value = %d in R%d\n", rn, index+1, rd);
				}
			}
		}
		else if(opcode == 24)
		{
			int index = (op2/4); // else would store at 4, 8, 12, ...
			for(int j = 0 ; j<=15 ; j++)
			{
				if(j == rn)
				{
					updated_register = &R_All[j][index];
					printf("EXECUTE Store R%d's value = %d in R%d\n", rn, index+1, rd);
				}
			}
		}
	}
	else if(f == 2)
	{
		signed int extended_number;
		unsigned int sign_bit = (offset>>23);
		if(sign_bit == 0)
		{
			extended_number = offset*4;
		}
		else
		{
			extended_number = ((0xff000000 | offset)*4);
		}
		if(opcode == 2)
		{
			switch (cond) {
				case 0:
				printf("EXECUTE: Branch Equals offset is: 0x%x\n",offset);
				if(equate == 1)
				{
					R[15] = R[15] + 4 + extended_number;
				}
				break;
				case 13:
				printf("EXECUTE: Branch Less Than Equals offset is: 0x%x\n",offset);
				if(negate == 1 || equate == 1)
				{
					R[15] = R[15] + 4 + extended_number;
				}
				break;
				case 10:
				printf("EXECUTE: Branch Greater Than Equals is: 0x%x\n",offset);
				if(negate == 0 || equate == 1)
				{
					R[15] = R[15] + 4 + extended_number;
				}
				break;
				case 1:
				printf("EXECUTE: Branch Not Equals offset is: 0x%x\n",offset);
				if(equate != 1)
				{
					R[15] = R[15] + 4 + extended_number;
					printf("dgkrtkuh");
				}
				break;
				case 14:
				printf("EXECUTE: Branch And Link offset is: 0x%x\n",offset);
				R[15] = R[15] + 4 + extended_number;
				break;
				case 12:
				printf("EXECUTE: Branch Greater Than offset is: 0x%x\n",offset);
				if(negate == 0 && equate == 0)
				{
					R[15] = R[15] + 4 + extended_number;
				}
				break;
				case 11:
				printf("EXECUTE: Branch Less Than offset is: 0x%x\n",offset);
				if(negate == 1 && equate == 0)
				{
					R[15] = R[15] + 4 + extended_number;
				}
				break;
			}
		}
	}
}

void Memory()
{
	if(cond == 14)
	{
		if(opcode == 25)
		{
			for(int j = 0 ; j<=15 ; j++)
			{
				if(j == rn)
				{
					unsigned int index = op2/4;
					printf("MEMORY: Load %d from memory\n",R_All[j][index]);
				}
			}
		}
		else if(opcode == 25)
		{
			printf("MEMORY: Store %d in memory\n", rd);
		}
		else
		{
			printf("MEMORY: No memory operation\n");
		}
	}
	else
	{
		printf("MEMORY: No memory operation\n");
	}
}

void Write_Back()
{
	switch(f) {
		case 2:
		printf("WRITEBACK: No writeback operation required\n");
		break;
		case 1:
		switch(opcode){
			case 24:
			*(updated_register) = R[rd];
			printf("WRITEBACK: write %d to memory array\n",*(updated_register));
			break;
			case 25:
			R[rd] = result;
			printf("WRITEBACK: write %d to R%d\n",result,rd);
			break;
		}
		break;
		case 0:
		switch(opcode){
			case 10:
			printf("WRITEBACK: No writeback operation required\n");
			break;
			default:
			R[rd] = result;
			printf("WRITEBACK: write %d to R%d\n",result,rd);
		}
		break;
		case 3:
		printf("EXIT:\n");
		swi_exit();
		break;
	}
	printf("\n");
}
void swi_exit()
{
	write_data_memory();
	exit(0);
}
void load_program_memory(char *file_name)
{
	FILE *fp;
	unsigned int address, instruction;
	fp = fopen(file_name, "r");
	if(fp == NULL)
	{
		printf("Error opening input mem file\n");
		exit(1);
	}
	while(fscanf(fp, "%x %x", &address, &instruction) != EOF)
	{
		write_word(MEM, address, instruction);
	}
	fclose(fp);
}
void write_word(char *mem, unsigned int address, unsigned int data)
{
	int *data_p;
	data_p = (int*) (mem + address);
	*data_p = data;
}

//writes the data memory in "data_out.mem" file
void write_data_memory()
{
	FILE *fp;
	unsigned int i;
	fp = fopen("data_out.mem", "w");
	if(fp == NULL)
	{
		printf("Error opening dataout.mem file for writing\n");
		return;
	}

	for(i=0; i < 4000; i = i+4)
	{
		fprintf(fp, "%x %x\n", i, read_word(MEM, i));
	}
	fclose(fp);
}
int read_word(char *mem, unsigned int address)
{
	int *data;
	data =  (int*) (mem + address);
	return *data;
}
