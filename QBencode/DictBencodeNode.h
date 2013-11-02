#ifndef DICTBENCODENODE_H
#define DICTBENCODENODE_H

#include "BencodeNode.h"

#include <QMap>
#include <QString>

class DictBencodeNode : public BencodeNode
{
public:
    DictBencodeNode(const QMap<QString, BencodeNode *>& dict = QMap<QString, BencodeNode *>());

    const QMap<QString, BencodeNode *>& dict() const;
    void setDict(const QMap<QString, BencodeNode *>& dict);

private:
    QMap<QString, BencodeNode *> _dict;
};

#endif // DICTBENCODENODE_H
