using System;
using System.Collections.Generic;

using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BinarySearch
{
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

                    List<int> array = new List<int>();
                    for (int i = 0; i < numberOfElements; i++)
                    {
                        //Пишем все элементы в массив
                        array.Add(int.Parse(file.ReadLine()));
                    }
                    file.Close();

                    //Для возможности бинарного поиска сортируем массив
                    array.Sort();
                    int keyindex = rnd.Next(1, numberOfElements);

                    DateTime one = DateTime.Now;
                    try
                    {
                        BinarySearch(array, array[keyindex]);
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

        static int BinarySearch(List<int> sortedarray, int key)
        {
            int p = 0;
            int l = 0;
            int r = sortedarray.Count - 1;
            
            while (l <= r)
            {
                p = l + (r - l) / 2;
                if (sortedarray[p] > key)
                {
                    r = p - 1;
                } else if (sortedarray[p] < key)
                {
                    l = p + 1;
                    
                } else
                {
                    return p;
                }
            }
            throw new ArgumentException();
        }
    }
}
