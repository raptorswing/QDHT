#include <QCoreApplication>
#include <QtDebug>

#include "Bencode.h"
#include "BencodeNodeVisitor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

////    QByteArray asdf = "d1:ad2:id20:abcdefghij0123456789e1:q4:ping1:t2:aa1:y1:qe";
////    QByteArray asdf = "d1:rd2:id20:mnopqrstuvwxyz123456e1:t2:aa1:y1:re";
////    QByteArray asdf = "d1:ad2:id20:abcdefghij01234567896:target20:mnopqrstuvwxyz123456e1:q9:find_node1:t2:aa1:y1:qe";
////    QByteArray asdf = "i5005e";
////    QByteArray asdf = "5:cats!";
////    QByteArray asdf = "l5:cats!i31337el5:dogs!ee";
////    QByteArray asdf = "d3:bar4:spam3:fooi42ee";

//    QSharedPointer<BencodeNode> top = Bencode::parse(asdf);

//    qDebug() << "";

//    BencodeNodeVisitor * visitor = new BencodeNodeVisitor();
//    top->accept(visitor);
//    delete visitor;

//    qDebug() << "";

//    qDebug() << Bencode::write(top);



    return a.exec();
}
