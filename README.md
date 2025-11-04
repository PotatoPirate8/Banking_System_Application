# Banking System Application

A robust C-based banking system with comprehensive error handling, data validation, and transaction management features.

## Features

### Core Banking Operations
- **Create Bank Account** - Register new accounts with validated user information
- **Delete Bank Account** - Securely remove accounts with PIN and ID verification
- **Deposit Money** - Add funds to accounts with transaction limits
- **Withdraw Money** - Withdraw funds with balance verification
- **Money Transfer (Remittance)** - Transfer funds between accounts with fee calculation

### Security Features
- 4-digit PIN authentication for all transactions
- ID verification for account deletion
- Account type validation (Savings/Current)
- Input sanitization and validation

### Data Integrity
- **Floating-point error protection** - All monetary calculations are rounded to 2 decimal places
- **Account file corruption detection** - Validates all required fields when reading account data
- **Atomic file operations** - Uses temporary files and atomic rename for crash safety
- **Transaction logging** - Maintains transaction logs for remittance operations with rollback capability
- **Index file integrity** - Atomic updates to prevent corruption during account creation/deletion

### Transaction Safety
- Overflow protection for extremely large monetary values (max: RM999,999,999.99)
- Automatic rollback on failed remittance transactions
- Balance validation before all withdrawal operations
- Comprehensive error reporting

## Technical Specifications

### Supported Platforms
- **Windows** (MinGW GCC, MSVC)
- **Linux/Unix** (GCC)

### Requirements
- C Compiler (GCC 7.0+ or compatible)
- Standard C libraries

### Account Number Range
- Minimum: 1,000,000
- Maximum: 999,999,999
- Total capacity: 998,999,999 accounts

### Transaction Limits
- **Deposit**: RM0.01 - RM50,000.00 per transaction
- **Withdrawal**: Limited by account balance
- **Transfer**: Limited by account balance + fees

### Remittance Fees
- **Savings → Current**: 2% of transfer amount
- **Current → Savings**: 3% of transfer amount
- **Same account type**: No fee

## Compilation

### Windows (MinGW)
```bash
gcc main.C -o main.exe -lm
```

### Linux/Unix
```bash
gcc -o banking_system main.C -lm
```

## Usage

Run the compiled executable:

### Windows
```bash
./main.exe
```

### Linux/Unix
```bash
./banking_system
```

## File Structure

```
Banking_System_Application/
├── main.C                  # Main source code
├── README.md               # This file
└── database/               # Auto-created database directory
    ├── index.txt          # Account index (AccountNumber|Name|ID|Type)
    ├── [account_num].txt  # Individual account files
    └── transaction_*.log  # Transaction logs
```

## Account File Format

Each account is stored as a text file with the following structure:
```
Name: [User Name]
ID: [Identification Number]
Account Type: [Savings|Current]
PIN: [4-digit PIN]
Account Number: [7-9 digit number]
Current Balance: [amount]
```

## Data Validation

### Input Validation
- **Name**: Letters and spaces only
- **ID**: Digits only
- **PIN**: Exactly 4 digits
- **Account Type**: "Savings" or "Current" (case-insensitive)
- **Monetary amounts**: Max 2 decimal places, positive values only

### File Validation
When reading account files, the system validates:
- All required fields are present
- Balance is within acceptable range (0 to RM999,999,999.99)
- PIN format is valid
- Account type is valid
- No NaN or Infinity values

## Error Handling

### Account File Corruption
If an account file is corrupted or missing required fields:
- Transaction is blocked
- Detailed error message is displayed
- User is advised to contact support

### Transaction Failures
- **Deposit/Withdrawal**: File operations are validated before confirming success
- **Remittance**: Automatic rollback if receiver update fails
- All errors are logged with descriptive messages

### Index File Protection
- Atomic writes using temporary files
- Original index preserved if update fails
- Cleanup of temporary files on errors

## Troubleshooting

### Program exits when selecting "1. Create New Bank Account"
- Symptom: The application appears to exit or crash immediately after entering option 1 in the main menu.
- Cause: This was due to a large array being allocated on the stack during account number uniqueness checks, which could overflow the default Windows stack.
- Status: Fixed on 2025-11-04 by replacing the stack array with a dynamically resized heap allocation. If you previously observed this behavior, rebuild with the latest source.
- Verify: From the main menu, enter `1` and complete the prompts. The account should be created successfully and the menu should display again.

## Known Limitations

1. **Maximum Accounts**: 1,000 accounts can be displayed in delete operation
2. **Account Number Generation**: May slow down when database is >90% full
3. **File Locking**: No concurrent access protection (single-user system)
4. **Index Recovery**: Manual recovery required if both index and backup fail

## Development Notes

### Floating-Point Handling
All monetary calculations use `round_money()` function to prevent precision errors:
```c
double round_money(double amount) {
    return round(amount * 100.0) / 100.0;
}
```

### Platform Compatibility
The code uses conditional compilation for platform-specific features:
- Directory creation (`mkdir` vs `_mkdir`)
- String comparison (`strcasecmp` vs `_stricmp`)

### Transaction Integrity
Remittance operations use a multi-step process with logging:
1. Create transaction log
2. Update sender account
3. Update receiver account
4. Mark transaction complete
5. Rollback on any failure


### Current Version
- Comprehensive input validation
- Floating-point error protection
- Account file corruption detection
- Atomic file operations
- Transaction rollback capability
- Overflow protection
- Cross-platform support (Windows/Linux)

## Changelog

- 2025-11-04: Fixed premature exit on selecting option 1 (Create New Bank Account). Replaced large stack allocation with dynamic memory in account number uniqueness check to prevent stack overflow, especially on Windows/MinGW.

## License

This is an educational project developed for COMP1312 coursework.

## Author

University of Southampton Malaysia COMP1312 - Wong Jun Han 36493732 
