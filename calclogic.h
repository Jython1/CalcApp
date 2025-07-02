// calclogic.h
#ifndef CALCLOGIC_H
#define CALCLOGIC_H

#include <QObject>
#include <QString>
#include <QTimer>

/**
 * @class CalcLogic
 * @brief Enhanced calculator logic with secret window functionality
 *
 * Adds hidden feature: Opens a special window when "=" button is held for 5 seconds
 * and when user types "123" sequence.
 */
class CalcLogic : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString expression READ expression WRITE setExpression NOTIFY expressionChanged)
    Q_PROPERTY(QString result READ result NOTIFY resultChanged)

public:
    explicit CalcLogic(QObject *parent = nullptr);

    QString expression() const;
    void setExpression(const QString &expr);
    QString result() const;

    Q_INVOKABLE void Append(const QString &value);
    Q_INVOKABLE void Calculate();
    Q_INVOKABLE void Clear();

    // New methods for secret window functionality
    Q_INVOKABLE void startHoldTimer();
    Q_INVOKABLE void stopHoldTimer();

signals:
    void expressionChanged();
    void resultChanged();
    void openSecretWindow(); // New signal for opening secret window

private slots:
    void onHoldTimerTimeout();

private:
    QString m_expression;
    QString m_result;

    // Secret functionality members
    QTimer *m_holdTimer;
    QString m_secretSequence;
    static const QString SECRET_CODE;

    // Helper methods
    void replaceOperator(const QString &op);
    bool isOperator(const QChar &op);
    void ToggleSign();
    void checkSecretSequence(const QString &value);
};

#endif // CALCLOGIC_H
