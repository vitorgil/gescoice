#pragma once

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class AddContainer;
class AddIngredient;
class SelectContainer;
class SelectIngredient;

class Lot;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addContainer(const QString& name, const double quantity);
    void addIngredient(const QString& name, const double quantity);

private slots:
    void on_actionNewLot_triggered();
    void on_actionOpenLot_triggered();
    void on_actionContainer_triggered();
    void on_actionIngredient_triggered();
    void handleButtonAddIngredient();
    void handleButtonRemoveIngredient();
    void handleButtonAddContainer();
    void handleButtonRemoveContainer();
    void handleButtonCalculate();
    void handleButtonSave();

private:
    void showEvent(QShowEvent* event);
    void loadLotInputs();
    void loadLotOutputs();
    void loadLotContainers();
    void loadLotIngredients();
    void loadLotLastPrices();

    Ui::MainWindow *ui;
    
    AddContainer* m_addContainer;
    AddIngredient* m_addIngredient;
    SelectContainer* m_selectContainer;
    SelectIngredient* m_selectIngredient;

    Lot* m_lot;
};
