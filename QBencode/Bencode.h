#ifndef BENCODE_H
#define BENCODE_H

#include "BencodeNode.h"
#include "IntegerBencodeNode.h"
#include "ByteStringBencodeNode.h"
#include "ListBencodeNode.h"
#include "DictBencodeNode.h"

#include "qbencode_global.h"

#include <QByteArray>
#include <QSharedPointer>

class QBENCODESHARED_EXPORT Bencode
{
public:
    static QSharedPointer<BencodeNode> parse(QByteArray bytes);

    static QByteArray write(const QSharedPointer<BencodeNode>& topNode);

private:
    static QSharedPointer<BencodeNode> _parse(QByteArray &bytes);
    static QSharedPointer<IntegerBencodeNode> parseInt(QByteArray & bytes);
    static QSharedPointer<ByteStringBencodeNode> parseByteString(QByteArray & bytes);
    static QSharedPointer<ListBencodeNode> parseList(QByteArray & bytes);
    static QSharedPointer<DictBencodeNode> parseDict(QByteArray & bytes);

};

#endif // BENCODE_H
