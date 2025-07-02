/**
 * @file calclogic.h
 * @brief Header file for CalcLogic class - A Qt-based calculator business logic component
 *
 * This file defines the CalcLogic class which handles mathematical expression
 * evaluation and calculator state management. It's designed to work with QML
 * frontends through Qt's property binding and invokable method system.
 */

#ifndef CALCLOGIC_H
#define CALCLOGIC_H

#include <QObject>
#include <QString>

/**
 * @class CalcLogic
 * @brief Business logic class for calculator operations
 *
 * CalcLogic provides the core functionality for a calculator application,
 * including expression building, mathematical evaluation, and state management.
 * It inherits from QObject to integrate with Qt's meta-object system, enabling
 * property bindings and signal-slot connections with QML user interfaces.
 *
 * Key Features:
 * - Expression building through user input
 * - Mathematical expression evaluation using JavaScript engine
 * - Property bindings for seamless QML integration
 * - Automatic UI updates through signal emissions
 * - Error handling for invalid expressions
 */
class CalcLogic : public QObject
{
    Q_OBJECT

    /**
     * @property expression
     * @brief The current mathematical expression as a string
     *
     * This property holds the mathematical expression being built by user input.
     * It's readable and writable from QML, with automatic change notifications.
     * Examples: "2+3", "10*5-2", "100/4"
     */
    Q_PROPERTY(QString expression READ expression WRITE setExpression NOTIFY expressionChanged)

    /**
     * @property result
     * @brief The calculated result of the current expression
     *
     * This read-only property contains the result of the last calculation.
     * It automatically updates when Calculate() is called and emits resultChanged
     * signal for UI binding updates. Shows "Error" for invalid expressions.
     */
    Q_PROPERTY(QString result READ result NOTIFY resultChanged)

public:
    /**
     * @brief Constructor for CalcLogic
     * @param parent Optional parent QObject for memory management hierarchy
     *
     * Creates a new CalcLogic instance with optional parent for Qt's automatic
     * memory management. The parent will handle cleanup when destroyed.
     */
    explicit CalcLogic(QObject *parent = nullptr);

    /**
     * @brief Getter for the expression property
     * @return Current mathematical expression as QString
     *
     * Returns the current expression string that's being built or displayed.
     * This method is used by Qt's property system for QML bindings.
     */
    QString expression() const;

    /**
     * @brief Setter for the expression property
     * @param expr New expression string to set
     *
     * Updates the internal expression and emits expressionChanged() if the
     * value actually changes. Used by Qt's property system and can be called
     * directly from QML or C++.
     */
    void setExpression(const QString &expr);

    /**
     * @brief Getter for the result property
     * @return Current calculation result as QString
     *
     * Returns the most recent calculation result. This is a read-only property
     * that gets updated when Calculate() is executed.
     */
    QString result() const;

    /**
     * @brief Appends a value to the current expression
     * @param value String to append (numbers, operators, decimal points, etc.)
     *
     * This method handles user input from calculator buttons. It includes
     * intelligent operator handling - if an operator is entered after another
     * operator, it replaces the previous one instead of appending.
     *
     * Q_INVOKABLE allows this method to be called directly from QML.
     */
    Q_INVOKABLE void Append(const QString &value);

    /**
     * @brief Evaluates the current expression and updates the result
     *
     * Performs mathematical calculation on the current expression using Qt's
     * JavaScript engine. Handles complex expressions with proper operator
     * precedence. Updates the result property and emits resultChanged signal.
     *
     * Error cases:
     * - Empty expression defaults to "0"
     * - Invalid syntax or math errors result in "Error"
     *
     * Q_INVOKABLE allows direct calling from QML interfaces.
     */
    Q_INVOKABLE void Calculate();

    /**
     * @brief Clears both expression and result, resetting calculator state
     *
     * Resets the calculator to its initial empty state by clearing both
     * expression and result strings. Emits both change signals to update
     * connected UI elements.
     *
     * Q_INVOKABLE enables calling this method from QML button handlers.
     */
    Q_INVOKABLE void Clear();

signals:
    /**
     * @brief Emitted when the expression property changes
     *
     * This signal is automatically connected to QML property bindings,
     * enabling real-time UI updates when the expression is modified.
     * Emitted by setExpression(), Append(), and Clear() methods.
     */
    void expressionChanged();

    /**
     * @brief Emitted when the result property changes
     *
     * This signal notifies observers when a new calculation result is available.
     * Connected to QML bindings to automatically update result displays.
     * Emitted by Calculate() and Clear() methods.
     */
    void resultChanged();

private:
    /**
     * @brief Internal storage for the mathematical expression
     *
     * Holds the current expression string being built by user input.
     * Modified by setExpression(), Append(), and Clear() methods.
     */
    QString m_expression;

    /**
     * @brief Internal storage for the calculation result
     *
     * Contains the result of the most recent calculation or "Error" if
     * the calculation failed. Updated by Calculate() and Clear() methods.
     */
    QString m_result;

    /**
     * @brief Helper method to replace the last operator in expression
     * @param op New operator to replace the last character with
     *
     * Used internally by Append() to handle consecutive operator input.
     * Removes the last character and appends the new operator, improving
     * user experience by allowing operator corrections.
     */
    void replaceOperator(const QString &op);

    /**
     * @brief Checks if a character is a mathematical operator
     * @param op Character to test
     * @return true if the character is an operator (+, -, *, /, .)
     *
     * Helper function used by Append() to determine if operator replacement
     * logic should be applied. Note: Decimal point '.' is treated as an
     * operator in this implementation.
     */
    bool isOperator(const QChar &op);

    /**
     * @brief Toggles the sign of the current number or result
     *
     * This method appears to be declared but not implemented in the provided
     * source. It would typically change positive numbers to negative and
     * vice versa, commonly found on calculators as a +/- button.
     *
     * @note This method is declared but implementation was not provided.
     */
    void ToggleSign();
};

#endif
