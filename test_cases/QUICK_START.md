# Quick Start Guide - Test Suite Scripts

## 🚀 Choose Your Platform

### Windows Users
```bash
run_tests.bat
```

### Linux/Mac Users
```bash
chmod +x run_tests.sh
./run_tests.sh
```

---

## 📝 What Each Script Does

Both scripts provide the same functionality:

1. **Compile Automated Test Suite** - Build test_suite executable
2. **Run Automated Test Suite** - Execute all 10 automated tests
3. **Clean Database** - Remove all test data
4. **Build and Run All Tests** - One-click testing
5. **Compile Main Application** - Build main banking app
6. **Exit** - Close the script

---

## 🎯 Recommended Workflow

### First Time Setup:
```bash
# 1. Navigate to test_cases directory
cd test_cases

# 2. Run the script (choose your platform)
./run_tests.sh              # Linux/Mac
run_tests.bat               # Windows

# 3. From the menu, select option 4
# "Build and Run All Tests"
```

### Regular Testing:
```bash
# Quick test after code changes
./run_tests.sh              # Linux/Mac
run_tests.bat               # Windows

# Then select option 2: "Run Automated Test Suite"
```

---

## 🔧 Requirements

### Shell Script (`run_tests.sh`):
- GCC compiler installed
- Bash shell
- Works on: Linux, macOS, WSL on Windows

### Batch File (`run_tests.bat`):
- GCC compiler installed (MinGW recommended)
- Works on: Windows

---

## 🆘 Troubleshooting

### "gcc: command not found"
**Solution:** Install GCC compiler
- Windows: Install MinGW or MSYS2
- Linux: `sudo apt install gcc` (Ubuntu/Debian)
- Mac: Install Xcode Command Line Tools

### "Permission denied" (Linux/Mac)
**Solution:** Make script executable
```bash
chmod +x run_tests.sh
```

### Colors don't show on Windows
**Solution:** Use Windows Terminal for better color support

---

## 📊 Quick Command Reference

| Task | Windows | Linux/Mac |
|------|---------|-----------|
| Run build script | `run_tests.bat` | `./run_tests.sh` |
| Make executable | N/A | `chmod +x run_tests.sh` |
| Compile manually | `gcc -o test_suite.exe test_suite.c` | `gcc -o test_suite test_suite.c -lm` |
| Run tests manually | `./test_suite.exe` | `./test_suite` |

---

## 💡 Tips

1. **Use the build script** for easiest setup and testing
2. **Select option 4** for first-time setup (builds and runs tests)
3. **Clean database** (option 3) before running tests for consistent results
4. **Run automated tests** (option 2) after making code changes

---

## 📖 Full Documentation

See `README.md` for complete documentation and test case details.
