#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEMORY_SIZE 100
#define INSTRUCTION_LENGTH 100

struct vmState{
    //struct tracks the state of the virtual machine
    int codeMemory[MEMORY_SIZE][INSTRUCTION_LENGTH];
    char currentLine[INSTRUCTION_LENGTH];
    int dataMemory[100];
    int R1, R2, R3, R4, R5, R6, R7, R8, R9, R10;
    int compareFlag;
};

enum registers {
    //this enum is used in several switch statements that need to select a register
    INST_UNDEFINED,
    INST_R1,
    INST_R2,
    INST_R3,
    INST_R4,
    INST_R5,
    INST_R6,
    INST_R7,
    INST_R8,
    INST_R9,
    INST_R10
};

int *get_reg_ptr(struct vmState *vmState, const char *reg) {
  //FUNCTION: creates a pointer to a register
  int *pReg = NULL;
  //compares strings to find the correct register to point to
  if (strcmp(reg, "R1") == 0) {
    pReg = &vmState->R1;
  } else if (strcmp(reg, "R2") == 0) {
    pReg = &vmState->R2;
  } else if (strcmp(reg, "R3") == 0) {
    pReg = &vmState->R3;
  } else if (strcmp(reg, "R4") == 0) {
    pReg = &vmState->R4;
  } else if (strcmp(reg, "R5") == 0) {
    pReg = &vmState->R5;
  } else if (strcmp(reg, "R6") == 0) {
    pReg = &vmState->R6;
  } else if (strcmp(reg, "R7") == 0) {
    pReg = &vmState->R7;
  } else if (strcmp(reg, "R8") == 0) {
    pReg = &vmState->R8;
  } else if (strcmp(reg, "R9") == 0) {
    pReg = &vmState->R9;
  } else if (strcmp(reg, "R10") == 0) {
    pReg = &vmState->R10;
  }
  //returns the pointer
  return pReg;
}

int MOVE(char * reg, char * valueToCopy, struct vmState *vmState) {
    //FUNCTION: moves a value from one register to another, or moves a constant into a register
    int opcode = INST_UNDEFINED;

    int *pReg = get_reg_ptr(vmState, reg);
    //compares strings to find the right enum value for the register
    if (strcmp(valueToCopy, "R1") == 0) {
        opcode = INST_R1;
      } else if (strcmp(valueToCopy, "R2") == 0) {
        opcode = INST_R2;
      } else if (strcmp(valueToCopy, "R3") == 0) {
        opcode = INST_R3;
      } else if (strcmp(valueToCopy, "R4") == 0) {
        opcode = INST_R4;
      } else if (strcmp(valueToCopy, "R5") == 0) {
        opcode = INST_R5;
      } else if (strcmp(valueToCopy, "R6") == 0) {
        opcode = INST_R6;
      } else if (strcmp(valueToCopy, "R7") == 0) {
        opcode = INST_R7;
      } else if (strcmp(valueToCopy, "R8") == 0) {
        opcode = INST_R8;
      } else if (strcmp(valueToCopy, "R9") == 0) {
        opcode = INST_R9;
      } else if (strcmp(valueToCopy, "R10") == 0) {
        opcode = INST_R10;
      }

      switch(opcode) {
        //this switch statement moves the value from the register selected in the enum code to the one pReg is pointing to,
        //or if the code is undefined then it assumes the value is a constant
        case INST_R1 :
          pReg = &vmState->R1;
          printf("MOVING R1 TO %s\n", reg);
          break;
        case INST_R2 :
          pReg = &vmState->R2;
          printf("MOVING R2 TO %s\n", reg);
          break;
        case INST_R3 :
          pReg = &vmState->R3;
          printf("MOVING R3 TO %s\n", reg);
          break;
        case INST_R4 :
          pReg = &vmState->R4;
          printf("MOVING R4 TO %s\n", reg);
          break;
        case INST_R5 :
          pReg = &vmState->R5;
          printf("MOVING R5 TO %s\n", reg);
          break;
        case INST_R6 :
          pReg = &vmState->R6;
          printf("MOVING R6 TO %s\n", reg);
          break;
        case INST_R7 :
          pReg = &vmState->R7;
          printf("MOVING R7 TO %s\n", reg);
          break;
        case INST_R8 :
          pReg = &vmState->R8;
          printf("MOVING R8 TO %s\n", reg);
          break;
        case INST_R9 :
          pReg = &vmState->R9;
          printf("MOVING R9 TO %s\n", reg);
          break;
        case INST_R10 :
          pReg = &vmState->R10;
          printf("MOVING R10 TO %s\n", reg);
          break;
        default : ;
          int num = atoi(valueToCopy);
          *pReg = num;
          printf("MOVING %d TO %s\n", num, reg);
      }

    return 0;
}

