#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filling_data.hpp"
#include <QMessageBox>
#include <QFileDialog>
#include <sstream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)//MainWindow constructor
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //populating comboboxes
    for(int i = 0; i < NUMBER_OF_CITIES; i++){
        ui->comboBox1_1->addItem(QString::fromStdString(ukrainianCities[i]));
    }
    ui->comboBox1_1->setStyleSheet("combobox-popup: 0;");
    for(int i = 0; i < NUMBER_OF_CITIES; i++){
        ui->comboBox2->addItem(QString::fromStdString(ukrainianCities[i]));
    }
    ui->comboBox2->setStyleSheet("combobox-popup: 0;");
    for(int i = 0; i < DELIVERY_CATEGORIES_NUM; i++){
        ui->comboBox1_2->addItem(QString::fromStdString(deliveryCategories[i]));
    }
    ui->comboBox1_2->setStyleSheet("combobox-popup: 0;");
    for(int i = 0; i < DELIVERY_CATEGORIES_NUM; i++){
        ui->comboBox3->addItem(QString::fromStdString(deliveryCategories[i]));
    }
    ui->comboBox3->setStyleSheet("combobox-popup: 0;");
    //placeholder texts:
    ui->file_path_lineEdit->setPlaceholderText("there will be path to file");
    ui->invoice_lineEdit->setPlaceholderText("invoice");
    ui->weight_lineEdit->setPlaceholderText("weight (kilograms)");
    ui->file_path_lineEdit->setReadOnly(true);
    //exit button color:
    QPalette Pal(palette());
    Pal.setColor(QPalette::Button, QColor(53,0,0));
    ui->exit_button->setAutoFillBackground(true);
    ui->exit_button->setPalette(Pal);
    //initialisinng queue:
    m_queue = new Queue;
}

MainWindow::~MainWindow()//MainWindow destructor
{
    delete ui;
    delete m_queue;
}


void MainWindow::on_deliver_button_clicked()
{
    if(m_queue->get_head() != nullptr){
        QMessageBox::information(this, "delivered",
                                 (QString::fromStdString(m_queue->get_head()->kind_of_delivery) + " package is of weight "
                                  + QString::number(m_queue->get_head()->weight)+ "kg delivered to " + QString::fromStdString(m_queue->get_head()->destination)
                                  + "\ninvoice: " + QString::fromStdString(m_queue->get_head()->invoice_number)));
        m_queue->Dequeue();
        //subtracting 1 from the dispayed number
        int count{-1};
        bool ok{true};
        count += ui->number_of_deliveries_label->text().toInt(&ok, 10);
        ui->number_of_deliveries_label->setText(QString::number(count));
    }else{
        QMessageBox::information(this, "message", "nothing to deliver");
    }
}


void MainWindow::on_deliver_all_button_clicked()
{
    while(m_queue->get_head() != nullptr){
        m_queue->Dequeue();
        //subtracting 1 from the dispayed number
        int count{-1};
        bool ok{true};
        count += ui->number_of_deliveries_label->text().toInt(&ok, 10);
        ui->number_of_deliveries_label->setText(QString::number(count));
    }
    QMessageBox::information(this, "notification", "everything is delivered");
}


void MainWindow::on_browse_button_clicked()
{
    ui->file_path_lineEdit->setText(QFileDialog::getOpenFileName());
}


void MainWindow::on_add_from_file_button_clicked()
{
    if(ui->file_path_lineEdit->text() != ""){
        QString file_path = ui->file_path_lineEdit->text();
        std::ifstream fin;
        fin.open(file_path.toStdString());
        if(fin){
            std::stringstream ss;
            ss << fin.rdbuf();
            std::string line;
            while (std::getline(ss, line)) {//splitting data line by line
                if (line != "") {
                    std::stringstream lineStream(line);
                    //initialising variables for reading
                    std::string invoice{ "" };
                    double weight{};
                    std::string kind_of_delivery{ "" };
                    std::string destination{""};
                    //reading
                    if ((lineStream >> invoice >> weight >> kind_of_delivery >> destination)) {
                        Package tmp;
                        tmp.invoice_number = invoice;
                        tmp.weight = weight;
                        tmp.kind_of_delivery = kind_of_delivery;
                        tmp.destination = destination;
                        m_queue->Enqueue(tmp);

                        int count{1};//changing number displayed +1
                        bool ok{true};
                        count += ui->number_of_deliveries_label->text().toInt(&ok, 10);
                        ui->number_of_deliveries_label->setText(QString::number(count));
                    }
                    else {
                        QMessageBox::critical(this, "error", "error reading data from file occured.");
                        break;
                    }
                }
            }
        }
        else
        {
            QMessageBox::warning(this, "error", "file could not be opened.");
            fin.close();
            return;
        }
        fin.close();
        return;
    }
}


