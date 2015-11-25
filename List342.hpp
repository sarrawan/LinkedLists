#ifndef List342_hpp
#define List342_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

template <class ItemType>
class List342
{
    template <class T>
    friend ostream& operator<<(ostream &outStream, const List342<T> &other);
    
public:
    List342();
    List342(const List342<ItemType> &other);
    virtual ~List342();
    
    bool BuildList(string fileName);
    bool Insert(ItemType *obj);
    bool Remove(ItemType target, ItemType &result);
    bool Peek(ItemType target, ItemType &result);
    bool isEmpty();
    void DeleteList();
    bool Merge(List342<ItemType> &list);
    bool MoveToEnd(ItemType target);
     
    List342<ItemType> operator+(const List342<ItemType> &other) const;
    List342<ItemType>& operator+=(const List342<ItemType> &other);
    
    bool operator==(const List342<ItemType> &other) const;
    bool operator!=(const List342<ItemType> &other) const;
    
    List342<ItemType>& operator=(const List342<ItemType> &other);
    
private:
    
    struct Node
    {
        ItemType *data;
        Node *next = NULL;
    };
    Node *headPtr;
};

template <class ItemType>
bool List342<ItemType>::MoveToEnd(ItemType target)
{
    Node *temp = NULL;
    if(headPtr == NULL)
    {
        return false;
    }
    if(*headPtr->data == target)
    {
        temp = headPtr;
        headPtr = headPtr->next;
    }
    Node *current = headPtr;
    while(current->next != NULL)
    {
        if(*current->next->data == target && temp == NULL)
        {
            temp = current->next;
            current->next = current->next->next;
            temp->next = NULL;
        }
        else
        {
            current = current->next;
        }
    }
    current->next = temp;
    return (temp == NULL);
}


template<class ItemType>
List342<ItemType>::List342()
{
    headPtr = NULL;
}

template<class ItemType>
List342<ItemType>::List342(const List342<ItemType> &other)
{
    headPtr = NULL;
    *this = other;
}

template<class ItemType>
List342<ItemType>::~List342()
{
    DeleteList();
}

template<class ItemType>
bool List342<ItemType>::BuildList(string file)
{
    if(file.empty())
    {
        return false;
    }
    else
    {
        ifstream inFile(file);
        if(inFile.is_open())
        {
            string line;
            while(getline(inFile, line))
            {
                stringstream inputLine(line);
                ItemType *p = new ItemType;
                inputLine >> *p;
                Insert(p);
                delete p;
            }
            inFile.close();
            return true;
        }
        else
        {
            return false;
        }
    }
}


template <class ItemType>
bool List342<ItemType>::Insert(ItemType *obj)
{
    Node *insNode;
    ItemType *insItem;
    if(headPtr == NULL)
    {
        insNode = new Node;
        insItem = new ItemType;
        (*insItem) = (*obj);
        insNode->data = insItem;
        headPtr = insNode;
        return true;
    }
    if(*headPtr->data > *obj)
    {
        insNode = new Node;
        insItem = new ItemType;
        (*insItem) = (*obj);
        insNode->data = insItem;
        insNode->next = headPtr;
        headPtr = insNode;
        return true;
    }
    if(*headPtr->data == *obj)
    {
        return false;
    }
    else
    {
        Node *temp = headPtr;
        while(temp->next != NULL && (*temp->next->data < *obj))
        {
            temp = temp->next;
        }
        if(temp->next != NULL && *temp->next->data == *obj)
        {
            return false;
        }
        insNode = new Node;
        insItem = new ItemType;
        (*insItem) = (*obj);
        insNode->data = insItem;
        insNode->next = temp->next;
        temp->next = insNode;
        return true;

    }
    return false;
}

template <class ItemType>
bool List342<ItemType>::Remove(ItemType target, ItemType &result)
{
    if(headPtr == NULL)
    {
        return false;
    }
    Node *temp, *removeNode;
    ItemType *removeItem;
    if(*headPtr->data == target)
    {
        result = target;
        removeNode = headPtr;
        removeItem = headPtr->data;
        headPtr = headPtr->next;
        delete removeItem;  //del removeNode->data
        delete removeNode;
        removeItem = NULL;
        removeNode = NULL;
        return true;
    }
    else
    {
        temp = headPtr;
        while(temp->next != NULL && *temp->next->data != target)
        {
            temp = temp->next;
        }
        if(temp->next == NULL)
        {
            return false;
        }
        else
        {
            result = target;
            removeNode = temp->next;
            removeItem = removeNode->data;
            temp->next = temp->next->next;
            delete removeItem;
            delete removeNode;
            removeItem = NULL;
            removeNode = NULL;
            return true;
        }
    }
}

template <class ItemType>
bool List342<ItemType>::Peek(ItemType target, ItemType &result)
{
    Node *current = headPtr;
    while((current != NULL))
    {
        if(*current->data == target)
        {
            result = target;
            return true;
        }
        else if(*current->data > target)
        {
            return false;
        }
        else
        {
            current = current->next;
        }
    }
    return false;
}

template <class ItemType>
bool List342<ItemType>::isEmpty()
{
    return (headPtr == NULL);
}

template <class ItemType>
void List342<ItemType>::DeleteList()
{
    while(headPtr != NULL)  //current != NULL
    {
        Node *current;
        current = headPtr;
        headPtr = headPtr->next;
        current->next = NULL;
        ItemType *currentItem;
        currentItem = current->data;
        delete currentItem; //current->data
        currentItem = NULL;
        delete current;
        current = NULL;
    }
}

