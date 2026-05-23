# Linear Algebra Library (C++)

This project implements a compact and efficient linear algebra library in **C++**, focused on core operations used in scientific computing, computer graphics, numerical methods, and machine learning.

# Table of Contents

1. [Basic Algebra Operations](#1-basic-algebra-operations)  
   1.1 [Vector Addition, Subtraction, Scalar Multiplication](#11-vector-addition-subtraction-and-scalar-multiplication)  
   1.2 [Linear Combination](#12-linear-combination)  
   1.3 [Linear Interpolation](#13-linear-interpolation)  
   1.4 [Dot Product](#14-dot-product)  
   1.5 [Norms](#15-norms)  
   1.6 [Cosine of the Angle](#16-cosine-of-the-angle-between-two-vectors)  
   1.7 [Cross Product](#17-cross-product-of-two-3d-vectors)

2. [Matrix Library](#2-matrix-library)  
   2.1 [Matrix–Matrix Multiplication](#21-matrixmatrix-multiplication)  
   2.2 [Matrix–Vector Multiplication](#22-matrixvector-multiplication)  
   2.3 [Trace](#23-trace)  
   2.4 [Transpose](#24-transpose)  
   2.5 [Row Echelon Form (REF)](#25-row-echelon-form-ref)  
   2.6 [Determinant](#26-determinant)  
   2.7 [Inverse](#27-inverse)  
   2.8 [Rank](#28-rank)

3. [Projection Matrices](#3-projection-matrices-opengl-vs-directx-lhrh)  
   3.1 [OpenGL](#31-opengl-conventions)  
   3.2 [DirectX Left-Handed](#32-directx-conventions-left-handed)  
   3.3 [DirectX Right-Handed](#33-directx-conventions-right-handed)  
   3.4 [Parameter Validation](#34-parameter-validation)  
   3.5 [Homogeneous Vectors](#35-use-with-homogeneous-vectors)

---
   
# 1. Basic Algebra Operations

This module implements the fundamental algebraic operations used throughout the
library: vector addition, subtraction, scalar multiplication, dot product,
norms, and angle computation. All operations are defined for generic types `K`,
including real and complex numbers.

## 1.1. Vector Addition, Subtraction and Scalar Multiplication

Given two vectors of equal size:
\
 u = (u₁, u₂, …, uₙ)  
 v = (v₁, v₂, …, vₙ)

and a scalar λ:
$$
 u + v = (u₁ + v₁, u₂ + v₂, …, uₙ + vₙ)
$$
$$
 u − v = (u₁ − v₁, u₂ − v₂, …, uₙ − vₙ)
$$
$$
 λ·u = (λu₁, λu₂, …, λuₙ)
$$
**Tip:** All operations require vectors of the same dimension.

## 1.2. Linear Combination

A linear combination of vectors u and v is:
$$
 λu + μv
$$
This generalizes addition and scaling and is the basis of vector spaces.

## 1.3. Linear Interpolation

Linear interpolation (LERP) between u and v:
$$
 lerp(u, v, t) = (1 − t)u + t·v
$$
Used in animation, graphics, and numerical blending.

## 1.4. Dot Product

### Definition

For vectors a, b ∈ ℝⁿ:

$$
a \cdot b = \sum_{i=0}^{n-1} a_i b_i
$$

### Geometric Interpretation

$$
a \cdot b = \|a\| \,\|b\| \cos(\theta)
$$

where θ is the angle between a and b.

### Applications

- Orthogonality testing (a·b = 0)  
- Norm computation  
- Cosine similarity  
- Physical work: W = F·d  

## 1.5. Norms

The Taxicab norm or Manhattan norm is:
$$
 ‖u‖_1 = \sum_{i=0}^{n-1} |u_i|
$$

The Euclidean norm is:
$$
‖u‖  = sqrt(u·u)
$$

The supremum norm is:
$$
‖u‖_∞= max(|u_i|)
$$

For complex vectors, the Hermitian product is used.

## 1.6. Cosine of the Angle Between Two Vectors

The cosine of the angle θ is:
$$
 cos(θ) = (u·v) / (‖u‖‖v‖)
$$
**Tip:** Only defined when both vectors are non‑zero.

## 1.7. Cross Product of Two 3D Vectors

For u = $(u_x, u_y, u_z) and v = (v_x, v_y, v_z)$:
$$
 u × v = (u_y·v_z − u_z·v_y, u_z·v_x − u_x·v_z, u_x·v_y − u_y·v_x)
$$
Produces a vector orthogonal to both u and v.

---

# 2. Matrix Library

## 2.1. Matrix–Matrix Multiplication

### Definition

Given A ∈ ℝᵐˣⁿ and B ∈ ℝⁿˣᵖ:

$$
C_{ij} = \sum_{k=0}^{n-1} A_{ik} B_{kj}
$$

Result: C ∈ ℝᵐˣᵖ.

### Interpretation

- Composition of linear transformations  
- Change of basis  
- Sequential transformations  

## 2.2. Matrix–Vector Multiplication

Given A ∈ ℝᵐˣⁿ and v ∈ ℝⁿ:

$$
(Av)_i = \sum_{k=0}^{n-1} A_{ik} v_k
$$

The result is a vector u ∈ ℝᵐ

## 2.3. Trace

The trace of a square matrix A is:
$$
 trace(A) = a₁₁ + a₂₂ + … + aₙₙ
$$
Represents the sum of eigenvalues.

## 2.4. Transpose

The transpose Aᵀ flips rows and columns:
$$
 (Aᵀ)ᵢⱼ = Aⱼᵢ
$$

## 2.5. Row Echelon Form (REF)

### Definition

A matrix $A$ is in **Row Echelon Form (REF)** if it satisfies:

1. All non-zero rows appear above any rows of all zeros.
2. The leading coefficient (pivot) of each non-zero row is strictly to the right of the pivot of the row above it.
3. All entries below each pivot are zero.

### Purpose

Row echelon form is used to:

- Solve linear systems
- Compute the rank of a matrix
- Determine invertibility
- Prepare matrices for determinant or inverse computation

### Algorithm (Gaussian Elimination)

Given a matrix $A \in \mathbb{R}^{m \times n}$:

1. For each column $j$, find a pivot element $a_{ij} \neq 0$.
2. Swap rows to move the pivot into position.
3. Normalize the pivot row so that the pivot equals $1$.
4. Eliminate all entries below the pivot.

The resulting matrix is upper triangular and **row-equivalent** to $A$.

## 2.6. Determinant

### Definition

For a square matrix $A \in \mathbb{R}^{n \times n}$, the **determinant** $\det(A)$ is a scalar that represents:

- The scaling factor of the linear transformation induced by $A$
- Whether $A$ is invertible
- The signed volume of the parallelepiped spanned by its rows or columns

### Fundamental Properties

- $\det(A) = 0 \iff A$ is singular
- $\det(AB) = \det(A)\,·\det(B)$
- Swapping two rows changes the sign of the determinant
- Multiplying a row by $\lambda$ multiplies the determinant by $\lambda$

### Computation

Two classical methods exist:

1. **Cofactor Expansion (Laplace Expansion)**  
   Suitable for small matrices and educational purposes.

2. **Triangularization (Gaussian Elimination)**  
   Efficient for large matrices.

This project uses **cofactor expansion** for mathematical clarity.

## 2.7. Inverse

### Definition

A square matrix $A$ is **invertible** if there exists a matrix $A^{-1}$ such that:

$$
A·A^{-1} = I \quad \text{and} \quad A^{-1}·A = I
$$

where $I$ is the identity matrix.

### Existence Conditions

A matrix $A$ is invertible if and only if:

- $\det(A) \neq 0$
- Its rows (or columns) are linearly independent

### Algorithm (Gauss–Jordan Elimination)

The inverse is computed using the augmented matrix:

$$
[A \mid I]
$$

Steps:

1. Apply row operations to transform $A$ into $I$.
2. Apply the same operations to $I$.
3. The resulting right block is $A^{-1}$.

If a pivot cannot be found at any step, $A$ is singular and has no inverse.

## 2.8. Rank

The rank of A is the number of linearly independent rows (or columns).  
Computed from REF or RREF.

---

# 3. Projection Matrices: OpenGL vs DirectX (LH/RH)

This document summarizes the mathematical differences between the perspective
projection matrices used by OpenGL and DirectX, along with the coordinate
system conventions associated with each API. All formulas match the
implementations provided in this library.

## 3.1. OpenGL Conventions

- Right-handed coordinate system  
- Camera looks toward **−Z**  
- Clip space range: $z \in [-1, 1]$
- Vertical field of view (FOV) in radians  
- Aspect ratio: $\text{ratio} = \frac{\text{width}}{\text{height}}$

The standard OpenGL perspective projection matrix is:

$
P_{\text{GL}} =
\begin{pmatrix}
\frac{1}{\text{ratio}\,\tan(\frac{fov}{2})} & 0 & 0 & 0 \\
0 & \frac{1}{\tan(\frac{fov}{2})} & 0 & 0 \\
0 & 0 & -\frac{f+n}{f-n} & -\frac{2fn}{f-n} \\
0 & 0 & -1 & 0
\end{pmatrix}
$

where $ n $ is the near plane and $ f $ is the far plane.

## 3.2. DirectX Conventions (Left-Handed)

- Left-handed coordinate system  
- Camera looks toward **+Z**  
- Clip space range: $ z \in [0, 1] $  
- Vertical FOV in radians  
- Aspect ratio: $ \text{ratio} = \frac{\text{width}}{\text{height}} $

The standard DirectX LH perspective projection matrix is:

$
P_{\text{DX-LH}} =
\begin{pmatrix}
\frac{1}{\text{ratio}\,\tan(\frac{fov}{2})} & 0 & 0 & 0 \\
0 & \frac{1}{\tan(\frac{fov}{2})} & 0 & 0 \\
0 & 0 & \frac{f}{f-n} & -\frac{fn}{f-n} \\
0 & 0 & 1 & 0
\end{pmatrix}
$

This matches `XMMatrixPerspectiveFovLH`.

## 3.3. DirectX Conventions (Right-Handed)

- Right-handed coordinate system  
- Camera looks toward **+Z**  
- Clip space range: $z \in [0, 1] $  
- Vertical FOV in radians  
- Aspect ratio: $\text{ratio} = \frac{\text{width}}{\text{height}} $

The standard DirectX RH perspective projection matrix is:

$
P_{\text{DX-RH}} =
\begin{pmatrix}
\frac{1}{\text{ratio}\,\tan(\frac{fov}{2})} & 0 & 0 & 0 \\
0 & \frac{1}{\tan(\frac{fov}{2})} & 0 & 0 \\
0 & 0 & \frac{f}{n-f} & \frac{fn}{n-f} \\
0 & 0 & -1 & 0
\end{pmatrix}
$

This matches `XMMatrixPerspectiveFovRH`.

## 3.4. Parameter Validation

All implementations enforce:

- $0 < fov < \pi $  
- $\text{ratio} > 0 $  
- $n > 0 $, $f > 0 $  
- $n < f $

If any condition fails, the function throws `std::invalid_argument`.

## 3.5. Use with Homogeneous Vectors

All projection matrices are designed to multiply homogeneous vectors:

$
(x, y, z, 1)^T
$

producing clip-space coordinates, which are then normalized via:

$
(x', y', z') = \left( \frac{x}{w}, \frac{y}{w}, \frac{z}{w} \right)
$

according to the conventions of the target API.
