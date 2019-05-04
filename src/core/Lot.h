#pragma once

#include <QMap>
#include <QString>

class Lot
{
public:
    Lot() = default;
    ~Lot() = default;
    
    void addContainer(const QString& recipientName, const double quantity);
    void removeContainer(const QString& name);

    void addIngredient(const QString& name, const double quantity);
    void removeIngredient(const QString& name);

    const QMap<QString, double>& getIngredients() const;
    const QMap<QString, double>& getContainers() const;
    const QMap<QString, double>& getLastPrices() const;

    void calculatePrices();
    double totalCost() const;

    static Lot* loadFromFile(const QString& fileName);
    void saveToFile(const QString& fileName) const;

private:
    QMap<QString, double> m_ingredientQuantities;
    QMap<QString, double> m_containers;
    QMap<QString, double> m_lastPrices;
};