int STORE(char * reg, char * value, struct vmState *vmState) {
    //FUNCTION: stores a value into the data memory of a given register
    int *pReg = get_reg_ptr(vmState, reg);

    int num = atoi(value);
    //an int value is created by using atoi on the constant, then stored in the data memory
    //of whatever register that pReg is pointing to
    vmState->dataMemory[*pReg] = num;
    printf("STORING %s INTO %s DATA MEMORY\n", value, reg);

    return 0;
}

int LOAD(char * reg1, char * reg2, struct vmState *vmState) {
    //FUNCTION: similar to STORE, except the value is copied from one register to another
    int *pReg1 = get_reg_ptr(vmState, reg1);
    int *pReg2 = get_reg_ptr(vmState, reg1);

    int value = vmState->dataMemory[*pReg2];
    vmState->dataMemory[*pReg1] = value;
    printf("LOADING VALUE FROM %s TO %s\n", reg2, reg1);

    return 0;
}

int INPUT(char * reg, struct vmState *vmState) {
    //FUNCTION: similar to STORE, except the value is an ASCII code provided by user input
    int *pReg = get_reg_ptr(vmState, reg);
    int value;
    printf("ENTER A VALUE: \n");
    value = getchar();

    vmState->dataMemory[*pReg] = value;
    printf("STORING %d INTO %s DATA MEMORY\n", value, reg);

    return 0;
}

int OUTPUT(char * value, struct vmState *vmState) {
    //FUNCTION: outputs the value stored in a given register
    int opcode = INST_UNDEFINED;
    //compares strings to find the correct register and sets the opcode
    if (strcmp(value, "R1") == 0) {
        opcode = INST_R1;
      } else if (strcmp(value, "R2") == 0) {
        opcode = INST_R2;
      } else if (strcmp(value, "R3") == 0) {
        opcode = INST_R3;
      } else if (strcmp(value, "R4") == 0) {
        opcode = INST_R4;
      } else if (strcmp(value, "R5") == 0) {
        opcode = INST_R5;
      } else if (strcmp(value, "R6") == 0) {
        opcode = INST_R6;
      } else if (strcmp(value, "R7") == 0) {
        opcode = INST_R7;
      } else if (strcmp(value, "R8") == 0) {
        opcode = INST_R8;
      } else if (strcmp(value, "R9") == 0) {
        opcode = INST_R9;
      } else if (strcmp(value, "R10") == 0) {
        opcode = INST_R10;
      }

    switch(opcode) {
      //outputs the contents of the register, or if opcode is undefined
      //assumes the value is a constant and outputs that constant
      case INST_R1 :
        printf("OUTPUTTING: %ls\n", &vmState->R1);
        break;
      case INST_R2 :
        printf("OUTPUTTING: %ls\n", &vmState->R2);
        break;
      case INST_R3 :
        printf("OUTPUTTING: %ls\n", &vmState->R3);
        break;
      case INST_R4 :
        printf("OUTPUTTING: %ls\n", &vmState->R4);
        break;
      case INST_R5 :
        printf("OUTPUTTING: %ls\n", &vmState->R5);
        break;
      case INST_R6 :
        printf("OUTPUTTING: %ls\n", &vmState->R6);
        break;
      case INST_R7 :
        printf("OUTPUTTING: %ls\n", &vmState->R7);
        break;
      case INST_R8 :
        printf("OUTPUTTING: %ls\n", &vmState->R8);
        break;
      case INST_R9 :
        printf("OUTPUTTING: %ls\n", &vmState->R9);
        break;
      case INST_R10 :
        printf("OUTPUTTING: %ls\n", &vmState->R10);
        break;
      default :
        printf("OUTPUTTING: %s\n", value);
        break;
    }
    return 0;
}

int ADD(char * reg, char * valueToCopy, struct vmState *vmState) {
    //FUNCTION: adds a constant to the value stored in a given register
    int *pReg = get_reg_ptr(vmState, reg);
    //creates an integer from valueToCopy
    int num = atoi(valueToCopy);
    //increments the value stored in whatever register pReg is pointing to by that integer
    *pReg += num;

    printf("ADDING %d TO %s\n", num, reg);

    return 0;
}

int XOR(char * reg1, char * reg2, struct vmState *vmState) {
    //FUNCTION: xors the values of two given registers and stores that value in the first register
    int *pReg1 = get_reg_ptr(vmState, reg1);
    int *pReg2 = get_reg_ptr(vmState, reg2);
    int value;
    //the registers that pReg1 and pReg2 are pointing to have their values xored
    value = *pReg1 ^ *pReg2;
    //that vale is stored in the register pReg1 points to
    *pReg1 = value;
    printf("STORING XOR OF %s AND %s INTO %s\n", reg1, reg2, reg1);

    return 0;
}

