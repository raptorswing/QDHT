#ifndef LISTBENCODENODE_H
#define LISTBENCODENODE_H

#include "BencodeNode.h"

#include <QList>

class ListBencodeNode : public BencodeNode
{
public:
    ListBencodeNode(const QList<BencodeNode *>& elements = QList<BencodeNode *>());

    const QList<BencodeNode *> elements() const;
    void setElements(const QList<BencodeNode *>& elements);

private:
    QList<BencodeNode *> _elements;
};

#endif // LISTBENCODENODE_H
