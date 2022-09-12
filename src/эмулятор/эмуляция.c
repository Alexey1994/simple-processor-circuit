#include "types.c"


#define BITNESS 9
#define DATA_MASK ((~(Number)0) >> (sizeof(Number) * 8 - BITNESS))
#define INDEX_MASK (DATA_MASK >> 2)
#define PROGRAM_END (1 << (BITNESS - 2))
#define PROGRAM_START (PROGRAM_END / 2)


typedef enum {
	LOAD_OPCODE         = 0b00 << (BITNESS - 2),
	STORE_OPCODE        = 0b01 << (BITNESS - 2),
	SKIP_IF_ZERO_OPCODE = 0b10 << (BITNESS - 2)
}
Opcode;


#define OPERATION_INDEX     0

#define OPERAND1_ADDRESS    1
#define OPERAND2_ADDRESS    2

#define SHIFT_LEFT_ADDRESS  3
#define SHIFT_RIGHT_ADDRESS 4
#define NOT_ADDRESS         5

#define AND_ADDRESS         6
#define OR_ADDRESS          7
//#define ADD_ADDRESS         8


// in_addr:  OPERATION_INDEX, OPERATION
// in_data:  DATA
// out_data: DATA, OPERATION


Number program_end;


void execute(Number memory[PROGRAM_END])
{
	Number previouse_load_address;

	Number operation;
	Number data_register;

	memory[OPERATION_INDEX] = PROGRAM_START;

	previouse_load_address = 0;

	while(memory[OPERATION_INDEX] != program_end) {
		memory[SHIFT_LEFT_ADDRESS] = (memory[OPERAND1_ADDRESS] << 1) & DATA_MASK;
		memory[SHIFT_RIGHT_ADDRESS] = (memory[OPERAND1_ADDRESS] >> 1) & DATA_MASK;
		memory[NOT_ADDRESS] = (~memory[OPERAND1_ADDRESS]) & DATA_MASK;

		memory[AND_ADDRESS] = ((memory[OPERAND1_ADDRESS] & DATA_MASK) & (memory[OPERAND2_ADDRESS] & DATA_MASK)) & DATA_MASK;
		memory[OR_ADDRESS] = ((memory[OPERAND1_ADDRESS] & DATA_MASK) | (memory[OPERAND2_ADDRESS] & DATA_MASK)) & DATA_MASK;
		//memory[ADD_ADDRESS] = ((memory[OPERAND1_ADDRESS] & DATA_MASK) + (memory[OPERAND2_ADDRESS] & DATA_MASK)) & DATA_MASK;

		operation = memory[memory[OPERATION_INDEX]] & DATA_MASK;

		if(!(operation & SKIP_IF_ZERO_OPCODE) || data_register) {
			if(operation & STORE_OPCODE) {
				if((operation & INDEX_MASK) >= PROGRAM_START) {
					print(
						"%x skip STORE in %x\n",
						memory[OPERATION_INDEX],
						operation & INDEX_MASK
					);
				}
				else {
					print(
						"%x [%x] = [%x] = %x\n",
						memory[OPERATION_INDEX],
						operation & INDEX_MASK,
						previouse_load_address,
						data_register
					);

					memory[operation & INDEX_MASK] = data_register;
				}
			}
			else {
				previouse_load_address = operation & INDEX_MASK;
				data_register = memory[operation & INDEX_MASK] & DATA_MASK;
			}
		}

		memory[OPERATION_INDEX] = (memory[OPERATION_INDEX] + 1) & DATA_MASK;
	}

	print("\n\n");
}


#include "memory.c"


#define LOAD(source) {memory[i] = LOAD_OPCODE | (source & INDEX_MASK); ++i;}
#define STORE(target) {memory[i] = STORE_OPCODE | (target & INDEX_MASK); ++i;}
#define LOAD_IF(source) {memory[i] = SKIP_IF_ZERO_OPCODE | LOAD_OPCODE | (source & INDEX_MASK); ++i;}
#define STORE_IF(target) {memory[i] = SKIP_IF_ZERO_OPCODE | STORE_OPCODE | (target & INDEX_MASK); ++i;}

