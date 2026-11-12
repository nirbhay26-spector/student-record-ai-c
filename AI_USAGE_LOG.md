# AI Usage Log

**Project:** AI-Assisted Student Record and Result Management System  
**Author:** Nirbhay Chauhan (SAP ID: 590033662)  
**Course:** PRC1001 – Programming in C (B.Tech CSE, Semester I), UPES

---

This document records every instance where an AI tool was used during the development of this project. AI was used as a **learning assistant** — all AI-generated suggestions were reviewed, verified, and modified before being incorporated into the final code.

---

## Usage Log

| # | AI Tool | Prompt / Question Asked | How I Used / Verified the Response |
|---|---------|------------------------|------------------------------------|
| 1 | ChatGPT | "Suggest simple CGPA-based academic advice categories for a student management system. The program should classify students based on their CGPA and give different recommendations." | ChatGPT suggested four categories: Excellent (≥ 9.0), Good (7.0–8.99), Average (5.0–6.99), and Poor (< 5.0). I adjusted the thresholds to Excellent (≥ 8.5), Good (7.0–8.49), Needs Improvement (5.0–6.99), and Requires Immediate Attention (< 5.0) to better fit the UPES grading scale. I also renamed the categories to sound more supportive. Implemented the logic using `if-else` in the `giveAdvice()` function. |
| 2 | ChatGPT | "Give test cases for a CGPA calculation function that averages all non-zero SGPA values from an array of 8 semesters." | ChatGPT provided 5 test cases including edge cases (all zeros, single semester, all 8 semesters filled). I tested each one manually by running my `calcCGPA()` function and verified the results matched. I also added a test case where only middle semesters had values to confirm the function skips zeros correctly. |
| 3 | ChatGPT | "What are good advice messages to give students who need to improve their grades in college?" | ChatGPT suggested messages like "Seek tutoring", "Create a study schedule", "Focus on weak areas". I picked the most relevant ideas and simplified them into short messages suitable for a C `printf()` statement. For example, I combined the "focus on weak areas" idea with my `weakestSemester()` function to print which semester was the weakest. |
| 4 | ChatGPT | "How to write a good README.md for a C programming project on GitHub?" | ChatGPT provided a template with sections like Description, How to Run, Features, and Author. I used the structure as a guide but wrote all the content myself based on my actual project. |
| 5 | ChatGPT | "How to validate a 10-digit phone number and email address in C without using regex?" | ChatGPT suggested checking the string length and using `isdigit()` for phone numbers, and checking for '@' and '.' characters for email. I implemented these ideas in the `isValidPhone()` and `isValidEmail()` functions. I tested both with valid and invalid inputs to make sure they work correctly. |

---

## Summary

- **AI tools used:** ChatGPT
- **Purpose:** Understanding concepts, designing the academic advisor logic, generating test cases, and improving documentation structure.
- **Important:** No code was blindly copied from AI. Every suggestion was understood, tested, and adapted to fit the project requirements. The final C code and all logic decisions are my own work.
