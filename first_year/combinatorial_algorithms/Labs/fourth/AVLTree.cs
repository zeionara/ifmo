using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AVLTree
{
    class Node
    {
        public Node left;
        public Node right;
        public int key;
        public int height;

        public Node (Node left, Node right, int key)
        {
            this.left = left;
            this.right = right;
            this.key = key;
            height = 1;
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
                    //Загружаем файл
                    System.IO.StreamReader file = new System.IO.StreamReader(@"C:\Users\Zerbs\Desktop\" + namesOfFiles[j]);
                    //В первой строчке - количество элементов
                    int numberOfElements = int.Parse(file.ReadLine());

                    //Получим момент выбора ключа, по которому будем осуществлять поиск
                    int keynum = rnd.Next(numberOfElements);
                    int key = 0;

                    Node root = null;
                    for (int i = 0; i < numberOfElements; i++)
                    {
                        //Читаем и добавляем в дерево все записи из файла
                        root = Insert(root, int.Parse(file.ReadLine()));
                        //Выбираем ключ, по которому будем осуществлять поиск
                        if (i == keynum)
                        {
                            key = root.key;
                        }
                    }
                    //Можем закрыть файл и начать работать с деревом
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

        //Обертка для свойства height
        public static int Height(Node node)
        {
            if (node != null)
            {
                return node.height;
            }
            return 0;
        }

        //Balance - factor выбранного node
        public static int Bfactor(Node node)
        {
            if (node != null)
            {
                return Height(node.right) - Height(node.left);
            }
            return 0;
        }

        //Пересчет высоты узла
        public static void FixHeight(Node node)
        {
            if (node != null)
            {
                int h1 = Height(node.left);
                int h2 = Height(node.right);
                node.height = (h1 > h2 ? h1 : h2) + 1;
            }
        }

        //Правый поворот узла
        public static Node RotateRight(Node node)
        {
            if (node.left != null)
            {
                Node child = node.left;
                node.left = child.right;
                child.right = node;
                FixHeight(node);
                FixHeight(child);
                return child;
            }
            return node;
        }

        //Левый поворот узла
        public static Node RotateLeft(Node node)
        {
            if (node.right != null)
            {
                Node child = node.right;
                node.right = child.left;
                child.left = node;
                FixHeight(node);
                FixHeight(child);
                return child;
            }
            return node;
        }

        //Метод для осуществления балансировки узла
        public static Node Balance(Node node)
        {
            FixHeight(node);
            if (Bfactor(node) == 2)
            {
                if (Bfactor(node.right) < 0)
                {
                    node.right = RotateRight(node.right);
                }
                return RotateLeft(node);
            } else if (Bfactor(node) == -2)
            {
                if (Bfactor(node.right) > 0)
                {
                    node.left = RotateLeft(node.left);
                }
                return RotateRight(node);
            }
            return node;
        }

        //Вставка в дерево
        public static Node Insert(Node root, int key)
        {
            if (root == null)
            {
                return new Node(null, null, key);
            } else if (root.key > key)
            {
                root.left = Insert(root.left, key);
            } else if (root.key < key)
            {
                root.right = Insert(root.right, key);
            }
            return Balance(root);
        }

        //Поиск минимума
        public static Node FindMin(Node root)
        {
            return (root.left == null) ? root.left : root;
        }

        //Удаление минимума
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
            return Balance(root);
        }

        //Удаление ключа из дерева
        public static Node RemoveKey(Node root, int key)
        {
            if (root == null)
            {
                return null;
            }
            if (key < root.key)
            {
                root.left = RemoveKey(root.left, key);
            } else if (key > root.key)
            {
                root.right = RemoveKey(root.right, key);
            } else
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
                return Balance(min);
            }
            return Balance(root);
        }

        //Поиск в АВЛ - дереве
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
    }
}