template <class ItemType>
bool List342<ItemType>::Merge(List342<ItemType> &list)
{
    if(this != &list) 
    {
        if(*this == list)
        {
            list.DeleteList();
        }
        else if(headPtr == NULL)
        {
            headPtr = list.headPtr;
            list.headPtr = NULL;
        }
        else
        {
            Node *thisCurrent, *temp;
            if(list.headPtr != NULL) //&& headPtr != NULL)
            {
                thisCurrent = headPtr;
                if(*list.headPtr->data < *thisCurrent->data)
                {
                    temp = list.headPtr;
                    list.headPtr = list.headPtr->next;
                    temp->next = headPtr;
                    headPtr = temp;
                    thisCurrent = headPtr;
                }
                while(list.headPtr != NULL && thisCurrent->next != NULL)
                {
                    if(*list.headPtr->data < *thisCurrent->next->data)
                    {
                        temp = list.headPtr;
                        list.headPtr = list.headPtr->next;
                        temp->next = thisCurrent->next;
                        thisCurrent->next = temp;
                        thisCurrent = thisCurrent->next;
                    }
                    else if(*list.headPtr->data == *thisCurrent->next->data)
                    {
                        temp = list.headPtr;
                        list.headPtr = list.headPtr->next;
                        temp->next = NULL;
                        delete temp->data;
                        delete temp;
                        thisCurrent = thisCurrent->next;
                    }
                    else
                    {
                        thisCurrent = thisCurrent->next;
                    }
                }
                if(list.headPtr != NULL && thisCurrent->next == NULL)
                {
                    temp = list.headPtr;
                    thisCurrent->next = temp;
                    list.headPtr = NULL;
                }
            }
        }
    }
    return true;
}

template <class ItemType>
List342<ItemType> List342<ItemType>::operator+(const List342<ItemType> &other) const
{
    List342<ItemType> result = *this;
    result += other;
    return result;
}

template <class ItemType>
List342<ItemType>& List342<ItemType>::operator+=(const List342<ItemType> &other)
{
    if(headPtr == NULL)
    {
        return (*this = other);
    }
    if(other.headPtr == NULL)
    {
        return *this;
    }
    else
    {
        Node *otherTemp, *add, *thisTemp;
        ItemType *addItem;
        if(*otherTemp->data < *headPtr->data)
        {
            add = new Node;
            addItem = new ItemType;
            (*addItem) = (*otherTemp->data);
            add->data = addItem;
            add->next = headPtr;
            headPtr = add;
            otherTemp = otherTemp->next;
        }
        thisTemp = headPtr;
        while(otherTemp != NULL && thisTemp->next != NULL)
        {
            if(*otherTemp->data < *thisTemp->next->data)
            {
                add = new Node;
                addItem = new ItemType;
                (*addItem) = (*otherTemp->data);
                add->data = addItem;
                add->next = thisTemp->next;
                thisTemp->next = add;
                thisTemp = thisTemp->next;
                otherTemp = otherTemp->next;
            }
            else if(*otherTemp->data > *thisTemp->next->data)
            {
                thisTemp = thisTemp->next;
                
            }
            else  
            {
                otherTemp = otherTemp->next;
            }
        }
        while(otherTemp != NULL)
        {
            add = new Node;
            addItem = new ItemType;
            (*addItem) = (*otherTemp->data);
            add->data = addItem;
            thisTemp->next = add;
            thisTemp = thisTemp->next;
            otherTemp = otherTemp->next;
        }
        
    }
    return *this;
}

template <class ItemType>
bool List342<ItemType>::operator==(const List342<ItemType> &other) const
{
    Node *otherTemp = other.headPtr;
    Node *thisTemp = headPtr;
    bool isEqual = true;
    while((otherTemp != NULL && thisTemp != NULL) && isEqual)
    {
        isEqual = (*otherTemp->data == *thisTemp->data);
        otherTemp = otherTemp->next;
        thisTemp = thisTemp->next;
    }
    if(otherTemp != NULL || thisTemp != NULL) 
    {
        isEqual = false;
    }
    return isEqual;
    
}

template <class ItemType>
bool List342<ItemType>::operator!=(const List342<ItemType> &other) const
{
    Node *otherTemp = other.headPtr;
    Node *thisTemp = headPtr;
    bool isNotEqual = true;
    while((otherTemp != NULL && thisTemp != NULL))
    {
        isNotEqual = (*otherTemp->data != *thisTemp->data);
        otherTemp = otherTemp->next;
        thisTemp = thisTemp->next;
    }
    if(otherTemp != NULL || thisTemp != NULL)
    {
        isNotEqual = true;
    }
    return isNotEqual;
}

template <class ItemType>
List342<ItemType>& List342<ItemType>::operator=(const List342<ItemType> &other)
{
    if(this == &other)
    {
        return *this;
    }
    if(other.headPtr == NULL)
    {
        DeleteList();
        return *this;
    }
    else
    {
        DeleteList();
        Node *temp = other.headPtr;
        headPtr = new Node();
        ItemType *item;
        item = new ItemType;
        (*item) = (*other.headPtr->data);
        headPtr->data = item;
        Node *current = headPtr;
        temp = temp->next;
        Node *insertNode;
        while(temp != NULL)
        {
            insertNode = new Node;
            item = new ItemType;
            (*item) = (*temp->data);
            insertNode->data = item;
            current->next = insertNode;
            current = current->next;
            temp = temp->next;
        }
    }
    return *this;
}




template<class ItemType>
ostream& operator<<(ostream &outStream, const List342<ItemType> &other)
{
    typename List342<ItemType>::Node *temp;
    temp = other.headPtr;
    while(temp != NULL)
    {
        outStream << *temp->data;
        temp = temp->next;
    }
    return outStream;
 
 
}

#endif /* List342_hpp */
