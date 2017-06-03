using System;
using System.Collections;
using System.Collections.Generic;
//using System.Linq;
//using System.Text;

using st = System.Collections.Stack;

namespace ConsoleApplication1
{
    class MyStack
    {
        st mystack;
        public MyStack()
        {
            mystack = new st();
            mystack.Push(12);
            mystack.Push(11);
            Console.WriteLine("Element in stack: {0}", mystack.Pop());
            Console.WriteLine("Type of stack = {0}", mystack.GetType());
            Console.WriteLine("String representation of object-stack =" + mystack.ToString());
            Console.WriteLine("Stack contains number 12, it is {0}", mystack.Contains(12));
            Console.WriteLine("Stack contains number 10, it is {0}", mystack.Contains(10));
            mystack.Clear();
            mystack.Push(1);
            mystack.Push(2);
            object[] arr = mystack.ToArray();
            for (int i = 0; i < arr.Length; i++)
            {
                Console.WriteLine("{0} element in stack = {1}", i, arr[i]);
            }
        }
    }
    class MyHashTable
    {
        Hashtable myhashtable;
        public MyHashTable()
        {
            myhashtable = new Hashtable();
            myhashtable.Add("net", "network");
            myhashtable.Add("com", "computer");
            myhashtable.Add("sel", "selection");
            if (!myhashtable.Contains("sel"))
            {
                myhashtable.Add("sel", "selector");
            }
            object[] arrayforhash = new object[10];
            Hashtable mynewhashtable = (Hashtable)myhashtable.Clone();
            mynewhashtable.Clear();
            myhashtable.CopyTo(arrayforhash, 0);
            int numberofhashelements = myhashtable.Count;
            Console.WriteLine(" Myhashtable has fixed size, it is " + myhashtable.IsFixedSize);
            Console.WriteLine("Array, created from hash table:");
            for (int i = 0; i < arrayforhash.Length; i++)
            {
                Console.WriteLine(arrayforhash[i]);
            }
        }
    }
    class MyArrayList
    {
        ArrayList arraylist;
        public MyArrayList()
        {
            arraylist = new ArrayList();
            arraylist.Add(5);
            arraylist[0] = 4;
            for (int i = 0; i <= 100; i++)
            {
                arraylist.Add(i);
            }
            for (int i = 0; i <= 2; i++)
            {
                Console.WriteLine("Type correct number:");
                arraylist.Add(int.Parse(Console.ReadLine()));
            }
            Console.WriteLine("First 6 elements in arraylist: ");
            for (int i = 5; i <= 10; i++)
            {
                Console.WriteLine(arraylist[i]);
                arraylist.Remove(arraylist[i]);
            }
        }
    }
    class MyQueue
    {
        Queue myqueue;
        public MyQueue()
        {
            myqueue = new Queue();
            Random rand = new Random();
            for (int i = 0; i < 10; i++)
            {
                myqueue.Enqueue((float)(rand.NextDouble() * 12));
            }
            Console.WriteLine("Type of queue = {0}", myqueue.GetType());
            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine("Next deleted element in queue = {0:0.##}", myqueue.Dequeue());
            }
            Console.WriteLine("Queue contains number 10 it is {0}",myqueue.Contains(5));
            myqueue.Clear();
            for (int i = 0; i < 10; i++)
            {
                myqueue.Enqueue(i * 15);
            }
            Console.WriteLine("Queue begins at element = " + myqueue.Peek().ToString());
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            //ArrayList
            MyArrayList myNewArrayList = new MyArrayList();
            //Stack
            MyStack myNewStack = new MyStack();
            //Queue
            MyQueue myNewQueue = new MyQueue();
            //Hashtable
            MyHashTable myNewHashTable = new MyHashTable();
            //Typed List to int
            List<int> listofint = new List<int>();
            Console.Read();
        }
    }
}
