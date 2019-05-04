#pragma once

#include <QWidget>

namespace Ui {
class SelectContainer;
}

class ShowEvent;

class SelectContainer : public QWidget
{
    Q_OBJECT

public:
    explicit SelectContainer(QWidget *parent = 0);
    ~SelectContainer();

signals:
    void addContainer(const QString& name, const double quantity);

private:
    void showEvent(QShowEvent* event);

    void clearFields();
    void loadContainers();

    void handleButtonAdd();

    Ui::SelectContainer* ui;
};
