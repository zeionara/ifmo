using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SplayTree
{
    public class Node
    {
        public Node left;
        public Node right;
        public Node parent;
        public int key;
        public Node(Node left, Node right, int key)
        {
            this.left = left;
            this.right = right;
            this.key = key;
        }

        public void KeepParent()
        {
            if (left != null)
            {
                left.parent = this;
            }
            if (right != null)
            {
                right.parent = this;
            }
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
                    int keyindex = rnd.Next(numberOfElements);
                    int key = 0;

                    for (int i = 0; i < numberOfElements; i++)
                    {
                        root = Insert(root, int.Parse(file.ReadLine()));
                        if (i == keyindex)
                        {
                            key = root.key;
                        }
                    }
                    file.Close();

                    DateTime one = DateTime.Now;
                    try
                    {
                        root = Find(root, key);
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

        public static void SetParent(Node child, Node parent)
        {
            if (child != null)
            {
                child.parent = parent;
            }
        }

        public static void Rotate(Node parent, Node child)
        {
            Node gparent = parent.parent;
            if (gparent != null)
            {
                if (gparent.left == parent)
                {
                    gparent.left = child;
                } else
                {
                    gparent.right = child;
                }
            }
            if (parent.left == child)
            {
                parent.left = child.right;
                child.right = parent;
            } else
            {
                parent.right = child.left;
                child.left = parent;
            }
            parent.KeepParent();
            child.KeepParent();
            SetParent(child, gparent);
        }

        public static Node Splay(Node node)
        {
            if (node.parent == null)
            {
                return node;
            }
            Node parent = node.parent;
            Node gparent = parent.parent;
            if (gparent == null)
            {
                Rotate(parent, node);
                return node;
            }
            if ((gparent.left == parent) == (parent.left == node))
            {
                Rotate(gparent, parent);
                Rotate(parent, node);
            } else
            {
                Rotate(parent, node);
                Rotate(gparent, node);
            }
            return Splay(node);
        }

        public static Node Find(Node root, int key)
        {
            if (root == null)
            {
                return null;
            }
            if (root.key == key)
            {
                return Splay(root);
            }
            if ((root.key > key) && (root.left != null))
            {
                return Find(root.left, key);
            }
            if ((root.key < key) && (root.right != null))
            {
                return Find(root.right, key);
            }
            return Splay(root);
        }

        public static List<Node> Split(Node root, int key)
        {
            List<Node> lr = new List<Node>();
            if (root == null)
            {
                lr.Add(null);
                lr.Add(null);
                return lr;
            }
            root = Find(root, key);
            if (root.key == key)
            {
                SetParent(root.left, null);
                SetParent(root.right, null);
                lr.Add(root.left);
                lr.Add(root.right);
                return lr;
            }
            if (root.key > key)
            {
                SetParent(root.left, null);
                lr.Add(root.left);
                root.left = null;
                lr.Add(root);
                return lr;
            }
            else
            {
                SetParent(root.right, null);
                Node right = root.right;
                root.right = null;
                lr.Add(root);
                lr.Add(right);
                return lr;
            }
        } 

        public static Node Insert(Node root, int key)
        {
            List<Node> lr = Split(root, key);
            Node node = new Node(lr[0], lr[1], key);
            node.KeepParent();
            return node;
        }

        public static Node Merge(Node left, Node right)
        {
            if (left == null)
            {
                return right;
            }
            if (right == null)
            {
                return left;
            }
            right = Find(right, left.key);
            right.left = left;
            left.parent = right;
            return right;
        }

        public static Node Remove(Node root, int key)
        {
            root = Find(root, key);
            SetParent(root.left, null);
            SetParent(root.right, null);
            return Merge(root.left, root.right);
        }
    }
}