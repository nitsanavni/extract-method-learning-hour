#ifndef THEATRICALPLAYERS_STATEMENT_H
#define THEATRICALPLAYERS_STATEMENT_H

#define MAX_NAME_LENGTH 120
#define MAX_TYPE_LENGTH 80
#define MAX_PERFORMANCES_PER_YEAR 365

typedef struct Play {
  char playID[MAX_NAME_LENGTH];
  char name[MAX_NAME_LENGTH];
  char type[MAX_TYPE_LENGTH];
} Play;
Play *Play_create(char *playID, char *name, char *type);

typedef struct Performance {
  char playID[MAX_NAME_LENGTH];
  int audience;
} Performance;
Performance *Performance_create(char *playID, int audience);

typedef struct Invoice {
  char customer[MAX_NAME_LENGTH];
  struct Performance *performances[MAX_PERFORMANCES_PER_YEAR];
} Invoice;
Invoice *Invoice_create(char *customer, struct Performance **performances);

void statement(char *result, struct Invoice *invoice, int numberOfPerformances,
               struct Play **plays, int numberOfPlays);

#endif // THEATRICALPLAYERS_STATEMENT_H