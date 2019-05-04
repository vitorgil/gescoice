#include "AddIngredient.h"
#include "ui_addingredient.h"

#include "Ingredients.h"

#include <QPaintEvent>
#include <QShowEvent>

AddIngredient::AddIngredient(QWidget *parent)
    : QWidget(parent, Qt::Window)
    , ui(new Ui::AddIngredient)
{
    ui->setupUi(this);

    connect(ui->buttonAdd, &QPushButton::released, this, &AddIngredient::handleButtonAdd);
    connect(ui->buttonRemove, &QPushButton::released, this, &AddIngredient::handleButtonRemove);
    connect(ui->ingredients, SIGNAL(cellClicked(int,int)), this, SLOT(handleIngredientSelected(int,int)));
}

AddIngredient::~AddIngredient()
{
    delete ui;
}

void AddIngredient::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    
    clearFields();
    loadIngredients();
}

void AddIngredient::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    ui->buttonAdd->setEnabled(!(ui->ingredientName->text().isEmpty() || ui->price->text().isEmpty()));
    ui->buttonRemove->setEnabled(ui->ingredients->selectedItems().count() > 0);
}

void AddIngredient::clearFields()
{
    ui->ingredientName->clear();
    ui->price->clear();
}

void AddIngredient::loadIngredients()
{
    ui->ingredients->clear();
    
    const auto& ingredients = Ingredients::getAll();

    ui->ingredients->setColumnCount(2);
    ui->ingredients->setRowCount(ingredients.count());
    ui->ingredients->setHorizontalHeaderLabels({ "Ingrediente", "Preço" });

    int row = 0;
    for (auto it = ingredients.cbegin(); it != ingredients.cend(); ++it, ++row)
    {
        // name
        auto item = new QTableWidgetItem(it.key());
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->ingredients->setItem(row, 0, item);
        
        // price
        item = new QTableWidgetItem(QString::number(it.value()));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->ingredients->setItem(row, 1, item);
    }
}

void AddIngredient::handleButtonAdd()
{
    Ingredients::add(
        ui->ingredientName->text(),
        ui->price->text().toDouble());
    
    clearFields();
    loadIngredients();
}

void AddIngredient::handleButtonRemove()
{
    for (auto item : ui->ingredients->selectedItems())
    {
        auto name = ui->ingredients->item(item->row(), 0)->text();
        Ingredients::remove(name);
    }

    loadIngredients();
}

void AddIngredient::handleIngredientSelected(int row, int column)
{
    auto name = ui->ingredients->item(row, 0)->text();
    auto price = Ingredients::getPrice(name);
    ui->ingredientName->setText(name);
    ui->price->setText(QString::number(price));
}

