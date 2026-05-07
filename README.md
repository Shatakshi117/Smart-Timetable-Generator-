# Smart Timetable Generator

A web-based **Smart Timetable Generator** that automatically creates a conflict-free weekly class schedule using **Backtracking**, **Constraint Satisfaction**, and **Heuristic Scheduling** techniques.

The system intelligently distributes subjects and labs while satisfying constraints such as:
- Break management
- Lab continuity
- Subject frequency
- Daily scheduling limits

This project demonstrates the practical implementation of:
- Recursion
- Backtracking
- Constraint Satisfaction Problem (CSP)
- Dynamic DOM Manipulation

---

# Features

- Automatic timetable generation
- Smart lab scheduling with continuous slots
- Break management system
- Configurable maximum labs per day
- Saturday inclusion/exclusion support
- Dynamic timetable rendering
- Responsive and interactive UI
- Constraint-based conflict handling

---

# Technologies Used

- HTML5
- CSS3
- JavaScript

---

# Core Concepts Used

- Recursion
- Backtracking Algorithm
- Constraint Satisfaction Problem (CSP)
- Heuristic Optimization
- Dynamic DOM Manipulation

---

# Algorithm Used

The project uses a **recursive backtracking algorithm** to generate valid timetable combinations.

A heuristic approach is applied by prioritizing LAB subjects first to reduce scheduling conflicts and improve efficiency.

## Constraints Handled

- No subject repetition in the same day
- No scheduling during breaks
- Continuous slot allocation for labs
- Maximum labs per day limit
- Empty slot validation before assignment

---

# Project Structure

```text
Smart-Timetable-Generator/
│
├── index.html
├── README.md
```

---

# How to Run

## Method 1 — Direct Run

1. Download or clone the repository

```bash
git clone https://github.com/your-username/Smart-Timetable-Generator.git
```

2. Open the project folder

3. Run `index.html` in any web browser

---

## Method 2 — VS Code Live Server

1. Open the project folder in VS Code
2. Install the **Live Server** extension
3. Right click on `index.html`
4. Select:

```text
Open with Live Server
```

---

# Working Principle

1. User enters:
   - Subject name
   - Teacher name
   - Weekly frequency

2. Subjects are expanded into a scheduling pool according to frequency.

3. LAB subjects are prioritized using heuristic sorting.

4. A recursive backtracking algorithm assigns subjects into timetable slots.

5. Constraints are checked before every assignment.

6. If conflict occurs, the algorithm backtracks and tries another possible arrangement.

7. The final timetable is dynamically rendered on the webpage.

---

# Sample Constraints

| Constraint | Description |
|---|---|
| Subject Repetition | Same subject cannot repeat in a day |
| Break Protection | No class can be scheduled during break |
| Lab Continuity | Labs require two continuous slots |
| Daily Lab Limit | Limits maximum labs per day |

---

# Complexity Analysis

## Time Complexity

Worst Case:

```text
O(Slots ^ Subjects)
```

Due to recursive backtracking.

---

## Space Complexity

```text
O(Days × Slots)
```

Used for timetable matrix and recursion stack.

---

# Future Enhancements

- Teacher clash detection
- Classroom allocation system
- PDF/Excel export
- Database integration
- Multi-section timetable generation
- AI-based optimization techniques

---
