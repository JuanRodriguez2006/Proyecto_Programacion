#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <QIntValidator>
#include <QDoubleValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configurar la tabla
    ui->tableWidget->setColumnCount(4);
    QStringList headers;
    headers << "Código" << "Nombre" << "Cantidad" << "Precio";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargarProductos() {
    productos.clear();
    std::ifstream archivo(archivoDatos);
    if (archivo.is_open()) {
        std::string linea;
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;
            std::vector<std::string> campos;
            std::stringstream ss(linea);
            std::string campo;
            while (getline(ss, campo, ';')) {
                campos.push_back(campo);
            }
            if (campos.size() == 4) {
                Producto p;
                p.codigo = campos[0];
                p.nombre = campos[1];
                p.cantidad = std::stoi(campos[2]);
                p.precio = std::stof(campos[3]);
                productos.push_back(p);
            }
        }
        archivo.close();
    }
}

void MainWindow::guardarProducto(Producto& p) {
    std::ofstream archivo(archivoDatos, std::ios::app);
    if (archivo.is_open()) {
        archivo << p.codigo << ";"
                << p.nombre << ";"
                << p.cantidad << ";"
                << p.precio << "\n";
        archivo.close();
    }
}

void MainWindow::guardarTodo() {
    std::ofstream archivo(archivoDatos);
    if (archivo.is_open()) {
        for (auto& p : productos) {
            archivo << p.codigo << ";"
                    << p.nombre << ";"
                    << p.cantidad << ";"
                    << p.precio << "\n";
        }
        archivo.close();
    }
}

void MainWindow::actualizarTabla() {
    ui->tableWidget->setRowCount(0);
    for (size_t i = 0; i < productos.size(); i++) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(productos[i].codigo)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(productos[i].nombre)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(productos[i].cantidad)));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(productos[i].precio, 'f', 2)));
    }
}

void MainWindow::limpiarCampos() {
    ui->lineEdit_nombre->clear();
    ui->lineEdit_codigo->clear();
    ui->lineEdit_cantidad->clear();
    ui->lineEdit_precio->clear();
}

void MainWindow::on_btnAgregar_clicked() {
    if (ui->lineEdit_codigo->text().isEmpty() || ui->lineEdit_nombre->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Debe completar Código o Nombre");
        return;
    }

    int cant = ui->lineEdit_cantidad->text().toInt();
    float prec = ui->lineEdit_precio->text().toFloat();

    if (cant < 0 || prec < 0 ) {
        QMessageBox::warning(this, "Error", "La cantidad o el precio no pueden ser negativos");
        return;
    }

    cargarProductos();

    Producto p;
    p.codigo = ui->lineEdit_codigo->text().toStdString();
    p.nombre = ui->lineEdit_nombre->text().toStdString();
    p.cantidad = cant;
    p.precio = prec;

    for (auto& prod : productos) {
        if (prod.codigo == p.codigo) {
            QMessageBox::warning(this, "Error", "El código ya existe");
            return;
        }
    }

    guardarProducto(p);
    cargarProductos();
    actualizarTabla();
    limpiarCampos();

    QMessageBox::information(this, "Éxito", "Producto agregado correctamente");
}

void MainWindow::on_btnActualizar_clicked() {
    if (ui->lineEdit_codigo->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Debe ingresar un código para actualizar");
        return;
    }

    cargarProductos();
    std::string codigo = ui->lineEdit_codigo->text().toStdString();
    bool encontrado = false;

    for (auto& p : productos) {
        if (p.codigo == codigo) {
            if (!ui->lineEdit_nombre->text().isEmpty())
                p.nombre = ui->lineEdit_nombre->text().toStdString();

            if (!ui->lineEdit_cantidad->text().isEmpty()) {
                int nCant = ui->lineEdit_cantidad->text().toInt();
                if (nCant < 0) {
                    QMessageBox::warning(this, "Error", "Cantidad negativa no permitida");
                    return;
                }
                p.cantidad = nCant;
            }

            if (!ui->lineEdit_precio->text().isEmpty()) {
                float nPrec = ui->lineEdit_precio->text().toFloat();
                if (nPrec < 0) {
                    QMessageBox::warning(this, "Error", "Precio negativo no permitido");
                    return;
                }
                p.precio = nPrec;
            }

            encontrado = true;
            break;
        }
    }

    if (encontrado) {
        guardarTodo();
        actualizarTabla();
        limpiarCampos();
        QMessageBox::information(this, "Éxito", "Producto actualizado correctamente");
    } else {
        QMessageBox::warning(this, "Error", "Producto no encontrado");
    }
}