#define IF(address_pointer) {LOAD_IF(address_pointer); STORE_IF(OPERATION_INDEX);}
#define JUMP(address_pointer) {LOAD(address_pointer); STORE(OPERATION_INDEX);}

#define COPY(source, target) {LOAD(source); STORE(target);}

#define NOT(operand, target) {LOAD(operand); STORE(OPERAND1_ADDRESS); LOAD(NOT_ADDRESS); STORE(target);}
#define SHIFT_LEFT(operand, target) {LOAD(operand); STORE(OPERAND1_ADDRESS); LOAD(SHIFT_LEFT_ADDRESS); STORE(target);}
#define SHIFT_RIGHT(operand, target) {LOAD(operand); STORE(OPERAND1_ADDRESS); LOAD(SHIFT_RIGHT_ADDRESS); STORE(target);}

#define AND(operand1, operand2, target) {LOAD(operand1); STORE(OPERAND1_ADDRESS); LOAD(operand2); STORE(OPERAND2_ADDRESS); LOAD(AND_ADDRESS); STORE(target);}
#define OR(operand1, operand2, target) {LOAD(operand1); STORE(OPERAND1_ADDRESS); LOAD(operand2); STORE(OPERAND2_ADDRESS); LOAD(OR_ADDRESS); STORE(target);}
//#define ADD(operand1, operand2, target) {LOAD(operand1); STORE(OPERAND1_ADDRESS); LOAD(operand2); STORE(OPERAND2_ADDRESS); LOAD(ADD_ADDRESS); STORE(target);}

#define CONSTANT_VALUE(index, value) {memory[PROGRAM_END - 1 - index] = value;}

#define VARIABLE(index) (8 + index)
#define CONSTANT(index) (PROGRAM_END - 1 - index)


Number memory[PROGRAM_END] = {0};


Number last_constant_index = 0;

Number constant_value(Number value)
{
	Number index;

	index = PROGRAM_END - 1 - last_constant_index;
	++last_constant_index;

	memory[index] = value;

	return index;
}


Number last_variable_index = 0;

Number variable()
{
	Number index;

	index = VARIABLE(last_variable_index);
	++last_variable_index;

	return index;
}


typedef struct {
	Byte   name[12];
	Number address;
}
Label;


Label  labels[128];
Number last_label_index = 0;


#define LABEL(label_name) {copy_bytes(labels[last_label_index].name, label_name, 12); labels[last_label_index].address = i; ++last_label_index;}

Number find_label(Byte* label_name)
{
	Number i;

	for(i = 0; i < sizeof(labels) / sizeof(Label); ++i) {
		if(!compare_null_terminated_bytes(label_name, labels[i].name))
			return labels[i].address - 1;
	}

	print("label %s not found\n", label_name);

	return 0;
}


Number main()
{
	Number operation;
	Number i;

	clean_bytes(memory, PROGRAM_END * sizeof(Number));
	i = PROGRAM_START;

	{
		#include "program.c"
	}

	program_end = i;
	execute(memory);

	for(i = PROGRAM_START; i < PROGRAM_END; ++i) {
		operation = memory[i];

		if(i < program_end) {
			if(operation & SKIP_IF_ZERO_OPCODE) {
				if(operation & STORE_OPCODE) {
					if((operation & INDEX_MASK) >= PROGRAM_START) {
						print("error ");
					}

					print("%x STORE IF %x\n", i, operation & INDEX_MASK);
				}
				else {
					print("%x LOAD IF  %x\n", i, operation & INDEX_MASK);
				}
			}
			else {
				if(operation & STORE_OPCODE) {
					if((operation & INDEX_MASK) >= PROGRAM_START) {
						print("error ");
					}

					print("%x STORE    %x\n", i, operation & INDEX_MASK);
				}
				else {
					print("%x LOAD     %x\n", i, operation & INDEX_MASK);
				}
			}
		}
		else
			print("%x %d\n", i, operation);
	}

	print("\n");

	for(i = 8; i < PROGRAM_START; ++i) {
		print("%x %d\n", i, memory[i]);
	}
}