#include"assembler.h"
void showWarning(const QString &title, const QString &message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.setWindowTitle(title);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStyleSheet("QMessageBox { background-color: #D0D0D0; color: #000000; }"
                        "QLabel { color: #000000; }"
                        "QPushButton { color: #000000; }");
    msgBox.exec();
}
void showError(const QString &title, const QString &message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.setWindowTitle(title);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStyleSheet("QMessageBox { background-color: #D0D0D0; color: #000000; }"
                        "QLabel { color: #000000; }"
                        "QPushButton { color: #000000; }");
    msgBox.exec();
}
void exportToBinaryFile(std::vector<uint16_t> instructionBuffer, uint16_t startAddress, uint16_t endAddress){
    if (!Binaryfile.open(QIODevice::WriteOnly)) {
        showWarning("Error file", "Cannot open file for writing:");
        return;
    }
    QDataStream out(&Binaryfile);
    out.setVersion(QDataStream::Qt_5_0);
    for (uint16_t address = startAddress; address <= endAddress; ++address) {
        uint16_t value = instructionBuffer[address];
        out << value; // Write the code value to the binary file
    }
   Binaryfile.close();
}
bool loadFromBinaryFile(uint16_t startAddress) {
    if (!Binaryfile.open(QIODevice::ReadOnly)) {
        showWarning("Error file", "Cannot open file for reading:");
        return false;
    }
    QDataStream in(&Binaryfile);
    in.setVersion(QDataStream::Qt_5_0);
    uint16_t address = startAddress;
    while (!in.atEnd()) {
        uint16_t value;
        in >> value;
        memory.writeMemory(address, value);
        address++;
    }
    Binaryfile.close();
    return true;
}
//##
std::vector<QString> loadFile(const QString &filename)
{
    std::vector<QString> lines;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        showError("File Error","Cannot open file for reading:\n" + filename );
        return lines;
    }
    QTextStream input(&file);
    while (!input.atEnd())
    {
        QString line = input.readLine();
        lines.push_back(line.trimmed());
    }
    file.close();
    return lines;
}
//##lable
QMap<QString, uint16_t> analyzeInstructions(const std::vector<QString> &lines)
{
    QMap<QString, uint16_t> labels;
       uint16_t address = 0x3000; // Starting address

       for (const QString &line : lines)
       {
           if (line.isEmpty() || line.startsWith(';'))
               continue;

           // Split the line on whitespace
           QRegularExpression regular("\\s+");
           QVector<QString> tokens = line.split(regular, Qt::SkipEmptyParts);

           // Skip if no tokens found
           if (tokens.isEmpty())
               continue;

           // Process ORG directive
           if (tokens[0] == "ORG")
           {

               bool ok;
               uint16_t newAddress = tokens[1].toInt(&ok, 16);
               if (ok)
               {
                   address = newAddress;
               }
               else
               {
                   showError("Error", "Error converting address: " + tokens[1]);
               }

               continue;
           }

           // Process label
           if (tokens[0].endsWith(','))
           {
               QString label = tokens[0].chopped(1);
               labels[label] = address;
               if (tokens.size() > 1)

                   address++;
           }
           else if (tokens[0] == "END")
           {
               break;
           }
           else
               address++;
       }

       return labels;
}
//##
QString assembleInstruction(const QString &instruction, const QMap<QString, uint16_t> &labels, uint16_t currentAddress) {
    QRegularExpression regular("\\s+");
    QVector<QString> tokens = instruction.split(regular, Qt::SkipEmptyParts);
    for (int i = 0; i < tokens.size(); ++i) {
        tokens[i] = tokens[i].remove(',').trimmed();
    }
    QString opcode = tokens[0];
    if (opcode == "ADD") {
        return handleADD(tokens);
    } else if (opcode == "AND") {
        return handleAND(tokens);
    } else if (opcode.startsWith("BR")) {
        return handleBR(tokens, labels, currentAddress);
    } else if (opcode == "JMP") {
        return handleJMP(tokens);
    } else if (opcode == "JSR") {
        return handleJSR(tokens, labels, currentAddress);
    } else if (opcode == "JSRR") {
        return handleJSRR(tokens);
    } else if (opcode == "LD") {
        return handleLD(tokens, labels, currentAddress);
    } else if (opcode == "LDI") {
        return handleLDI(tokens, labels, currentAddress);
    } else if (opcode == "LDR") {
        return handleLDR(tokens);
    } else if (opcode == "LEA") {
        return handleLEA(tokens, labels, currentAddress);
    } else if (opcode == "NOT") {
        return handleNOT(tokens);
    } else if (opcode == "RET") {
        return handleRET();
    } else if (opcode == "ST") {
        return handleST(tokens, labels, currentAddress);
    } else if (opcode == "STI") {
        return handleSTI(tokens, labels, currentAddress);
    } else if (opcode == "STR") {
        return handleSTR(tokens);
    } else if (opcode == "HALT") {
        return handleHALT();
    }  else if (opcode == "DEC") {
        return handleDEC(tokens);
    } else if (opcode == "HEX") {
        return handleHEX(tokens);
    }
    return "";
}

