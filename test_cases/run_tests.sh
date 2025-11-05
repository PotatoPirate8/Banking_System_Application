#!/bin/bash
# Test Suite Build and Run Script for Linux/Mac/Unix
# This script compiles and runs the banking system test suite

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

print_header() {
    echo -e "${CYAN}========================================${NC}"
    echo -e "${CYAN}  Banking System - Test Suite Builder${NC}"
    echo -e "${CYAN}========================================${NC}"
    echo
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

print_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

compile_auto() {
    echo
    echo "Compiling Automated Test Suite..."
    if gcc -o test_suite test_suite.c -lm; then
        print_success "Test suite compiled successfully!"
    else
        print_error "Compilation failed!"
    fi
    echo
    read -p "Press Enter to continue..."
}

run_auto() {
    echo
    if [ ! -f "test_suite" ]; then
        print_error "test_suite not found. Please compile first."
        echo
        read -p "Press Enter to continue..."
        return
    fi
    echo "Running Automated Test Suite..."
    echo
    ./test_suite
    echo
    read -p "Press Enter to continue..."
}

clean_db() {
    echo
    echo "Cleaning database directory..."
    
    # Get the parent directory path
    PARENT_DIR="$(dirname "$(pwd)")"
    DB_DIR="${PARENT_DIR}/database"
    
    if [ -d "$DB_DIR" ]; then
        rm -f "$DB_DIR"/* 2>/dev/null
        print_success "Database cleaned!"
    else
        print_info "Database directory doesn't exist."
    fi
    echo
    read -p "Press Enter to continue..."
}

build_and_run() {
    echo
    echo "Building and running test suite..."
    echo
    
    echo "[1/2] Compiling Automated Test Suite..."
    if ! gcc -o test_suite test_suite.c -lm; then
        print_error "Test suite compilation failed!"
        read -p "Press Enter to continue..."
        return
    fi
    
    echo "[2/2] Cleaning database..."
    PARENT_DIR="$(dirname "$(pwd)")"
    DB_DIR="${PARENT_DIR}/database"
    rm -f "$DB_DIR"/* 2>/dev/null
    
    echo
    print_success "Test suite built successfully!"
    echo
    echo "Running Automated Tests..."
    echo
    ./test_suite
    echo
    read -p "Press Enter to continue..."
}

compile_main() {
    echo
    echo "Compiling Main Banking Application..."
    
    # Get the parent directory path
    PARENT_DIR="$(dirname "$(pwd)")"
    CURRENT_DIR="$(pwd)"
    
    # Change to parent directory
    cd "$PARENT_DIR" || {
        print_error "Failed to access parent directory"
        read -p "Press Enter to continue..."
        return
    }
    
    if gcc -o main main.C -lm; then
        print_success "Main application compiled successfully!"
    else
        print_error "Compilation failed!"
    fi
    
    # Return to test_cases directory
    cd "$CURRENT_DIR" || exit
    
    echo
    read -p "Press Enter to continue..."
}

show_menu() {
    clear
    print_header
    echo "Select an option:"
    echo "1. Compile Automated Test Suite"
    echo "2. Run Automated Test Suite"
    echo "3. Clean Database"
    echo "4. Build and Run All Tests"
    echo "5. Compile Main Application"
    echo "6. Exit"
    echo
    read -p "Enter choice (1-6): " choice
}

# Main loop
while true; do
    show_menu
    
    case $choice in
        1)
            compile_auto
            ;;
        2)
            run_auto
            ;;
        3)
            clean_db
            ;;
        4)
            build_and_run
            ;;
        5)
            compile_main
            ;;
        6)
            echo
            echo "Exiting Test Suite Builder."
            echo "Goodbye!"
            echo
            exit 0
            ;;
        *)
            echo
            print_error "Invalid choice! Please enter 1-6."
            echo
            read -p "Press Enter to continue..."
            ;;
    esac
done
