using System;
using System.Threading;

namespace FirstLab
{
    class Threads
    {

        static void Main()
        {
            Thread mainThread = new Thread(main);
            mainThread.Start();
        }

        static void main()
        {
            Semaphore main_work_semaphore;
            Semaphore main_sum_element_semaphore;

            main_work_semaphore = new Semaphore(0, 1);
            main_sum_element_semaphore = new Semaphore(0, 1);

            int arraySize = getIntFromUser("Please, type size of array:");
            uint[] array = new uint[arraySize];

            for (int i = 0; i < arraySize; i++){
              array[i] = getUintFromUser("Please, type "+(i+1)+" element of array:");
            }

            showArray(array);

            int k = getIntFromUser("Please, type k:");

            //Create threads
            Thread workThread = new Thread(() => work(ref array, k, ref main_work_semaphore));
            Thread sumElementThread = new Thread(() => SumElement(ref array, k, ref main_sum_element_semaphore));

            //Run threads
            workThread.Start();
            sumElementThread.Start();

            int current_index = 0;
            while (current_index < k){
              main_work_semaphore.WaitOne();
              Console.WriteLine("main: "+(current_index+1)+" element is known: "+array[current_index]);
              current_index++;
            }
            Console.WriteLine("main: "+k+" elements are known, so signaling to the SumElement...");
            main_sum_element_semaphore.Release();
        }

        static void work(ref uint[] array, int k, ref Semaphore main_work_semaphore)
        {
            int rest_interval = getIntFromUser("Please, type rest interval (milliseconds):");
            for (int i = 0; i < array.Length; i++){
              int selected_element = i;
              for (int j = i; j < array.Length; j++){
                if (isSimple(array[j])){
                  selected_element = j;
                  break;
                }
              }
              uint tmp = array[i];
              array[i] = array[selected_element];
              array[selected_element] = tmp;
              Console.WriteLine("work: "+(i+1)+" element is ready!");
              if (i < k) main_work_semaphore.Release();
              Thread.Sleep(rest_interval);
            }
        }

        static void SumElement(ref uint[] array, int k, ref Semaphore main_sum_element_semaphore)
        {
            main_sum_element_semaphore.WaitOne();
            Console.WriteLine("SumElement: Sum of first "+k+" elements of array is "+countSum(array,k));
        }

        static void showArray(uint[] array){
          Console.Write("Given array with size "+array.Length+" and elements ");
          for (int i = 0; i < array.Length; i++){
            if (i != 0) Console.Write(", ");
            Console.Write(array[i]);
          }
          Console.WriteLine();
        }

        static uint countSum(uint[] array, int k){
          uint sum = 0;
          for (int i = 0; i < k; i++){
            sum += array[i];
          }
          return sum;
        }

        static bool isSimple(uint number){
          if (number < 2) return true;
          for (uint i = 2; i < (uint)(Math.Floor(Math.Sqrt(number)) + 1); i++){
            if (0 == number % i) return false;
          }
          return true;
        }

        static uint getUintFromUser(string msg){
          Console.WriteLine(msg);
          return Convert.ToUInt32(Console.ReadLine());
        }

        static int getIntFromUser(string msg){
          Console.WriteLine(msg);
          return Convert.ToInt32(Console.ReadLine());
        }
    }
}
