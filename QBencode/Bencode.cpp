#include "Bencode.h"

#include <QStack>
#include <QDataStream>
#include <QtDebug>

#include <cctype>

//public static
BencodeNode *Bencode::parse(QByteArray bytes)
{
    return _parse(bytes);
}

//private static
BencodeNode *Bencode::_parse(QByteArray& bytes)
{
    char next = bytes.at(0);

    BencodeNode * toRet = 0;

    if (next == 'i')
    {
        toRet = Bencode::parseInt(bytes);
    }
    else if (isdigit(next))
    {
        toRet = Bencode::parseByteString(bytes);
    }
    else if (next == 'l')
    {
        toRet = Bencode::parseList(bytes);
    }
    else if (next == 'd')
    {
        toRet = Bencode::parseDict(bytes);
    }
    else
    {
        qWarning() << "Bad bencoding! Unknown type" << next;
        return 0;
    }

    return 0;
}

//private static
IntegerBencodeNode * Bencode::parseInt(QByteArray &bytes)
{
    int endIndex = bytes.indexOf('e');
    bool ok;
    qint64 result;

    if (!bytes.isEmpty()
            && bytes.at(0) == 'i'
            && endIndex != -1
            && (result = bytes.mid(1, endIndex - 1).toLongLong(&ok)) == result
            && ok)
    {
        bytes.remove(0, endIndex + 1);

        qDebug() << "Parsed int" << result;

        return new IntegerBencodeNode(result);
    }
    else
    {
        qWarning() << "Failed to parse int" << bytes;
        return 0;
    }
}

//private static
ByteStringBencodeNode * Bencode::parseByteString(QByteArray &bytes)
{
    int endLengthIndex = bytes.indexOf(':');
    bool ok;
    qint64 lengthResult;

    if (!bytes.isEmpty()
            && isdigit(bytes.at(0))
            && endLengthIndex != -1
            && (lengthResult = bytes.mid(0, endLengthIndex).toLongLong(&ok)) == lengthResult
            && ok
            && bytes.length() >= lengthResult + endLengthIndex)
    {
        const QByteArray string = bytes.mid(endLengthIndex + 1, lengthResult);
        bytes.remove(0, endLengthIndex + lengthResult + 1);

        qDebug() << "Parsed bytestring" << string;

        return new ByteStringBencodeNode(string);
    }
    else
    {
        qWarning() << "Failed to parse bytestring" << bytes;
        return 0;
    }
}

//private static
ListBencodeNode *Bencode::parseList(QByteArray &bytes)
{
    if (!bytes.isEmpty()
            && bytes.at(0) == 'l')
    {
        //Remove the beginning 'l'
        bytes.remove(0,1);

        qDebug() << "Begin list";

        QList<BencodeNode *> listEntries;

        //Retrieve list elements
        while (!bytes.isEmpty() && bytes.at(0) != 'e')
        {
            BencodeNode * node = Bencode::_parse(bytes);
            listEntries.append(node);
        }

        //Remove the trailing 'e'
        bytes.remove(0,1);

        qDebug() << "End list";

        return new ListBencodeNode(listEntries);
    }
    else
    {
        qWarning() << "Failed to parse list" << bytes;
        return 0;
    }
}

//private static
DictBencodeNode *Bencode::parseDict(QByteArray &bytes)
{
    if (!bytes.isEmpty()
            && bytes.at(0) == 'd')
    {
        //Remove the beginning 'd'
        bytes.remove(0,1);

        qDebug() << "Begin dict";

        QMap<QString, BencodeNode *> dictEntries;

        //Retrieve dict elements
        while (!bytes.isEmpty() && isdigit(bytes.at(0)))
        {
            //Get the key
            ByteStringBencodeNode * keyNameNode = Bencode::parseByteString(bytes);
            const QByteArray key = keyNameNode->byteString();
            delete keyNameNode;

            //Get the value
            BencodeNode * valueNode = Bencode::_parse(bytes);
            dictEntries.insert(key, valueNode);
        }

        //Remove the trailing 'e'
        bytes.remove(0,1);

        qDebug() << "End dict";

        return new DictBencodeNode(dictEntries);
    }
    else
    {
        qWarning() << "Failed to parse dict" << bytes;
        return 0;
    }
}
