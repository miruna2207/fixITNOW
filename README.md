# Electronic Service Management System

A comprehensive C++ application for managing electronic appliance repair services, including employee management, appliance catalogue management, service request processing, and reporting.

##  Project Overview

This system simulates an electronic appliance repair service where:
- **Employees** (technicians) are managed with their qualifications and salaries
- **Electronic-appliances** are catalogued with repair specifications
- **Service requests** are processed through a queue system
- **Reports** provide insights into service operations

##  Project Structure

project/
├── main.cpp # Main program with menu interface
├── employees/ # Employee-related classes
├── electronics/ # Electronic appliance classes
├── GestiuneAngajati/ # Employee management module
├── GestiuneElectrocasnice/ # Appliance management module
├── GestiuneCereri/ # Service request management
├── Raportari/ # Reporting module
├── tests/ # Test data sets
├── output/ # Generated CSV reports (created at runtime)
└── Makefile # Build configuration

#  Features

### 1. **Employee Management**
- Add/remove employees (via file or manual input)
- Modify employee details
- Search by CNP (Personal Numeric Code)
- Display all employees
- Validate employee qualifications

### 2. **Electronic Appliance Management**
- Load appliance catalogue from CSV files
- Add/remove appliance models
- Display repair-compatible appliances
- View completed repairs
- Rejected appliance statistics

### 3. **Service Request Processing**
- Load service requests from CSV
- Add manual service requests
- Automated simulation with TIC (time unit) system
- Queue management for pending requests
- Team assignment and rejection handling

### 4. **Reporting System**
- Top 3 highest-paid employees
- Technician with longest repair duration
- Ordered pending service requests
- CSV report generation in `output/` folder


##  Test Data Sets

The system includes multiple test scenarios:

| Set | Description |
|-----|-------------|
| **Set 1** | All files contain input errors but functional |
| **Set 2** | All working correctly |
| **Set 3** | Long queue simulation |
| **Set 4** | Team rejection scenarios |
| **Set 5** | Long repair durations |
| **Set 6** | team rejections( another case) |
| **Set 7** | Large data + catalogue inputs without technicians able to fix |
| **Set 8** | Normal size + rejected (incomplete) requests |

### Test Files:
- **Employees**: `angajati.csv` (all accepted), `angajati_rau.csv` (mix of accepted/rejected)
- **Appliances**: `electrocasnice_1_bun.csv` (all good), `electrocasnice_rau_1.csv` (some errors), `catalog_rau.csv` (all possible errors)
- **Requests**: `cereri_bune_1.csv` (all processable), `cereri_rele_1.csv` and `cereri_rele_2.csv` (input errors)

##  Building and Running

### Prerequisites
- GCC/G++ compiler with C++17 support
- Windows/Linux/macOS environment

### Build Commands

```bash
# Compile the project
mingw32-make

# Clean build files
mingw32-make clean

# Run the program
mingw32-make run

# Rebuild from scratch
mingw32-make rebuild

For Manual Compilation (32-bit compilation)

g++ -std=c++17 -Wall -Wextra -O2 -g -m32 -I. -Iemployees -Ielectronics -IGestiuneAngajati -IGestiuneElectrocasnice -IGestiuneCereri -IRaportari *.cpp employees/*.cpp electronics/*.cpp GestiuneAngajati/*.cpp GestiuneElectrocasnice/*.cpp GestiuneCereri/*.cpp Raportari/*.cpp -o service.exe


## Key Features in Detail:
# ** Simulation System ** #:

TIC-based time progression

Automatic team assignment

Queue processing

Completion tracking


# ** CSV Report Generation:
Reports are saved in the output/ folder

Includes statistical data and performance metrics

Can be imported into spreadsheet software

## Technical Details

Language: C++17

Design Patterns: Singleton (ServiceManager)

Data Structures: Custom collections and STL containers

File I/O: CSV parsing with validation

Memory Management: Smart pointers and RAII principles


## Modification Guide

** To use different test data:**

Update file paths in main.cpp menu functions

Ensure CSV files follow the expected format

Recompile with make rebuild