int TEST(char * reg1, char * reg2, struct vmState *vmState) {
    //FUNCTION: compares the values two registers or of a register with a constant
    //and sets the compare flag to 1 for true or 0 for false if they are equal or not
    int val1, val2;

    int *pReg1 = get_reg_ptr(vmState, reg1);
    int *pReg2 = get_reg_ptr(vmState, reg2);

    // If pReg is not NULL, derefence it, otherwise try string->integer conversion
    val1 = pReg1 ? *pReg1 : atoi(reg1);
    val2 = pReg2 ? *pReg2 : atoi(reg2);

    // Compare val1 and val2
    if (val1 == val2) {
      printf("%s(%d) IS EQUAL TO %s(%d)\n", reg1, val1, reg2, val2);
      vmState->compareFlag = 1;
    }
    else {
      printf("%s(%d) IS NOT EQUAL TO %s(%d)\n", reg1, val1, reg2, val2);
      vmState->compareFlag = 0;
    }

    return 0;
}

//forward declaring fetch_instructions function
int fetch_instructions(struct vmState *vmState, int i);

int JUMP(char * jumpTo, struct vmState *vmState) {
    //FUNCTION: jumps to a specific line in the code memory and runs it
    int jumpToInt = atoi(jumpTo);
    //check the given line in code memory and only run the function if it is NOT null
    if (vmState->codeMemory[jumpToInt] != NULL) {
      printf("JUMPING TO LINE %s\n", jumpTo);
      //run the fetch_instructions function to run the instruction
      fetch_instructions(vmState, jumpToInt);
    }
    else {
      printf("INVALID LINE NUMBER\n");
    }

    return 0;
}

int JUMPEQ(char * jumpTo, struct vmState *vmState) {
    //FUNCTION: same as JUMP, but only runs if the compare flag is true
    enum compareFlagEnum{
      INST_UNDEFINED,
      INST_TRUE,
      INST_FALSE
    };

    int compareFlagTest = INST_UNDEFINED;
    int jumpToInt = atoi(jumpTo);
    //checks if the compare flag is true and runs fetch_instructions if it is. otherwise,
    //the jump is cancelled
    if (vmState->compareFlag == 1) {
      compareFlagTest = INST_TRUE;
    } else if (vmState->compareFlag == 0) {
      compareFlagTest = INST_FALSE;
    }
    switch(compareFlagTest) {
      case INST_TRUE :
        printf("COMPARE FLAG IS TRUE JUMPING TO LINE %s\n", jumpTo);
        fetch_instructions(vmState, jumpToInt);
        vmState->compareFlag = 0;
        printf("JUMP COMPLETED, COMPARE FLAG SET TO FALSE\n");
        break;
      case INST_FALSE :
        printf("COMPARE FLAG IS FALSE, JUMP CANCELLED\n");
        break;
      default :
        puts("INVALID COMPARE FLAG\n");
        break;
    }

    return 0;
}

int JUMPNEQ(char * jumpTo, struct  vmState *vmState) {
    //FUNCTION: same as JUMP, but only runs if the compare flag is false
    enum compareFlagEnum{
      INST_UNDEFINED,
      INST_TRUE,
      INST_FALSE
    };

    int compareFlagTest = INST_UNDEFINED;
    int jumpToInt = atoi(jumpTo);
    //checks if the compare flag is false and runs fetch_instructions if it is. otherwise,
    //the jump is cancelled
    if (vmState->compareFlag == 1) {
      compareFlagTest = INST_TRUE;
    } else if (vmState->compareFlag == 0) {
      compareFlagTest = INST_FALSE;
    }
    switch(compareFlagTest) {
      case INST_FALSE :
        printf("COMPARE FLAG IS FALSE, JUMPING TO LINE %s\n", jumpTo);
        fetch_instructions(vmState, jumpToInt);
        break;
      case INST_TRUE :
        printf("COMPARE FLAG IS TRUE, JUMP CANCELLED\n");
        vmState->compareFlag = 0;
        printf("SETTING COMPARE FLAG TO FALSE\n");
        break;
      default :
        puts("INVALID COMPARE FLAG\n");
        break;
    }

    return 0;
}

