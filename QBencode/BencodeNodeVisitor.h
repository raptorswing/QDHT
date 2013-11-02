#ifndef BENCODENODEVISITOR_H
#define BENCODENODEVISITOR_H

#include "qbencode_global.h"

#include "IntegerBencodeNode.h"
#include "ByteStringBencodeNode.h"
#include "ListBencodeNode.h"
#include "DictBencodeNode.h"

///
/// \brief The BencodeNodeVisitor class is a base class for other visitors and implements a bad "pretty printer"
///
class QBENCODESHARED_EXPORT BencodeNodeVisitor
{
public:
    BencodeNodeVisitor();
    virtual ~BencodeNodeVisitor();

    virtual bool preVisit(IntegerBencodeNode * node);
    virtual bool preVisit(ByteStringBencodeNode * node);
    virtual bool preVisit(ListBencodeNode * node);
    virtual bool preVisit(DictBencodeNode * node);

    virtual void postVisit(IntegerBencodeNode * node);
    virtual void postVisit(ByteStringBencodeNode * node);
    virtual void postVisit(ListBencodeNode * node);
    virtual void postVisit(DictBencodeNode * node);

protected:
    QString getTabs() const;
    void increaseTab();
    void decreaseTab();

private:
    int _tabLevel;
};

#endif // BENCODENODEVISITOR_H
