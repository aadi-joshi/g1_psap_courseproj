# Personal Finance Tracker

## Made by CS-K Group 1
### Team Members:
| Name            | PRN       |
|-----------------|-----------|
| Aadi Joshi      | 12414579  |
| Sachin Aage     | 12411942  |
| Sujal Shahane   | 12414560  |
| Shaikh Anas     | 12412236  |
| Shambhavi Verma | 12413626  |
| Manav Sharma    | 12412516  |

## Overview: 
A C-based Personal Finance Tracker that allows users to manage their financial transactions with features like authentication, transaction management, reporting, and statistical analysis.

## Features:
- User Authentication: Sign-in, registration, and user verification.
- Transaction Management: Add, view, edit, and delete transactions.
- Reporting: Generate financial reports.
- Statistical Analysis: Analyze financial trends with mean, variance, and standard deviation.
- Data Visualization: Visualize transactions using matrix representation.
- Cross-Platform Compatibility: Works on different operating systems.

## File Breakdown:
### auth.c/h:
Handles user authentication with functions for sign-in, registration, and user verification. Uses file I/O for storing user credentials in CSV format, implements basic string operations and input validation. Core functions: signIn(), registerUser(), authenticateUser().
### colors.h:
Contains ANSI escape code definitions for terminal color output. Implements defines for RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, and RESET colors. Used throughout the application for visual feedback.
### main.c/h:
Program entry point and core structure definitions. Defines User and Transaction structs, handles the main menu loop, and coordinates between authentication and transaction modules. Uses standard C libraries (stdio.h, stdlib.h, string.h, math.h).
### transactions.c/h:
Core transaction management functionality with functions for CRUD operations, sorting, searching, and analysis. Implements file I/O for transaction storage, statistical calculations, and data visualization through matrix representation. Key functions include addTransaction(), viewTransactions(), generateReport(), analyzeTrends().
### utils.c/h:
Utility functions for input handling, screen clearing, color printing, and menu display. Implements cross-platform compatibility for screen clearing and input buffer management.
Mathematical/DS/Algorithm Concepts Used:

## Statistical Analysis: Mean, Variance, Standard Deviation
- Sorting: Bubble Sort (transactions by amount), Selection Sort (by date)
- Matrix Operations: 2D array for transaction visualization
- File I/O: Binary and text file operations
- Recursion: Total calculation
- Data Structures: Structs, Arrays
- Search Algorithms: Linear search for transactions

## Building the Project:
To compile the project and create an executable, follow these steps:

1. Ensure you have a C compiler installed (e.g., `gcc`).
2. Open a terminal or command prompt.
3. Navigate to the directory containing your project files.
4. Run the following command to compile the source files into an executable:

```sh
gcc -o finance_tracker main.c auth.c transactions.c utils.c
```

This will generate an executable named `finance_tracker`.

## Authentication Instructions:
When entering your password during sign-in or registration, the input will be masked with asterisks (*) for security. To toggle the visibility of the password, press the 'Tab' key while typing your password.