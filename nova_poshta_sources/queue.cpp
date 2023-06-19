#include "queue.hpp"


Queue::~Queue()
{
    while(m_head != nullptr){
        Dequeue();
    }
}

void Queue::Enqueue(const Package package){
    Package* tmp = new Package;
    tmp->weight = package.weight;
    tmp->invoice_number = package.invoice_number;
    tmp->destination = package.destination;
    tmp->kind_of_delivery = package.kind_of_delivery;
    if((m_head == nullptr) && (m_rear == nullptr)){
        m_head = m_rear = tmp;
        return;
    }
    m_rear->next = tmp;
    m_rear = tmp;
}

void Queue::Dequeue(){
    Package* tmp = m_head;
    if(m_head == nullptr){
        return;
    }
    if(m_head == m_rear){
        m_head = m_rear = nullptr;
    }else{
        m_head = m_head->next;
    }
    delete tmp;
}

void Queue::search_deliveries_to(const std::string place, int& num_of_deliveries)
{
    Package* tmp = m_head;
    num_of_deliveries = 0;
    while(tmp != nullptr){
        if(tmp->destination == place){
            num_of_deliveries++;
        }
        tmp = tmp->next;
    }
}

void Queue::sum_weight_in_category(const std::string category, double& weight)
{
    Package* tmp = m_head;
    weight = 0;
    while(tmp != nullptr){
        if(tmp->kind_of_delivery == category){
            weight += tmp->weight;
        }
        tmp = tmp->next;
    }
}

void Queue::find_by_invoice(const std::string invoice, Package& package)
{
    Package* tmp = m_head;
    while(tmp != nullptr){
        if(tmp->invoice_number == invoice){
            package = *tmp;
            return;
        }
        tmp = tmp->next;
    }
}

Package *Queue::get_head()
{
    return m_head;
}

Package *Queue::get_rear()
{
    return m_rear;
}



