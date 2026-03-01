# PowerSim-Core

A lightweight C++ module for power system calculations.

This repository provides the computational core for a power system simulator, focusing on fundamental AC circuit theory and grid topology analysis.

## Project Structure

- **models/**: Physical equipment representations (Bus, Line, Load, etc.).
- **core/**: Calculation engines and analysis logic.
- **utils/**: Shared constants and mathematical helpers.

```text
powersim-core/
├── include/
│   ├── models/
│   ├── core/
│   └── utils/
├── src/
│   ├── models/
│   ├── core/
│   └── main.cpp
└── test/
    ├── models/
    └── core/
```

## Current Focus

- Object-oriented modeling of power system elements using complex numbers.
- Providing a foundation for grid analysis (e.g., Short-circuit, Unbalance, Voltage drop).
