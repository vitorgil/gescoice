#include "Containers.h"

#include "IO.h"

#include <QJsonObject>

namespace
{
constexpr const char* containersFile = "containers.json";

class ContainersImpl
{
    ContainerMap m_containers;
    
    ContainersImpl()
    {
        fetch();
    }

    ~ContainersImpl()
    {
        save();
    }

    void fetch()
    {
        auto doc = IO::readJson(containersFile);
        const auto& object = doc.object();
        for (auto it = object.constBegin(); it != object.constEnd(); ++it)
        {
            auto valueObject = it->toObject();
            m_containers[it.key()] = ContainerPtr(
                new Container(
                    it.key(),
                    valueObject["capacity"].toDouble(),
                    valueObject["price"].toDouble()));
        }
    }

    void save()
    {
        QJsonObject object;
        for (auto it = m_containers.cbegin(); it != m_containers.cend(); ++it)
        {
            QJsonObject valueObject;
            valueObject.insert("capacity", it.value()->m_capacityLiters);
            valueObject.insert("price", it.value()->m_price);

            object.insert(it.key(), QJsonValue(valueObject));
        }

        IO::saveJson(containersFile, QJsonDocument(object));
    }

public:
    static ContainersImpl& instance()
    {
        static ContainersImpl instance;
        return instance;
    }

    void add(const QString& name, const double capacity, const double price)
    {
        m_containers[name] = ContainerPtr(new Container(name, capacity, price));
    }
    
    void remove(const QString& name)
    {
        m_containers.remove(name);
    }

    ContainerPtr get(const QString& name)
    {
        return m_containers.constFind(name).value();
    }

    const ContainerMap& getAll()
    {
        return m_containers;
    }
};
}

Container::Container(const QString& name, const double capacityLiters, const double price)
    : m_name(name)
    , m_capacityLiters(capacityLiters)
    , m_price(price)
{
}

ContainerPtr Containers::get(const QString& name)
{
    return ContainersImpl::instance().get(name);
}

void Containers::add(const QString& name, const double capacityLiters, const double price)
{
    ContainersImpl::instance().add(name, capacityLiters, price);
}

void Containers::remove(const QString& name)
{
    ContainersImpl::instance().remove(name);
}

const ContainerMap& Containers::getAll()
{
    return ContainersImpl::instance().getAll();
}
