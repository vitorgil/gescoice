#include "SelectContainer.h"
#include "ui_selectcontainer.h"

#include "Containers.h"

#include <QShowEvent>

SelectContainer::SelectContainer(QWidget *parent)
    : QWidget(parent, Qt::Window)
    , ui(new Ui::SelectContainer)
{
    ui->setupUi(this);

    connect(ui->buttonAdd, &QPushButton::released, this, &SelectContainer::handleButtonAdd);
    connect(ui->buttonCancel, &QPushButton::released, this, &SelectContainer::close);
}

SelectContainer::~SelectContainer()
{
    delete ui;
}

void SelectContainer::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    
    clearFields();    
    loadContainers();
}

void SelectContainer::clearFields()
{
    ui->containerName->clear();
    ui->quantity->clear();
}

void SelectContainer::loadContainers()
{
    const auto& containers = Containers::getAll();

    int row = 0;
    for (auto it = containers.cbegin(); it != containers.cend(); ++it, ++row)
    {
        ui->containerName->addItem(it.key());
    }
}

void SelectContainer::handleButtonAdd()
{
    if (ui->quantity->text().isEmpty())
    {
        return;
    }

    emit(addContainer(ui->containerName->currentText(), ui->quantity->text().toDouble()));
    
    close();
}