//##
QVector<QString> splitLineBySeparator(const QString &line, const QChar &separatorChar) {
    QVector<QString> splitTokens;
    QString currentToken;
    for (const QChar &currentChar : line) {
        if (currentChar == ';') {
            break; // Stop when the comment character is encountered
        }
        if (currentChar == separatorChar) {
            if (!currentToken.isEmpty()) {
                splitTokens.append(currentToken.trimmed());
                currentToken.clear();
            }
        } else {
            currentToken += currentChar;
        }
    }

    if (!currentToken.isEmpty()) {
        splitTokens.append(currentToken.trimmed());
    }

    return splitTokens;
}

//##
// Check if a token represents a register in the form of R0 to R7
bool isValidRegister(const QString &token)
{
    int registerNumber = token.at(1).digitValue();
    return token.startsWith('R') && registerNumber >= 0 && registerNumber <= 7;
}

// Check if a token represents an immediate value within a specific range
bool isValidImmediateValue(const QString &token, int minValue, int maxValue)
{
    bool conversionSuccessful;
    int immediateValue = token.mid(1).toInt(&conversionSuccessful);
    return conversionSuccessful && immediateValue >= minValue && immediateValue <= maxValue;
}

// Check if a token is a valid label present in the labels map
bool isValidLabel(const QString &token, const QMap<QString, uint16_t> &labelsMap)
{
    return labelsMap.contains(token);
}

// Check if a token is a valid numeric value, with an optional hex base
bool isValidNumericValue(const QString &token, bool isHex)
{
    bool conversionSuccessful;
    if (isHex)
    {
        token.toUInt(&conversionSuccessful, 16);
    }
    else
    {
        token.toUInt(&conversionSuccessful);
    }
    return conversionSuccessful;
}

// Main function to validate the instruction based on its opcode and tokens
bool validateInstruction(const QVector<QString> &tokens, const QMap<QString, uint16_t> &labelsMap)
{
    if (tokens.isEmpty())
        return false;

    QString opcode = tokens[0].trimmed(); // Remove whitespace

    if (opcode == "AND" || opcode == "ADD")
    {
        // ADD and AND require exactly 4 tokens: opcode, two source registers, and a destination register or immediate value
        if (tokens.size() != 4)
            return false;

        if (!isValidRegister(tokens[1]) || !isValidRegister(tokens[2]))
            return false;

        if (tokens[3].startsWith('R'))
        {
            return isValidRegister(tokens[3]);
        }
        else
        {
            return isValidImmediateValue(tokens[3], -16, 15);
        }
    }
    else if (opcode.startsWith("BR"))
    {
        // BR requires exactly 2 tokens: opcode and a label
        if (tokens.size() != 2)
            return false;

        return isValidLabel(tokens[1], labelsMap);
    }
    else if (opcode == "JMP" || opcode == "JSRR")
    {
        // JMP and JSRR require exactly 2 tokens: opcode and a register
        if (tokens.size() != 2)
            return false;

        return isValidRegister(tokens[1]);
    }
    else if (opcode == "JSR")
    {
        // JSR requires exactly 2 tokens: opcode and a label
        if (tokens.size() != 2)
            return false;

        return isValidLabel(tokens[1], labelsMap);
    }
    else if (opcode == "LD" || opcode == "LDI" || opcode == "LEA" || opcode == "ST" || opcode == "STI")
    {
        // LD, LDI, LEA, ST, and STI require exactly 3 tokens: opcode, a register, and a label
        if (tokens.size() != 3)
            return false;

        if (!isValidRegister(tokens[1]))
            return false;

        return isValidLabel(tokens[2], labelsMap);
    }
    else if (opcode == "LDR" || opcode == "STR")
    {
        // LDR and STR require exactly 4 tokens: opcode, two registers, and an offset
        if (tokens.size() != 4)
            return false;

        if (!isValidRegister(tokens[1]) || !isValidRegister(tokens[2]))
            return false;

        bool conversionSuccessful;
        int offset = tokens[3].toInt(&conversionSuccessful);
        return conversionSuccessful && offset >= -32 && offset <= 31;
    }
    else if (opcode == "NOT")
    {
        // NOT requires exactly 3 tokens: opcode, a source register, and a destination register
        if (tokens.size() != 3)
            return false;

        return isValidRegister(tokens[1]) && isValidRegister(tokens[2]);
    }
    else if (opcode == "RET" || opcode == "HALT" || opcode == "END")
    {
        // RET, HALT, and END require exactly 1 token: opcode
        if (tokens.size() != 1)
            return false;
    }
    else if (opcode == "DEC")
    {
        // DEC requires exactly 2 tokens: opcode and an integer value
        if (tokens.size() != 2)
            return false;

        bool conversionSuccessful;
        tokens[1].toInt(&conversionSuccessful);
        return conversionSuccessful;
    }
    else if (opcode == "HEX")
    {
        // HEX requires exactly 2 tokens: opcode and a hex value
        if (tokens.size() != 2)
            return false;

        return isValidNumericValue(tokens[1], true); // Validate hex value
    }
    else
    {
        showWarning("Invalid Opcode", "Invalid opcode: " + opcode);
        return false;
    }

    return true;
}

