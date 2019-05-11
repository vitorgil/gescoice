#pragma once

#include <QMap>
#include <QString>

#include <memory>

typedef struct Container
{
    Container(const QString& name, const double capacityLiters, const double price);

    const QString m_name;
    const double m_capacityLiters;
    const double m_price;
} Container;

typedef std::shared_ptr<Container> ContainerPtr;
typedef QMap<QString, ContainerPtr> ContainerMap;

class Containers
{
public:
    static void add(const QString& name, const double capacityLiters, const double price);
    static void remove(const QString& name);

    static ContainerPtr get(const QString& name);
    static const ContainerMap& getAll();

};
