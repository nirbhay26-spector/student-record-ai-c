# AI-Assisted Student Record and Result Management System

**Course:** PRC1001 – Programming in C (B.Tech CSE, Semester I)  
**University:** University of Petroleum and Energy Studies (UPES)  
**Author:** Nirbhay Chauhan  
**SAP ID:** 590033662

---

## Project Description

A console-based, menu-driven **Student Record and Result Management System** written in C. The program manages student records, calculates CGPA, sorts data, and provides simple AI-assisted academic advice based on each student's performance.

This project was developed as part of the PRC1001 course assignment and demonstrates:
- Structured programming in C (structs, arrays, functions)
- Input validation and menu-driven design
- Sorting algorithms (bubble sort)
- Simple decision-making logic for academic advice (AI-assisted design)
- Use of GitHub for version control

---

## Features

### Part A – Core C Programming
| # | Feature | Function |
|---|---------|----------|
| 1 | Add a new student record | `addStudent()` |
| 2 | Display all student records | `displayAll()` |
| 3 | Search a student by SAP ID | `searchStudent()` |
| 4 | Delete a student record | `deleteStudent()` |
| 5 | Calculate CGPA of each student | `calcCGPA()`, `displayAllCGPA()` |
| 6 | Average CGPA year-wise | `yearWiseAverage()` |
| 7 | Sort and display by SAP ID (ascending) | `displaySortedBySap()` |
| 8 | Sort and display by Name (A–Z) | `displaySortedByName()` |

### Part B – AI-Assisted Academic Advisor
The program includes a simple **Academic Advisor** feature (`giveAdvice()`) that classifies each student into one of four categories based on their CGPA and gives a personalised recommendation:

| CGPA Range | Category | Sample Advice |
|------------|----------|---------------|
| 8.5 – 10.0 | Excellent Performance | Maintain your current study pattern. |
| 7.0 – 8.49 | Good Performance | Keep revising regularly and aim for 8.5+. |
| 5.0 – 6.99 | Needs Improvement | Focus more on subjects with lower SGPA. |
| Below 5.0  | Requires Immediate Attention | Meet your faculty mentor and make a study plan. |

The categories and advice messages were designed with the help of an AI tool (ChatGPT) and then reviewed and adjusted manually. See [AI_USAGE_LOG.md](AI_USAGE_LOG.md) for details.

---

## How to Compile and Run

### Prerequisites
- A C compiler (GCC recommended)

### Steps

```bash
# Clone the repository
git clone https://github.com/nirbhay26-spector/student-record-ai-c.git
cd student-record-ai-c

# Compile
gcc -Wall -o student_record 590033662.c

# Run
./student_record
```

The program starts with 5 pre-loaded sample student records. Use the menu to explore all features.

---

## Sample Input / Output

Sample input and output files are available in the [`tests/`](tests/) folder:
- [`tests/sample_input.txt`](tests/sample_input.txt) – Menu choices fed to the program
- [`tests/sample_output.txt`](tests/sample_output.txt) – Complete console output

**Example – Academic Advisor output (4 CGPA cases):**

```
Aarav Sharma (SAP 590010001) | CGPA = 9.00
  Category : Excellent Performance
  Advice   : Excellent performance - maintain your current study pattern.

Diya Verma (SAP 590010002) | CGPA = 7.40
  Category : Good Performance
  Advice   : Good performance - keep revising regularly and aim for 8.5+.

Kabir Singh (SAP 590010003) | CGPA = 5.77
  Category : Needs Improvement
  Advice   : Needs improvement - focus more on subjects with lower SGPA (weakest: semester 2).

Meera Nair (SAP 590010004) | CGPA = 4.42
  Category : Requires Immediate Attention
  Advice   : Requires immediate attention - meet your faculty mentor and make a study plan (weakest: semester 4).
```

---

## Repository Structure

```
student-record-ai-c/
├── 590033662.c            # Main C source file
├── README.md              # This file
├── AI_USAGE_LOG.md        # Log of AI tool usage
└── tests/
    ├── sample_input.txt   # Sample input for the program
    └── sample_output.txt  # Corresponding output
```

---

## Technologies Used

- **Language:** C (C99)
- **Compiler:** GCC
- **Version Control:** Git & GitHub
- **AI Tool:** ChatGPT (used as a learning assistant for designing the academic advisor logic and generating test cases)

---

## Author

**Nirbhay Chauhan**  
B.Tech CSE, Semester I  
University of Petroleum and Energy Studies (UPES)  
SAP ID: 590033662
