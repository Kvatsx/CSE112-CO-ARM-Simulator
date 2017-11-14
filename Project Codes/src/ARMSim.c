/* 

The project is developed as part of Computer Architecture class
Project Name: Functional Simulator for subset of ARM Processor

Developer's Name: Kaustav Vats, Shravika Mittal, Meghna Gupta.

*/
#include <stdio.h>
#include <stdlib.h>

// Registers
static int Registers[16];
// Instructions Memory
static char MEM[4000];

// Intermediate Datapath.
static int Op_1;
static int Op_2;

void reset_proc();
void load_program_memory(char *file_name);

int main()
{
	reset_proc();
	// load_program_memory("Input.mem");
	// Run_ARMSim();
	return 0;
}
// Resets all Arrays & Variables to 0.
void reset_proc() 
{
	for ( int i=0; i<16; i++ )
	{
		Registers[i] = 0;
	}
	for ( int i=0; i<4000; i++ )
	{
		MEM[i] = '0';
	}
	Op_1 = 0;
	Op_2 = 0;
}
// void Run_ARMSim()
// {
	
// }
// void Fetch()
// {

// }
// void Decode()
// {

// }
// void Execute()
// {

// }
// void Memory()
// {

// }
// void Write_Back()
// {

// }
// void swi_exit() 
// {
//   	write_data_memory();
//   	exit(0);
// }
// void load_program_memory(char *file_name) 
// {
// 	FILE *fp;
//   	unsigned int address, instruction;
//   	fp = fopen(file_name, "r");
//   	if(fp == NULL) 
//   	{
//     	printf("Error opening input mem file\n");
//     	exit(1);
//   	}
//   	while(fscanf(fp, "%x %x", &address, &instruction) != EOF) 
//   	{
//     	write_word(MEM, address, instruction);
//   	}
//   	fclose(fp);
// }
// void write_word(char *mem, unsigned int address, unsigned int data) 
// {
//   	int *data_p;
//   	data_p = (int*) (mem + address);
//   	*data_p = data;
// }

// //writes the data memory in "data_out.mem" file
// void write_data_memory() 
// {
//   	FILE *fp;
//   	unsigned int i;
//   	fp = fopen("data_out.mem", "w");
//   	if(fp == NULL) 
//   	{
//     	printf("Error opening dataout.mem file for writing\n");
//     	return;
//   	}
  
//   	for(i=0; i < 4000; i = i+4)
//   	{
//     	fprintf(fp, "%x %x\n", i, read_word(MEM, i));
//   	}
//   	fclose(fp);
// }
// int read_word(char *mem, unsigned int address) 
// {
//   	int *data;
//   	data =  (int*) (mem + address);
//   	return *data;
// }