#pragma once

#include <QWidget>

namespace Ui {
class AddIngredient;
}

class ShowEvent;

class AddIngredient : public QWidget
{
    Q_OBJECT

public:
    explicit AddIngredient(QWidget *parent = 0);
    ~AddIngredient();

private slots:
    void handleIngredientSelected(int row, int column);
    
private:
    void showEvent(QShowEvent* event);
    void paintEvent(QPaintEvent* event);

    void clearFields();
    void loadIngredients();

    void handleButtonAdd();
    void handleButtonRemove();

    Ui::AddIngredient* ui;
};
