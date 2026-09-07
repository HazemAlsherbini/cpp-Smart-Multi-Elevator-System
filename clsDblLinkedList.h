#pragma once
#include <iostream>
//using namespace std;



template <class T>
class clsDblLinkedList
{
protected:
    int _Size = 0;
public:
    class Node
    {
    public:
        T Value;
        Node* Next;
        Node* Previous;
    };

    Node* Head;

    clsDblLinkedList()
    {
        Head = NULL;
    }  

    void InsertAtBeginning(T Value)
    {

        /*
            1- Creat a new node with the desired value.
            2- Set the next pointer of the new node to the current head of the list.
            3- Set the previous node of the head to the new node.
            4- Set the head of the list to the new node
        */
        Node* NewNode = new Node();
        NewNode->Value = Value;
        NewNode->Next = Head;
        NewNode->Previous = NULL;

        if (Head != NULL)
            Head->Previous = NewNode;
        Head = NewNode;
        _Size++;
    }

    //void PrintLinkedList()
    //{
    //    Node* Current = Head;
    //    while (Current != NULL)
    //    {
    //        std::cout << Current->Value << " ";
    //        Current = Current->Next;
    //    }
    //}

    //Node* Find(T Value)
    //{
    //    Node* Current = Head;
    //    while (Current != NULL)
    //    {
    //        if (Current->Value == Value)
    //            return Current;
    //        Current = Current->Next;
    //    }
    //    return NULL;
    //}

    void InsertAfter(Node* CurrentNode, T Value)
    {
        /*
            1- Create a new node with the desired value.
            2- Set the previous pointer of the new node to the current node.
            3- Set the next pointer of the new node to the next of the current node.
            4- If the next node after current exists, set the next pointer of the new node to it, otherwise set it to NULL.
            5- Set the next pointer of the current to the new node.
            */

        Node* NewNode = new Node();
        NewNode->Value = Value;
        NewNode->Previous = CurrentNode;
        NewNode->Next = CurrentNode->Next;

        if (CurrentNode->Next != NULL)
            CurrentNode->Next->Previous = NewNode;
        CurrentNode->Next = NewNode;
        _Size++;

    }

    void InsertAfter(int index, T Value)
    {
        Node* N = GetNode(index);
        if (N != NULL)
            InsertAfter(N, Value);
    }

    void InsertAtEnd(T Value)
    {
        /*
            1- Creat a new node with the desired value.
            2- Traverse the list to find the last node.
            3- Set the next pointer of the last to the new.
            4- Set the previous pointer of the new to the last
        */
        Node* NewNode = new Node();
        NewNode->Value = Value;
        NewNode->Next = NULL;

        if (Head == NULL)
        {
            NewNode->Previous = NULL;
            Head = NewNode;
        }
        else
        {
            Node* CurrentNode = Head;
            while (CurrentNode->Next != NULL)
            {
                CurrentNode = CurrentNode->Next;
            }
            NewNode->Previous = CurrentNode;
            CurrentNode->Next = NewNode;
        }
        _Size++;

    }

    void DeleteNode(Node*& NodeToDelete)
    {
        /*
            1- Set the next pointer of the previous to the next of the current.
            2- Set the previous pointer of the nrxt to the prev. of the current.
            3- Delete the current node.
        */

        if (Head == NULL || NodeToDelete == NULL)
            return;

        if (Head == NodeToDelete)
        {
            Head = NodeToDelete->Next;
        }

        if (NodeToDelete->Next != NULL)
            NodeToDelete->Next->Previous = NodeToDelete->Previous;

        if (NodeToDelete->Previous != NULL)
            NodeToDelete->Previous->Next = NodeToDelete->Next;

        delete NodeToDelete;
        _Size--;

    }

    void DeleteFirstNode()
    {
        /*
            1- Store a refrence to head in a temporary variable.
            2- Set the head pointer to the next node.
            3- Se the previous pointer of the head to NULL
            4- Delete temp node.
        */
        if (Head == NULL)
            return;
        Node* Temp = Head;

        Head = Head->Next;
        if (Head != NULL)
            Head->Previous = NULL;
        delete Temp;
        _Size--;

    }

    void DeleteLastNode()
    {
        if (Head == NULL)
            return;

        Node* Current = Head;
        while (Current->Next != NULL)
            Current = Current->Next;

        if (Current->Previous == NULL)
        {
            delete Current;
            Head = NULL;
            return;
        }

        Current->Previous->Next = NULL;
        delete Current;
        _Size--;

    }

    int Size()
    {
        return _Size;
    }

    bool IsEmpty()
    {
        //return Head == NULL;
        return _Size == 0;
    }

    void Clear()
    {
        while (_Size > 0)
            DeleteFirstNode();
        //while (Head != NULL)
        //    DeleteFirstNode();
    }

    void Reverse()
    {
        Node* Current = Head;
        Node* Temp = nullptr;

        while (Current != nullptr)
        {
            Temp = Current->Previous;
            Current->Previous = Current->Next;
            Current->Next = Temp;

            Current = Current->Previous;
        }

        if (Temp != nullptr)
            Head = Temp->Previous;
    }

    Node* GetNode(int index)
    {
        if ((index + 1) > _Size || index < 0)
            return NULL;

        Node* Current = Head;
        //int counter = 0;
        //while (Current != NULL && Current->Next != NULL)
        //{
        //    if (counter == index)
        //        break;
        //    Current = Current->Next;
        //    counter++;
        //}
        for (int i = 0; i < index; i++)
            Current = Current->Next;
        return Current;
    }

    T GetItem(int index)
    {
        Node* N = GetNode(index);

        if (N != NULL)
            return N->Value;
        else
            return NULL;
    }

    bool UpdateItem(int index, T newValue)
    {
        Node* ItemNode = GetNode(index);
        if (ItemNode != NULL)
        {
            ItemNode->Value = newValue;
            return true;
        }
        else
            return false;
    }
};

