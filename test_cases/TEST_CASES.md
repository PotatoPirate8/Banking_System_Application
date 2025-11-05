# Top 10 Most Important Test Cases for Banking System Application

## Test Environment
- **Platform:** Windows
- **Compiler:** GCC (MinGW)
- **Database Location:** `database/` directory

---

## Critical Test Cases

### 1. TC-AC-001: Create Account with Valid Inputs (CRITICAL)
**Category:** Account Creation  
**Priority:** HIGH  
**Description:** Verify that a valid account can be created successfully

**Test Steps:**
1. Start the application
2. Select option 1 (Create New Bank Account)
3. Enter Name: "John Smith"
4. Enter ID: "1234567" (7 digits)
5. Enter Account Type: "Savings"
6. Enter PIN: "1234"
7. Confirm: "yes"

**Expected Result:**
- Account created successfully
- Unique account number generated (between 1000000 and 999999999)
- Account file created in `database/` directory
- Entry added to `database/index.txt`
- Success message displayed

**Actual Result:** _______________  
**Status:** ☐ Pass ☐ Fail  

---

### 2. TC-AC-205: ID Length Validation (CRITICAL)
**Category:** Account Creation - Input Validation  
**Priority:** HIGH  
**Description:** Verify that ID must be between 7 and 12 digits

**Test Steps:**
1. Start account creation
2. Enter Name: "Jane Doe"
3. Try ID: "123456" (6 digits - too short)
4. Try ID: "1234567890123" (13 digits - too long)
5. Enter valid ID: "12345678" (8 digits)

**Expected Result:**
- ID with 6 digits: Error message "Invalid ID length! ID must be between 7 and 12 digits."
- ID with 13 digits: Error message "Invalid ID length! ID must be between 7 and 12 digits."
- ID with 8 digits: Accepted and proceed to next field
- System prompts for re-entry on invalid input

**Actual Result:** _______________  
**Status:** ☐ Pass ☐ Fail  

---

### 3. TC-DP-001: Deposit Money Successfully (CRITICAL)
**Category:** Deposit  
**Priority:** HIGH  
**Description:** Verify that money can be deposited into an existing account

**Test Steps:**
1. Create an account with initial balance RM0.00
2. Select option 3 (Deposit Money)
3. Enter valid account number
4. Enter correct PIN
5. Enter amount: "500.00"
6. Confirm: "yes"

**Expected Result:**
- Deposit successful
- Balance increased from RM0.00 to RM500.00
- Account file updated with "Current Balance: 500.00"
- Success message with new balance displayed

**Actual Result:** _______________  
**Status:** ☐ Pass ☐ Fail  

---

### 4. TC-WD-101: Withdraw More Than Balance (CRITICAL)
**Category:** Withdrawal - Insufficient Funds  
**Priority:** HIGH  
**Description:** Verify that withdrawal fails when amount exceeds balance

**Test Steps:**
1. Use account with balance RM100.00
2. Select option 4 (Withdraw Money)
3. Enter account number and PIN
4. Enter amount: "200.00"

**Expected Result:**
- Error message: "Insufficient funds. Available balance: RM100.00"
- Transaction rejected
- Balance remains RM100.00 (unchanged)
- System prompts to enter valid amount or cancel

**Actual Result:** _______________  
**Status:** ☐ Pass ☐ Fail  

---

### 5. TC-RM-102: Transfer with Fee (Current to Savings) (CRITICAL)
**Category:** Remittance  
**Priority:** HIGH  
**Description:** Verify that 3% fee is applied when transferring from Current to Savings account

**Test Steps:**
1. Create Account A: Type "Current", Balance RM1000.00
2. Create Account B: Type "Savings", Balance RM500.00
3. Select option 5 (Remittance)
4. Enter Account A number and PIN
5. Enter Account B number as receiver
6. Enter transfer amount: "100.00"
7. Confirm: "yes"

**Expected Result:**
- Fee calculated: RM100.00 × 3% = RM3.00
- Total deduction from sender: RM103.00
- Sender new balance: RM1000.00 - RM103.00 = RM897.00
- Receiver new balance: RM500.00 + RM100.00 = RM600.00
- Transaction summary shows fee breakdown
- Both account files updated correctly

**Actual Result:** _______________  
**Status:** ☐ Pass ☐ Fail  

---

### 6. TC-RM-203: Transfer to Same Account (CRITICAL)
**Category:** Remittance - Validation  
**Priority:** HIGH  
**Description:** Verify that system prevents transferring to the same account

**Test Steps:**
1. Create an account (e.g., account number 1234567)
2. Select option 5 (Remittance)
3. Enter account 1234567 as sender
4. Enter correct PIN
5. Enter account 1234567 as receiver

**Expected Result:**
- Error message: "Error: Cannot transfer to the same account."
- Transaction rejected
- System prompts to enter different receiver account
- No balance changes occur

**Actual Result:** _______________  
**Status:** ☐ Pass ☐ Fail  

---

