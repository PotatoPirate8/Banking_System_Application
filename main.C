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

// Helper function to validate monetary amount (max 2 decimal places)
int validate_money_format(const char *amount_str) {
    if (strlen(amount_str) == 0) {
        return 0; // Empty string
    }

    int decimal_count = 0;
    int digits_after_decimal = 0;
    int has_digit = 0;

    for (int i = 0; amount_str[i] != '\0'; i++) {
        if (isdigit((unsigned char)amount_str[i])) {
            has_digit = 1;
            if (decimal_count > 0) {
                digits_after_decimal++;
                if (digits_after_decimal > 2) {
                    return 0; // More than 2 decimal places
                }
            }
        } else if (amount_str[i] == '.') {
            decimal_count++;
            if (decimal_count > 1) {
                return 0; // Multiple decimal points
            }
        } else {
            return 0; // Invalid character
        }
    }

    return has_digit; // Valid if at least one digit present
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

    // Add entry to index file
    FILE *index_file = fopen("database/index.txt", "a");
    if (index_file != NULL) {
        fprintf(index_file, "%d|%s|%s|%s\n", bank_account_number, name, id, account_type);
        fclose(index_file);
    } else {
        fprintf(stderr, "Warning: Could not update index file\n");
    }

    printf("Created your new bank account successfully!\n");
    return 0; // Success
}

