#include "SelectIngredient.h"
#include "ui_selectingredient.h"

#include "Ingredients.h"

#include <QShowEvent>

SelectIngredient::SelectIngredient(QWidget *parent)
    : QWidget(parent, Qt::Window)
    , ui(new Ui::SelectIngredient)
{
    ui->setupUi(this);

    connect(ui->buttonAdd, &QPushButton::released, this, &SelectIngredient::handleButtonAdd);
    connect(ui->buttonCancel, &QPushButton::released, this, &SelectIngredient::close);
}

SelectIngredient::~SelectIngredient()
{
    delete ui;
}

void SelectIngredient::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    
    clearFields();    
    loadIngredients();
}

void SelectIngredient::clearFields()
{
    ui->ingredientName->clear();
    ui->quantity->clear();
}

void SelectIngredient::loadIngredients()
{
    const auto& ingredients = Ingredients::getAll();

    int row = 0;
    for (auto it = ingredients.cbegin(); it != ingredients.cend(); ++it, ++row)
    {
        ui->ingredientName->addItem(it.key());
    }
}

void SelectIngredient::handleButtonAdd()
{
    if (ui->quantity->text().isEmpty())
    {
        return;
    }

    emit(addIngredient(ui->ingredientName->currentText(), ui->quantity->text().toDouble()));
    
    close();
}
