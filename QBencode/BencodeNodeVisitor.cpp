#include "BencodeNodeVisitor.h"

#include <QtDebug>

BencodeNodeVisitor::BencodeNodeVisitor()
{
}

BencodeNodeVisitor::~BencodeNodeVisitor()
{
}

void BencodeNodeVisitor::visit(QSharedPointer<IntegerBencodeNode> node)
{
    qDebug() << "Int:" << node->num();
}

void BencodeNodeVisitor::visit(QSharedPointer<ByteStringBencodeNode> node)
{
    qDebug() << "Byte String:" << node->byteString();
}

void BencodeNodeVisitor::visit(QSharedPointer<ListBencodeNode> node)
{
    qDebug() << "List ( size" << node->elements().count() << "):";
}

void BencodeNodeVisitor::visit(QSharedPointer<DictBencodeNode> node)
{
    qDebug() << "Dict ( size" << node->dict().count() << "):";
}
