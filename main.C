#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <limits.h>

int Create_New_Bank_Account(void) {

    // Enter Name, ID, Account Type, PIN
    printf("Enter name: ");
    char name[100];
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;  

    printf("Enter Identification Number (ID): ");
    char id[20];
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;  

    printf("Type of Account (Savings or Current) : ");
    char account_type[20];
    fgets(account_type, sizeof(account_type), stdin);
    account_type[strcspn(account_type, "\n")] = 0;  

    printf("Create 4-digit PIN: ");
    char pin[5];
    fgets(pin, sizeof(pin), stdin);
    pin[strcspn(pin, "\n")] = 0; 

    // Generate Random Bank Account Number
    int bank_account_number = rand() % (999999999 - 1000000 + 1) + 1000000; // Random 7 to 9 digit number
    printf("Your Bank Account Number is: %d\n", bank_account_number);

    // Initial Deposit
    double initial_deposit = 0.00;

    // Save account details to a file named with the bank account number
    char filename[50];
    sprintf(filename, "%d.txt", bank_account_number);
    FILE *fptr;
    fptr = fopen(filename, "w");

    // Check if file opened successfully
    if (fptr == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return -1; // Indicate failure
    }

    // Write account details to the file
    fprintf(fptr, "Name: %s\n", name);
    fprintf(fptr, "ID: %s\n", id);
    fprintf(fptr, "Account Type: %s\n", account_type);
    fprintf(fptr, "PIN: %s\n", pin);
    fprintf(fptr, "Account Number: %d\n", bank_account_number);
    fprintf(fptr, "Initial Deposit: %.2f\n", initial_deposit);
    fclose(fptr);

    printf("Created your new bank account...\n");
    return 0; // Success
}

int Delete_Bank_Account(void) {
    // Placeholder implementation
    printf("Deleting a bank account...\n");
    return 0; // Success
}

int Deposit_Money(void) {
    // Placeholder implementation
    printf("Depositing money into the account...\n");
    return 0; // Success
}

int Withdraw_Money(void) {
    // Placeholder implementation
    printf("Withdrawing money from the account...\n");
    return 0; // Success
}

int Remittance(void) {
    // Placeholder implementation
    printf("Transferring money to another account...\n");
    return 0; // Success
}

int main(void) {
    // Seed the random number generator
    srand(time(NULL));
    
    int choice;
    while (1) {
        printf("\nBank Account Management System\n");
        printf("--------------------------------\n");
        /* Show session info: current date/time and count of loaded accounts (from accounts.txt) */
        {
            time_t now = time(NULL);
            char timebuf[64] = "Unknown time";
            struct tm *tm_info = localtime(&now);
            if (tm_info) {
                strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_info);
            }

            int loaded_accounts = 0;
            FILE *fa = fopen("accounts.txt", "r");
            if (fa) {
                char line[512];
                while (fgets(line, sizeof(line), fa)) {
                    char *p = line;
                    while (*p && isspace((unsigned char)*p)) p++;
                    if (*p != '\0' && *p != '\n') loaded_accounts++;
                }
                fclose(fa);
            }

            printf("Session started: %s\n", timebuf);
            printf("Loaded accounts: %d\n\n", loaded_accounts);
        }
        printf("Select :\n");
        printf("1. Create New Bank Account\n");
        printf("2. Delete Bank Account\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Remittance\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear invalid input
            continue;
        }
        while (getchar() != '\n'); 

        switch (choice) {
            case 1:
                Create_New_Bank_Account();
                break;
            case 2:
                Delete_Bank_Account();
                break;
            case 3:
                Deposit_Money();
                break;
            case 4:
                Withdraw_Money();
                break;
            case 5:
                Remittance();
                break;
            case 6:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}