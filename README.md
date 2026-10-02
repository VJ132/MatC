# MatC

A lightweight matrix manipulation library written in C, providing basic matrix operations using dynamically allocated, contiguous memory.

## Features

- Dynamic matrix allocation and deallocation
- Direct element access using row and column indices
- Matrix initialization with a specified value
- Matrix addition and subtraction
- Matrix multiplication
- Scalar multiplication
- Matrix transposition
- Support for rectangular matrices
- Simple API with minimal dependencies

## Requirements

- C compiler (GCC or Clang)
- Standard C library
- GNU Make is not required

## Project Structure

```text
MatC/
├── src/
│   ├── MatC.c
│   └── MatC.h
├── tests/
│   └── test_MatC.c
├── bin/
├── main.c
├── build.sh
├── .gitignore
├── LICENSE
└── README.md
```

## Getting Started

Clone the repository:

```bash
git clone https://github.com/VJ132/MatC.git
cd MatC
```

### Build

Run the provided build script:

```bash
chmod +x build.sh
./build.sh
```

Alternatively, compile manually:

```bash
gcc -Wall -Wextra -O2 -o bin/build main.c src/MatC.c
```

Run the example:

```bash
./bin/build
```

## Usage

Include the library header:

```c
#include "src/MatC.h"
```

### Creating a Matrix

```c
Matrix *A = matc_allocate(2, 3);

if (A == NULL) {
    return 1;
}

matc_fill(A, 5);
matc_print(A);

matc_free(A);
```

This creates a 2 × 3 matrix and initializes every element to `5`.

### Accessing Elements

MatC uses zero-based indexing.

```c
*matc_at(A, 0, 1) = 10;

int value = *matc_at(A, 0, 1);
```

The matrix stores its elements in contiguous row-major order.

### Matrix Addition

```c
Matrix *A = matc_allocate(2, 2);
Matrix *B = matc_allocate(2, 2);
Matrix *C = matc_allocate(2, 2);

matc_fill(A, 4);
matc_fill(B, 6);

matc_sum(C, A, B);

matc_print(C);
```

### Matrix Multiplication

```c
Matrix *A = matc_allocate(2, 3);
Matrix *B = matc_allocate(3, 2);
Matrix *C = matc_allocate(2, 2);

matc_fill(A, 2);
matc_fill(B, 3);

matc_mul(C, A, B);

matc_print(C);
```

For matrix multiplication, if A has dimensions `m × n` and B has dimensions `n × p`, the resulting matrix C must have dimensions `m × p`.

## API Reference

| Function                       | Description                     |
| ------------------------------ | ------------------------------- |
| `matc_allocate(rows, columns)` | Allocates a matrix              |
| `matc_free(matrix)`            | Frees matrix memory             |
| `matc_fill(matrix, value)`     | Fills all elements with a value |
| `matc_at(matrix, i, j)`        | Returns a pointer to an element |
| `matc_print(matrix)`           | Prints the matrix               |
| `matc_sum(c, a, b)`            | Computes A + B                  |
| `matc_sub(c, a, b)`            | Computes A - B                  |
| `matc_mul(c, a, b)`            | Computes A × B                  |
| `matc_scale(c, a, scalar)`     | Multiplies a matrix by a scalar |
| `matc_transpose(c, a)`         | Computes the transpose of A     |

## Running Tests

Compile the test suite:

```bash
gcc -Wall -Wextra -O2 -o bin/test_MatC tests/test_MatC.c src/MatC.c
```

Run the tests:

```bash
./bin/test_MatC
```

The test suite covers:

- Allocation and element access
- Matrix initialization
- Addition and subtraction
- Square and rectangular multiplication
- Scalar multiplication
- Square and rectangular transposition
- In-place element-wise operations

## Limitations

- Matrices currently store signed integer elements (`int`).
- Dimension compatibility is checked using assertions.
- Element access does not perform bounds checking.
- Arithmetic overflow is not handled.
- Matrix operations require appropriately sized output matrices.

## License

MatC is distributed under the MIT License. See [LICENSE](LICENSE) for details.
