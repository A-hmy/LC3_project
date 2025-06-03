#ifndef HANDLEFUNCTION_H
#define HANDLEFUNCTION_H

#include<QString>
#include "qmessagebox.h"
#include<bitset>
QString ConvertBinary(int data, int bits);
QString convertRegister(const QString &reg) ;
QString convertImmediate(const QString &imm, int bits) ;
QString handleADD(const QVector<QString> &tokens);
QString handleAND(const QVector<QString> &tokens);
QString handleBR(const QVector<QString> &tokens, const QMap<QString, uint16_t> &labels, uint16_t currentAddress);
QString handleJMP(const QVector<QString> &tokens);
QString handleJSR(const QVector<QString> &tokens, const QMap<QString, uint16_t> &labels, uint16_t currentAddress);
QString handleJSRR(const QVector<QString> &tokens);
QString handleLD(const QVector<QString> &tokens, const QMap<QString, uint16_t> &labels, uint16_t currentAddress);
QString handleLDI(const QVector<QString> &tokens, const QMap<QString, uint16_t> &labels, uint16_t currentAddress);
QString handleLDR(const QVector<QString> &tokens);
QString handleLEA(const QVector<QString> &tokens, const QMap<QString, uint16_t> &labels, uint16_t currentAddress);
QString handleNOT(const QVector<QString> &tokens);
QString handleRET() ;
QString handleST(const QVector<QString> &tokens, const QMap<QString, uint16_t> &labels, uint16_t currentAddress);
QString handleSTI(const QVector<QString> &tokens, const QMap<QString, uint16_t> &labels, uint16_t currentAddress);
QString handleSTR(const QVector<QString> &tokens);
QString handleHALT();
QString handleDEC(const QVector<QString> &tokens) ;
QString handleHEX(const QVector<QString> &tokens);
#endif // HANDLEFUNCTION_H
