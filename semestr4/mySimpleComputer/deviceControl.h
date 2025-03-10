#include<stdio.h>

#define COMMAND_MASK 0x7F  // Маска для команды (7 бит)
#define OPERAND_MASK 0x7F  // Маска для операнда (7 бит)
#define SIGN_MASK 0x80     // Маска для знака (1 бит)

int sc_commandEncode(int sign, int command, int operand, int *value);
int sc_commandDecode(int value, int *sign, int *command, int *operand);
int sc_commandValidate(int command);