int Delete_Bank_Account(void) {
    FILE *index_file = fopen("database/index.txt", "r");
    if (index_file == NULL) {
        printf("No accounts found in the database.\n");
        return -1;
    }

    // Read all accounts from index file
    int account_numbers[1000];
    char names[1000][100];
    char ids[1000][20];
    char account_types[1000][20];
    int count = 0;

    char line[512];
    while (fgets(line, sizeof(line), index_file) && count < 1000) {
        // Parse: AccountNumber|Name|ID|AccountType
        if (sscanf(line, "%d|%99[^|]|%19[^|]|%19[^\n]", 
                   &account_numbers[count], names[count], ids[count], account_types[count]) == 4) {
            count++;
        }
    }
    fclose(index_file);

    if (count == 0) {
        printf("No accounts found in the database.\n");
        return -1;
    }

    // Display all accounts
    printf("\n========================================\n");
    printf("       Existing Bank Accounts\n");
    printf("========================================\n");
    for (int i = 0; i < count; i++) {
        printf("%d. Account Number: %d\n", i + 1, account_numbers[i]);
        printf("   Name: %s\n", names[i]);
        printf("   Account Type: %s\n", account_types[i]);
        printf("----------------------------------------\n");
    }

    // Ask user to select account
    int choice;
    printf("\nEnter the number of the account to delete (1-%d), or 0 to cancel: ", count);
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return -1;
    }
    while (getchar() != '\n'); // Clear newline

    if (choice == 0) {
        printf("Account deletion cancelled.\n");
        return 0;
    }

    if (choice < 1 || choice > count) {
        printf("Invalid choice.\n");
        return -1;
    }

    int selected_index = choice - 1;
    int account_to_delete = account_numbers[selected_index];

    printf("\nYou selected:\n");
    printf("Account Number: %d\n", account_to_delete);
    printf("Name: %s\n", names[selected_index]);
    printf("Account Type: %s\n", account_types[selected_index]);

    // Verify with last 4 digits of ID and PIN
    char id_last4[100];  // Larger buffer to catch excess input
    char pin_input[100];

    printf("\nFor security, please verify:\n");
    
    // Validate last 4 digits of ID
    while (1) {
        printf("Enter the last 4 digits of your ID: ");
        fgets(id_last4, sizeof(id_last4), stdin);
        id_last4[strcspn(id_last4, "\n")] = 0;

        // Validate that input is exactly 4 digits
        if (strlen(id_last4) != 4) {
            printf("Error: Please enter exactly 4 digits.\n");
            continue;
        }

        // Check if all characters are digits
        int valid = 1;
        for (int i = 0; i < 4; i++) {
            if (!isdigit((unsigned char)id_last4[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("Error: ID must contain only digits.\n");
            continue;
        }

        break; // Valid input
    }

    // Get last 4 characters of stored ID
    char *stored_id = ids[selected_index];
    int id_len = strlen(stored_id);
    char *actual_last4 = (id_len >= 4) ? &stored_id[id_len - 4] : stored_id;

    if (strcmp(id_last4, actual_last4) != 0) {
        printf("ID verification failed. Account deletion cancelled.\n");
        return -1;
    }

    // Read PIN from account file
    char filename[100];
    sprintf(filename, "database/%d.txt", account_to_delete);
    FILE *account_file = fopen(filename, "r");
    if (account_file == NULL) {
        printf("Error: Account file not found.\n");
        return -1;
    }

    char stored_pin[100] = "";
    while (fgets(line, sizeof(line), account_file)) {
        if (strncmp(line, "PIN: ", 5) == 0) {
            sscanf(line, "PIN: %s", stored_pin);
            break;
        }
    }
    fclose(account_file);

    // Validate PIN input
    while (1) {
        printf("Enter your 4-digit PIN: ");
        fgets(pin_input, sizeof(pin_input), stdin);
        pin_input[strcspn(pin_input, "\n")] = 0;

        // Validate PIN format
        if (!validate_pin(pin_input)) {
            printf("Error: PIN must be exactly 4 digits.\n");
            continue;
        }

        break; // Valid format
    }

    if (strcmp(pin_input, stored_pin) != 0) {
        printf("PIN verification failed. Account deletion cancelled.\n");
        return -1;
    }

    // Final confirmation
    char confirm[10];
    printf("\nAre you sure you want to permanently delete this account? (yes/no): ");
    fgets(confirm, sizeof(confirm), stdin);
    confirm[strcspn(confirm, "\n")] = 0;

    if (strcasecmp(confirm, "yes") != 0 && strcasecmp(confirm, "y") != 0) {
        printf("Account deletion cancelled.\n");
        return 0;
    }

    // Delete the account file
    if (remove(filename) != 0) {
        printf("Error: Could not delete account file.\n");
        return -1;
    }

    // Update index file - remove the deleted account
    FILE *temp_index = fopen("database/index_temp.txt", "w");
    if (temp_index == NULL) {
        printf("Error: Could not update index file.\n");
        return -1;
    }

    for (int i = 0; i < count; i++) {
        if (i != selected_index) {
            fprintf(temp_index, "%d|%s|%s|%s\n", 
                    account_numbers[i], names[i], ids[i], account_types[i]);
        }
    }
    fclose(temp_index);

    // Replace old index with new one
    remove("database/index.txt");
    rename("database/index_temp.txt", "database/index.txt");

    printf("\nAccount %d has been successfully deleted.\n", account_to_delete);
    printf("All associated data has been removed from the system.\n");

    return 0; // Success
}

int Deposit_Money(void) {
    // Get and validate account number
    int account_number;
    char account_input[100];
    
    printf("\n========================================\n");
    printf("          Deposit Money\n");
    printf("========================================\n");
    
    while (1) {
        printf("Enter your account number: ");
        fgets(account_input, sizeof(account_input), stdin);
        account_input[strcspn(account_input, "\n")] = 0;

        // Validate numeric input
        char *endptr;
        long temp = strtol(account_input, &endptr, 10);
        
        if (*endptr != '\0' || account_input[0] == '\0') {
            printf("Error: Account number must contain only digits.\n");
            continue;
        }

        if (temp < 1000000 || temp > 999999999) {
            printf("Error: Invalid account number format.\n");
            continue;
        }

        account_number = (int)temp;
        break; // Valid account number
    }

    // Check if account exists
    char filename[100];
    sprintf(filename, "database/%d.txt", account_number);
    FILE *account_file = fopen(filename, "r");
    if (account_file == NULL) {
        printf("Error: Account not found.\n");
        return -1;
    }

    // Read account details
    char line[512];
    char stored_pin[100] = "";
    char name[100] = "";
    char account_type[20] = "";
    double current_balance = 0.00;

    while (fgets(line, sizeof(line), account_file)) {
        if (strncmp(line, "PIN: ", 5) == 0) {
            sscanf(line, "PIN: %s", stored_pin);
        } else if (strncmp(line, "Name: ", 6) == 0) {
            sscanf(line, "Name: %99[^\n]", name);
        } else if (strncmp(line, "Account Type: ", 14) == 0) {
            sscanf(line, "Account Type: %s", account_type);
        } else if (strncmp(line, "Initial Deposit: ", 17) == 0) {
            sscanf(line, "Initial Deposit: %lf", &current_balance);
        } else if (strncmp(line, "Current Balance: ", 17) == 0) {
            sscanf(line, "Current Balance: %lf", &current_balance);
        }
    }
    fclose(account_file);

    // Authenticate with PIN
    char pin_input[100];
    
    while (1) {
        printf("Enter your 4-digit PIN: ");
        fgets(pin_input, sizeof(pin_input), stdin);
        pin_input[strcspn(pin_input, "\n")] = 0;

        // Validate PIN format
        if (!validate_pin(pin_input)) {
            printf("Error: PIN must be exactly 4 digits.\n");
            continue;
        }

        break; // Valid format
    }

    if (strcmp(pin_input, stored_pin) != 0) {
        printf("PIN verification failed. Access denied.\n");
        return -1;
    }

    // Display account info
    printf("\n========================================\n");
    printf("Account Number: %d\n", account_number);
    printf("Name: %s\n", name);
    printf("Account Type: %s\n", account_type);
    printf("Current Balance: RM %.2f\n", current_balance);
    printf("========================================\n");

    // Get deposit amount
    double deposit_amount;
    char amount_str[100];
    
    while (1) {
        printf("\nEnter amount to deposit (RM0.01 - RM50,000.00): RM ");
        fgets(amount_str, sizeof(amount_str), stdin);
        amount_str[strcspn(amount_str, "\n")] = 0;

        // Validate money format (max 2 decimal places)
        if (!validate_money_format(amount_str)) {
            printf("Invalid amount format. Please enter a valid number with maximum 2 decimal places.\n");
            continue;
        }

        // Convert to double
        char *endptr;
        deposit_amount = strtod(amount_str, &endptr);

        // Validate input
        if (*endptr != '\0' || amount_str[0] == '\0') {
            printf("Invalid amount. Please enter a valid number.\n");
            continue;
        }

        if (deposit_amount <= 0) {
            printf("Amount must be greater than RM0.00\n");
            continue;
        }

        if (deposit_amount > 50000.00) {
            printf("Amount must not exceed RM50,000.00 per transaction.\n");
            continue;
        }

        break; // Valid amount
    }

    // Calculate new balance
    double new_balance = current_balance + deposit_amount;

    // Confirm transaction
    char confirm[10];
    printf("\n========================================\n");
    printf("Transaction Summary:\n");
    printf("Deposit Amount: RM %.2f\n", deposit_amount);
    printf("Current Balance: RM %.2f\n", current_balance);
    printf("New Balance: RM %.2f\n", new_balance);
    printf("========================================\n");
    printf("Confirm deposit? (yes/no): ");
    fgets(confirm, sizeof(confirm), stdin);
    confirm[strcspn(confirm, "\n")] = 0;

    if (strcasecmp(confirm, "yes") != 0 && strcasecmp(confirm, "y") != 0) {
        printf("Deposit cancelled.\n");
        return 0;
    }

    // Update account file with new balance
    account_file = fopen(filename, "r");
    if (account_file == NULL) {
        printf("Error: Could not open account file.\n");
        return -1;
    }

    // Read all content and update balance
    FILE *temp_file = fopen("database/temp_account.txt", "w");
    if (temp_file == NULL) {
        fclose(account_file);
        printf("Error: Could not create temporary file.\n");
        return -1;
    }

    int balance_updated = 0;
    while (fgets(line, sizeof(line), account_file)) {
        if (strncmp(line, "Initial Deposit: ", 17) == 0 || 
            strncmp(line, "Current Balance: ", 17) == 0) {
            fprintf(temp_file, "Current Balance: %.2f\n", new_balance);
            balance_updated = 1;
        } else {
            fputs(line, temp_file);
        }
    }

    // If no balance line existed, add it
    if (!balance_updated) {
        fprintf(temp_file, "Current Balance: %.2f\n", new_balance);
    }

    fclose(account_file);
    fclose(temp_file);

    // Replace old file with updated file
    remove(filename);
    rename("database/temp_account.txt", filename);

    printf("\n========================================\n");
    printf("Deposit Successful!\n");
    printf("Amount Deposited: RM %.2f\n", deposit_amount);
    printf("New Balance: RM %.2f\n", new_balance);
    printf("========================================\n");

    return 0; // Success
}

int Withdraw_Money(void) {
    // Get and validate account number
    int account_number;
    char account_input[100];
    
    printf("\n========================================\n");
    printf("          Withdraw Money\n");
    printf("========================================\n");
    
    while (1) {
        printf("Enter your account number: ");
        fgets(account_input, sizeof(account_input), stdin);
        account_input[strcspn(account_input, "\n")] = 0;

        // Validate numeric input
        char *endptr;
        long temp = strtol(account_input, &endptr, 10);
        
        if (*endptr != '\0' || account_input[0] == '\0') {
            printf("Error: Account number must contain only digits.\n");
            continue;
        }

        if (temp < 1000000 || temp > 999999999) {
            printf("Error: Invalid account number format.\n");
            continue;
        }

        account_number = (int)temp;
        break; // Valid account number
    }

    // Check if account exists
    char filename[100];
    sprintf(filename, "database/%d.txt", account_number);
    FILE *account_file = fopen(filename, "r");
    if (account_file == NULL) {
        printf("Error: Account not found.\n");
        return -1;
    }

    // Read account details
    char line[512];
    char stored_pin[100] = "";
    char name[100] = "";
    char account_type[20] = "";
    double current_balance = 0.00;

    while (fgets(line, sizeof(line), account_file)) {
        if (strncmp(line, "PIN: ", 5) == 0) {
            sscanf(line, "PIN: %s", stored_pin);
        } else if (strncmp(line, "Name: ", 6) == 0) {
            sscanf(line, "Name: %99[^\n]", name);
        } else if (strncmp(line, "Account Type: ", 14) == 0) {
            sscanf(line, "Account Type: %s", account_type);
        } else if (strncmp(line, "Initial Deposit: ", 17) == 0) {
            sscanf(line, "Initial Deposit: %lf", &current_balance);
        } else if (strncmp(line, "Current Balance: ", 17) == 0) {
            sscanf(line, "Current Balance: %lf", &current_balance);
        }
    }
    fclose(account_file);

    // Authenticate with PIN
    char pin_input[100];
    
    while (1) {
        printf("Enter your 4-digit PIN: ");
        fgets(pin_input, sizeof(pin_input), stdin);
        pin_input[strcspn(pin_input, "\n")] = 0;

        // Validate PIN format
        if (!validate_pin(pin_input)) {
            printf("Error: PIN must be exactly 4 digits.\n");
            continue;
        }

        break; // Valid format
    }

    if (strcmp(pin_input, stored_pin) != 0) {
        printf("PIN verification failed. Access denied.\n");
        return -1;
    }

    // Display account info with available balance
    printf("\n========================================\n");
    printf("Account Number: %d\n", account_number);
    printf("Name: %s\n", name);
    printf("Account Type: %s\n", account_type);
    printf("Available Balance: RM %.2f\n", current_balance);
    printf("========================================\n");

    // Check if account has sufficient balance
    if (current_balance <= 0) {
        printf("\nInsufficient balance. Cannot process withdrawal.\n");
        return -1;
    }

    // Get withdrawal amount
    double withdrawal_amount;
    char amount_str[100];
    
    while (1) {
        printf("\nEnter amount to withdraw: RM ");
        fgets(amount_str, sizeof(amount_str), stdin);
        amount_str[strcspn(amount_str, "\n")] = 0;

        // Validate money format (max 2 decimal places)
        if (!validate_money_format(amount_str)) {
            printf("Invalid amount format. Please enter a valid number with maximum 2 decimal places.\n");
            continue;
        }

        // Convert to double
        char *endptr;
        withdrawal_amount = strtod(amount_str, &endptr);

        // Validate input
        if (*endptr != '\0' || amount_str[0] == '\0') {
            printf("Invalid amount. Please enter a valid number.\n");
            continue;
        }

        if (withdrawal_amount <= 0) {
            printf("Amount must be greater than RM0.00\n");
            continue;
        }

        if (withdrawal_amount > current_balance) {
            printf("Insufficient funds. Available balance: RM %.2f\n", current_balance);
            continue;
        }

        break; // Valid amount
    }

    // Calculate new balance
    double new_balance = current_balance - withdrawal_amount;

    // Confirm transaction
    char confirm[10];
    printf("\n========================================\n");
    printf("Transaction Summary:\n");
    printf("Withdrawal Amount: RM %.2f\n", withdrawal_amount);
    printf("Current Balance: RM %.2f\n", current_balance);
    printf("New Balance: RM %.2f\n", new_balance);
    printf("========================================\n");
    printf("Confirm withdrawal? (yes/no): ");
    fgets(confirm, sizeof(confirm), stdin);
    confirm[strcspn(confirm, "\n")] = 0;

    if (strcasecmp(confirm, "yes") != 0 && strcasecmp(confirm, "y") != 0) {
        printf("Withdrawal cancelled.\n");
        return 0;
    }

    // Update account file with new balance
    account_file = fopen(filename, "r");
    if (account_file == NULL) {
        printf("Error: Could not open account file.\n");
        return -1;
    }

    // Read all content and update balance
    FILE *temp_file = fopen("database/temp_account.txt", "w");
    if (temp_file == NULL) {
        fclose(account_file);
        printf("Error: Could not create temporary file.\n");
        return -1;
    }

    int balance_updated = 0;
    while (fgets(line, sizeof(line), account_file)) {
        if (strncmp(line, "Initial Deposit: ", 17) == 0 || 
            strncmp(line, "Current Balance: ", 17) == 0) {
            fprintf(temp_file, "Current Balance: %.2f\n", new_balance);
            balance_updated = 1;
        } else {
            fputs(line, temp_file);
        }
    }

    // If no balance line existed, add it
    if (!balance_updated) {
        fprintf(temp_file, "Current Balance: %.2f\n", new_balance);
    }

    fclose(account_file);
    fclose(temp_file);

    // Replace old file with updated file
    remove(filename);
    rename("database/temp_account.txt", filename);

    printf("\n========================================\n");
    printf("Withdrawal Successful!\n");
    printf("Amount Withdrawn: RM %.2f\n", withdrawal_amount);
    printf("New Balance: RM %.2f\n", new_balance);
    printf("========================================\n");

    return 0; // Success
}

int Remittance(void) {
    // Get and validate sender's account number
    int sender_account;
    char account_input[100];
    
    printf("\n========================================\n");
    printf("          Money Transfer\n");
    printf("========================================\n");
    
    while (1) {
        printf("Enter your account number (sender): ");
        fgets(account_input, sizeof(account_input), stdin);
        account_input[strcspn(account_input, "\n")] = 0;

        // Validate numeric input
        char *endptr;
        long temp = strtol(account_input, &endptr, 10);
        
        if (*endptr != '\0' || account_input[0] == '\0') {
            printf("Error: Account number must contain only digits.\n");
            continue;
        }

        if (temp < 1000000 || temp > 999999999) {
            printf("Error: Invalid account number format.\n");
            continue;
        }

        sender_account = (int)temp;
        break; // Valid account number
    }

    // Check if sender's account exists
    char sender_filename[100];
    sprintf(sender_filename, "database/%d.txt", sender_account);
    FILE *sender_file = fopen(sender_filename, "r");
    if (sender_file == NULL) {
        printf("Error: Sender account not found.\n");
        return -1;
    }

    // Read sender's account details
    char line[512];
    char sender_pin[100] = "";
    char sender_name[100] = "";
    char sender_type[20] = "";
    double sender_balance = 0.00;

    while (fgets(line, sizeof(line), sender_file)) {
        if (strncmp(line, "PIN: ", 5) == 0) {
            sscanf(line, "PIN: %s", sender_pin);
        } else if (strncmp(line, "Name: ", 6) == 0) {
            sscanf(line, "Name: %99[^\n]", sender_name);
        } else if (strncmp(line, "Account Type: ", 14) == 0) {
            sscanf(line, "Account Type: %s", sender_type);
        } else if (strncmp(line, "Initial Deposit: ", 17) == 0) {
            sscanf(line, "Initial Deposit: %lf", &sender_balance);
        } else if (strncmp(line, "Current Balance: ", 17) == 0) {
            sscanf(line, "Current Balance: %lf", &sender_balance);
        }
    }
    fclose(sender_file);

    // Authenticate sender with PIN
    char pin_input[100];
    
    while (1) {
        printf("Enter your 4-digit PIN: ");
        fgets(pin_input, sizeof(pin_input), stdin);
        pin_input[strcspn(pin_input, "\n")] = 0;

        // Validate PIN format
        if (!validate_pin(pin_input)) {
            printf("Error: PIN must be exactly 4 digits.\n");
            continue;
        }

        break; // Valid format
    }

    if (strcmp(pin_input, sender_pin) != 0) {
        printf("PIN verification failed. Access denied.\n");
        return -1;
    }

    // Display sender's account info
    printf("\n========================================\n");
    printf("Sender Account Details:\n");
    printf("Account Number: %d\n", sender_account);
    printf("Name: %s\n", sender_name);
    printf("Account Type: %s\n", sender_type);
    printf("Available Balance: RM %.2f\n", sender_balance);
    printf("========================================\n");

    // Check if sender has sufficient balance
    if (sender_balance <= 0) {
        printf("\nInsufficient balance. Cannot process transfer.\n");
        return -1;
    }

    // Get and validate receiver's account number
    int receiver_account;
    
    while (1) {
        printf("\nEnter receiver's account number: ");
        fgets(account_input, sizeof(account_input), stdin);
        account_input[strcspn(account_input, "\n")] = 0;

        // Validate numeric input
        char *endptr;
        long temp = strtol(account_input, &endptr, 10);
        
        if (*endptr != '\0' || account_input[0] == '\0') {
            printf("Error: Account number must contain only digits.\n");
            continue;
        }

        if (temp < 1000000 || temp > 999999999) {
            printf("Error: Invalid account number format.\n");
            continue;
        }

        receiver_account = (int)temp;

        // Check that accounts are distinct
        if (receiver_account == sender_account) {
            printf("Error: Cannot transfer to the same account.\n");
            continue;
        }

        break; // Valid account number
    }

    // Check if receiver's account exists
    char receiver_filename[100];
    sprintf(receiver_filename, "database/%d.txt", receiver_account);
    FILE *receiver_file = fopen(receiver_filename, "r");
    if (receiver_file == NULL) {
        printf("Error: Receiver account not found.\n");
        return -1;
    }

    // Read receiver's account details
    char receiver_name[100] = "";
    char receiver_type[20] = "";
    double receiver_balance = 0.00;

    while (fgets(line, sizeof(line), receiver_file)) {
        if (strncmp(line, "Name: ", 6) == 0) {
            sscanf(line, "Name: %99[^\n]", receiver_name);
        } else if (strncmp(line, "Account Type: ", 14) == 0) {
            sscanf(line, "Account Type: %s", receiver_type);
        } else if (strncmp(line, "Initial Deposit: ", 17) == 0) {
            sscanf(line, "Initial Deposit: %lf", &receiver_balance);
        } else if (strncmp(line, "Current Balance: ", 17) == 0) {
            sscanf(line, "Current Balance: %lf", &receiver_balance);
        }
    }
    fclose(receiver_file);

    // Display receiver's account info
    printf("\n========================================\n");
    printf("Receiver Account Details:\n");
    printf("Account Number: %d\n", receiver_account);
    printf("Name: %s\n", receiver_name);
    printf("Account Type: %s\n", receiver_type);
    printf("========================================\n");

    // Get transfer amount
    double transfer_amount;
    char amount_str[100];
    
    while (1) {
        printf("\nEnter amount to transfer: RM ");
        fgets(amount_str, sizeof(amount_str), stdin);
        amount_str[strcspn(amount_str, "\n")] = 0;

        // Validate money format (max 2 decimal places)
        if (!validate_money_format(amount_str)) {
            printf("Invalid amount format. Please enter a valid number with maximum 2 decimal places.\n");
            continue;
        }

        // Convert to double
        char *endptr;
        transfer_amount = strtod(amount_str, &endptr);

        // Validate input
        if (*endptr != '\0' || amount_str[0] == '\0') {
            printf("Invalid amount. Please enter a valid number.\n");
            continue;
        }

        if (transfer_amount <= 0) {
            printf("Amount must be greater than RM0.00\n");
            continue;
        }

        break; // Valid amount
    }

    // Calculate remittance fee based on account types
    double fee_percentage = 0.0;
    double remittance_fee = 0.0;
    
    if (strcasecmp(sender_type, "Savings") == 0 && strcasecmp(receiver_type, "Current") == 0) {
        fee_percentage = 2.0; // 2% fee for Savings to Current
        remittance_fee = transfer_amount * 0.02;
    } else if (strcasecmp(sender_type, "Current") == 0 && strcasecmp(receiver_type, "Savings") == 0) {
        fee_percentage = 3.0; // 3% fee for Current to Savings
        remittance_fee = transfer_amount * 0.03;
    }
    // No fee for same account type transfers

    // Calculate total deduction from sender (transfer amount + fee)
    double total_deduction = transfer_amount + remittance_fee;

    // Check if sender has sufficient balance for transfer + fee
    if (total_deduction > sender_balance) {
        printf("\nInsufficient balance. Required: RM %.2f (Transfer: RM %.2f + Fee: RM %.2f)\n", 
               total_deduction, transfer_amount, remittance_fee);
        printf("Available balance: RM %.2f\n", sender_balance);
        return -1;
    }

    // Calculate new balances
    double sender_new_balance = sender_balance - total_deduction;
    double receiver_new_balance = receiver_balance + transfer_amount;

    // Display transaction summary
    printf("\n========================================\n");
    printf("Transaction Summary:\n");
    printf("----------------------------------------\n");
    printf("From: %s (Account: %d)\n", sender_name, sender_account);
    printf("To: %s (Account: %d)\n", receiver_name, receiver_account);
    printf("----------------------------------------\n");
    printf("Transfer Amount: RM %.2f\n", transfer_amount);
    if (remittance_fee > 0) {
        printf("Remittance Fee (%.0f%%): RM %.2f\n", fee_percentage, remittance_fee);
        printf("Total Deduction: RM %.2f\n", total_deduction);
    }
    printf("----------------------------------------\n");
    printf("Sender's Current Balance: RM %.2f\n", sender_balance);
    printf("Sender's New Balance: RM %.2f\n", sender_new_balance);
    printf("----------------------------------------\n");
    printf("Receiver's Current Balance: RM %.2f\n", receiver_balance);
    printf("Receiver's New Balance: RM %.2f\n", receiver_new_balance);
    printf("========================================\n");

    // Confirm transaction
    char confirm[10];
    printf("Confirm transfer? (yes/no): ");
    fgets(confirm, sizeof(confirm), stdin);
    confirm[strcspn(confirm, "\n")] = 0;

    if (strcasecmp(confirm, "yes") != 0 && strcasecmp(confirm, "y") != 0) {
        printf("Transfer cancelled.\n");
        return 0;
    }

    // Update sender's account file
    sender_file = fopen(sender_filename, "r");
    if (sender_file == NULL) {
        printf("Error: Could not open sender's account file.\n");
        return -1;
    }

    FILE *temp_file = fopen("database/temp_sender.txt", "w");
    if (temp_file == NULL) {
        fclose(sender_file);
        printf("Error: Could not create temporary file.\n");
        return -1;
    }

    int balance_updated = 0;
    while (fgets(line, sizeof(line), sender_file)) {
        if (strncmp(line, "Initial Deposit: ", 17) == 0 || 
            strncmp(line, "Current Balance: ", 17) == 0) {
            fprintf(temp_file, "Current Balance: %.2f\n", sender_new_balance);
            balance_updated = 1;
        } else {
            fputs(line, temp_file);
        }
    }

    if (!balance_updated) {
        fprintf(temp_file, "Current Balance: %.2f\n", sender_new_balance);
    }

    fclose(sender_file);
    fclose(temp_file);

    remove(sender_filename);
    rename("database/temp_sender.txt", sender_filename);

    // Update receiver's account file
    receiver_file = fopen(receiver_filename, "r");
    if (receiver_file == NULL) {
        printf("Error: Could not open receiver's account file.\n");
        return -1;
    }

    temp_file = fopen("database/temp_receiver.txt", "w");
    if (temp_file == NULL) {
        fclose(receiver_file);
        printf("Error: Could not create temporary file.\n");
        return -1;
    }

    balance_updated = 0;
    while (fgets(line, sizeof(line), receiver_file)) {
        if (strncmp(line, "Initial Deposit: ", 17) == 0 || 
            strncmp(line, "Current Balance: ", 17) == 0) {
            fprintf(temp_file, "Current Balance: %.2f\n", receiver_new_balance);
            balance_updated = 1;
        } else {
            fputs(line, temp_file);
        }
    }

    if (!balance_updated) {
        fprintf(temp_file, "Current Balance: %.2f\n", receiver_new_balance);
    }

    fclose(receiver_file);
    fclose(temp_file);

    remove(receiver_filename);
    rename("database/temp_receiver.txt", receiver_filename);

    // Display success message
    printf("\n========================================\n");
    printf("Transfer Successful!\n");
    printf("----------------------------------------\n");
    printf("Amount Transferred: RM %.2f\n", transfer_amount);
    if (remittance_fee > 0) {
        printf("Remittance Fee: RM %.2f\n", remittance_fee);
        printf("Total Deducted: RM %.2f\n", total_deduction);
    }
    printf("----------------------------------------\n");
    printf("Your New Balance: RM %.2f\n", sender_new_balance);
    printf("Receiver's New Balance: RM %.2f\n", receiver_new_balance);
    printf("========================================\n");

    return 0; // Success
}

int main(void) {
    // Seed the random number generator
    srand(time(NULL));
    
    int choice;
    while (1) {
        printf("\nBank Account Management System\n");
        printf("--------------------------------\n");
        /* Show session info: current date/time and count of loaded accounts from index */
        {
            time_t now = time(NULL);
            char timebuf[64] = "Unknown time";
            struct tm *tm_info = localtime(&now);
            if (tm_info) {
                strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_info);
            }

            int loaded_accounts = 0;
            FILE *fa = fopen("database/index.txt", "r");
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