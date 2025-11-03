# Changelog

## Corrections

### Commit 7035e9e - Message Correction
**Original Message:** "Created the withdraw function as well as improved validation for deleting accounts"

**Correction:** This commit actually created the **deposit** function (fully implemented at line 479 in main.C), not the withdraw function. The withdraw function (at line 671) is only a placeholder stub in this commit.

**Details:**
- The `Deposit_Money()` function is fully implemented with:
  - Account validation
  - PIN verification
  - Balance checking
  - Transaction recording
- The `Withdraw_Money()` function is only a stub that prints a message

**Date of Correction:** 2025-11-03
