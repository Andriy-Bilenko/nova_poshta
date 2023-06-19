#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <string>

///
/// \brief Package \struct is a node, and our queue will contain list of these nodes
///
struct Package{
    double weight{};
    std::string invoice_number{""};
    std::string destination{""};
    std::string kind_of_delivery{""};
    Package* next{nullptr};
};

///
/// \brief The Queue \class had to be manually constructed (that was the main task)
///
class Queue{
public:
    /// \brief destrcutor
    /// empties the queue
    ~Queue();
    ///
    /// \brief Enqueue \fn inserts a package to the rear of the queue
    /// \param package will be inserted to a queue
    ///
    void Enqueue(const Package package);
    ///
    /// \brief Dequeue \fn pops the package at the front if available
    ///
    void Dequeue();
    ///
    /// \brief search_deliveries_to \fn traverses the queue in order to find number of occurencies of
    /// packages with destination = place \param.
    /// \param place is an input parameter
    /// \param num_of_deliveries is an output parameter
    ///
    void search_deliveries_to(const std::string place, int& num_of_deliveries);
    ///
    /// \brief sum_weight_in_category \fn traverses the queue in order to find sum of weights of
    /// packages with kind_of_delivery = category \param.
    /// \param category is an input parameter
    /// \param weight is an output parameter
    ///
    void sum_weight_in_category(const std::string category, double& weight);
    ///
    /// \brief find_by_invoice \fn finds the first from head package with invoice_number = invoice \param.
    /// \param invoice is an input parameter
    /// \param package is an output parameter
    ///
    void find_by_invoice(const std::string invoice, Package& package);
    ///
    ///getters:
    Package* get_head();
    Package* get_rear();

private:
    //member variables
    Package* m_head{nullptr};
    Package* m_rear{nullptr};
};

#endif // QUEUE_HPP
