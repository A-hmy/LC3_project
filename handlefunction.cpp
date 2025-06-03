#include "handlefunction.h"

QString ConvertBinary(int data, int bits)
{
    if (data < 0)
    {
        data = (1 << bits) + data;
        QString binaryString = QString::fromStdString(std::bitset<16>(data).to_string());
        return binaryString.right(bits).rightJustified(bits, '1');
    }
    else
    {
        QString binaryString = QString::fromStdString(std::bitset<16>(data).to_string());
        return binaryString.right(bits).rightJustified(bits, '0');
    }
}

QString convertRegister(const QString &reg) {
    return ConvertBinary(reg.mid(1).toInt(), 3);
}

QString convertImmediate(const QString &imm, int bits) {
    return ConvertBinary(imm.mid(1).toInt(), bits);
}

QString handleADD(const QVector<QString> &tokens) {
    QString dr = convertRegister(tokens[1]);
    QString sr1 = convertRegister(tokens[2]);
    if (tokens[3].startsWith('R')) {
        QString sr2 = convertRegister(tokens[3]);
         QString inst="0001" + dr + sr1 + "000" + sr2;
        return inst;
    } else {
        QString imm5 = convertImmediate(tokens[3], 5);
        QString inst="0001" + dr + sr1 + "1" + imm5;
        return inst;
    }
}

QString handleAND(const QVector<QString> &tokens) {
    QString dr = convertRegister(tokens[1]);
    QString sr1 = convertRegister(tokens[2]);
    if (tokens[3].startsWith('R')) {
        QString sr2 = convertRegister(tokens[3]);
        QString inst="0101" + dr + sr1 + "000" + sr2;
        return inst;
    } else {
        QString imm5 = convertImmediate(tokens[3], 5);
        QString inst="0101" + dr + sr1 + "1" + imm5;
        return inst;
    }
}

QString handleBR(const QVector<QString> &tokens, const QMap<QString, uint16_t> &labels, uint16_t currentAddress) {
    QString n ;
    QString z ;
    QString p ;
    if(tokens[0].contains('p'))
        p="1";
    else
        p="0";
    if(tokens[0].contains('z'))
        z="1";
    else
        z="0";
    if(tokens[0].contains('n'))
        n="1";
    else
        n="0";
    int offset = labels.value(tokens[1]) - currentAddress - 1;
    QString offsetBinary = ConvertBinary(offset, 9);
    QString inst="0000" + n + z + p + offsetBinary;
    return  inst;
}

QString handleJMP(const QVector<QString> &tokens) {
    QString baseR = convertRegister(tokens[1]);
    return "1100000" + baseR + "000000";
}

QString handleJSR(const QVector<QString> &tokens, const QMap<QString, uint16_t> &labels, uint16_t currentAddress) {
    int16_t offset = labels.value(tokens[1]) - currentAddress - 1;
    QString BinaryOffser = ConvertBinary(offset, 11);
    return "01001" + BinaryOffser;
}

QString handleJSRR(const QVector<QString> &tokens) {
    QString baseR = convertRegister(tokens[1]);
    return "0100000" + baseR + "000000";
}

QString handleLD(const QVector<QString> &tokens, const QMap<QString, uint16_t> &labels, uint16_t currentAddress) {
    QString dr = convertRegister(tokens[1]);
    int offset = labels.value(tokens[2]) - currentAddress - 1;
    return "0010" + dr + ConvertBinary(offset, 9);
}

QString handleLDI(const QVector<QString> &tokens, const QMap<QString, uint16_t> &labels, uint16_t currentAddress) {
    QString dr = convertRegister(tokens[1]);
    int offset = labels.value(tokens[2]) - currentAddress - 1;
    return "1010" + dr + ConvertBinary(offset, 9);
}

QString handleLDR(const QVector<QString> &tokens) {
    QString dr = convertRegister(tokens[1]);
    QString baseR = convertRegister(tokens[2]);
    int offset = tokens[3].mid(1).toInt();
    return "0110" + dr + baseR + ConvertBinary(offset, 6);
}

QString handleLEA(const QVector<QString> &tokens, const QMap<QString, uint16_t> &labels, uint16_t currentAddress) {
    QString dr = convertRegister(tokens[1]);
    int offset = labels.value(tokens[2]) - currentAddress - 1;
    return "1110" + dr + ConvertBinary(offset, 9);
}

QString handleNOT(const QVector<QString> &tokens) {
    QString dr = convertRegister(tokens[1]);
    QString sr = convertRegister(tokens[2]);
    return "1001" + dr + sr + "111111";
}

QString handleRET() {
    return "1100000111000000";
}

QString handleST(const QVector<QString> &tokens, const QMap<QString, uint16_t> &labels, uint16_t currentAddress) {
    QString sr = convertRegister(tokens[1]);
    int offset = labels.value(tokens[2]) - currentAddress - 1;
    return "0011" + sr + ConvertBinary(offset, 9);
}

QString handleSTI(const QVector<QString> &tokens, const QMap<QString, uint16_t> &labels, uint16_t currentAddress) {
    QString sr = convertRegister(tokens[1]);
    int offset = labels.value(tokens[2]) - currentAddress - 1;
    return "1011" + sr + ConvertBinary(offset, 9);
}

QString handleSTR(const QVector<QString> &tokens) {
    QString sr = convertRegister(tokens[1]);
    QString baseR = convertRegister(tokens[2]);
    int offset = tokens[3].mid(1).toInt();
    return "0111" + sr + baseR + ConvertBinary(offset, 6);
}

QString handleHALT() {
    return "1111000000100101";
}

QString handleDEC(const QVector<QString> &tokens) {
    bool correct;
    int16_t value = tokens[1].toInt(&correct);
    if (!correct) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Invalid .DEC value: " + tokens[1]);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStyleSheet("QMessageBox { background-color: grey; }");
        msgBox.exec();
        return "";
    }
    return ConvertBinary(value, 16);
}

QString handleHEX(const QVector<QString> &tokens) {
    bool correct;
    uint16_t value = tokens[1].toUInt(&correct, 16);
    if (!correct) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Invalid .HEX value: " + tokens[1]);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStyleSheet("QMessageBox { background-color: grey; }");
        msgBox.exec();
        return "";
    }
    return ConvertBinary(value, 16);
}
