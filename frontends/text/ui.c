#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "disasm.h"
#include "cpu.h"

// available commands
typedef struct command_struct
{
	enum {
		COMMAND_UNKNOWN,
		COMMAND_QUIT,
		COMMAND_STEP,
		COMMAND_INFO,
	} parsed_command;
	char* text;
} command_t;

command_t commands[] = {
	{COMMAND_UNKNOWN,""},
	{COMMAND_QUIT,"quit"},
	{COMMAND_QUIT,"exit"},
	{COMMAND_STEP,"step"},
	{COMMAND_STEP,"s"},
	{COMMAND_INFO,"info"},
	{COMMAND_INFO,"i"}
};

// functions specific to the text-based frontend
void prompt(cpu_t cpu);
command_t parse_command(char* command);

void ui_step(cpu_t* cpu)
{
	char* command_buf = NULL;
	size_t line_size;
	command_t cmd;
	prompt(*cpu);
	getline(&command_buf,&line_size,stdin);
	command_buf[strlen(command_buf)-1] = 0;
	
	// this if statement mimics gdb's ability to remember your last command when you hit 'enter' without typing a command
	if(strcmp(command_buf,"") != 0)
		cmd = parse_command(command_buf);
		
	switch(cmd.parsed_command)
	{
		case COMMAND_QUIT:
			printf("Shutting down...\n");
			cpu->power = OFF;
			break;
		case COMMAND_STEP:
			step(cpu);
			break;
		case COMMAND_INFO:
			dump_state(*cpu);
			break;
		default:
			printf("Unknown command: %s\n",command_buf);
			break;
	}
	free(command_buf);
}

void prompt(cpu_t cpu)
{
	printf("[%.6X] Next Opcode: %.2X\n>",cpu.ip,cpu.memory[cpu.ip]);
}

command_t parse_command(char* command)
{
	unsigned int i = 0;
	command_t rv = commands[0];
	while(i < sizeof commands / sizeof commands[0])
	{
		if(strcmp(commands[i].text,command)==0)
			rv = commands[i];
		i++;
	}
	return rv;
}