//#####################################################################################
void generateMachineCode(const std::vector<QString> &lines, const QMap<QString, uint16_t> &labels, std::vector<uint16_t> &memory)
{
    uint16_t address = 0x3000;

    for (auto &line : lines)
    {
        if (line.isEmpty() || line.startsWith(';'))
            continue; // empty lines and comments

        // Split based on whitespace
        QRegularExpression regular("\\s+");
        QVector<QString> tokens = line.split(regular, Qt::SkipEmptyParts);
        //ORG directive
        if (tokens.size() > 1 && tokens[0] == "ORG")
        {
            processOrgDirective(tokens[1], address);
        }
        //END directive
        else if (tokens.size() >= 1 && tokens[0] == "END")
        {
            break; // End of the program
        }
        // Process label
        else if (tokens[0].endsWith(','))
        {
            processLabel(tokens, line, labels, address, memory);
        }
        // Process regular instruction
        else
        {
            processInstruction(line, labels, address, memory);
        }
    }
}

void processOrgDirective(const QString &addrString, uint16_t &address)
{
    bool ok;
    uint16_t newAddress = static_cast<uint16_t>(addrString.toInt(&ok, 16));
    if (ok)
    {
        address = newAddress; // Set starting address
    }
    else
    {
        showWarning("Error", "Error converting address: " + addrString);
    }
}

void processLabel(const QVector<QString> &tokens, const QString &line, const QMap<QString, uint16_t> &labels, uint16_t &address, std::vector<uint16_t> &memory)
{
    if (tokens.size() > 1)
    {
        QString instruction = line.mid(line.indexOf(',') + 1).trimmed();
        QVector<QString> instructionTokens = splitLineBySeparator(instruction, ' ');

        if (validateInstruction(instructionTokens, labels))
        {
            QString binaryInstruction = assembleInstruction(instruction, labels, address);
            bool correct;
            uint16_t machineCode = static_cast<uint16_t>(binaryInstruction.toUInt(&correct, 2));

            if (correct)
            {
                memory[address] = machineCode;
                address++;
            }
            else
            {
                showWarning("Error", "Failed to convert code");
            }
        }
        else
        {
            showWarning("Invalid Instruction", "invalid instruction: " + line);
        }
    }
}

void processInstruction(const QString &line, const QMap<QString, uint16_t> &labels, uint16_t &address, std::vector<uint16_t> &memory)
{
    QVector<QString> instructionTokens = splitLineBySeparator(line, ' ');

    if (validateInstruction(instructionTokens, labels))
    {
        QString binaryInstruction = assembleInstruction(line, labels, address);
        bool correct;
        uint16_t machineCode = static_cast<uint16_t>(binaryInstruction.toUInt(&correct, 2));

        if (correct)
        {
            memory[address] = machineCode;
            address++;
        }
        else
        {
            showWarning("Error", "Failed to convert code");
        }
    }
    else
    {
        showWarning("Invalid Instruction", "invalid instruction: " + line);
    }
}


//######################################################################################
int AssemblyStart(QString sourceFile)
{
    // Assemble the code
    std::vector<QString> assembledInstruction = loadFile(sourceFile);
    if (assembledInstruction.empty())
    {
        showWarning("Error", "Can not Assemble");
        return 0;
    }
    QMap<QString, uint16_t> labels = analyzeInstructions(assembledInstruction);
    std::vector<uint16_t> instructionBuffer(0xFFFF); // (64KB)
    generateMachineCode(assembledInstruction, labels, instructionBuffer);
    // Write code to output file
    exportToBinaryFile(instructionBuffer,  0x3000,0x3000 + assembledInstruction.size() - 1);
    return 1;
}
