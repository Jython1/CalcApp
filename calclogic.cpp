// calclogic.cpp
#include "calclogic.h"
#include <QJSEngine>
#include <QTimer>

// Static constant for secret code
const QString CalcLogic::SECRET_CODE = "123";

/**
 * @brief Constructor with enhanced functionality
 * @param parent Parent QObject for memory management
 *
 * Initializes calculator logic and sets up secret window functionality
 * including hold timer for "=" button and sequence tracking.
 */
CalcLogic::CalcLogic(QObject *parent) : QObject(parent)
{
    // Initialize hold timer for "=" button
    m_holdTimer = new QTimer(this);
    m_holdTimer->setSingleShot(true);  // Timer fires only once
    m_holdTimer->setInterval(5000);    // 5 seconds in milliseconds

    // Connect timer timeout to secret window opening
    connect(m_holdTimer, &QTimer::timeout, this, &CalcLogic::onHoldTimerTimeout);

    // Initialize secret sequence tracker
    m_secretSequence.clear();
}

/**
 * @brief Getter for the mathematical expression property
 * @return Current expression as QString
 */
QString CalcLogic::expression() const {
    return m_expression;
}

/**
 * @brief Setter for the mathematical expression property
 * @param expr New expression string to set
 */
void CalcLogic::setExpression(const QString &expr) {
    if (m_expression != expr) {
        m_expression = expr;
        emit expressionChanged();
    }
}

/**
 * @brief Getter for the calculation result property
 * @return Current result as QString
 */
QString CalcLogic::result() const {
    return m_result;
}

/**
 * @brief Enhanced append method with secret sequence detection
 * @param value String to append (numbers, operators, etc.)
 *
 * Handles normal calculator input while also tracking secret sequence "123".
 * When "123" is detected, triggers the secret window opening.
 */
void CalcLogic::Append(const QString &value) {
    // Check for secret sequence before normal processing
    checkSecretSequence(value);

    // Normal calculator logic
    if (!m_expression.isEmpty()) {
        QChar lastChar = m_expression.back();
        if (isOperator(lastChar) && isOperator(value[0])) {
            replaceOperator(value);
            return;
        }
    }

    m_expression += value;
    emit expressionChanged();
}

/**
 * @brief Clears both expression and result, resetting calculator state
 *
 * Also resets the secret sequence tracker to start fresh.
 */
void CalcLogic::Clear() {
    m_expression.clear();
    m_result.clear();

    // Reset secret sequence tracking
    m_secretSequence.clear();

    emit expressionChanged();
    emit resultChanged();
}

/**
 * @brief Starts the hold timer for "=" button
 *
 * Called when user presses and holds the "=" button.
 * Starts a 5-second timer that will trigger secret window if not stopped.
 */
void CalcLogic::startHoldTimer() {
    m_holdTimer->start();
}

/**
 * @brief Stops the hold timer for "=" button
 *
 * Called when user releases the "=" button before 5 seconds.
 * Prevents the secret window from opening.
 */
void CalcLogic::stopHoldTimer() {
    m_holdTimer->stop();
}

/**
 * @brief Handles hold timer timeout (5 seconds elapsed)
 *
 * Private slot that gets called when the hold timer expires.
 * Emits signal to open the secret window.
 */
void CalcLogic::onHoldTimerTimeout() {
    emit openSecretWindow();
}

/**
 * @brief Checks if the input value contributes to secret sequence "123"
 * @param value Input value to check
 *
 * Tracks sequential input to detect "123" pattern. When complete
 * sequence is detected, triggers secret window opening.
 */
void CalcLogic::checkSecretSequence(const QString &value) {
    // Only track single digit numbers for the sequence
    if (value.length() == 1 && value[0].isDigit()) {
        m_secretSequence += value;

        // Keep only the last 3 characters to check for "123"
        if (m_secretSequence.length() > 3) {
            m_secretSequence = m_secretSequence.right(3);
        }

        // Check if we have the secret sequence
        if (m_secretSequence == SECRET_CODE) {
            m_secretSequence.clear(); // Reset to prevent repeated triggers
            emit openSecretWindow();
        }
    } else {
        // Reset sequence if non-digit is entered
        m_secretSequence.clear();
    }
}

/**
 * @brief Checks if a character is a mathematical operator
 * @param op Character to check
 * @return true if the character is an operator
 */
bool CalcLogic::isOperator(const QChar &op) {
    static const QChar operators[] = { '+', '-', '*', '/' , '.'};
    size_t size = sizeof(operators) / sizeof(operators[0]);
    for (size_t i = 0; i < size; ++i) {
        if (operators[i] == op) return true;
    }
    return false;
}

/**
 * @brief Replaces the last operator in expression with a new one
 * @param op New operator to replace with
 */
void CalcLogic::replaceOperator(const QString &op) {
    if (!m_expression.isEmpty()) {
        m_expression.chop(1);
        m_expression += op;
        emit expressionChanged();
    }
}

/**
 * @brief Evaluates the mathematical expression and stores the result
 *
 * Uses Qt's JavaScript engine to safely evaluate expressions.
 * Handles errors gracefully and provides user feedback.
 */
void CalcLogic::Calculate() {
    if (m_expression.isEmpty()) {
        m_result = "0";
    } else {
        QJSEngine engine;
        QJSValue evalResult = engine.evaluate(m_expression);
        if (evalResult.isError()) {
            m_result = "Error";
        } else {
            m_result = evalResult.toString();
        }
    }
    emit resultChanged();
}

/**
 * @brief Toggles the sign of the current number (placeholder)
 *
 * Method declared but not yet implemented.
 */
void CalcLogic::ToggleSign() {
    // TODO: Implement sign toggle functionality
}