int fetch_instructions(struct vmState *vmState, int i) {
  //FUNCTION: runs the instructions on one line from code memory
  enum Instruction {
    INST_UNDEFINED,
    INST_MOVE,
    INST_STORE,
    INST_LOAD,
    INST_INPUT,
    INST_OUTPUT,
    INST_ADD,
    INST_XOR,
    INST_TEST,
    INST_JUMP,
    INST_JUMPEQ,
    INST_JUMPNEQ,
    INST_EXIT
  };

  char *instruction;
  char *param1;
  char *param2;
  int opcode = INST_UNDEFINED;
  //takes the current instruction from the code memory and copies it to currentLine
  snprintf(vmState->currentLine, INSTRUCTION_LENGTH, "%s", (char *)vmState->codeMemory[i]);
  //initialises the token
  char *token = strtok(vmState->currentLine, " ");
  while (token != NULL) {
    //splits the line into an instruction and two parameters, using strtok
    instruction = token;
    param1 = strtok(NULL, ", ");
    param2 = strtok(NULL, ", ");
    token = strtok(NULL, " ");
    printf("FETCHING INSTRUCTIONS: %s %s %s\n", instruction, param1, param2);
    //compares strings to find the correct instruction to run
    if (strcmp(instruction, "MOVE") == 0) {
      opcode = INST_MOVE;
    } else if (strcmp(instruction, "STORE") == 0) {
      opcode = INST_STORE;
    } else if (strcmp(instruction, "LOAD") == 0) {
      opcode = INST_LOAD;
    } else if (strcmp(instruction, "INPUT") == 0) {
      opcode = INST_INPUT;
    } else if (strcmp(instruction, "OUTPUT") == 0) {
      opcode = INST_OUTPUT;
    } else if (strcmp(instruction, "ADD") == 0) {
      opcode = INST_ADD;
    } else if (strcmp(instruction, "XOR") == 0) {
      opcode = INST_XOR;
    } else if (strcmp(instruction, "TEST") == 0){
      opcode = INST_TEST;
    } else if (strcmp(instruction, "JUMP") == 0) {
      opcode = INST_JUMP;
    } else if (strcmp(instruction, "JUMPEQ") == 0) {
      opcode = INST_JUMPEQ;
    } else if (strcmp(instruction, "JUMPNEQ") == 0){
      opcode = INST_JUMPNEQ;
    } else if (strcmp(instruction, "EXIT") == 0) {
      opcode = INST_EXIT;
    }
    //switch statement calls the right function for the instruction. some instructions do not
    //have a second parameter, so that variable is simply ignored
    switch (opcode) {
      case INST_MOVE :
        MOVE(param1, param2, vmState);
        break;
      case INST_STORE :
        STORE(param1, param2, vmState);
        break;
      case INST_LOAD :
        LOAD(param1, param2, vmState);
        break;
      case INST_INPUT :
        INPUT(param1, vmState);
        break;
      case INST_OUTPUT :
        OUTPUT(param1, vmState);
        break;
      case INST_ADD :
        ADD(param1, param2, vmState);
        break;
      case INST_XOR :
        XOR(param1, param2, vmState);
        break;
      case INST_TEST :
        TEST(param1, param2, vmState);
        break;
      case INST_JUMP :
        JUMP(param1, vmState);
        break;
      case INST_JUMPEQ :
        JUMPEQ(param1, vmState);
        break;
      case INST_JUMPNEQ :
        JUMPNEQ(param1, vmState);
        break;
      case INST_EXIT :
        puts("EXITING...");
        exit(0);
        break;
      default:
        puts("UNDEFINED INSTRUCTION");
        break;
    }
  }
  return 0;
}

int main(void){
    //FUNCTION: the main function
    //initialises the vm state
    struct vmState vmState = {0};
    char buffer[1000];
    FILE *ptr_myfile;
    //opens the (hardcoded) file and puts it into a buffer
    ptr_myfile = fopen("comp_prog.bin","rb");
    if (!ptr_myfile){
        printf("unable to open");
    }
    else{
        int count = fread(&buffer, sizeof(char),1000,ptr_myfile);
        fclose(ptr_myfile);
    }

    char *start = buffer;
    char *end = NULL;
    int lineIndex = 0;
    //puts the buffer line by line into code memory
    while ((end = strchr(start, '\n'))) {
        snprintf((char * restrict)vmState.codeMemory[lineIndex], sizeof(vmState.codeMemory[0]), "%.*s", (int)(end - start), start);
        printf("Added line to code memory: %s\n", (char *)vmState.codeMemory[lineIndex]);
        start = end + 1;
        lineIndex++;
    }

    if (*start) {
        printf("And the rest of the string: '%s'\n", start);
    }
    //iterates through each line of the code memory. for each line, it calls
    //the fetch_instructions function to run the instruction
    for(int i = 0;vmState.codeMemory[i] != NULL && i < MEMORY_SIZE; i++) {
      fetch_instructions(&vmState, i);
    }
    return 0;
}
