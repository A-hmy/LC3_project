#include "mainwindow.h"
#include "assembler.h"
#include "instructions.h"
#include "ui_mainwindow.h"
#include"globalvariable.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ShowError("qq","dd","ee");
    initializeMemory();
    refreshRegisterDisplays();
    manager=0;
    memory.resetMemory();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::updateMemoryView(int index)
{
    if (index < ui->memory_table->rowCount())
    {
        QTableWidgetItem *valueItem = ui->memory_table->item(index, 1);
        if (valueItem == nullptr)
        {
            valueItem = new QTableWidgetItem();
            ui->memory_table->setItem(index, 1, valueItem);
        }
        valueItem->setText(QString("0x%1").arg(memory.readMemory(index), 4, 16, QChar('0')).toUpper());
        ui->memory_table->scrollToItem(valueItem, QAbstractItemView::PositionAtCenter);
    }
}
void MainWindow::initializeMemory()
{
    ui->memory_table->setRowCount(0xFFFF);
    ui->memory_table->setColumnCount(2);
    QStringList headers = {"Address", "Value"};
    ui->memory_table->setHorizontalHeaderLabels(headers);
    ui->memory_table->verticalHeader()->setVisible(false);

    ui->memory_table->setSortingEnabled(false);

    for (size_t i = 0; i < 0xFFFF; ++i)
    {
        QTableWidgetItem *addressItem = new QTableWidgetItem(QString("0x%1").arg(i, 4, 16, QChar('0')).toUpper());
        ui->memory_table->setItem(i, 0, addressItem);

        QTableWidgetItem *valueItem = new QTableWidgetItem(QString("0x%1").arg(memory.readMemory(i), 4, 16, QChar('0')).toUpper());
        ui->memory_table->setItem(i, 1, valueItem);
    }

    ui->memory_table->setSortingEnabled(true);
}
void MainWindow::refreshRegisterDisplays()
{

    for (int i = 0; i < 8; ++i) {
        QLabel* label = findChild<QLabel*>(QString("label_R%1").arg(i));
        if (label) {
            label->setText(QString("R%1   0x%2").arg(i).arg(QString::number(registers.getR(i), 16).toUpper()));
        }
    }


    ui->label_MAR->setText(QString("MAR   ")+"0x" + QString::number(registers.getMAR(), 16).toUpper());
    ui->label_MDR->setText(QString("MDR   ")+"0x" + QString::number(registers.getMDR(), 16).toUpper());
    ui->label_Pc->setText(QString("PC   ")+"0x" + QString::number(registers.getPC(), 16).toUpper());
    ui->label_P->setText(QString("P   ")+"0x" + QString::number(registers.getCC() & 0x1, 16).toUpper());
    ui->label_N->setText(QString("N   ")+"0x" + QString::number((registers.getCC() >> 2) & 0x1, 16).toUpper());
    ui->label_Z->setText(QString("Z   ")+"0x" + QString::number((registers.getCC() >> 1) & 0x1, 16).toUpper());
    ui->label_IR->setText(QString("IR   ")+"0x" + QString::number(registers.getIR(), 16).toUpper());
}
void MainWindow::on_Upload_file_pushButton_clicked()
{
    if(manager==0||manager==-1){
        manager=0;
        memory.resetMemory();
        initializeMemory();
        registers.resetRegisters();
        Binaryfile.open(QIODevice::WriteOnly);//clear file
        Binaryfile.close();
        refreshRegisterDisplays();
        updateMemoryView(index);
        QString InputFileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Assembly Files (*.asm)"));
        if (!InputFileName.isEmpty())
        {
            if (InputFileName.endsWith(".asm", Qt::CaseInsensitive))
            {
                ShowHappyMessageBox("Select file","The file has been uploaded","Enjoy working with LC3");
                AssemblyStart(InputFileName);
            }
            else
            {
                ShowErrorMessageBox("Select file","No File Selected","Try again");
            }
        }
        else
        {
            ShowErrorMessageBox("Select file","No File Selected","Try again");
        }
    }
}
void MainWindow::on_Start_Assemble_PushButton_clicked()
{
    loadFromBinaryFile(0x3000);//fill memory
    registers.setPC(0x3000);
    index = 0x3000;
    initializeMemory();
    updateMemoryView(index);
    manager=1;
}
void MainWindow::on_Next_PushButto_clicked()
{
    switch (manager) {
    case -1:
        // HALT
        if (isHalt()) {
            QMessageBox::information(this, "Program Done", "The program has reached the HALT instruction and is done.");
        }
        break;

    case 1:
        fetch();
        if (isHalt()) {
            QMessageBox::information(this, "Program Done", "The program has reached the HALT instruction and is done.");
            manager = -1;
        } else {
            refreshRegisterDisplays();
            ui->phases_lable->setText("Fetch");
            manager++;
        }
        break;

    case 2:
        decode();
        refreshRegisterDisplays();
        ui->phases_lable->setText("Decode");
        manager++;
        break;

    case 3:
        evaluateAddress();
        refreshRegisterDisplays();
        ui->phases_lable->setText("Evaluate Address");
        manager++;
        break;

    case 4:
        fetchOperands();
        refreshRegisterDisplays();
        ui->phases_lable->setText("Fetch Operands");
        manager++;
        break;

    case 5:
        execute();
        refreshRegisterDisplays();
        ui->phases_lable->setText("Execute");
        manager++;
        break;

    case 6:
        store();
        refreshRegisterDisplays();
        ui->phases_lable->setText("Store");
        updateMemoryView(index);
        manager = 1;
        break;

    default:
        break;
    }

}
void MainWindow::on_StopPushButto_clicked()
{
    manager=0;
    memory.resetMemory();
    initializeMemory();
    registers.resetRegisters();
    Binaryfile.open(QIODevice::WriteOnly);//clear file
    Binaryfile.close();
    refreshRegisterDisplays();
    updateMemoryView(index);
}

