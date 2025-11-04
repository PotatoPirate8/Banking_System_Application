# Banking System Application - User Manual

## Table of Contents
1. [Getting Started](#getting-started)
2. [Creating a Bank Account](#creating-a-bank-account)
3. [Depositing Money](#depositing-money)
4. [Withdrawing Money](#withdrawing-money)
5. [Transferring Money (Remittance)](#transferring-money-remittance)
6. [Deleting a Bank Account](#deleting-a-bank-account)
7. [Troubleshooting](#troubleshooting)

---

## Getting Started

### Launching the Application

**Windows:**
```bash
./banking_system.exe
```

**Linux/Unix:**
```bash
./banking_system
```

### Main Menu

When you start the application, you'll see the main menu:

```
Bank Account Management System
--------------------------------
Session started: 2025-11-04 10:30:45
Loaded accounts: 5

Select :
1. Create New Bank Account
2. Delete Bank Account
3. Deposit Money
4. Withdraw Money
5. Remittance
6. Exit
Enter your choice:
```

Simply enter the number (1-6) corresponding to your desired operation.

---

## Creating a Bank Account

### Step 1: Select Option 1
From the main menu, enter `1` to create a new bank account.

### Step 2: Enter Your Information

#### Name
- **Prompt:** `Enter name (letters and spaces only):`
- **Rules:** Only letters (A-Z, a-z) and spaces are allowed
- **Example:** `John Smith` ✅
- **Invalid:** `John123` ❌, `John-Smith` ❌

#### Identification Number (ID)
- **Prompt:** `Enter Identification Number (digits only):`
- **Rules:** Only digits (0-9) are allowed
- **Example:** `1234567890` ✅
- **Invalid:** `ABC123` ❌, `123-456` ❌

#### Account Type
- **Prompt:** `Type of Account (Savings or Current):`
- **Options:** 
  - `Savings` - For saving money (earns interest in future versions)
  - `Current` - For regular transactions
- **Note:** Case-insensitive (you can type "savings", "SAVINGS", or "Savings")
- **Example:** `Savings` ✅, `current` ✅
- **Invalid:** `Checking` ❌, `Save` ❌

#### PIN
- **Prompt:** `Create 4-digit PIN:`
- **Rules:** Exactly 4 digits
- **Example:** `1234` ✅, `0000` ✅
- **Invalid:** `123` ❌, `12345` ❌, `abcd` ❌

### Step 3: Review Your Information

The system will display all your entered information:

```
===========================================
         Account Information Review        
===========================================
Name:          John Smith
ID:            1234567890
Account Type:  Savings
PIN:           1234
===========================================

Is all information correct? (yes/no):
```

**Options:**
- Type `yes` or `y` to confirm and create the account
- Type `no` or `n` to edit information

### Step 4: Editing Information (if needed)

If you chose "no", you'll see:

```
What would you like to edit?
1. Name
2. ID
3. Account Type
4. PIN
5. Re-enter all information
6. Cancel account creation
Enter your choice:
```

Select the number for the field you want to change.

### Step 5: Account Created

Upon successful creation, you'll receive:

```
Your Bank Account Number is: 12345678

Created your new bank account successfully!
```

**IMPORTANT:** Write down your account number! You'll need it for all future transactions.

---

## Depositing Money

### Step 1: Select Option 3
From the main menu, enter `3` to deposit money.

### Step 2: Enter Account Number
- **Prompt:** `Enter your account number:`
- **Format:** 7-9 digit number
- **Example:** `12345678`

### Step 3: Enter PIN
- **Prompt:** `Enter your 4-digit PIN:`
- **Note:** Must match the PIN you created

### Step 4: View Account Information

The system displays your account details:

```
========================================
Account Number: 12345678
Name: John Smith
Account Type: Savings
Current Balance: RM 0.00
========================================
```

### Step 5: Enter Deposit Amount

- **Prompt:** `Enter amount to deposit (RM0.01 - RM50,000.00): RM`
- **Rules:**
  - Minimum: RM 0.01
  - Maximum: RM 50,000.00 per transaction
  - Maximum 2 decimal places
- **Examples:** `100.50` ✅, `1000` ✅, `50000.00` ✅
- **Invalid:** `100.505` ❌ (3 decimal places), `60000` ❌ (exceeds limit)

### Step 6: Confirm Transaction

Review the transaction summary:

```
========================================
Transaction Summary:
Deposit Amount: RM 1000.00
Current Balance: RM 0.00
New Balance: RM 1000.00
========================================
Confirm deposit? (yes/no):
```

- Type `yes` or `y` to confirm
- Type `no` or `n` to cancel

### Step 7: Transaction Complete

```
========================================
Deposit Successful!
Amount Deposited: RM 1000.00
New Balance: RM 1000.00
========================================
```

---

## Withdrawing Money

### Step 1: Select Option 4
From the main menu, enter `4` to withdraw money.

### Step 2: Enter Account Number
- **Prompt:** `Enter your account number:`
- **Example:** `12345678`

### Step 3: Enter PIN
- **Prompt:** `Enter your 4-digit PIN:`

### Step 4: View Available Balance

```
========================================
Account Number: 12345678
Name: John Smith
Account Type: Savings
Available Balance: RM 1000.00
========================================
```

### Step 5: Enter Withdrawal Amount

- **Prompt:** `Enter amount to withdraw: RM`
- **Rules:**
  - Must be greater than RM 0.00
  - Cannot exceed available balance
  - Maximum 2 decimal places
- **Examples:** `500.00` ✅, `100` ✅
- **Invalid:** `1500` ❌ (exceeds balance), `100.999` ❌ (3 decimals)

### Step 6: Confirm Transaction

```
========================================
Transaction Summary:
Withdrawal Amount: RM 500.00
Current Balance: RM 1000.00
New Balance: RM 500.00
========================================
Confirm withdrawal? (yes/no):
```

### Step 7: Transaction Complete

```
========================================
Withdrawal Successful!
Amount Withdrawn: RM 500.00
New Balance: RM 500.00
========================================
```

---

## Transferring Money (Remittance)

### Step 1: Select Option 5
From the main menu, enter `5` for money transfer.

### Step 2: Enter Your Account Number (Sender)
- **Prompt:** `Enter your account number (sender):`
- **Example:** `12345678`

### Step 3: Enter PIN
- **Prompt:** `Enter your 4-digit PIN:`

### Step 4: View Your Account Details

```
========================================
Sender Account Details:
Account Number: 12345678
Name: John Smith
Account Type: Savings
Available Balance: RM 500.00
========================================
```

### Step 5: Enter Receiver's Account Number

- **Prompt:** `Enter receiver's account number:`
- **Note:** Must be different from your account
- **Example:** `87654321`

### Step 6: View Receiver's Details

```
========================================
Receiver Account Details:
Account Number: 87654321
Name: Jane Doe
Account Type: Current
========================================
```

### Step 7: Enter Transfer Amount

- **Prompt:** `Enter amount to transfer: RM`
- **Rules:**
  - Must be greater than RM 0.00
  - Must have sufficient balance for amount + fees
  - Maximum 2 decimal places

### Step 8: Review Transaction with Fees

The system calculates applicable fees:

**Fee Structure:**
- Savings → Current: 2% fee
- Current → Savings: 3% fee
- Same type → Same type: No fee

```
========================================
Transaction Summary:
----------------------------------------
From: John Smith (Account: 12345678)
To: Jane Doe (Account: 87654321)
----------------------------------------
Transfer Amount: RM 200.00
Remittance Fee (2%): RM 4.00
Total Deduction: RM 204.00
----------------------------------------
Sender's Current Balance: RM 500.00
Sender's New Balance: RM 296.00
----------------------------------------
Receiver's Current Balance: RM 100.00
Receiver's New Balance: RM 300.00
========================================
Confirm transfer? (yes/no):
```

### Step 9: Transaction Complete

```
========================================
Transfer Successful!
Transaction ID: 1699012345
----------------------------------------
Amount Transferred: RM 200.00
Remittance Fee: RM 4.00
Total Deducted: RM 204.00
----------------------------------------
Your New Balance: RM 296.00
Receiver's New Balance: RM 300.00
========================================
```

**IMPORTANT:** Save the Transaction ID for your records!

---

## Deleting a Bank Account

### Step 1: Select Option 2
From the main menu, enter `2` to delete an account.

### Step 2: View All Accounts

The system displays all existing accounts:

```
========================================
       Existing Bank Accounts
========================================
1. Account Number: 12345678
   Name: John Smith
   Account Type: Savings
----------------------------------------
2. Account Number: 87654321
   Name: Jane Doe
   Account Type: Current
----------------------------------------

Enter the number of the account to delete (1-2), or 0 to cancel:
```

### Step 3: Select Account to Delete

- Enter the number (1, 2, etc.) of the account you want to delete
- Enter `0` to cancel

### Step 4: Review Selected Account

```
You selected:
Account Number: 12345678
Name: John Smith
Account Type: Savings
```

### Step 5: Security Verification

#### Last 4 Digits of ID
- **Prompt:** `Enter the last 4 digits of your ID:`
- **Example:** If your ID is `1234567890`, enter `7890`
- **Rules:** Exactly 4 digits

#### PIN Verification
- **Prompt:** `Enter your 4-digit PIN:`
- **Must match the account's PIN**

### Step 6: Final Confirmation

```
Are you sure you want to permanently delete this account? (yes/no):
```

**WARNING:** This action cannot be undone!
- Type `yes` to permanently delete the account
- Type `no` to cancel

### Step 7: Account Deleted

```
Account 12345678 has been successfully deleted.
All associated data has been removed from the system.
```

---

## Troubleshooting

### Common Error Messages

#### "Invalid input. Please enter a number."
- **Cause:** You entered text instead of a number
- **Solution:** Enter only numeric values when prompted for account numbers, PINs, or menu choices

#### "Account not found."
- **Cause:** The account number doesn't exist in the database
- **Solution:** Double-check the account number and try again

#### "PIN verification failed. Access denied."
- **Cause:** Incorrect PIN entered
- **Solution:** Re-enter the correct 4-digit PIN for your account

#### "Insufficient balance."
- **Cause:** Trying to withdraw or transfer more than your available balance
- **Solution:** Check your balance and enter an amount less than or equal to available funds

#### "Amount must not exceed RM50,000.00 per transaction."
- **Cause:** Deposit amount is too large
- **Solution:** Split large deposits into multiple transactions of RM50,000 or less

#### "Error: Could not read account file or file is corrupted."
- **Cause:** Account file has missing or invalid data
- **Solution:** Contact support (see transaction logs in `database/` folder)

#### "Account number space is XX% full."
- **Cause:** Database is getting crowded (warning at >90%)
- **Solution:** This is informational; account creation may take longer but will still work

### Invalid Input Examples

#### Names
- ❌ `John123` - Contains numbers
- ❌ `John-Smith` - Contains special characters
- ✅ `John Smith` - Letters and spaces only

#### IDs
- ❌ `ABC123` - Contains letters
- ❌ `123-456-789` - Contains special characters
- ✅ `123456789` - Digits only

#### PINs
- ❌ `123` - Less than 4 digits
- ❌ `12345` - More than 4 digits
- ❌ `abcd` - Contains letters
- ✅ `1234` - Exactly 4 digits

#### Money Amounts
- ❌ `100.505` - More than 2 decimal places
- ❌ `-50` - Negative amount
- ❌ `1,000.00` - Contains comma
- ✅ `1000.00` - Valid format
- ✅ `100.5` - Valid (will be treated as 100.50)

### What to Do If...

#### You Forgot Your Account Number
- View all accounts in the Database

#### Transaction Appears to Fail
- Check the `database/transaction_*.log` files for details
- The transaction ID will be in the log file name
- Contact support with the Transaction ID

#### Account Balance Shows RM 0.00 Unexpectedly
- This may indicate file corruption
- Check the account file in `database/[account_number].txt`
- Look for transaction logs that may show the actual transactions
- Contact support immediately

---

## Quick Reference Card

| Operation | Menu Option | Required Info |
|-----------|-------------|---------------|
| Create Account | 1 | Name, ID, Account Type, PIN |
| Delete Account | 2 | Account Number, Last 4 of ID, PIN |
| Deposit | 3 | Account Number, PIN, Amount |
| Withdraw | 4 | Account Number, PIN, Amount |
| Transfer | 5 | Both Account Numbers, Sender's PIN, Amount |
| Exit | 6 | None |

### Fee Structure Quick Reference
- Savings → Current: **2% fee**
- Current → Savings: **3% fee**
- Savings → Savings: **No fee**
- Current → Current: **No fee**

### Transaction Limits
- **Deposit**: RM 0.01 - RM 50,000.00
- **Withdrawal**: Up to available balance
- **Transfer**: Up to available balance (minus fees if applicable)

---

**Last Updated:** November 4, 2025  
**Application Version:** COMP1312 Coursework Edition
