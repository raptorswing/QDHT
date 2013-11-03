#include "Bencode.h"

#include <QStack>
#include <QDataStream>
#include <QtDebug>

#include <cctype>

#include "WriteBencodeNodeVisitor.h"

//public static
QSharedPointer<BencodeNode>Bencode::parse(QByteArray bytes)
{
    return _parse(bytes);
}

//public static
QByteArray Bencode::write(const QSharedPointer<BencodeNode> &topNode)
{
    WriteBencodeNodeVisitor * visitor = new WriteBencodeNodeVisitor();

    topNode->accept(visitor);

    return visitor->output();
}

//private static
QSharedPointer<BencodeNode>Bencode::_parse(QByteArray& bytes)
{
    char next = bytes.at(0);

    QSharedPointer<BencodeNode> toRet;

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
    }

    return toRet;
}

//private static
QSharedPointer<IntegerBencodeNode> Bencode::parseInt(QByteArray &bytes)
{
    QSharedPointer<IntegerBencodeNode> toRet;

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

        toRet = QSharedPointer<IntegerBencodeNode>(new IntegerBencodeNode(result));
    }
    else
    {
        qWarning() << "Failed to parse int" << bytes;
    }

    return toRet;
}

//private static
QSharedPointer<ByteStringBencodeNode> Bencode::parseByteString(QByteArray &bytes)
{
    QSharedPointer<ByteStringBencodeNode> toRet;

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

        toRet = QSharedPointer<ByteStringBencodeNode>(new ByteStringBencodeNode(string));
    }
    else
    {
        qWarning() << "Failed to parse bytestring" << bytes;
    }

    return toRet;
}

//private static
QSharedPointer<ListBencodeNode> Bencode::parseList(QByteArray &bytes)
{
    QSharedPointer<ListBencodeNode> toRet;

    if (!bytes.isEmpty()
            && bytes.at(0) == 'l')
    {
        //Remove the beginning 'l'
        bytes.remove(0,1);

        qDebug() << "Begin list";

        QList<QSharedPointer<BencodeNode> > listEntries;

        //Retrieve list elements
        while (!bytes.isEmpty() && bytes.at(0) != 'e')
        {
            QSharedPointer<BencodeNode> node = Bencode::_parse(bytes);
            if (node.isNull())
                return toRet;

            listEntries.append(node);
        }

        //Remove the trailing 'e'
        bytes.remove(0,1);

        qDebug() << "End list";

        toRet = QSharedPointer<ListBencodeNode>(new ListBencodeNode(listEntries));
    }
    else
    {
        qWarning() << "Failed to parse list" << bytes;
    }

    return toRet;
}

//private static
QSharedPointer<DictBencodeNode> Bencode::parseDict(QByteArray &bytes)
{
    QSharedPointer<DictBencodeNode> toRet;

    if (!bytes.isEmpty()
            && bytes.at(0) == 'd')
    {
        //Remove the beginning 'd'
        bytes.remove(0,1);

        qDebug() << "Begin dict";

        QMap<QByteArray, QSharedPointer<BencodeNode> > dictEntries;

        //Retrieve dict elements
        while (!bytes.isEmpty() && isdigit(bytes.at(0)))
        {
            //Get the key
            QSharedPointer<ByteStringBencodeNode> keyNameNode = Bencode::parseByteString(bytes);

            //Get the value
            QSharedPointer<BencodeNode> valueNode = Bencode::_parse(bytes);

            if (keyNameNode.isNull() || valueNode.isNull())
                return toRet;

            dictEntries.insert(keyNameNode->byteString(), valueNode);
        }

        //Remove the trailing 'e'
        bytes.remove(0,1);

        qDebug() << "End dict";

        toRet = QSharedPointer<DictBencodeNode>(new DictBencodeNode(dictEntries));
    }
    else
    {
        qWarning() << "Failed to parse dict" << bytes;
    }

    return toRet;
}
