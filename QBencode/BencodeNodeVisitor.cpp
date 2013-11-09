#include "BencodeNodeVisitor.h"

#include <QtDebug>

BencodeNodeVisitor::BencodeNodeVisitor() :
    _tabLevel(0)
{
}

BencodeNodeVisitor::~BencodeNodeVisitor()
{
}

bool BencodeNodeVisitor::preVisit(IntegerBencodeNode *node)
{
    qDebug() << this->getTabs() << "Int:" << node->num();

    return true;
}

bool BencodeNodeVisitor::preVisit(ByteStringBencodeNode * node)
{
    qDebug() << this->getTabs() << "Byte String:" << node->byteString();

    return true;
}

bool BencodeNodeVisitor::preVisit(ListBencodeNode * node)
{
    qDebug() << this->getTabs() << "List ( size" << node->elements().count() << "):";

    this->increaseTab();

    return true;
}

bool BencodeNodeVisitor::preVisit(DictBencodeNode * node)
{
    qDebug() << this->getTabs() << "Dict ( size" << node->dict().count() << "):";
    this->increaseTab();

    foreach(const QByteArray& key, node->dict().keys())
    {
        qDebug() << this->getTabs() << "Key:" << key;
        this->increaseTab();
        node->dict().value(key)->accept(this);
        this->decreaseTab();
    }

    return false;
}

void BencodeNodeVisitor::postVisit(IntegerBencodeNode * node)
{
    Q_UNUSED(node)
}

void BencodeNodeVisitor::postVisit(ByteStringBencodeNode * node)
{
    Q_UNUSED(node)
}

void BencodeNodeVisitor::postVisit(ListBencodeNode * node)
{
    Q_UNUSED(node)
    this->decreaseTab();
}

void BencodeNodeVisitor::postVisit(DictBencodeNode * node)
{
    Q_UNUSED(node)
    this->decreaseTab();
}

//protected
QString BencodeNodeVisitor::getTabs() const
{
    QString toRet;

    for (int i = 0; i < _tabLevel; i++)
        toRet += '\t';
    return toRet;
}

//protected
void BencodeNodeVisitor::increaseTab()
{
    _tabLevel = qBound<uint>(0, _tabLevel + 1, 10);
}

//protected
void BencodeNodeVisitor::decreaseTab()
{
    _tabLevel = qBound<uint>(0, _tabLevel - 1, 10);
}
