using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MultiwaysMerging
{
    public struct Node
    {
        public int key;
        public int serial;
    }

    class MinQueue
    {
        private List<Node> queue = new List<Node>();

        private void SiftUp(int currentIndex)
        {
            while (currentIndex >= 1)
            {
                int parent = (currentIndex - 1) / 2;
                if (queue[parent].key <= queue[currentIndex].key)
                {
                    break;
                }
                Node node = queue[parent];
                queue[parent] = queue[currentIndex];
                queue[currentIndex] = node;
                currentIndex = parent;
            }
        }

        private void SiftDown(int currentIndex)
        {
            while (currentIndex < queue.Count() / 2)
            {
                int child = currentIndex * 2 + 1;
                if ((child + 1 < queue.Count()) && (queue[child + 1].key < queue[child].key))
                {
                    child += 1;
                }
                if (queue[child].key >= queue[currentIndex].key)
                {
                    break;
                }
                Node node = queue[child];
                queue[child] = queue[currentIndex];
                queue[currentIndex] = node;
                currentIndex = child;
            }
        }

        public void Append(Node node)
        {
            queue.Add(node);
            SiftUp(queue.Count()-1);
        }

        public Node ExtractMin()
        {
            Node minNode = queue[0];
            queue[0] = queue[queue.Count() - 1];
            queue.RemoveAt(queue.Count() - 1);
            SiftDown(0);
            return minNode;
        }
    }

    class Program
    {
        
        static void Main(string[] args)
        {
            List<int> array = new List<int>();
            Random rand = new Random();
            string[] namesOfFiles = {"data8192.txt", "data16384.txt", "data32768.txt", "data65536.txt",
            "data131072.txt","data262144.txt"};
            for (int j = 0; j < namesOfFiles.Length; j++)
            {
                System.IO.StreamReader file = new System.IO.StreamReader(@"C:\Users\Zerbs\Desktop\Additions\" + namesOfFiles[j]);
                int numberOfElements = int.Parse(file.ReadLine());
                int[] arrayForSorting = new int[numberOfElements];
                for (int i = 0; i < numberOfElements; i++)
                {
                    arrayForSorting[i] = int.Parse(file.ReadLine());
                }
                file.Close();
                DateTime one = DateTime.Now;
                List<Node> listOfNodes = ConvertToListOfNodes(arrayForSorting);
                listOfNodes = MMergeSort(listOfNodes, 5);
                DateTime two = DateTime.Now;
                Console.WriteLine("For " + namesOfFiles[j] + " : " + (two - one));
            }
            Console.ReadLine();
        }

        static List<Node> ConvertToListOfNodes(int[] array)
        {
            List<Node> listOfNodes = new List<Node>();
            for (int i = 0; i < array.Count(); i++)
            {
                Node node = new Node();
                node.key = array[i];
                node.serial = 0;
                listOfNodes.Add(node);
            }
            return listOfNodes;
        }

        static List<Node> MMergeSort(List<Node> array, int numberOfWays)
        {
            if (array.Count() <= 1)
            {
                return array;
            }
            int initialSerial = array[0].serial;
            List<List<Node>> series = new List<List<Node>>();
            for (int i = 0; i < numberOfWays; i++)
            {
                series.Add(new List<Node>());
            }
            for (int i = 0; i < array.Count(); i++)
            {
                Node node = new Node();
                node.key = array[i].key;
                node.serial = i % numberOfWays;
                series[i % numberOfWays].Add(node);
            }
            for (int i = 0; i < numberOfWays; i++)
            {
                series[i] = MMergeSort(series[i],numberOfWays);
            }
            List<Node> merged = Merge(series);
            for (int i = 0; i < merged.Count(); i++)
            {
                Node node = new Node();
                node.key = merged[i].key;
                node.serial = initialSerial;
                merged[i] = node;
            }
            return merged;
        }

        static List<Node> Merge(List<List<Node>> series)
        {
            List<int> indexes = new List<int>();
            MinQueue queue = new MinQueue();
            List<Node> merged = new List<Node>();
            int numberOfSteps = 0;
            for (int i = 0; i < series.Count(); i++)
            {
                indexes.Add(0);
                if (series[i].Count() > 0)
                {
                    numberOfSteps += series[i].Count();
                    queue.Append(series[i][0]);
                    indexes[i] += 1;
                }
            }
            for (int i = 0; i < numberOfSteps; i++)
            {
                merged.Add(queue.ExtractMin());
                if (indexes[merged.Last().serial] < series[merged.Last().serial].Count())
                {
                    queue.Append(series[merged.Last().serial][indexes[merged.Last().serial]]);
                    indexes[merged.Last().serial] += 1;
                }
            }
            return merged;
        }
    }
}
