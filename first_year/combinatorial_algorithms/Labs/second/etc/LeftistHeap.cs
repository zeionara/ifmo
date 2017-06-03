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

            public Node(int key)
            {
                this.key = key;
            }
        }

        static Node leftistHeap;

        static void Main(string[] args)
        {
            string[] namesOfFiles = {"data8192.txt", "data16384.txt", "data32768.txt", "data65536.txt",
            "data131072.txt","data262144.txt"};
            Node node;
            for (int j = 0; j < namesOfFiles.Length; j++)
            {
                System.IO.StreamReader file = new System.IO.StreamReader(@"C:\Users\Zerbs\Desktop\Additions\"+namesOfFiles[j]);
                int numberOfElements = int.Parse(file.ReadLine());
                int[] arrayForSorting = new int[numberOfElements];
                for (int i = 0; i < numberOfElements; i++)
                {
                    arrayForSorting[i] = int.Parse(file.ReadLine());
                }
                file.Close();
                DateTime one = DateTime.Now;
                for (int i = 0; i < numberOfElements; i++)
                {
                    node = new Node(arrayForSorting[i]);
                    AddNodeTo(ref leftistHeap, ref node);
                }
                for (int i = 0; i < numberOfElements; i++)
                {
                    arrayForSorting[numberOfElements - 1 - i] = ExtractMaxKey(ref leftistHeap);
                }
                DateTime two = DateTime.Now;
                Console.WriteLine("For " + namesOfFiles[j] + " : " + (two - one));
            }
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
            node1.npl = Npl(node1);
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
            if (node.rightchild != null)
            {
                node.leftchild.parent = null;
            }
            if (node.rightchild != null)
            {
                node.rightchild.parent = null;
            }
            node = Merge(ref node.leftchild, ref node.rightchild);
            return maxkey;
        }
    }
}
