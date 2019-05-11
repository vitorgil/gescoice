#include "Ingredients.h"
#include "IO.h"

#include <algorithm>

#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>

namespace
{
constexpr const char* ingredientsFile = "ingredients.json";

class IngredientsImpl
{
    QMap<QString, double> m_prices;

    IngredientsImpl()
    {
        fetch();
    }

    ~IngredientsImpl()
    {
        save();
    }

    void fetch()
    {
        auto doc = IO::readJson(ingredientsFile);
        const auto& object = doc.object();
        for (auto it = object.constBegin(); it != object.constEnd(); ++it)
        {
            m_prices[it.key()] = it.value().toDouble();
        }
    }

    void save()
    {
        QJsonObject object;
        for (auto it = m_prices.cbegin(); it != m_prices.cend(); ++it)
        {
            object.insert(it.key(), it.value());
        }

        IO::saveJson(ingredientsFile, QJsonDocument(object));
    }
    
public:
    static IngredientsImpl& instance()
    {
        static IngredientsImpl instance;
        return instance;
    }

    void add(const QString& name, const double price)
    {
        m_prices[name] = price;
    }
    
    void remove(const QString& name)
    {
        m_prices.remove(name);
    }

    double getPrice(const QString& name)
    {
        auto it = m_prices.constFind(name);
        if (it == m_prices.constEnd())
        {
            return -1;
        }
        return it.value();
    }

    const QMap<QString, double>& getAll()
    {
        return m_prices;
    }
};
}

void Ingredients::add(const QString& name, const double price)
{
    IngredientsImpl::instance().add(name, price);
}

void Ingredients::remove(const QString& name)
{
    IngredientsImpl::instance().remove(name);
}

double Ingredients::getPrice(const QString& name)
{
    return IngredientsImpl::instance().getPrice(name);
}

const QMap<QString, double>& Ingredients::getAll()
{
    return IngredientsImpl::instance().getAll();
}
