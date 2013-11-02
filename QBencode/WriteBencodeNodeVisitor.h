#ifndef WRITEBENCODENODEVISITOR_H
#define WRITEBENCODENODEVISITOR_H

#include "BencodeNodeVisitor.h"

#include <QByteArray>

class WriteBencodeNodeVisitor : public BencodeNodeVisitor
{
public:
    WriteBencodeNodeVisitor();

    const QByteArray &output() const;
    void reset();

    virtual bool preVisit(IntegerBencodeNode * node);
    virtual bool preVisit(ByteStringBencodeNode * node);
    virtual bool preVisit(ListBencodeNode * node);
    virtual bool preVisit(DictBencodeNode * node);

//    virtual void postVisit(IntegerBencodeNode * node);
//    virtual void postVisit(ByteStringBencodeNode * node);
    virtual void postVisit(ListBencodeNode * node);
    virtual void postVisit(DictBencodeNode * node);

private:
    QByteArray _output;
};

#endif // WRITEBENCODENODEVISITOR_H