void MainWindow::on_add_delivery_manually_button_clicked()
{
    if((ui->comboBox1_1->currentText() != "") && (ui->comboBox1_1->currentText() != "") && (ui->weight_lineEdit->text() != "")){
        std::string weight_string = ui->weight_lineEdit->text().toStdString();
        double weight{};
        try{
        weight = std::stod(weight_string);//can throw std::invalid_argument on user's wrong input
        }catch(...){
            QMessageBox::warning(this, "warning", "error for weight was found.");
            return;
        }
        if(weight <= 0){
            QMessageBox::warning(this, "warning", "error for weight was found.");
            return;
        }else{
            Package package;
            //filling package
            package.weight = weight;
            package.destination = ui->comboBox1_1->currentText().toStdString();
            package.kind_of_delivery = ui->comboBox1_2->currentText().toStdString();
            Package* tmp = m_queue->get_rear();

            int invoice_num{};
            if(tmp != nullptr){
                std::string last_invoice_num = tmp->invoice_number;
                last_invoice_num.erase(last_invoice_num.begin(), last_invoice_num.begin()+3);
                invoice_num = std::stoi(last_invoice_num) + 1;
            }else{
                invoice_num = 210401;
            }
            package.invoice_number = ("INV" + std::to_string(invoice_num));
            m_queue->Enqueue(package);//enqueueing
            QMessageBox::information(this, "recorded", ("invoice: " + QString::fromStdString(package.invoice_number)));

            int count{1};//changing number displayed +1
            bool ok{true};
            count += ui->number_of_deliveries_label->text().toInt(&ok, 10);
            ui->number_of_deliveries_label->setText(QString::number(count));
        }
    }else{
        QMessageBox::warning(this, "warning", "Not all fields are specified.");
    }
}


void MainWindow::on_find_button1_clicked()//finding number of deliveries to x
{
    if(ui->comboBox2->currentText() != ""){
        int num_of_deliveries{};
        m_queue->search_deliveries_to(ui->comboBox2->currentText().toStdString(), num_of_deliveries);
        QMessageBox::information(this, QString::number(num_of_deliveries), ("number of deliveries to " + ui->comboBox2->currentText()));
    }else{
        QMessageBox::warning(this, "warning", "Not all fields are specified.");
    }
}


void MainWindow::on_find_button2_clicked()//find summary weight of deliveries in category x
{
    if(ui->comboBox3->currentText() != ""){
        double weight{};
        m_queue->sum_weight_in_category(ui->comboBox3->currentText().toStdString(), weight);
        QMessageBox::information(this, QString::number(weight)+"kg", ("sum weight in category " + ui->comboBox3->currentText()));
    }else{
        QMessageBox::warning(this, "warning", "Not all fields are specified.");
    }
}


void MainWindow::on_find_button3_clicked()//lookup by invoice
{
    if(ui->invoice_lineEdit->text() != ""){
        Package package;
        m_queue->find_by_invoice(ui->invoice_lineEdit->text().toStdString(), package);
        if(package.invoice_number == ""){
            QMessageBox::information(this, "package not found", "please check if the invoice code is correct");
        }else{
            double weight = package.weight;
            QString invoice = QString::fromStdString(package.invoice_number);
            QString destination = QString::fromStdString(package.destination);
            QString kind_of_delivery = QString::fromStdString(package.kind_of_delivery);
            QMessageBox::information(this, "package found",
                                     ("your " + kind_of_delivery + " package is of weight " + QString::number(weight)
                                      + "kg heading to " + destination + "\ninvoice: " + invoice));
        }
    }else{
        QMessageBox::warning(this, "warning", "Not all fields are specified.");
    }

}


void MainWindow::on_exit_button_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "please resubmit", "do you want to quit?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        QCoreApplication::quit();//exiting whole app
    }
}


void MainWindow::on_show_all_button_clicked()
{
    Package* tmp = m_queue->get_head();
    QString message = {""};
    if(tmp == nullptr){
        QMessageBox::information(this, "message", "the queue is empty.");
        return;
    }
    while(tmp != nullptr){
        message += QString::fromStdString(tmp->kind_of_delivery) + " package is of weight "
                   + QString::number(tmp->weight)+ "kg going to " + QString::fromStdString(tmp->destination)
                   + "\ninvoice: " + QString::fromStdString(tmp->invoice_number) + "\n";
        tmp = tmp->next;
    }
    QMessageBox::information(this, "queue:",message);
}

