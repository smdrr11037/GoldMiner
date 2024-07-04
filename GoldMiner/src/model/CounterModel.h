#ifndef COUNTERMODEL_H
#define COUNTERMODEL_H

#include <QObject>

class CounterModel : public QObject {
    Q_OBJECT
public:
    explicit CounterModel(QObject *parent = nullptr);

    int count() const;
    void increment();

signals:
    void countChanged(int newCount);

private:
    int m_count;
};

#endif // COUNTERMODEL_H
