# Banking System Test Suite

This directory contains automated testing tools for the Banking System Application.

## Test Files

1. **test_suite.c** - Automated test suite with 10 critical test cases
2. **TEST_CASES.md** - Comprehensive test case documentation
3. **TOP_10_TEST_CASES.md** - Top 10 critical test cases

## Quick Start

### Using the Build Scripts (Recommended)

**Linux/Mac/Unix:**
```bash
chmod +x run_tests.sh
./run_tests.sh
```

**Windows:**
```bash
run_tests.bat
```

### Manual Compilation

**Compile the Test Suite:**

Windows (MinGW):
```bash
gcc -o test_suite.exe test_suite.c
```

Linux/Mac:
```bash
gcc -o test_suite test_suite.c -lm
```

**Run Automated Tests:**

Windows:
```bash
./test_suite.exe
```

Linux/Mac:
```bash
./test_suite
```

---

## Build Scripts

Two platform-specific scripts are provided:

### 1. Shell Script (`run_tests.sh`) - Linux/Mac/Unix

**Advantages:**
- ✅ Native shell scripting
- ✅ Fast execution
- ✅ Color-coded output
- ✅ No additional dependencies

**Usage:**
```bash
chmod +x run_tests.sh
./run_tests.sh
```

### 2. Batch File (`run_tests.bat`) - Windows

**Advantages:**
- ✅ Native Windows support
- ✅ No dependencies
- ✅ Menu-driven interface

**Usage:**
```bash
run_tests.bat
```

---

### Run Manual Test Helper

**Windows:**
```bash
./manual_test.exe
```

**Linux/Mac:**
```bash
./manual_test
```

## Automated Test Suite (`test_suite.c`)

The automated test suite includes the following tests:

1. **TC-AC-001**: Create Account with Valid Inputs
2. **TC-AC-205**: ID Length Validation (7-12 digits)
3. **TC-DP-001**: Deposit Money Successfully
4. **TC-WD-101**: Withdraw More Than Balance (Insufficient Funds)
5. **TC-RM-102**: Transfer with Fee (Current to Savings - 3%)
6. **TC-RM-203**: Transfer to Same Account (Prevention)
7. **TC-AD-001**: Delete Account Successfully
8. **TC-FS-301**: Transfer Rollback on Error
9. **TC-SEC-001**: Buffer Overflow Prevention
10. **TC-INT-001**: Complete Lifecycle Test

### Features

- ✅ Automated test execution
- ✅ Color-coded output (Pass/Fail/Skip)
- ✅ Test summary with pass rate
- ✅ Database setup and cleanup
- ✅ Account file verification
- ✅ Balance calculation verification

### Sample Output

```
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
✓ ALL TESTS PASSED!
```

## Test Case Coverage

### Functional Tests
- Account Creation (valid and invalid inputs)
- Deposit Operations
- Withdrawal Operations
- Money Transfer (with fee calculation)
- Account Deletion

### Validation Tests
- ID Length (7-12 digits) ⭐ NEW
- PIN Format (4 digits)
- Account Type (Savings/Current)
- Monetary Amount (format and range)
- Insufficient Funds

### Security Tests
- Buffer Overflow Prevention
- Input Validation
- Transaction Atomicity

### Integration Tests
- Complete Account Lifecycle
- Multi-operation Scenarios
- Fee Calculation (2% and 3%)

## Fee Structure Testing

The tests verify the following fee structure:
- **Savings → Savings**: No fee
- **Current → Current**: No fee
- **Savings → Current**: 2% fee
- **Current → Savings**: 3% fee

## Before Running Tests

1. **Backup your database** (if you have important data):
   ```bash
   cp -r database database_backup
   ```

2. **Clean the database** for testing:
   ```bash
   rm -f database/*        # Linux/Mac
   del /Q database\*       # Windows
   ```

## Troubleshooting

### Tests fail to create database directory
**Solution:** Ensure you have write permissions in the current directory.

### "Command not found" errors
**Solution:** Make sure gcc is installed and in your PATH.
```bash
gcc --version
```

### Color codes don't work on Windows
**Solution:** Use Windows Terminal or enable ANSI colors in Command Prompt:
```bash
reg add HKCU\Console /v VirtualTerminalLevel /t REG_DWORD /d 1
```

### Tests fail due to existing database files
**Solution:** Use option 3 in the build script to clean the database, or manually delete files:
```bash
rm -f database/*        # Linux/Mac
del /Q database\*       # Windows
```

## Contributing to Tests

When adding new test cases:

1. Add test function to `test_suite.c`
2. Use TEST_START, TEST_PASS, TEST_FAIL macros
3. Include setup and cleanup
4. Add verification assertions
5. Update this README

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
| ID | 123456 | Too short (< 7 digits) |
| ID | 1234567890123 | Too long (> 12 digits) |
| PIN | 123 | Too short (< 4 digits) |
| PIN | 12345 | Too long (> 4 digits) |
| Amount | -100 | Negative value |
| Amount | 100.123 | Too many decimals |

## Expected Test Duration

- Automated Tests: ~2-5 seconds
- Manual Tests (all 10): ~15-20 minutes
- Complete Lifecycle Test: ~5 minutes

## Support

If you encounter issues with the test suite:
1. Check the main application compiles correctly
2. Verify database directory exists
3. Review error messages carefully
4. Consult TOP_10_TEST_CASES.md for expected behavior

## Version History

- **v1.0** - Initial test suite with 10 critical tests
- Added ID length validation (7-12 digits)
- Added comprehensive documentation

---

**Last Updated:** November 5, 2025  
**Maintainer:** Banking System Development Team
