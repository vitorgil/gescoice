#pragma once

#include <QWidget>

namespace Ui {
class AddContainer;
}

class ShowEvent;

class AddContainer : public QWidget
{
    Q_OBJECT

public:
    explicit AddContainer(QWidget *parent = 0);
    ~AddContainer();

private slots:
    void handleContainerSelected(int row, int column);

private:
    void showEvent(QShowEvent* event);
    void paintEvent(QPaintEvent* event);

    void clearFields();
    void loadContainers();

    void handleButtonAdd();
    void handleButtonRemove();

    Ui::AddContainer* ui;
};
