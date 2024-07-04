#ifndef COUNTERVIEWMODEL_H
#define COUNTERVIEWMODEL_H

#include <QObject>
#include "../model/CounterModel.h"

class CounterViewModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    explicit CounterViewModel(QObject *parent = nullptr);

    int count() const;

public slots:
    void increment();

signals:
    void countChanged(int newCount);

private:
    CounterModel m_model;
};

#endif // COUNTERVIEWMODEL_H
