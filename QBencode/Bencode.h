#ifndef BENCODE_H
#define BENCODE_H

#include "BencodeNode.h"
#include "IntegerBencodeNode.h"
#include "ByteStringBencodeNode.h"
#include "ListBencodeNode.h"
#include "DictBencodeNode.h"

#include "qbencode_global.h"

#include <QByteArray>

class QBENCODESHARED_EXPORT Bencode
{
public:
    static BencodeNode * parse(QByteArray bytes);

private:
    static BencodeNode * _parse(QByteArray &bytes);
    static IntegerBencodeNode * parseInt(QByteArray & bytes);
    static ByteStringBencodeNode * parseByteString(QByteArray & bytes);
    static ListBencodeNode * parseList(QByteArray & bytes);
    static DictBencodeNode * parseDict(QByteArray & bytes);

};

#endif // BENCODE_H
