using System;
using System.Threading;
using System.Diagnostics;
using System.Collections;

namespace SecondLab
{
    class Boss
    {
        const string CHILD_MUTEX_NAME = "child_mutex_name";
        const string PARENT_MUTEX_NAME = "parent_mutex_name";

        const string A_EVENT_NAME = "a_event_name";
        const string B_EVENT_NAME = "b_event_name";
        const string C_EVENT_NAME = "c_event_name";
        const string D_EVENT_NAME = "d_event_name";

        const string A_R_EVENT_NAME = "a_r_event_name";
        const string B_R_EVENT_NAME = "b_r_event_name";
        const string C_R_EVENT_NAME = "c_r_event_name";
        const string D_R_EVENT_NAME = "d_r_event_name";

        const string A_MUTEX_NAME = "a_mutex_name";
        const string B_MUTEX_NAME = "b_mutex_name";
        const string C_MUTEX_NAME = "c_mutex_name";
        const string D_MUTEX_NAME = "d_mutex_name";

        private static Mutex msg_quantity_mutex;
        private static int msg_quantity;

        private static Semaphore child_handling_semaphore;

        private static Mutex parent_handling_mutex;


        private static ArrayList aThreads;
        private static ArrayList aThreadsInfo;
        private static ArrayList bThreadsInfo;
        private static ArrayList cThreadsInfo;
        private static ArrayList dThreadsInfo;
        private static ArrayList bThreads;

        private static ArrayList cThreads;
        private static ArrayList dThreads;

        private static ArrayList runningThreads;

        private static int parentIndex = 0;
        private static int childIndex = 0;

        static void crp(int tmp){
          Thread parentHandlerThread = new Thread(() => parentHandler(tmp));
          parentHandlerThread.Start();
        }

        static void Main()
        {
          aThreads = new ArrayList();
          aThreadsInfo = new ArrayList();
          bThreads = new ArrayList();
          bThreadsInfo = new ArrayList();

          cThreads = new ArrayList();
          cThreadsInfo = new ArrayList();
          dThreads = new ArrayList();
          dThreadsInfo = new ArrayList();

          runningThreads = new ArrayList();

          child_handling_semaphore = new Semaphore(2, 2);
          msg_quantity_mutex = new Mutex(false);
          parent_handling_mutex = new Mutex(false);
          int child_quantity = getIntFromUser("How many child processes do you want?");
          int parent_quantity = getIntFromUser("How many parent processes do you want?");
          msg_quantity = getIntFromUser("How many messages do you want to get?");
          int tmp;
          for (int i = 0; i < child_quantity; i++){
            tmp = i;
            Thread childHandlerThread = new Thread(() => childHandler(tmp));
            childHandlerThread.Start();
          }

          for (int i = 0; i < parent_quantity; i++){
            tmp = i;
            crp(tmp);
          }

          while (true){
            SwitchHandledProcesses();
            Thread.Sleep(30000);
          }

        }

        static void ShiftChildIndex(){
          childIndex += 1;
          if (childIndex >= cThreads.Count){
            childIndex = 0;
          }
        }

        static void ShiftParentIndex(){
          parentIndex += 1;
          if (parentIndex >= aThreads.Count){
            parentIndex = 0;
          }
        }

        static void SwitchHandledProcesses(){
          Console.WriteLine("Switching...");
          foreach(Thread thread in runningThreads){
            thread.Interrupt();
          }
          runningThreads = new ArrayList();
          ArrayList runningThreadsInfo = new ArrayList();

          runningThreadsInfo.Add(aThreadsInfo[parentIndex]);
          runningThreadsInfo.Add(bThreadsInfo[parentIndex]);
          ShiftParentIndex();
          runningThreadsInfo.Add(cThreadsInfo[childIndex]);
          runningThreadsInfo.Add(dThreadsInfo[childIndex]);
          ShiftChildIndex();
          runningThreadsInfo.Add(cThreadsInfo[childIndex]);
          runningThreadsInfo.Add(dThreadsInfo[childIndex]);
          ShiftChildIndex();

          foreach(ArrayList info in runningThreadsInfo){
            //Console.WriteLine("start!");
            EventWaitHandle arg0 = (EventWaitHandle)info[0];
            EventWaitHandle arg1 = (EventWaitHandle)info[1];
            Mutex arg2 = (Mutex)info[2];
            Thread thread = new Thread(() => fEventHandler(ref arg0, ref arg1, ref arg2, (int)info[3], (string)info[4], (string)info[5]));
            //Console.WriteLine(thread);
            runningThreads.Add(thread);
            thread.Start();
          }

        }

