#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "queue.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);//constructor
    ~MainWindow();//destructor
private slots:
    ///
    /// \brief on_deliver_button_clicked
    /// dequeues and displays a message (what was delivered)
    void on_deliver_button_clicked();
    ///
    /// \brief on_deliver_all_button_clicked
    /// delivers untill queue is empty
    void on_deliver_all_button_clicked();
    ///
    /// \brief on_browse_button_clicked
    /// that one "..." button, triggers file dialog and sets file_path_lineEdit to a chosen by user file path
    void on_browse_button_clicked();
    ///
    /// \brief on_add_from_file_button_clicked
    /// reads all packages from selected file info in format:
    /// {invoice} {weight} {delivery type (one word)} {destination place (one word)}
    /// and adds those packages to a queue
    void on_add_from_file_button_clicked();
    ///
    /// \brief on_add_delivery_manually_button_clicked
    /// reads user's input (comboboxes and weight_lineEdit) and enqueues the created package
    /// shows error message if lineEdit input cannot be converted to a number or not all comboboxes are selected
    void on_add_delivery_manually_button_clicked();
    ///
    /// \brief on_find_button1_clicked
    /// finding number of deliveries to selected destination, shows output as a messageBox
    void on_find_button1_clicked();
    ///
    /// \brief on_find_button2_clicked
    /// finding summary weight of deliveries in selected category, shows output as a messageBox
    void on_find_button2_clicked();
    ///
    /// \brief on_find_button3_clicked
    /// lookup by invoice, invoice example: "INV210432". Shows output in a messageBox
    void on_find_button3_clicked();
    ///
    /// \brief on_exit_button_clicked
    /// asks to resumbit and quits the whole program.
    void on_exit_button_clicked();
    ///
    /// \brief on_show_all_button_clicked
    /// traverses the whole queue and shows all the packages info in a messageBox.
    void on_show_all_button_clicked();
private:
    Ui::MainWindow *ui;
    Queue* m_queue{nullptr};//will be created in constructor and deleted in destructor
};
#endif // MAINWINDOW_H
