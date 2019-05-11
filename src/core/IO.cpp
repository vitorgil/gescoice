#include "IO.h"

#include <QFile>

namespace IO
{
void saveJson(const QString& fileName, const QJsonDocument& doc)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    file.write(doc.toJson());
}

QJsonDocument readJson(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        return {};
    }

    QByteArray data = file.readAll();
    return QJsonDocument(QJsonDocument::fromJson(data));
}
}
