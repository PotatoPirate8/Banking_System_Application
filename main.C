#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <limits.h>

// Platform-specific includes for directory creation
#ifdef _WIN32
    #include <direct.h>  // For _mkdir on Windows   
    #define mkdir(dir) _mkdir(dir)
#else
    #include <sys/stat.h>
    #include <sys/types.h>
#endif

// ==================== VALIDATION HELPER FUNCTIONS ====================

// Helper function to validate name (only letters and spaces)
int validate_name(const char *name) {
    if (strlen(name) == 0) {
        return 0; // Empty name
    }
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha((unsigned char)name[i]) && name[i] != ' ') {
            return 0; // Invalid character
        }
    }
    return 1; // Valid
}

// Helper function to validate ID (only digits)
int validate_id(const char *id) {
    if (strlen(id) == 0) {
        return 0; // Empty ID
    }
    for (int i = 0; id[i] != '\0'; i++) {
        if (!isdigit((unsigned char)id[i])) {
            return 0; // Invalid character
        }
    }
    return 1; // Valid
}

// Helper function to validate account type
int validate_account_type(const char *type) {
    // Case-insensitive comparison
    if (strcasecmp(type, "Savings") == 0 || strcasecmp(type, "Current") == 0) {
        return 1; // Valid
    }
    return 0; // Invalid
}

// Helper function to validate PIN (exactly 4 digits)
int validate_pin(const char *pin) {
    if (strlen(pin) != 4) {
        return 0; // Not exactly 4 characters
    }
    for (int i = 0; i < 4; i++) {
        if (!isdigit((unsigned char)pin[i])) {
            return 0; // Contains non-digit
        }
    }
    return 1; // Valid
}

// ==================== INPUT HELPER FUNCTIONS ====================

// Get and validate name input
void get_name_input(char *name, size_t size) {
    while (1) {
        printf("Enter name (letters and spaces only): ");
        fgets(name, size, stdin);
        name[strcspn(name, "\n")] = 0;
        
        if (validate_name(name)) {
            break;
        }
        printf("Invalid name! Please use only letters and spaces.\n");
    }
}

// Get and validate ID input
void get_id_input(char *id, size_t size) {
    while (1) {
        printf("Enter Identification Number (digits only): ");
        fgets(id, size, stdin);
        id[strcspn(id, "\n")] = 0;
        
        if (validate_id(id)) {
            break;
        }
        printf("Invalid ID! Please enter digits only.\n");
    }
}

// Get and validate account type input
void get_account_type_input(char *account_type, size_t size) {
    while (1) {
        printf("Type of Account (Savings or Current): ");
        fgets(account_type, size, stdin);
        account_type[strcspn(account_type, "\n")] = 0;
        
        if (validate_account_type(account_type)) {
            // Normalize the input to proper case
            if (strcasecmp(account_type, "savings") == 0) {
                strcpy(account_type, "Savings");
            } else {
                strcpy(account_type, "Current");
            }
            break;
        }
        printf("Invalid account type! Please enter 'Savings' or 'Current'.\n");
    }
}

// Get and validate PIN input
void get_pin_input(char *pin, size_t size) {
    while (1) {
        printf("Create 4-digit PIN: ");
        fgets(pin, size, stdin);
        pin[strcspn(pin, "\n")] = 0;
        
        if (validate_pin(pin)) {
            break;
        }
        printf("Invalid PIN! Please enter exactly 4 digits.\n");
    }
}

// ==================== BANK ACCOUNT FUNCTIONS ====================

int Create_New_Bank_Account(void) {

    // Get user inputs with validation
    char name[100];
    char id[20];
    char account_type[20];
    char pin[100];
    char confirm[10];
    int choice;

    // Initial input collection
    get_name_input(name, sizeof(name));
    get_id_input(id, sizeof(id));
    get_account_type_input(account_type, sizeof(account_type));
    get_pin_input(pin, sizeof(pin));

    // Loop until user confirms all information is correct
    while (1) {
        // Display summary for confirmation
        printf("\n===========================================\n");
        printf("         Account Information Review        \n");
        printf("===========================================\n");
        printf("Name:          %s\n", name);
        printf("ID:            %s\n", id);
        printf("Account Type:  %s\n", account_type);
        printf("PIN:           %s\n", pin);
        printf("===========================================\n");
        
        // Ask for confirmation
        while (1) {
            printf("\nIs all information correct? (yes/no): ");
            fgets(confirm, sizeof(confirm), stdin);
            confirm[strcspn(confirm, "\n")] = 0;
            
            if (strcasecmp(confirm, "yes") == 0 || strcasecmp(confirm, "y") == 0) {
                goto create_account;  // Proceed to account creation
            } else if (strcasecmp(confirm, "no") == 0 || strcasecmp(confirm, "n") == 0) {
                // Ask what to edit
                printf("\nWhat would you like to edit?\n");
                printf("1. Name\n");
                printf("2. ID\n");
                printf("3. Account Type\n");
                printf("4. PIN\n");
                printf("5. Re-enter all information\n");
                printf("6. Cancel account creation\n");
                printf("Enter your choice: ");
                
                if (scanf("%d", &choice) != 1) {
                    while (getchar() != '\n'); // Clear input
                    printf("Invalid choice. Please try again.\n");
                    continue;
                }
                while (getchar() != '\n'); // Clear newline
                
                switch (choice) {
                    case 1:
                        get_name_input(name, sizeof(name));
                        break;
                    case 2:
                        get_id_input(id, sizeof(id));
                        break;
                    case 3:
                        get_account_type_input(account_type, sizeof(account_type));
                        break;
                    case 4:
                        get_pin_input(pin, sizeof(pin));
                        break;
                    case 5:
                        // Re-enter all information
                        get_name_input(name, sizeof(name));
                        get_id_input(id, sizeof(id));
                        get_account_type_input(account_type, sizeof(account_type));
                        get_pin_input(pin, sizeof(pin));
                        break;
                    case 6:
                        printf("Account creation cancelled.\n");
                        return 0;
                    default:
                        printf("Invalid choice.\n");
                }
                break; // Break inner loop to show summary again
            } else {
                printf("Invalid input. Please enter 'yes' or 'no'.\n");
            }
        }
    }

create_account:
    // Create database directory if it doesn't exist (ignore error if already exists)
    mkdir("database");

    // Generate unique Bank Account Number
    int bank_account_number;
    char filename[100];
    FILE *check_file;
    int attempts = 0;
    
    // Edge case: Ensure unique account number
    do {
        bank_account_number = rand() % (999999999 - 1000000 + 1) + 1000000; // 7 to 9 digits
        sprintf(filename, "database/%d.txt", bank_account_number);
        check_file = fopen(filename, "r");
        
        if (check_file != NULL) {
            fclose(check_file);
            attempts++;
            if (attempts > 100) {
                fprintf(stderr, "Error: Unable to generate unique account number after 100 attempts.\n");
                return -1;
            }
        }
    } while (check_file != NULL);
    
    printf("Your Bank Account Number is: %d\n", bank_account_number);

    // Initial Deposit
    double initial_deposit = 0.00;

    // Save account details to a file in the database folder
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

    printf("Created your new bank account successfully!\n");
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