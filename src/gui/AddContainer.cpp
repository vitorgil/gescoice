#include "AddContainer.h"
#include "ui_addcontainer.h"

#include "Containers.h"

#include <QPaintEvent>
#include <QShowEvent>

AddContainer::AddContainer(QWidget *parent)
    : QWidget(parent, Qt::Window)
    , ui(new Ui::AddContainer)
{
    ui->setupUi(this);

    connect(ui->buttonAdd, &QPushButton::released, this, &AddContainer::handleButtonAdd);
    connect(ui->buttonRemove, &QPushButton::released, this, &AddContainer::handleButtonRemove);
    connect(ui->containers, SIGNAL(cellClicked(int,int)), this, SLOT(handleContainerSelected(int,int)));
}

AddContainer::~AddContainer()
{
    delete ui;
}

void AddContainer::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);

    clearFields();
    loadContainers();
}

void AddContainer::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    ui->buttonAdd->setEnabled(!(
        ui->containerName->text().isEmpty() ||
        ui->capacity->text().isEmpty() ||
        ui->price->text().isEmpty()));
    ui->buttonRemove->setEnabled(ui->containers->selectedItems().count() > 0);
}

void AddContainer::clearFields()
{
    ui->containerName->clear();
    ui->capacity->clear();
    ui->price->clear();
}

void AddContainer::loadContainers()
{
    ui->containers->clear();
    
    const auto& containers = Containers::getAll();

    ui->containers->setColumnCount(3);
    ui->containers->setRowCount(containers.count());
    ui->containers->setHorizontalHeaderLabels({ "Recipiente", "Capacidade", "Preço" });

    int row = 0;
    for (auto it = containers.cbegin(); it != containers.cend(); ++it, ++row)
    {
        // name
        auto item = new QTableWidgetItem(it.key());
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->containers->setItem(row, 0, item);

        // capacity
        item = new QTableWidgetItem(QString::number(it.value()->m_capacityLiters));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->containers->setItem(row, 1, item);

        // price
        item = new QTableWidgetItem(QString::number(it.value()->m_price));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->containers->setItem(row, 2, item);
    }
}

void AddContainer::handleButtonAdd()
{
    Containers::add(
        ui->containerName->text(),
        ui->capacity->text().toDouble(),
        ui->price->text().toDouble());
    
    clearFields();
    loadContainers();
}

void AddContainer::handleButtonRemove()
{
    for (auto item : ui->containers->selectedItems())
    {
        auto name = ui->containers->item(item->row(), 0)->text();
        Containers::remove(name);
    }

    loadContainers();
}

void AddContainer::handleContainerSelected(int row, int column)
{
    auto name = ui->containers->item(row, 0)->text();
    auto container = Containers::get(name);
    ui->containerName->setText(name);
    ui->capacity->setText(QString::number(container->m_capacityLiters));
    ui->price->setText(QString::number(container->m_price));
}