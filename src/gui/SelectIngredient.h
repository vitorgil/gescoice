#pragma once

#include <QWidget>

namespace Ui {
class SelectIngredient;
}

class ShowEvent;

class SelectIngredient : public QWidget
{
    Q_OBJECT

public:
    explicit SelectIngredient(QWidget *parent = 0);
    ~SelectIngredient();

signals:
    void addIngredient(const QString& name, const double quantity);

private:
    void showEvent(QShowEvent* event);

    void clearFields();
    void loadIngredients();

    void handleButtonAdd();

    Ui::SelectIngredient* ui;
};
