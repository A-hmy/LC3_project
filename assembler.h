#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include "qregularexpression.h"
#include <QString>
#include<bitset>
#include<QVector>
#include<QTextStream>
#include<QIODevice>
#include <QMessageBox>
#include "handlefunction.h"
#include "registers.h"
#include"globalvariable.h"
void showWarning(const QString &title, const QString &message);
void showError(const QString &title, const QString &message);
void exportToBinaryFile(std::vector<uint16_t> instructionBuffer, uint16_t startAddress, uint16_t endAddress);
bool loadFromBinaryFile(uint16_t startAddress);
std::vector<QString> loadFile(const QString &filename);
QMap<QString, uint16_t> analyzeInstructions(const std::vector<QString> &lines);
QString assembleInstruction(const QString &instruction, const QMap<QString, uint16_t> &labels, uint16_t currentAddress);
QVector<QString> splitLineBySeparator(const QString &line, const QChar &separatorChar) ;
bool isValidRegister(const QString &token);
bool isValidImmediateValue(const QString &token, int minValue, int maxValue);
bool isValidLabel(const QString &token, const QMap<QString, uint16_t> &labelsMap);
bool isValidNumericValue(const QString &token, bool isHex = false);
bool validateInstruction(const QVector<QString> &tokens, const QMap<QString, uint16_t> &labelsMap);
void generateMachineCode(const std::vector<QString> &lines, const QMap<QString, uint16_t> &labels, std::vector<uint16_t> &memory);
void processOrgDirective(const QString &addrString, uint16_t &address);
void processLabel(const QVector<QString> &tokens, const QString &line, const QMap<QString, uint16_t> &labels, uint16_t &address, std::vector<uint16_t> &memory);
void processInstruction(const QString &line, const QMap<QString, uint16_t> &labels, uint16_t &address, std::vector<uint16_t> &memory);
int AssemblyStart(QString sourceFile);
#endif // ASSEMBLER_H
