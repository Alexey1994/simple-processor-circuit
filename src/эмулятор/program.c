// inc a
Number repeat = constant_value(0);
Number next   = constant_value(0);
Number end    = constant_value(0);

Number zero        = constant_value(0);
Number one         = constant_value(1);
Number rezak_value = constant_value(0xFFFE);
Number a           = constant_value(15);

Number shifter = variable();
Number l1      = variable();
Number rezak   = variable();
Number a_copy  = variable();

COPY(a, a_copy)
COPY(one, shifter)
COPY(rezak_value, rezak)

LABEL("repeat")
AND(a_copy, shifter, l1)
IF(next)

OR(a_copy, shifter, a_copy)
JUMP(end)

LABEL("next") {
	AND(a_copy, rezak, a_copy);
	SHIFT_LEFT(rezak, rezak)
	OR(rezak, one, rezak)
	SHIFT_LEFT(shifter, shifter)
	IF(repeat)
}

LABEL("end")


memory[repeat] = find_label("repeat");
memory[next] = find_label("next");
memory[end] = find_label("end");


//AND(a, one, r);
//r = a & b
//c = a ? 0 : 1

/*
// a + b
Number a;
Number b;
Number c;

a = constant_value(12);
b = constant_value(23);
c = variable();

ADD(a, b, c)
*/

/*
Number initial_index;
Number one;
Number index;
Number cycle;

initial_index = constant_value(DATA_MASK - 3);
one = constant_value(1);
index = variable();
cycle = constant_value(0);

COPY(initial_index, index)
LABEL("cycle")
ADD(index, one, index)
IF(cycle)

memory[cycle] = find_label("cycle");
*/

/*
//SUB
Number one;
Number a;
Number b;
Number c;

one = constant_value(1);
a = constant_value(7);
b = constant_value(3);
c = variable();

NOT(b, c)
ADD(c, one, c)
ADD(c, a, c)
*/

/*
//MUL
Number zero;
Number one;
Number a;
Number b;
Number initial_index;
Number c;
Number index;
Number a_copy;
Number b_copy;
Number b_copy2;
Number repeat;
Number add_a;
Number skip_add_a;

zero = constant_value(0);
one = constant_value(1);
a = constant_value(16);
b = constant_value(31);
initial_index = constant_value(DATA_MASK - BITNESS);

c = variable();
index = variable();
a_copy = variable();
b_copy = variable();
b_copy2 = variable();

repeat = constant_value(0);
add_a = constant_value(0);
skip_add_a = constant_value(0);

COPY(zero, c)               //             c = 0
COPY(initial_index, index)  //             index = DATA_MASK - BITNESS
COPY(a, a_copy)             //             a_copy = a
COPY(b, b_copy)             //             b_copy = b
LABEL("repeat")
COPY(b_copy, b_copy2)       // repeat:     b_copy2 = b_copy
AND(b_copy2, one, b_copy2)  //             b_copy2 &= 1
IF(add_a)                   //             b_copy2 => add_a
JUMP(skip_add_a)            //             1 => skip_add_a
LABEL("add_a")
ADD(c, a_copy, c)           // add_a:      c += a_copy
LABEL("skip_add_a")
SHIFT_LEFT(a_copy, a_copy)  // skip_add_a: a_copy <<= 1
SHIFT_RIGHT(b_copy, b_copy) //             b_copy >>= 1
ADD(index, one, index)      //             index += 1
IF(repeat)                  //             index => repeat

memory[repeat] = find_label("repeat");
memory[add_a] = find_label("add_a");
memory[skip_add_a] = find_label("skip_add_a");*/


/*
#define RETURN_ADDRESS 0
#define RETURN {ADD(VARIABLE(RETURN_ADDRESS), CONSTANT(2), VARIABLE(RETURN_ADDRESS)); JUMP(VARIABLE(RETURN_ADDRESS));}
#define CALL(address) {COPY(OPERATION_INDEX, VARIABLE(RETURN_ADDRESS)); JUMP(address);}


CONSTANT_VALUE (0, 1)
CONSTANT_VALUE (1, 1)
CONSTANT_VALUE (2, 3) //добавка к return

CONSTANT_VALUE (3, 15)
CONSTANT_VALUE (4, 6)

COPY(CONSTANT(3), VARIABLE(1))
COPY(CONSTANT(4), VARIABLE(2))
CALL(CONSTANT(6))
JUMP(CONSTANT(5))

LABEL("SUB")
CONSTANT_VALUE (6, find_label("SUB"))
	NOT(VARIABLE(2), VARIABLE(2))
	ADD(VARIABLE(2), CONSTANT(1), VARIABLE(2))
	ADD(VARIABLE(1), VARIABLE(2), VARIABLE(1))
	RETURN

LABEL("MUL")
CONSTANT_VALUE (7, find_label("MUL"))
	CONSTANT_VALUE (4, DATA_MASK - BITNESS)

	COPY (CONSTANT(0), VARIABLE(0))             //             result = 0
	COPY (CONSTANT(4), VARIABLE(1))             //             i = DATA_MASK - BITNESS
	COPY (CONSTANT(2), VARIABLE(2))             //             a_copy = a
	COPY (CONSTANT(3), VARIABLE(3))             //             b_copy = b
	LABEL("repeat")
	COPY (VARIABLE(3), VARIABLE(4))             // repeat:     b_copy2 = b_copy
	AND (VARIABLE(4), CONSTANT(1), VARIABLE(4)) //             b_copy2 &= 1
	IF (CONSTANT(6))                            //             b_copy2 => add_a
	JUMP (CONSTANT(7))                          //             1 => skip_add_a
	LABEL("add_a")
	ADD (VARIABLE(0), VARIABLE(2), VARIABLE(0)) // add_a:      result += a_copy
	LABEL("skip_add_a")
	SHIFT_LEFT(VARIABLE(2), VARIABLE(2))        // skip_add_a: a_copy <<= 1
	SHIFT_RIGHT(VARIABLE(3), VARIABLE(3))       //             b_copy >>= 1
	ADD(VARIABLE(1), CONSTANT(1), VARIABLE(1))  //             i += 1
	IF (CONSTANT(5))                            //             i => repeat

	CONSTANT_VALUE (5, find_label("repeat"))
	CONSTANT_VALUE (6, find_label("add_a"))
	CONSTANT_VALUE (7, find_label("skip_add_a"))
	RETURN


LABEL("end")
CONSTANT_VALUE (5, find_label("end"))*/