#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "AddContainer.h"
#include "AddIngredient.h"
#include "SelectContainer.h"
#include "SelectIngredient.h"

#include "GuiUtils.h"
#include "Lot.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_lot(new Lot)
{
    ui->setupUi(this);

    m_addContainer = new AddContainer(this);
    m_addIngredient = new AddIngredient(this);
    m_selectContainer = new SelectContainer(this);
    m_selectIngredient = new SelectIngredient(this);

    guiutils::centerOnScreen(this);
    guiutils::centerOnScreen(m_addContainer);
    guiutils::centerOnScreen(m_addIngredient);
    guiutils::centerOnScreen(m_selectContainer);
    guiutils::centerOnScreen(m_selectIngredient);

    connect(ui->buttonAddIngredient, &QPushButton::released, this, &MainWindow::handleButtonAddIngredient);
    connect(ui->buttonRemoveIngredient, &QPushButton::released, this, &MainWindow::handleButtonRemoveIngredient);
    connect(ui->buttonAddContainer, &QPushButton::released, this, &MainWindow::handleButtonAddContainer);
    connect(ui->buttonRemoveContainer, &QPushButton::released, this, &MainWindow::handleButtonRemoveContainer);
    connect(ui->buttonCalculate, &QPushButton::released, this, &MainWindow::handleButtonCalculate);
    connect(ui->buttonSave, &QPushButton::released, this, &MainWindow::handleButtonSave);
    connect(m_selectContainer, SIGNAL(addContainer(const QString&, const double)),
            this, SLOT(addContainer(const QString&, const double)));
    connect(m_selectIngredient, SIGNAL(addIngredient(const QString&, const double)),
            this, SLOT(addIngredient(const QString&, const double)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_lot;
    delete m_addContainer;
    delete m_addIngredient;
    delete m_selectContainer;
    delete m_selectIngredient;
}

void MainWindow::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
}

void MainWindow::on_actionOpenLot_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Abrir lote"), "",
        tr("Ficheiro lote (*.lote)"));
    
    delete m_lot;
    m_lot = Lot::loadFromFile(fileName);
    if (!m_lot)
    {
        return;
    }
    
    loadLotInputs();
    loadLotOutputs();
}

void MainWindow::on_actionNewLot_triggered()
{
    delete m_lot;
    m_lot = new Lot;

    ui->lotIngredients->clear();
    ui->lotIngredients->setRowCount(0);
    ui->lotIngredients->setColumnCount(0);
    
    ui->lotContainers->clear();
    ui->lotContainers->setRowCount(0);
    ui->lotContainers->setColumnCount(0);

    ui->lotLastPrices->clear();
    ui->lotLastPrices->setRowCount(0);
    ui->lotLastPrices->setColumnCount(0);
    
    ui->costTotal->clear();
}

void MainWindow::on_actionContainer_triggered()
{
    m_addContainer->show();
}

void MainWindow::on_actionIngredient_triggered()
{
    m_addIngredient->show();
}

void MainWindow::handleButtonAddIngredient()
{
    m_selectIngredient->show();
}

void MainWindow::handleButtonRemoveIngredient()
{
    auto row = ui->lotIngredients->currentRow();
    if (row < 0)
    {
        return;
    }

    auto name = ui->lotIngredients->item(row, 0)->text();
    m_lot->removeIngredient(name);
    
    loadLotIngredients();
}

void MainWindow::handleButtonAddContainer()
{
    m_selectContainer->show();
}

void MainWindow::handleButtonRemoveContainer()
{
    auto row = ui->lotContainers->currentRow();
    if (row < 0)
    {
        return;
    }

    auto name = ui->lotContainers->item(row, 0)->text();
    m_lot->removeContainer(name);
    
    loadLotContainers();
}

void MainWindow::handleButtonCalculate()
{
    m_lot->calculatePrices();
    loadLotOutputs();
}

void MainWindow::handleButtonSave()
{
    if (ui->lotContainers->rowCount() == 0)
    {
        return;
    }

    const QString fileName = QFileDialog::getSaveFileName(this, tr("Guardar lote"), "", tr("Ficheiro lote (*.lote)"));
    m_lot->saveToFile(fileName);
}

void MainWindow::loadLotInputs()
{
    loadLotContainers();
    loadLotIngredients();
}

void MainWindow::loadLotOutputs()
{
    loadLotLastPrices();
    ui->costTotal->setText(QString::number(m_lot->totalCost()));
}

void MainWindow::loadLotContainers()
{
    ui->lotContainers->clear();

    const auto& containers = m_lot->getContainers();

    ui->lotContainers->setColumnCount(2);
    ui->lotContainers->setRowCount(containers.count());
    ui->lotContainers->setHorizontalHeaderLabels({ "Recipiente", "Quantidade" });

    int row = 0;
    for (auto it = containers.cbegin(); it != containers.cend(); ++it, ++row)
    {
        auto item = new QTableWidgetItem(it.key());
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->lotContainers->setItem(row, 0, item);
        
        item = new QTableWidgetItem(QString::number(it.value()));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->lotContainers->setItem(row, 1, item);
    }
}

void MainWindow::loadLotIngredients()
{
    ui->lotIngredients->clear();

    const auto& ingredients = m_lot->getIngredients();

    ui->lotIngredients->setColumnCount(2);
    ui->lotIngredients->setRowCount(ingredients.count());
    ui->lotIngredients->setHorizontalHeaderLabels({ "Ingrediente", "Quantidade" });

    int row = 0;
    for (auto it = ingredients.cbegin(); it != ingredients.cend(); ++it, ++row)
    {
        auto item = new QTableWidgetItem(it.key());
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->lotIngredients->setItem(row, 0, item);

        item = new QTableWidgetItem(QString::number(it.value()));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->lotIngredients->setItem(row, 1, item);
    }
}

void MainWindow::loadLotLastPrices()
{
    ui->lotLastPrices->clear();

    const auto& lastPrices = m_lot->getLastPrices();

    ui->lotLastPrices->setColumnCount(2);
    ui->lotLastPrices->setRowCount(lastPrices.count());
    ui->lotLastPrices->setHorizontalHeaderLabels({ "Recipiente", "Custo unitário" });

    int row = 0;
    for (auto it = lastPrices.cbegin(); it != lastPrices.cend(); ++it, ++row)
    {
        auto item = new QTableWidgetItem(it.key());
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->lotLastPrices->setItem(row, 0, item);

        item = new QTableWidgetItem(QString::number(it.value()));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->lotLastPrices->setItem(row, 1, item);
    }
}

void MainWindow::addContainer(const QString& name, const double quantity)
{
    m_lot->addContainer(name, quantity);
    loadLotContainers();
}

void MainWindow::addIngredient(const QString& name, const double quantity)
{
    m_lot->addIngredient(name, quantity);
    loadLotIngredients();
}