        static void parentHandler(int id){
          Console.WriteLine("Parent "+id+" is created");
          EventWaitHandle ewh_a = new EventWaitHandle(false, EventResetMode.ManualReset, A_EVENT_NAME+"_"+id);
          EventWaitHandle ewh_b = new EventWaitHandle(false, EventResetMode.ManualReset, B_EVENT_NAME+"_"+id);

          EventWaitHandle ewh_r_a = new EventWaitHandle(true, EventResetMode.ManualReset, A_R_EVENT_NAME+"_"+id);
          EventWaitHandle ewh_r_b = new EventWaitHandle(true, EventResetMode.ManualReset, B_R_EVENT_NAME+"_"+id);

          Mutex mta = new Mutex(false, A_MUTEX_NAME+"_"+id);
          Mutex mtb = new Mutex(false, B_MUTEX_NAME+"_"+id);

          aThreadsInfo.Add(new ArrayList{ewh_a, ewh_r_a, mta, id, "A", "parent"});
          Thread aEventHandlerThread = new Thread(() => fEventHandler(ref ewh_a, ref ewh_r_a, ref mta, id, "A", "parent"));
          aThreads.Add(aEventHandlerThread);
          //aEventHandlerThread.Start();
          //Console.WriteLine();
          bThreadsInfo.Add(new ArrayList{ewh_b, ewh_r_b, mtb, id, "B", "parent"});
          Thread bEventHandlerThread = new Thread(() => fEventHandler(ref ewh_b, ref ewh_r_b, ref mtb, id, "B", "parent"));
          bThreads.Add(bEventHandlerThread);
          //bEventHandlerThread.Start();

          Process process_parent = new Process();
          process_parent.StartInfo.FileName = "parent.exe";
          process_parent.StartInfo.Arguments = ""+id;
          process_parent.Start();

          //aEventHandlerThread.Join();
          //bEventHandlerThread.Join();
          //Console.Write("Handled");

          process_parent.WaitForExit();
        }

        static void fEventHandler(ref EventWaitHandle ewh, ref EventWaitHandle rewh, ref Mutex mt, int id, string msg_type, string proc_type){
          int lok = 10;
          try{
            while(true){
              //if (proc_type == "parent") {parent_handling_mutex.WaitOne();} else {
              //  child_handling_semaphore.WaitOne();
              //};
              ewh.WaitOne();
              Console.WriteLine("Got message "+msg_type+" from "+id+" "+proc_type+"!");
              mt.WaitOne();
              ewh.Reset();
              rewh.Set();
              mt.ReleaseMutex();
              //if (proc_type == "parent") {parent_handling_mutex.ReleaseMutex();} else {
              //  child_handling_semaphore.Release();
              //};
              msg_quantity_mutex.WaitOne();
              msg_quantity -= 1;
              lok = msg_quantity;
              msg_quantity_mutex.ReleaseMutex();
              if (lok < 1) {
                Console.WriteLine("Maximal number of messages reached. Exiting...");
                Environment.Exit(0);
              }
            }
          } catch(ThreadInterruptedException e)
          {
            //Console.WriteLine("switching");
          }
        }

        /*static void bEventHandler(ref EventWaitHandle ewh, ref EventWaitHandle rewh, ref Mutex mt, int id){
          Console.WriteLine("----------b------"+id);
          while(true){
            ewh.WaitOne();
            Console.WriteLine("Got message B from "+id+" parent!");
            mt.WaitOne();
            ewh.Reset();
            rewh.Set();
            mt.ReleaseMutex();
          }
        }

        static void aEventHandler(ref EventWaitHandle ewh, ref EventWaitHandle rewh, ref Mutex mt, int id){
          Console.WriteLine("---------a-------"+id);
          while(true){
            ewh.WaitOne();
            Console.WriteLine("Got message A from "+id+" parent!");
            mt.WaitOne();
            ewh.Reset();
            rewh.Set();
            mt.ReleaseMutex();
          }
        }*/



        static void childHandler(int id){
          EventWaitHandle ewh_c = new EventWaitHandle(false, EventResetMode.AutoReset, C_EVENT_NAME+"_"+id);
          EventWaitHandle ewh_d = new EventWaitHandle(false, EventResetMode.AutoReset, D_EVENT_NAME+"_"+id);

          EventWaitHandle ewh_r_c = new EventWaitHandle(true, EventResetMode.ManualReset, C_R_EVENT_NAME+"_"+id);
          EventWaitHandle ewh_r_d = new EventWaitHandle(true, EventResetMode.ManualReset, D_R_EVENT_NAME+"_"+id);

          Mutex mtc = new Mutex(false, C_MUTEX_NAME+"_"+id);
          Mutex mtd = new Mutex(false, D_MUTEX_NAME+"_"+id);

          cThreadsInfo.Add(new ArrayList{ewh_c, ewh_r_c, mtc, id, "C", "child"});
          Thread cEventHandlerThread = new Thread(() => fEventHandler(ref ewh_c, ref ewh_r_c, ref mtc, id, "C", "child"));
          cThreads.Add(cEventHandlerThread);
          //cEventHandlerThread.Start();

          dThreadsInfo.Add(new ArrayList{ewh_d, ewh_r_d, mtd, id, "D", "child"});
          Thread dEventHandlerThread = new Thread(() => fEventHandler(ref ewh_d, ref ewh_r_d, ref mtd, id, "D", "child"));
          dThreads.Add(dEventHandlerThread);
          //dEventHandlerThread.Start();

          Process process_child = new Process();
          process_child.StartInfo.FileName = "child.exe";
          process_child.StartInfo.Arguments = ""+id;
          process_child.Start();
          //process_child.WaitForExit();
        }

        /*static void cEventHandler(ref EventWaitHandle ewh, ref EventWaitHandle rewh, ref Mutex mt, int id){
          Console.WriteLine("----------c------"+id);
          while(true){
            ewh.WaitOne();
            Console.WriteLine("Got message C from "+id+" child!");
            mt.WaitOne();
            ewh.Reset();
            rewh.Set();
            mt.ReleaseMutex();
          }
        }

        static void dEventHandler(ref EventWaitHandle ewh, ref EventWaitHandle rewh, ref Mutex mt, int id){
          Console.WriteLine("---------d-------"+id);
          while(true){
            ewh.WaitOne();
            Console.WriteLine("Got message D from "+id+" child!");
            mt.WaitOne();
            ewh.Reset();
            rewh.Set();
            mt.ReleaseMutex();
          }
        }*/

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
