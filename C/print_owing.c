#include <stdio.h>

void print_banner() {
  printf("-----------\n");
  printf("The Invoice\n");
  printf("-----------\n");
  printf("\n");
}

int calculate_outstanding() { return 42; }

typedef struct {
  const char *customer;
} invoice_t;

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