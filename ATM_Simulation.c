#include <stdio.h>
void Menu();
void CheckBalance(float balance);
float deposit(float balance);
float withdraw(float balance);
int changepin(int pin);
int main()
{
  int pin = 1234;
  int enteredpin;
  int newpin;
  int choice;
  int attempts= 0;
  float balance= 1000000;
  float amount;

  printf("===== ATM Machines =====\n");

  while(attempts<3)
    {
      printf("Enter your pin");
      scanf("%d", &enteredpin);

      if(enteredpin==pin)
      {
        printf("Login Succesfully\n");
        break;
      }
      attempts++;
      
      printf("Incorect PIN \n");
      printf("Attempts remaining:%d \n",3-attempts);

      if(attempts == 3)
      {
        printf("Too many incorrect attempts. \n");
        printf("Account temporarily blocked. \n");
      }
    }

    do{
      Menu();
      printf("enter your Choice:");
      scanf("%d", &choice);

      switch(choice)
        {
          case 1:
            CheckBalance(balance);
          break;

          case 2:
            deposit(balance);
          break;

          case 3:
            withdraw(balance);
          break;
          
          case 4:
            changedpin(pin);
            if("newpin != pin")
            {
              pin = newpin;
            }
          break;

          case 5:
             printf("Thank You for using the ATM. \n");
             printf("Have a nice day \n" );
          break;

          default:
            printf("Invalid choice! Please try again");
          break;
                            
        }
    }while( choice !=5);

  return 0;
} 
void Menu()
{
  printf("-----Menu-----\n");
  printf("1.Check Balance \n");
  printf("2.Deposit Money \n");
  printf("3.Withdraw Money \n");
  printf("4.Change PIN \n");
  printf("5.Exit \n");
}
void CheckBalance(float balance)
{
  printf("Current Balance:%.2f \n", balance);
}
float deposit(float balance)
{
  float amount;

  printf("Enter amount to deposit:");
  scanf("%f", &amount);

  if(amount <= 0)
    {
    printf("Invalid amount \n");
    }
 else{
   balance += amount;

   printf("%.2f deposited sucessessfully. \n", amount);
   printf("New Balance: %2f \n", balance);
 }
return balance;
}

float withdraw(float balance)
{
  float amount;

  printf("Enter amount to withdraw:");
  scanf("%f", &amount);

  if(amount <=0)
  {
    printf("Invalid amount \n");
  }
  else if(amount > balance)
  {
    printf("Insufficient balance \n");
  }
  else{
    balance -= amount ;

    printf("please collect your cash. \n");
    printf("%.2f withdraw successfully \n");
    printf("Remaining Balance:%.2f \n",balance);      
  }
  return balance;
}
int  changedpin()
{
  int currentpin;
  int newpin;
  int pin;

  printf("enter you current PIN:");
  scanf("%d", &currentpin);

  if(currentpin != pin)
  {
    printf("Incorrect PIN \n");

    return pin;
  }
  else{
  printf("enter your new 4-digit PIN: ");
  scanf("%d", &newpin);
  }
  
  if(newpin>= 1000 && newpin<=9999)
  {
    printf("PIN changed successfully \n");

    return newpin;
  }
  else{
    printf("PIN must contian exaclty 4 digit");

    return pin;
  }
}
