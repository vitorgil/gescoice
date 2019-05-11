#pragma once

#include <QMap>
#include <QString>

class Ingredients
{
public:
    static void add(const QString& name, const double price);
    static void remove(const QString& name);

    static double getPrice(const QString& name);
    static const QMap<QString, double>& getAll();
};
