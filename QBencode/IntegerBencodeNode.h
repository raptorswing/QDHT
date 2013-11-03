#ifndef INTEGERBENCODENODE_H
#define INTEGERBENCODENODE_H

#include "BencodeNode.h"

#include <QtGlobal>
#include <QByteArray>

class IntegerBencodeNode : public BencodeNode
{
public:
    IntegerBencodeNode(qint64 num);

    qint64 num() const;
    void setNum(qint64 num);

    //pure-virtual from BencodeNode
    virtual void accept(BencodeNodeVisitor * visitor);

    //pure-virtual from BencodeNode
    virtual BencodeNodeType type() const;

private:
    qint64 _num;
};

#endif // INTEGERBENCODENODE_H
