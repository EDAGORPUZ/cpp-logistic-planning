# C++ Logistics Route Planning Simulation

This project is a grid-based logistics planning simulation developed in C++ for the ISE105 - Introduction to Programming course at Sakarya University, Department of Information Systems Engineering.

## 📌 Project Description

A courier starts at (0,0) on a 10x10 cost matrix and visits 5 randomly placed customers. Each cell represents a movement cost. The courier moves step-by-step toward each customer, accumulating delivery cost, and finally returns to the starting point.

## 🎯 Objectives

- Simulate path planning in a grid
- Visualize courier and customer locations with terminal coloring
- Track and print cumulative cost
- Save customer data and total cost to `Cost.txt`

## 🧠 Concepts & Tools Used

- 2D arrays
- Structs and pointers
- ANSI escape codes for terminal colors
- Random number generation
- File output (`ofstream`)

## 🖥️ How to Run

1. Compile:
   ```bash
   g++ cpp-logistic-planning.cpp -o logistics
