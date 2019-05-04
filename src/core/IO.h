#pragma once

#include <QJsonDocument>
#include <QString>

namespace IO
{
void saveJson(const QString& fileName, const QJsonDocument& doc);
QJsonDocument readJson(const QString& fileName);
}
