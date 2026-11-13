#include <stdio.h>
#include <string.h>

#define MAX_HISTORY 10

typedef struct
{
  char  type[12];      /* "Deposit" or "Withdraw" */
  float amount;
  float balanceAfter;
} Transaction;

void  Menu();
void  CheckBalance(float balance);
float deposit(float *balance);
float withdraw(float *balance);
int   changepin(int pin);
void  addTransaction(Transaction history[], int *count,
                     const char *type, float amount, float balanceAfter);
void  showHistory(Transaction history[], int count);

/* Clears bad input so scanf doesn't loop forever */
void clearInput()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
  int pin = 1234;
  int enteredpin;
  int choice;
  int attempts = 0;
  int loggedIn = 0;
  float balance = 1000000;
  float amount;

  Transaction history[MAX_HISTORY];
  int historyCount = 0;

  printf("===== ATM Machine =====\n");

  while (attempts < 3)
  {
    printf("Enter your PIN: ");
    if (scanf("%d", &enteredpin) != 1)
    {
      clearInput();
      enteredpin = -1;
    }

    if (enteredpin == pin)
    {
      printf("Login Successful\n");
      loggedIn = 1;
      break;
    }

    attempts++;
    printf("Incorrect PIN\n");
    printf("Attempts remaining: %d\n", 3 - attempts);

    if (attempts == 3)
    {
      printf("Too many incorrect attempts.\n");
      printf("Account temporarily blocked.\n");
    }
  }

  if (!loggedIn)
  {
    return 0;
  }

  do
  {
    Menu();
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1)
    {
      clearInput();
      choice = 0;
    }

    switch (choice)
    {
      case 1:
        CheckBalance(balance);
        break;

      case 2:
        amount = deposit(&balance);
        if (amount > 0)
          addTransaction(history, &historyCount, "Deposit", amount, balance);
        break;

      case 3:
        amount = withdraw(&balance);
        if (amount > 0)
          addTransaction(history, &historyCount, "Withdraw", amount, balance);
        break;

      case 4:
        pin = changepin(pin);
        break;

      case 5:
        showHistory(history, historyCount);
        break;

      case 6:
        printf("Thank you for using the ATM.\n");
        printf("Have a nice day!\n");
        break;

      default:
        printf("Invalid choice! Please try again.\n");
        break;
    }
  } while (choice != 6);

  return 0;
}

void Menu()
{
  printf("Welcome again Lavish");
  printf("\n-----Menu-----\n");
  printf("1. Check Balance\n");
  printf("2. Deposit Money\n");
  printf("3. Withdraw Money\n");
  printf("4. Change PIN\n");
  printf("5. Transaction History\n");
  printf("6. Exit\n");
}

void CheckBalance(float balance)
{
  printf("Current Balance: %.2f\n", balance);
}

/* Returns the amount deposited, or 0 if nothing was deposited */
float deposit(float *balance)
{
  float amount;

  printf("Enter amount to deposit: ");
  if (scanf("%f", &amount) != 1)
  {
    clearInput();
    printf("Invalid input\n");
    return 0;
  }

  if (amount <= 0)
  {
    printf("Invalid amount\n");
    return 0;
  }

  *balance += amount;
  printf("%.2f deposited successfully.\n", amount);
  printf("New Balance: %.2f\n", *balance);
  return amount;
}

/* Returns the amount withdrawn, or 0 if nothing was withdrawn */
float withdraw(float *balance)
{
  float amount;

  printf("Enter amount to withdraw: ");
  if (scanf("%f", &amount) != 1)
  {
    clearInput();
    printf("Invalid input\n");
    return 0;
  }

  if (amount <= 0)
  {
    printf("Invalid amount\n");
    return 0;
  }
  if (amount > *balance)
  {
    printf("Insufficient balance\n");
    return 0;
  }

  *balance -= amount;
  printf("Please collect your cash.\n");
  printf("%.2f withdrawn successfully\n", amount);
  printf("Remaining Balance: %.2f\n", *balance);
  return amount;
}

int changepin(int pin)
{
  int currentpin;
  int newpin;

  printf("Enter your current PIN: ");
  if (scanf("%d", &currentpin) != 1)
  {
    clearInput();
    printf("Invalid input\n");
    return pin;
  }

  if (currentpin != pin)
  {
    printf("Incorrect PIN\n");
    return pin;
  }

  printf("Enter your new 4-digit PIN: ");
  if (scanf("%d", &newpin) != 1)
  {
    clearInput();
    printf("Invalid input\n");
    return pin;
  }

  if (newpin >= 1000 && newpin <= 9999)
  {
    printf("PIN changed successfully\n");
    return newpin;
  }

  printf("PIN must contain exactly 4 digits\n");
  return pin;
}

/* Saves a transaction; if full, drops the oldest one */
void addTransaction(Transaction history[], int *count,
                    const char *type, float amount, float balanceAfter)
{
  int i;

  if (*count == MAX_HISTORY)
  {
    for (i = 1; i < MAX_HISTORY; i++)
      history[i - 1] = history[i];
    (*count)--;
  }

  strncpy(history[*count].type, type, sizeof(history[*count].type) - 1);
  history[*count].type[sizeof(history[*count].type) - 1] = '\0';
  history[*count].amount = amount;
  history[*count].balanceAfter = balanceAfter;
  (*count)++;
}

void showHistory(Transaction history[], int count)
{
  int i;

  if (count == 0)
  {
    printf("No transactions yet.\n");
    return;
  }

  printf("\n--- Transaction History (last %d) ---\n", MAX_HISTORY);
  printf("%-4s %-10s %-14s %s\n", "No.", "Type", "Amount", "Balance After");
  for (i = 0; i < count; i++)
  {
    printf("%-4d %-10s %-14.2f %.2f\n",
           i + 1, history[i].type, history[i].amount, history[i].balanceAfter);
  }
}
