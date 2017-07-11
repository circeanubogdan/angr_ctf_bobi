#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#define USERDEF0 "AaBbLcDz"

char msg[] =
 "This level takes the command line argument, applies a simple function\n"
 "to it, and then compares that to another string. If they are the same,\n"
 "the program outputs \"Success\", otherwise, \"Try again\" While you\n"
 "could analyze the binary by hand to determine the function that\n"
 "transforms the command line argument, it would be much easier to use\n"
 "angr. With angr, use a symbolic variable as the command line argument\n"
 "to find the correct input.\n";

int main(int argc, char* argv[]) {
  char user_input[8];
  char* key = USERDEF0;
  unsigned int equal;

  printf("%sEnter password: ", msg);
  scanf("%8s", user_input);
  
  equal = 1;
  for (int i=0; i<8; ++i) {
    char user_byte = (*((unsigned long long*) user_input) & (((unsigned long long) 0xFF) << (8 * i))) >> (8 * i);
    char key_byte = (*((unsigned long long*) key) & (((unsigned long long) 0xFF) << (8 * i))) >> (8 * i);
    if (user_byte != ((key_byte - 33 + 17*i) % 94) + 33) {
      equal = 0;
      break;
    }
  }

  if (equal) {
    printf("Success.\n");
  } else {
    printf("Try again.\n");
  }

  return 0;
}

void detectTrace(void) __attribute__((constructor));
void detectTrace(void) {
    if (ptrace(PTRACE_TRACEME, 0, 1, 0) < 0) {
        exit(1);
    };
};