#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_LENGTH 100

char *FILENAME = "contact_book_data.csv";

typedef struct Contact {
  char name[INPUT_LENGTH];
  char address[INPUT_LENGTH];
  char email[INPUT_LENGTH];
  char number[INPUT_LENGTH];
} Contact;

Contact contact_array[100];

int add_new_entry() {
  printf("When entering details, please do not include any spaces.\n");
  FILE *fptr;

  fptr = fopen(FILENAME, "a");

  char name[INPUT_LENGTH];
  char address[INPUT_LENGTH];
  char email[INPUT_LENGTH];
  char number[INPUT_LENGTH];

  printf("Please enter a name: ");
  scanf("%s", name);
  printf("\nPlease enter an address: ");
  scanf("%s", address);
  printf("\nPlease enter an email: ");
  scanf("%s", email);
  printf("\nPlease enter a phone number: ");
  scanf("%s", number);
  printf("\n");

  fprintf(fptr, "'%s','%s','%s','%s'\n", name, address, email, number);
  fclose(fptr);

  printf("\nSaved contact!\n\n");

  return 0;
}

void print_contact(const Contact *contact) {
  printf("Name:    %s\n", contact->name);
  printf("Address: %s\n", contact->address);
  printf("Email:   %s\n", contact->email);
  printf("Number:  %s\n", contact->number);
  printf("\n");
}

int read_from_csv(Contact contact_array[]) {
  FILE *fptr;
  char buffer[INPUT_LENGTH * 4 + 5];

  int i = 0;

  fptr = fopen(FILENAME, "r");
  if (fptr == NULL) {
    printf("Could not open %s\n", FILENAME);
    return 0;
  }

  while (fgets(buffer, sizeof(buffer), fptr)) {
    char *p = buffer;
    while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') 
      p++;
    if (*p == '\0')
      continue;

    char *new_line_pointer = strchr(buffer, '\n');
    if (new_line_pointer)
      *new_line_pointer = '\0';

    char *field = strtok(buffer, ",");
    int x = 0;

    while (field != NULL) {
      if (x == 0) {
        strncpy(contact_array[i].name, field, INPUT_LENGTH - 1);
        contact_array[i].name[INPUT_LENGTH - 1] = '\0';
      } else if (x == 1) {
        strncpy(contact_array[i].address, field, INPUT_LENGTH - 1);
        contact_array[i].address[INPUT_LENGTH - 1] = '\0';
      } else if (x == 2) {
        strncpy(contact_array[i].email, field, INPUT_LENGTH - 1);
        contact_array[i].email[INPUT_LENGTH - 1] = '\0';
      } else if (x == 3) {
        strncpy(contact_array[i].number, field, INPUT_LENGTH - 1);
        contact_array[i].number[INPUT_LENGTH - 1] = '\0';
      }
      x++;
      field = strtok(
          NULL,
          ",");
    }

    i++;
    if (i >= 100)
      break;
  }

  fclose(fptr);
  return i;
}

int list_contacts() {
  int contact_count = read_from_csv(contact_array);
  for (int i = 0; i < contact_count; i++) {
    print_contact(&contact_array[i]);
  }

  return 0;
}

int main(int argc, char *argv[]) {
  printf("=======================================\n");
  printf("      Welcome to the contact book      \n");
  printf("=======================================\n");

  if (argc > 1) {
    FILENAME = argv[1];
  }

  while (1) {
    int selection;
    printf("\nPlease select an operation:\n");
    printf("  1. Add a contact\n");
    printf("  2. List contacts\n");
    printf("  3. Get some help\n");
    printf("  4. Quit (exit)\n");

    scanf("%d", &selection);
    system("cls");
    system("clear");

    switch (selection) {
    case 1:
      add_new_entry();
      break;
    case 2:
      list_contacts();
      break;
    case 3:
      printf("| USAGE\n");
      printf("|  ./contacts.out [ARGS]\n");
      printf("| ACCEPTED ARGS\n");
      printf("|  1 (OPT) - Path to .csv contacts file\n");
      break;
    case 4:
      printf("Goodbye!\n");
      return 0;
    default:
      printf("That's not a valid operation! Let's try again...\n");
    }
  }
  return 0;
}

