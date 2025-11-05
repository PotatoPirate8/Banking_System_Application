@echo off
REM Test Suite Build and Run Script for Windows
REM This script compiles and runs the banking system test suite

echo ========================================
echo   Banking System - Test Suite Builder
echo ========================================
echo.

:menu
echo Select an option:
echo 1. Compile Automated Test Suite
echo 2. Run Automated Test Suite
echo 3. Clean Database
echo 4. Build and Run All Tests
echo 5. Compile Main Application
echo 6. Exit
echo.
set /p choice="Enter choice (1-6): "

if "%choice%"=="1" goto compile_auto
if "%choice%"=="2" goto run_auto
if "%choice%"=="3" goto clean_db
if "%choice%"=="4" goto build_all
if "%choice%"=="5" goto compile_main
if "%choice%"=="6" goto end
goto invalid

:compile_auto
echo.
echo Compiling Automated Test Suite...
gcc -o test_suite.exe test_suite.c
if %errorlevel% equ 0 (
    echo [SUCCESS] Test suite compiled successfully!
) else (
    echo [ERROR] Compilation failed!
)
echo.
pause
cls
goto menu

:run_auto
echo.
if not exist test_suite.exe (
    echo [ERROR] test_suite.exe not found. Please compile first.
    echo.
    pause
    cls
    goto menu
)
echo Running Automated Test Suite...
echo.
test_suite.exe
echo.
pause
cls
goto menu

:run_auto
echo.
if not exist test_suite.exe (
    echo [ERROR] test_suite.exe not found. Please compile first.
    echo.
    pause
    cls
    goto menu
)
echo Running Automated Test Suite...
echo.
test_suite.exe
echo.
pause
cls
goto menu

:clean_db
echo.
echo Cleaning database directory...
del /Q ..\database\* 2>NUL
if %errorlevel% equ 0 (
    echo [SUCCESS] Database cleaned!
) else (
    echo [INFO] Database already clean or doesn't exist.
)
echo.
pause
cls
goto menu

:build_all
echo.
echo Building all components...
echo.

echo [1/2] Compiling Automated Test Suite...
gcc -o test_suite.exe test_suite.c
if %errorlevel% neq 0 (
    echo [ERROR] Test suite compilation failed!
    pause
    cls
    goto menu
)

echo [2/2] Cleaning database...
del /Q ..\database\* 2>NUL

echo.
echo [SUCCESS] Test suite built successfully!
echo.
echo Running Automated Tests...
echo.
test_suite.exe
echo.
pause
cls
goto menu

:compile_main
echo.
echo Compiling Main Banking Application...
cd ..
gcc -o main.exe main.C
if %errorlevel% equ 0 (
    echo [SUCCESS] Main application compiled successfully!
) else (
    echo [ERROR] Compilation failed!
)
cd test_cases
echo.
pause
cls
goto menu

:invalid
echo.
echo [ERROR] Invalid choice! Please enter 1-6.
echo.
pause
cls
goto menu

:end
echo.
echo Exiting Test Suite Builder.
echo Goodbye!
echo.
exit /b 0
