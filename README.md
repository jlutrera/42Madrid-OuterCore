# 📘 Project Portfolio

Welcome to my repository!  
Here you’ll find several projects developed during the **42 Common Core** curriculum.

---

## 📑 Table of Contents
- [🧮 Computor v1](#-computor-v1)
- [🖥️ Computor v2](#-computor-v2)
- [📊 ft_linear_regression](#-ft_linear_regression)
- [🌌 Ray Tracer (rt)](#-ray-tracer-rt)

---

## 🧮 Computor v1
> A program that solves polynomial equations (degree ≤ 3).

### ✨ Features
- Reduces equations to canonical form.
- Displays degree and discriminant polarity.
- Provides solution(s).

---

## 🖥️ Computor v2
> An instruction interpreter, similar to a shell, for advanced computations.

### 🔧 Mandatory Features
- Supports **rational numbers, complex numbers, matrices**.
- Variable assignment and reassignment with type inference.
- Assignment of variables to other variables.
- Equation solving (degree ≤ 2).
- Arithmetic operations: `+ - * / % ^ ! **`.
- Exit with `exit`.

### 🎁 Bonus Features
- Function plotting (`plot "expression"`).
- Trigonometric, exponential, logarithmic functions.
- Angle conversion (rad ↔ deg).
- Function composition.
- Variable management (`list`, `delete`).
- Matrix operations (+, -, scalar product, inverse, power).
- History, help, clear screen, visual mode.

### 📜 Available Commands
- `help` → Display help
- `exit` → Exit program
- `visual on/off` → Toggle intermediate calculations
- `clear` → Clear screen
- `solve "equation"` → Solve linear/quadratic/cubic equations
- `plot "function"` → Plot functions of `x`
- `delete` → Delete all stored variables
- `list [var1] [var2] ...` → Show stored variables
- `expression = ?` → Evaluate an expression

---

## 📊 ft_linear_regression
> Introduction to machine learning: predicting car prices using linear regression with gradient descent.

### 📖 Overview
Implements linear regression:  


\[
y = \theta_0 + \theta_1 \cdot x
\]



- Trains parameters with **gradient descent**.
- Evaluates with error metrics: MAE, MSE, RMSE, \(R^2\).

### 📈 Error Metrics Comparison
| Metric | Sensitivity to Outliers | Units | Interpretation |
|--------|--------------------------|-------|----------------|
| **MAE** | Low | Same as data | Average absolute error |
| **MSE** | High | Squared units | Penalizes large errors |
| **RMSE** | High | Same as data | Intuitive scale |
| **R²** | — | None | Variance explained |

### 🚨 Overfitting
- Occurs when the model memorizes training data instead of generalizing.
- Signs: perfect predictions on training but poor test performance.
- Solutions: simplify model, regularization (Ridge/Lasso/Elastic Net), cross-validation, early stopping.

---

## 🌌 Ray Tracer (rt)
> Generate images using the **ray tracing technique**.

### 🎨 Features
- Render scenes from a camera perspective.
- Support for geometric objects and light sources.
- Produces realistic computer-generated images.

---

## 📂 Suggested Repo Organization
To keep things clean:
