using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LeftistHeap
{
    class Program
    {
        class Node
        {
            internal int npl = 0;
            internal int key;
            internal int value;
            internal Node parent;
            internal Node leftchild;
            internal Node rightchild;
        }

        static Node leftistHeap;

        static void Main(string[] args)
        {
            Node node1 = new Node();
            node1.key = 15;
            Node node2 = new Node();
            node2.key = 2;
            Node node3 = new Node();
            node3.key = 3;
            Node node4 = new Node();
            node4.key = 22;
            Node node5 = new Node();
            node5.key = 1;
            leftistHeap = Merge(ref node1, ref node2);
            AddNodeTo(ref leftistHeap, ref node3);
            AddNodeTo(ref leftistHeap, ref node4);
            AddNodeTo(ref leftistHeap, ref node5);
            Console.WriteLine(ExtractMaxKey(ref leftistHeap));

            Console.ReadLine();
        }

        static Node Merge(ref Node node1, ref Node node2)
        {
            if (node1 == null)
            {
                return node2;
            }
            if (node2 == null)
            {
                return node1;
            }
            int k1 = node1.key;
            int k2 = node2.key;
            if (k1 < k2)
            {
                Swap(ref node1, ref node2);
            }
            node1.rightchild = Merge(ref node1.rightchild, ref node2);
            node1.rightchild.parent = node1;
            if (Npl(node1.rightchild) > Npl(node1.leftchild))
            {
                Swap(ref node1.rightchild, ref node1.leftchild);
            }
            node1.npl = Npl(node1.rightchild) + 1;
            return node1;
        }

        static void Swap(ref Node node1, ref Node node2)
        {
            Node temp = node1;
            node1 = node2;
            node2 = temp;
        }

        static int Npl(Node node)
        {
            if (node == null)
            {
                return -1;
            }
            if (node.rightchild == null)
            {
                return 0;
            }
            return node.rightchild.npl + 1;
        }

        static void AddNodeTo(ref Node leftistHeap, ref Node node)
        {
            leftistHeap = Merge(ref leftistHeap, ref node);
        }

        static int ExtractMaxKey(ref Node node)
        {
            int maxkey = node.key;
            node.leftchild.parent = null;
            node.rightchild.parent = null;
            node = Merge(ref node.leftchild, ref node.rightchild);
            return maxkey;
        }
    }
}
