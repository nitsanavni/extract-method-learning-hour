#include "./statement.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Extract Method
// 1. create the new function
// 2. copy the extracted code into it
// 3. for each variable used:
//    a. local that's only used in the extracted code - declare inside (slide)
//    b. used elsewhere - pass as parameter
//    c. assigned && passed by value
//       either: change to pass by reference
//       or: return from function (if single)
// 4. return expression result
// 5. compile
// 6. replace original code with a call to the function
//    care for assigned to variables
//    care to return expression result
// 7. test
// 8. replace similar code

// Extract Variable
// 1. expression has no side-effects
// 2. declare an immutable variable, assign it with a copy of the expression
// 3. replace original expresion with new variable
// 4. test

#define the_max(x, y) (((x) >= (y)) ? (x) : (y))

void statement(char *result, const Invoice *invoice, int numberOfPerformances,
               const Play **plays, int numberOfPlays) {
  float total_amount = 0;
  int volume_credits = 0;
  const Play *play;

  sprintf(result, "Statement for %s\n", invoice->customer);

  for (int i = 0; i < numberOfPerformances; i++) {
    float this_amount = 0;

    for (int j = 0; j < numberOfPlays; j++) {
      if (strcmp(plays[j]->playID, invoice->performances[i]->playID) == 0) {
        play = plays[j];
      }
    }

    if (strcmp(play->type, "tragedy") == 0) {
      this_amount = 40000;

      if (invoice->performances[i]->audience > 30) {
        this_amount += 1000 * (invoice->performances[i]->audience - 30);
      }
    } else if (strcmp(play->type, "comedy") == 0) {
      this_amount = 30000;

      if (invoice->performances[i]->audience > 20) {
        this_amount += 10000 + 500 * (invoice->performances[i]->audience - 20);
      }

      this_amount += 300 * invoice->performances[i]->audience;
    } else {
      sprintf(result, "ERROR: unknown play type %s", play->type);

      return;
    }

    // add volume credits
    volume_credits += the_max(invoice->performances[i]->audience - 30, 0);

    // add extra credit for every ten comedy attendees
    if (strcmp(play->type, "comedy") == 0) {
      volume_credits += invoice->performances[i]->audience / 5;
    }

    // print line for this order
    sprintf(result, "%s %s: $%.2f (%d seats)\n", result, play->name,
            (this_amount / 100), invoice->performances[i]->audience);

    total_amount += this_amount;
  }

  sprintf(result, "%sAmount owed is $%.2f\n", result, (total_amount / 100));
  sprintf(result, "%sYou earned %d credits", result, volume_credits);
}

Invoice *Invoice_create(char *customer, Performance **performances) {
  Invoice *invoice = malloc(sizeof(Invoice));
  strncpy(invoice->customer, customer, sizeof(invoice->customer) - 1);
  memcpy(invoice->performances, performances, sizeof(invoice->performances));

  return invoice;
}

Play *Play_create(char *playID, char *name, char *type) {
  Play *play = malloc(sizeof(Play));
  strncpy(play->playID, playID, sizeof(play->playID) - 1);
  strncpy(play->name, name, sizeof(play->name) - 1);
  strncpy(play->type, type, sizeof(play->type) - 1);

  return play;
}

Performance *Performance_create(char *playID, int audience) {
  Performance *performance = malloc(sizeof(Performance));
  strncpy(performance->playID, playID, sizeof(performance->playID) - 1);
  performance->audience = audience;

  return performance;
}

int main() {
  Play *hamlet = Play_create("hamlet", "Hamlet", "tragedy");
  Play *aslike = Play_create("as-like", "As You Like It", "comedy");
  Play *othello = Play_create("othello", "Othello", "tragedy");
  const Play *plays[] = {hamlet, aslike, othello};

  Performance *bigCoHamlet = Performance_create("hamlet", 55);
  Performance *bigCoAsLike = Performance_create("as-like", 35);
  Performance *bigCoOthello = Performance_create("othello", 40);
  Performance *performances[] = {bigCoHamlet, bigCoAsLike, bigCoOthello};
  Invoice *invoice = Invoice_create("BigCo", performances);

  char result[2000];
  statement(result, invoice, 3, plays, 3);

  printf("statement:\n%s", result);
}
