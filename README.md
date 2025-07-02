# Qt Calculator

A simple calculator application built with Qt 6/QML in Qt Creator as a test task.

---

## Features

- Basic arithmetic operations: addition (+), subtraction (-), multiplication (*), division (/), and modulo (%).
- Support for parentheses to handle operator precedence.
- Real-time display of the current expression and calculation result.
- Robust error handling for invalid input and division by zero.
- Clear function to reset the calculator state.
- Custom styled buttons with hover and press effects.
- Long press support on "=" button to trigger additional functionality.
- Dynamic creation of secret popup windows triggered by specific logic.

---

## Technology Stack

- **Qt 6**: Application framework providing UI and event handling.
- **QML**: Declarative UI language for building fluid and responsive interfaces.
- **C++17**: Core business logic implementation via `CalcLogic` class.
- **QJSEngine**: JavaScript engine used for safe evaluation of mathematical expressions.
- **CMake**: Cross-platform build system for project configuration and compilation.

---

## Project Structure

| File               | Description                              |
|--------------------|------------------------------------------|
| `calclogic.h`      | Header for calculator logic class.       |
| `calclogic.cpp`    | Implementation of calculator logic.      |
| `main.cpp`         | Application entry point and setup.       |
| `Main.qml`         | Main calculator UI definition.           |
| `CalcButton.qml`   | Custom reusable button component.        |
| `Calc.qml`         | Calculator component encapsulating logic and UI. |
| `SecretWindow.qml` | Popup window shown as a secret feature.  |
| `CMakeLists.txt`   | Build configuration file for CMake.      |

---

## How It Works

### CalcLogic Class

- **Append(value: string)** — Adds numbers or operators to the current expression.
- **Calculate()** — Safely evaluates the mathematical expression and updates the result.
- **Clear()** — Resets the expression and result to initial empty states.
- **startHoldTimer() / stopHoldTimer()** — Handles long press behavior on the "=" button.
- **openSecretWindow() signal** — Triggers opening of a secret popup window.

The class uses QJSEngine to parse and safely evaluate expressions, catching syntax errors or invalid operations such as division by zero.

---

## UI Components

### Main Calculator (`Main.qml`)

- Two-line display:
  - **Expression display:** Shows the current input expression.
  - **Result display:** Shows the calculated result.
- Grid of buttons (4 columns x 5 rows) including digits, operators, clear, and equals.
- Color-coded buttons for clarity:
  - Numbers — light blue background with dark text.
  - Operators — teal background.
  - Clear button — red background.
- The "=" button supports press and hold events for additional functionality.

### CalcButton (`CalcButton.qml`)

- Reusable button component with:
  - Customizable background, pressed, and text colors.
  - Circular shape for consistent touch targets.
  - MouseArea handling click, press, release, and exit events.
  - Visual feedback on press and hover.

---

## Usage Example

```cpp
CalcLogic calc;
calc.Append("2");
calc.Append("+");
calc.Append("3");
calc.Calculate();
// Result: "5"
