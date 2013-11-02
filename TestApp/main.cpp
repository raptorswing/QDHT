#include <QCoreApplication>

#include "Bencode.h"

#include "BencodeNodeVisitor.h"

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    QByteArray asdf = "d1:ad2:id20:abcdefghij0123456789e1:q4:ping1:t2:aa1:y1:qe";
//    QByteArray asdf = "i5005e";
//    QByteArray asdf = "5:cats!";
//    QByteArray asdf = "l5:cats!i31337el5:dogs!ee";

    QSharedPointer<BencodeNode> top = Bencode::parse(asdf);

    BencodeNodeVisitor * visitor = new BencodeNodeVisitor();
    top->accept(visitor);

    return a.exec();
}
