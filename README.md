# Qt Calculator

A simple calculator application built with Qt/QML for a test task.

## Features

- Basic math operations (+, -, *, /, %)
- Parentheses support
- Real-time expression display
- Error handling for invalid input
- Clear function to reset
- Custom styled buttons with hover effects

## Technology

- **Qt 6** - Application framework
- **QML** - Declarative UI
- **C++17** - Business logic
- **QJSEngine** - Expression evaluation
- **CMake** - Build system

## Files

- `calclogic.h` - Calculator logic header
- `calclogic.cpp` - Calculator logic implementation
- `main.cpp` - Application entry point
- `Main.qml` - Main calculator UI
- `CalcButton.qml` - Custom button component
- `Calc.qml` - Calculator component
- `CMakeLists.txt` - Build configuration

## How it works

The `CalcLogic` class handles all calculator operations:

- `Append(value)` - Adds numbers/operators
- `Calculate()` - Evaluates the expression  
- `Clear()` - Resets everything

## UI Components

**Main Calculator (main.qml)**
- Two-line display showing expression and result
- 4x5 grid layout with number and operator buttons
- Color-coded buttons: numbers (light blue), operators (teal), clear (red)

**Custom Button (CalcButton.qml)**
- Reusable button component with customizable colors
- Press animation and hover effects
- Circular design with proper touch targets

## Usage Example

```cpp
CalcLogic calc;
calc.Append("2");
calc.Append("+");
calc.Append("3");
calc.Calculate();
// Result: "5"
```

## Building

**Prerequisites:**
- Qt 6.0 or later
- CMake 3.16+
- C++17 compiler

**Build steps:**
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

**Run:**
```bash
./appCalcApp
```

## Notes

- Uses JavaScript engine for safe math evaluation
- Handles division by zero and syntax errors
- Properties work with QML data binding
