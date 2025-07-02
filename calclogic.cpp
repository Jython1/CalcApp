#include "calclogic.h"
#include <QJSEngine>


CalcLogic::CalcLogic(QObject *parent) : QObject(parent)
{

}

/**
 * @brief Getter for the mathematical expression property
 * @return Current expression as QString
 *
 * This is a const method that returns the current mathematical expression
 * stored in m_expression. Used by QML bindings and other components that
 * need to read the current expression without modifying it.
 */
QString CalcLogic::expression() const {
    return m_expression;
}

/**
 * @brief Setter for the mathematical expression property
 * @param expr New expression string to set
 *
 * Updates the internal expression string and emits expressionChanged() signal
 * if the value actually changes. This prevents unnecessary signal emissions
 * when the same value is set multiple times. The signal emission enables
 * automatic UI updates in QML through property bindings.
 */
void CalcLogic::setExpression(const QString &expr) {
    if (m_expression != expr) {  // Avoid unnecessary updates and signal emissions
        m_expression = expr;     // Update internal storage
        emit expressionChanged(); // Notify QML and other observers of the change
    }
}

/**
 * @brief Getter for the calculation result property
 * @return Current result as QString
 *
 * Returns the most recent calculation result. This is typically called
 * by QML property bindings to display the result in the user interface.
 */
QString CalcLogic::result() const {
    return m_result;
}

/**
 * @brief Appends a value to the current mathematical expression
 * @param value String to append (numbers, operators, etc.)
 *
 * This method handles user input from calculator buttons. It includes
 * logic to prevent consecutive operators by replacing the last operator
 * if a new operator is entered. This improves user experience by allowing
 * operator corrections without having to clear and restart.
 */
void CalcLogic::Append(const QString &value) {
    // Check if we're trying to add an operator after another operator
    if (!m_expression.isEmpty()) {
        QChar lastChar = m_expression.back();  // Get the last character
        // If both last character and new input are operators, replace instead of append
        if (isOperator(lastChar) && isOperator(value[0])) {
            replaceOperator(value);  // Replace the last operator with the new one
            return;  // Exit early, don't append
        }
    }

    // Normal case: append the value to the expression
    m_expression += value;
    emit expressionChanged();  // Notify observers of the change
}

/**
 * @brief Clears both expression and result, resetting calculator state
 *
 * This method resets the calculator to its initial empty state by clearing
 * both the expression and result strings. It emits both change signals to
 * ensure the UI is properly updated to reflect the cleared state.
 */
void CalcLogic::Clear() {
    m_expression.clear();    // Reset expression to empty string
    m_result.clear();        // Reset result to empty string
    emit expressionChanged(); // Update UI to show empty expression
    emit resultChanged();    // Update UI to show empty result
}

/**
 * @brief Checks if a character is a mathematical operator
 * @param op Character to check
 * @return true if the character is an operator, false otherwise
 *
 * Helper function that determines if a given character is one of the
 * supported mathematical operators. Note: The decimal point '.' is
 * included in the operator list, which may be a design choice for
 * preventing multiple decimal points in a number.
 */
bool CalcLogic::isOperator(const QChar &op) {
    // Static array of supported operators for efficient lookup
    static const QChar operators[] = { '+', '-', '*', '/'};
    size_t size = sizeof(operators) / sizeof(operators[0]);

    // Linear search through the operator array
    for (size_t i = 0; i < size; ++i) {
        if (operators[i] == op) return true;
    }
    return false;  // Character not found in operator list
}

/**
 * @brief Replaces the last character in expression with a new operator
 * @param op New operator to replace the last character with
 *
 * Helper method used by Append() to handle operator replacement.
 * Removes the last character from the expression and appends the new
 * operator, then notifies observers of the change.
 */
void CalcLogic::replaceOperator(const QString &op) {
    if (!m_expression.isEmpty()) {
        m_expression.chop(1);     // Remove the last character
        m_expression += op;       // Add the new operator
        emit expressionChanged(); // Notify observers
    }
}

/**
 * @brief Evaluates the mathematical expression and stores the result
 *
 * This method performs the actual calculation by leveraging Qt's JavaScript
 * engine (QJSEngine) to safely evaluate mathematical expressions. The JS
 * engine handles operator precedence, parentheses, and complex expressions
 * automatically. Results are converted back to strings for display purposes.
 *
 * Error handling includes:
 * - Empty expressions default to "0"
 * - Invalid syntax or runtime errors result in "Error" message
 * - Division by zero and other mathematical errors are caught
 */
void CalcLogic::Calculate() {
    if (m_expression.isEmpty()) {
        // Handle empty expression case - default to zero
        m_result = "0";
    } else {
        // Create JavaScript engine instance for expression evaluation
        QJSEngine engine;

        // Evaluate the mathematical expression as JavaScript code
        // This handles complex expressions with proper operator precedence
        QJSValue evalResult = engine.evaluate(m_expression);

        if (evalResult.isError()) {
            // Handle evaluation errors (syntax errors, division by zero, etc.)
            m_result = "Error";
        } else {
            // Convert numerical result back to string for UI display
            // QJSValue::toString() handles number formatting automatically
            m_result = evalResult.toString();
        }
    }

    // Notify observers (typically QML UI) that new result is available
    emit resultChanged();
}
