#include "Lot.h"

#include "Containers.h"
#include "Ingredients.h"
#include "IO.h"

#include <QJsonDocument>
#include <QJsonObject>

void Lot::addContainer(const QString& recipientName, const double quantity)
{
    if (quantity > 0)
    {
        m_containers[recipientName] = quantity;
    }
    else
    {
        m_containers.remove(recipientName);
    }
}

void Lot::removeContainer(const QString& name)
{
    m_containers.remove(name);
}

void Lot::addIngredient(const QString& name, const double quantity)
{
    m_ingredientQuantities[name] = quantity;
}

void Lot::removeIngredient(const QString& name)
{
    m_ingredientQuantities.remove(name);
}

const QMap<QString, double>& Lot::getIngredients() const
{
    return m_ingredientQuantities;
}

const QMap<QString, double>& Lot::getContainers() const
{
    return m_containers;
}

const QMap<QString, double>& Lot::getLastPrices() const
{
    return m_lastPrices;
}

void Lot::calculatePrices()
{
    double totalPrice = 0.0;    
    for (auto it = m_ingredientQuantities.constBegin(); it != m_ingredientQuantities.constEnd(); ++it)
    {
        totalPrice += it.value() * Ingredients::getPrice(it.key());
    }

    double lotTotalVolume = 0.0;
    for (auto it = m_containers.constBegin(); it != m_containers.constEnd(); ++it)
    {
        lotTotalVolume += it.value();
    }

    auto lotPricePerLiter = totalPrice / lotTotalVolume;

    m_lastPrices.clear();
    for (auto it = m_containers.constBegin(); it != m_containers.constEnd(); ++it)
    {
        const auto& container = Containers::get(it.key());
        m_lastPrices[it.key()] = lotPricePerLiter * container->m_capacityLiters + container->m_price;
    }
}

double Lot::totalCost() const
{
    double totalCost = 0.0;
    for (auto it = m_containers.constBegin(); it != m_containers.constEnd(); ++it)
    {
        totalCost += m_containers[it.key()] * m_lastPrices[it.key()];
    }
    return totalCost;
}

Lot* Lot::loadFromFile(const QString& fileName)
{
    auto jsonDoc = IO::readJson(fileName);
    const auto& object = jsonDoc.object();

    Lot* lot = new Lot;
    const auto& ingredientsObject = object["ingredients"].toObject();
    for (auto it = ingredientsObject.constBegin(); it != ingredientsObject.constEnd(); ++it)
    {
        lot->m_ingredientQuantities[it.key()] = it.value().toDouble();
    }

    const auto& containersObject = object["containers"].toObject();
    for (auto it = containersObject.constBegin(); it != containersObject.constEnd(); ++it)
    {
        lot->m_containers[it.key()] = it.value().toDouble();
    }

    const auto& lastPricesObject = object["lastPrices"].toObject();
    for (auto it = lastPricesObject.constBegin(); it != lastPricesObject.constEnd(); ++it)
    {
        lot->m_lastPrices[it.key()] = it.value().toDouble();
    }

    return lot;
}

void Lot::saveToFile(const QString& fileName) const
{
    QJsonObject ingredientsObject;
    for (auto it = m_ingredientQuantities.cbegin(); it != m_ingredientQuantities.cend(); ++it)
    {
        ingredientsObject.insert(it.key(), it.value());
    }

    QJsonObject containersObject;
    for (auto it = m_containers.cbegin(); it != m_containers.cend(); ++it)
    {
        containersObject.insert(it.key(), it.value());
    }

    QJsonObject lastPricesObject;
    for (auto it = m_lastPrices.cbegin(); it != m_lastPrices.cend(); ++it)
    {
        lastPricesObject.insert(it.key(), it.value());
    }

    QJsonObject object;
    object.insert("ingredients", QJsonValue(ingredientsObject));
    object.insert("containers", QJsonValue(containersObject));
    object.insert("lastPrices", QJsonValue(lastPricesObject));
    
    IO::saveJson(fileName, QJsonDocument(object));
}
