#include "listmodel.h"

int ListModel::size() const
{
    return rowCount();
}

QVariantMap ListModel::get(int row) const
{
    QHash<int, QByteArray> names = roleNames();
    QModelIndex idx = index(row, 0);
    QVariantMap r;

    for (auto i = names.constBegin(); i != names.constEnd(); i++) {
        auto data = idx.data(i.key());
        r[i.value()] = data;
    }

    return r;
}
