using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BinarySearchTree
{
    public class Node
    {
        public Node left;
        public Node right;
        public int key;
        public Node(Node left, Node right, int key)
        {
            this.left = left;
            this.right = right;
            this.key = key;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            string[] namesOfFiles = {"data8192.txt", "data16384.txt", "data32768.txt", "data65536.txt",
            "data131072.txt","data262144.txt"};
            for (int j = 0; j < namesOfFiles.Length; j++)
            {
                List<int> times = new List<int>();
                for (int k = 0; k < 5; k++)
                {
                    Random rnd = new Random();
                    System.IO.StreamReader file = new System.IO.StreamReader(@"C:\Users\Zerbs\Desktop\" + namesOfFiles[j]);
                    int numberOfElements = int.Parse(file.ReadLine());

                    Node root = null;
                    
                    int keyindex = rnd.Next(1, numberOfElements);
                    int key = 0;

                    for (int i = 0; i < numberOfElements; i++)
                    {
                        if (i == keyindex)
                        {
                            key = int.Parse(file.ReadLine());
                            root = Insert(root, key);
                        } else
                        {
                            root = Insert(root, int.Parse(file.ReadLine()));
                        }
                    }
                    file.Close();

                    DateTime one = DateTime.Now;
                    try
                    {
                        Find(root, key);
                    }
                    catch (ArgumentException)
                    {

                    }
                    DateTime two = DateTime.Now;
                    times.Add(two.Millisecond - one.Millisecond);
                }
                Console.WriteLine("Average time for " + namesOfFiles[j] + "is " + times.Average() + "ms");
            }
            Console.ReadLine();
        }

        public static Node Find(Node root, int key)
        {
            if (root == null)
            {
                throw new ArgumentException();
            }
            if (root.key == key)
            {
                return root;
            }
            if ((root.key > key) && (root.left != null))
            {
                return Find(root.left, key);
            }
            if ((root.key < key) && (root.right != null))
            {
                return Find(root.right, key);
            }
            throw new ArgumentException();
        }

        public static Node Insert(Node root, int key)
        {
            if (root == null)
            {
                return new Node(null, null, key);
            }
            if (root.key == key)
            {
                return new Node(root.left, root.right, key);
            }
            if (root.key > key)
            {
                root.left = Insert(root.left, key);
            }
            if (root.key < key)
            {
                root.right = Insert(root.right, key);
            }
            return root;
        }

        public static Node FindMin(Node root)
        {
            return (root.left == null) ? root.left : root;
        }

        public static Node RemoveMin(Node root)
        {
            if (root == null)
            {
                return null;
            }
            if (root.left == null)
            {
                return root.right;
            }
            root.left = RemoveMin(root.left);
            return root;
        }

        public static Node RemoveKey(Node root, int key)
        {
            if (root == null)
            {
                return null;
            }
            if (key < root.key)
            {
                root.left = RemoveKey(root.left, key);
            }
            else if (key > root.key)
            {
                root.right = RemoveKey(root.right, key);
            }
            else
            {
                Node l = root.left;
                Node r = root.right;
                if (r == null)
                {
                    return l;
                }
                Node min = FindMin(r);
                min.right = RemoveMin(r);
                min.left = l;
                return min;
            }
            return root;
        }
    }
}
