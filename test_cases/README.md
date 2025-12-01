<div align="center">

# Banking System Test Suite

[![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![GCC](https://img.shields.io/badge/GCC-Compiler-blue?style=for-the-badge)](https://gcc.gnu.org/)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20Mac-lightgrey?style=for-the-badge)](README.md)

**Automated testing framework for the Banking System Application**

[Features](#features) | [Quick Start](#quick-start) | [Test Cases](#test-cases) | [Documentation](#documentation)

</div>

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Quick Start](#quick-start)
- [Test Cases](#test-cases)
- [Build Scripts](#build-scripts)
- [Test Coverage](#test-coverage)
- [Documentation](#documentation)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)

## Overview

This directory contains a comprehensive automated testing suite for the Banking System Application. The test framework validates critical functionality including account operations, transaction processing, fee calculations, and security measures.

### Test Files

| File | Description |
|------|-------------|
| `test_suite.c` | Automated test suite with 10 critical test cases |
| `TEST_CASES.md` | Comprehensive test case documentation |
| `run_tests.sh` | Linux/Mac build and execution script |
| `run_tests.bat` | Windows build and execution script |

## Features

- **10 Automated Test Cases** - Comprehensive coverage of critical functionality
- **Cross-Platform Support** - Works on Windows, Linux, and macOS
- **Color-Coded Output** - Visual feedback with ANSI color codes
- **Detailed Reporting** - Test summaries with pass rates
- **Automatic Cleanup** - Database setup and teardown
- **Zero Dependencies** - Only requires GCC compiler
- **Menu-Driven Interface** - Easy-to-use build scripts

## Quick Start

### Option 1: Using Build Scripts (Recommended)

#### Linux/Mac/Unix
```bash
cd test_cases
chmod +x run_tests.sh
./run_tests.sh
# Select option 4: "Build and Run All Tests"
```

#### Windows
```cmd
cd test_cases
run_tests.bat
REM Select option 4: "Build and Run All Tests"
```

### Option 2: Manual Compilation

<details>
<summary>Click to expand manual compilation instructions</summary>

#### Compile Test Suite

**Windows (MinGW):**
```bash
gcc -o test_suite.exe test_suite.c -lm
```

**Linux/Mac:**
```bash
gcc -o test_suite test_suite.c -lm
```

#### Run Tests

**Windows:**
```bash
./test_suite.exe
```

**Linux/Mac:**
```bash
./test_suite
```

</details>

---

## Test Cases

The automated test suite includes **10 critical test cases** covering all major functionality:

| # | Test ID | Description | Category |
|---|---------|-------------|----------|
| 1 | TC-AC-001 | Create Account with Valid Inputs | Account Creation |
| 2 | TC-AC-205 | ID Length Validation (7-12 digits) | Validation NEW |
| 3 | TC-DP-001 | Deposit Money Successfully | Deposits |
| 4 | TC-WD-101 | Withdraw More Than Balance | Withdrawals |
| 5 | TC-RM-102 | Transfer with Fee (Current to Savings 3%) | Transfers |
| 6 | TC-RM-203 | Transfer to Same Account Prevention | Validation |
| 7 | TC-AD-001 | Delete Account Successfully | Account Deletion |
| 8 | TC-FS-301 | Transfer Rollback on Error | Fault Tolerance |
| 9 | TC-SEC-001 | Buffer Overflow Prevention | Security |
| 10 | TC-INT-001 | Complete Lifecycle Test | Integration |

### Sample Output

```ansi
========================================
  BANKING SYSTEM - AUTOMATED TEST SUITE
========================================

[TEST] TC-AC-001: Create Account with Valid Inputs
[PASS] Account created successfully with all fields

[TEST] TC-AC-205: ID Length Validation
[PASS] ID length validation logic verified

...

========================================
         TEST EXECUTION SUMMARY         
========================================
Total Tests:   10
Passed:        10
Failed:        0
Skipped:       0
Pass Rate:     100.00%
========================================
ALL TESTS PASSED!
```

---

## Build Scripts

Both build scripts provide a **menu-driven interface** with 6 options:

```
1. Compile Automated Test Suite
2. Run Automated Test Suite
3. Clean Database
4. Build and Run All Tests
5. Compile Main Banking System
6. Exit
```

### Shell Script (`run_tests.sh`) - Linux/Mac/Unix

| Feature | Status |
|---------|--------|
| Native shell scripting | Yes |
| Fast execution | Yes |
| Color-coded output | Yes |
| No additional dependencies | Yes |

**Usage:**
```bash
chmod +x run_tests.sh
./run_tests.sh
```

### Batch File (`run_tests.bat`) - Windows

**Usage:**
```cmd
run_tests.bat
```

---

## Test Coverage

### Functional Testing
- Account Creation (valid and invalid inputs)
- Deposit Operations
- Withdrawal Operations
- Money Transfer (with fee calculation)
- Account Deletion

### Validation Testing
- ID Length (7-12 digits) **NEW**
- PIN Format (4 digits)
- Account Type (Savings/Current)
- Monetary Amount (format and range)
- Insufficient Funds

### Security Testing
- Buffer Overflow Prevention
- Input Validation
- Transaction Atomicity

### Integration Testing
- Complete Account Lifecycle
- Multi-operation Scenarios
- Fee Calculation Verification

### Fee Structure

The test suite verifies the following fee structure:

| From | To | Fee |
|------|-----|-----|
| Savings | Savings | 0% |
| Current | Current | 0% |
| Savings | Current | 2% |
| Current | Savings | 3% |

---

## Documentation

| Document | Purpose |
|----------|---------|
| [TEST_CASES.md](TEST_CASES.md) | Comprehensive test case documentation (200+ cases) |

---

## Test Data Reference

### Valid Test Accounts

| Name | ID | Type | PIN | Purpose |
|------|-----|------|-----|---------|
| John Smith | 1234567 | Savings | 1234 | Basic account creation |
| Alice Deposit | 7777777 | Savings | 1111 | Deposit testing |
| Bob Withdraw | 8888888 | Current | 2222 | Withdrawal testing |
| Sender Current | 9999991 | Current | 3333 | Transfer sender |
| Receiver Savings | 9999992 | Savings | 4444 | Transfer receiver |

### Invalid Test Data

| Field | Invalid Value | Reason |
|-------|---------------|--------|
| ID | `123456` | Too short (< 7 digits) |
| ID | `1234567890123` | Too long (> 12 digits) |
| PIN | `123` | Too short (< 4 digits) |
| PIN | `12345` | Too long (> 4 digits) |
| Amount | `-100` | Negative value |
| Amount | `100.123` | Too many decimals |

---

## Before Running Tests

> **Warning:** Tests will modify the database directory. Make sure to backup important data!

1. **Backup your database** (if you have important data):
   ```bash
   cp -r ../database ../database_backup        # Linux/Mac
   xcopy ..\database ..\database_backup /E/I   # Windows
   ```

2. **Clean the database** for testing:
   ```bash
   rm -f ../database/*        # Linux/Mac
   del /Q ..\database\*       # Windows
   ```

   Or use **Option 3** in the build scripts menu.

---

## Troubleshooting

<details>
<summary><b>Tests fail to create database directory</b></summary>

**Solution:** Ensure you have write permissions in the parent directory.

```bash
# Check permissions
ls -la ../database          # Linux/Mac

# Create directory manually if needed
mkdir -p ../database        # Linux/Mac
mkdir ..\database           # Windows
```
</details>

<details>
<summary><b>"Command not found" or "gcc not recognized" errors</b></summary>

**Solution:** Make sure GCC is installed and in your PATH.

```bash
# Check GCC installation
gcc --version

# Install GCC if needed
sudo apt-get install gcc    # Ubuntu/Debian
brew install gcc            # macOS
# Windows: Install MinGW from mingw.org
```
</details>

<details>
<summary><b>Color codes don't work on Windows</b></summary>

**Solution:** Use Windows Terminal or enable ANSI colors in Command Prompt:

```cmd
reg add HKCU\Console /v VirtualTerminalLevel /t REG_DWORD /d 1
```

Or use **Windows Terminal** (recommended) instead of Command Prompt.
</details>

<details>
<summary><b>Tests fail due to existing database files</b></summary>

**Solution:** Use **Option 3** in the build script to clean the database, or manually delete files:

```bash
rm -f ../database/*         # Linux/Mac
del /Q ..\database\*        # Windows
```
</details>

<details>
<summary><b>Permission denied when running shell script</b></summary>

**Solution:** Make the script executable:

```bash
chmod +x run_tests.sh
```
</details>

<details>
<summary><b>Math library linking errors</b></summary>

**Solution:** Include the `-lm` flag when compiling:

```bash
gcc -o test_suite test_suite.c -lm
```
</details>

---

## Contributing

When adding new test cases:

1. Add test function to `test_suite.c`
2. Use `TEST_START`, `TEST_PASS`, `TEST_FAIL` macros
3. Include setup and cleanup in your test
4. Add verification assertions (`ASSERT_*`)
5. Update this README with the new test
6. Document the test case in `TEST_CASES.md`

### Test Function Template

```c
int test_your_feature() {
    TEST_START("TC-XX-XXX: Your Test Description");
    setup_test_environment();
    
    // Your test logic here
    
    ASSERT_TRUE(condition, "Your assertion message");
    
    TEST_PASS("Your success message");
    return 1;
}
```

---

## Performance Metrics

| Test Type | Duration |
|-----------|----------|
| Automated Test Suite | 2-5 seconds |
| Single Test Case | <1 second |
| Complete Lifecycle Test | ~1 second |
| Full Build & Test | 5-10 seconds |

---

## Test Results Summary

After running tests, you'll see:
- **Total Tests** - Number of tests executed
- **Passed** - Tests that completed successfully
- **Failed** - Tests that encountered errors
- **Skipped** - Tests that were skipped
- **Pass Rate** - Percentage of tests passed

---

## Support

If you encounter issues with the test suite:

1. Check this README for troubleshooting steps
2. Consult [TEST_CASES.md](TEST_CASES.md) for test details and expected behavior
3. Verify the main application compiles correctly
4. Ensure database directory exists in parent folder
5. Review error messages carefully

---

<div align="center">

**Banking System Test Suite**

Made for COMP1312 Coursework

[Back to Top](#-banking-system-test-suite)

</div>