### 7. TC-AD-001: Delete Account Successfully (CRITICAL)
**Category:** Account Deletion  
**Priority:** HIGH  
**Description:** Verify that an existing account can be deleted with proper verification

**Test Steps:**
1. Create account: Name "Test User", ID "1234567890", PIN "5678"
2. Note the generated account number
3. Select option 2 (Delete Bank Account)
4. Select the account from the list
5. Enter last 4 digits of ID: "7890"
6. Enter PIN: "5678"
7. Confirm deletion: "yes"

**Expected Result:**
- ID verification successful
- PIN verification successful
- Account file deleted from `database/` directory
- Entry removed from `database/index.txt`
- Success message: "Account X has been successfully deleted."
- All associated data removed

**Actual Result:** _______________  
**Status:** ☐ Pass ☐ Fail  

---

### 8. TC-FS-301: Transfer Rollback on Error (CRITICAL)
**Category:** Transaction Atomicity  
**Priority:** HIGH  
**Description:** Verify that failed transfer transactions rollback properly

**Test Steps:**
1. Create two valid accounts
2. Initiate transfer from Account A to Account B
3. Simulate failure scenario (e.g., manually make receiver file read-only if possible, or test with corrupted receiver file)

**Expected Result:**
- Error detected during receiver update
- Sender's balance automatically restored to original amount
- Transaction log shows "Status: ROLLED_BACK"
- Error message displayed to user
- System remains stable, no data corruption

**Actual Result:** _______________  
**Status:** ☐ Pass ☐ Fail  

---

### 9. TC-SEC-001: Buffer Overflow Prevention (CRITICAL)
**Category:** Security  
**Priority:** HIGH  
**Description:** Verify that system handles extremely long inputs safely

**Test Steps:**
1. Start account creation
2. Enter name with 200 characters (long string of letters)
3. Enter ID with 100 characters (long string of digits)
4. Enter amount "999999999999999999999999999" (very large number)

**Expected Result:**
- System handles all inputs without crashing
- Long inputs are either:
  - Truncated and validated properly, OR
  - Rejected with appropriate error messages
- No buffer overflow occurs
- No segmentation faults or crashes
- System continues to function normally

**Actual Result:** _______________  
**Status:** ☐ Pass ☐ Fail  

---

### 10. TC-INT-001: Complete Lifecycle Test (CRITICAL)
**Category:** Integration  
**Priority:** HIGH  
**Description:** Verify that all major operations work together in sequence

**Test Steps:**
1. Create new account (Name: "Alice", ID: "7777777", Type: "Savings", PIN: "1111")
2. Note the account number
3. Deposit RM1000.00 into the account
4. Withdraw RM300.00 from the account
5. Create second account (Name: "Bob", ID: "8888888", Type: "Current", PIN: "2222")
6. Transfer RM200.00 from Alice to Bob
7. Verify both balances
8. Delete Alice's account

**Expected Result:**
- Account creation successful for both
- After deposit: Alice balance = RM1000.00
- After withdrawal: Alice balance = RM700.00
- After transfer: Alice balance = RM496.00 (RM700 - RM200 - RM4 fee), Bob balance = RM200.00
- Both accounts show correct balances in files
- Alice's account deleted successfully
- Bob's account remains intact
- All operations execute without errors

**Actual Result:** _______________  
**Status:** ☐ Pass ☐ Fail  

---

## Test Execution Summary

**Date:** _______________  
**Tester:** _______________  
**Build Version:** _______________

| Test ID | Description | Status | Notes |
|---------|-------------|--------|-------|
| TC-AC-001 | Create Valid Account | ☐ Pass ☐ Fail | |
| TC-AC-205 | ID Length Validation | ☐ Pass ☐ Fail | |
| TC-DP-001 | Deposit Successfully | ☐ Pass ☐ Fail | |
| TC-WD-101 | Insufficient Funds | ☐ Pass ☐ Fail | |
| TC-RM-102 | Transfer with Fee | ☐ Pass ☐ Fail | |
| TC-RM-203 | Same Account Transfer | ☐ Pass ☐ Fail | |
| TC-AD-001 | Delete Account | ☐ Pass ☐ Fail | |
| TC-FS-301 | Transfer Rollback | ☐ Pass ☐ Fail | |
| TC-SEC-001 | Buffer Overflow | ☐ Pass ☐ Fail | |
| TC-INT-001 | Complete Lifecycle | ☐ Pass ☐ Fail | |

**Total Passed:** _____ / 10  
**Pass Rate:** _____%

---

## Critical Issues Found

| Issue # | Test Case | Severity | Description | Status |
|---------|-----------|----------|-------------|--------|
| | | | | |
| | | | | |
| | | | | |

---

## Testing Notes

1. **Before Testing:** Clear the `database/` directory to start fresh
2. **During Testing:** Document all unexpected behavior
3. **After Testing:** Keep database files for issue reproduction
4. **Priority:** Execute tests in order as some build upon previous test data
5. **Security:** TC-SEC-001 and TC-FS-301 are critical for data integrity
