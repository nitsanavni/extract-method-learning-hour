#include <stdio.h>

// 1. create the new function
// 2. copy the extracted code into it
// 3. for each variable used:
//    a. local that's only used in the extracted code - declare inside (slide)
//    b. used elsewhere - pass as parameter
//    c. assigned && passed by value
// 4. compile
// 5. replace original code with a call to the function
// 6. test
// 7. replace similar code

void print_banner() {
  printf("-----------\n");
  printf("The Invoice\n");
  printf("-----------\n");
  printf("\n");
}

int calculate_outstanding() { return 42 * 1000000; }

typedef struct invoice_t {
  const char *customer;
} invoice_t;

// example taken from https://refactoring.com/catalog/extractFunction.html
void print_owing(const invoice_t *invoice) {
  print_banner();
  const int outstanding = calculate_outstanding();

  // print details
  printf("name : %s\n", invoice->customer);
  printf("amount : %d\n", outstanding);
}

int main() {
  const invoice_t zorg_invoice = {"Zorg Industries"};
  print_owing(&zorg_invoice);
}
