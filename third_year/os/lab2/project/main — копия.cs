using System;
using System.Threading;
using System.Diagnostics;

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

        private static int[] childs_receiving = {-1, -1};
        private static int[] childs_receiving_quantity = {0, 0};
        private static int parent_receiving = -1;
        private static int parent_receiving_quantity = 0;

        private static Mutex receiving_control_mutex;

        static void Main()
        {
          msg_quantity_mutex = new Mutex(false);
          receiving_control_mutex = new Mutex(false);
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
            Thread parentHandlerThread = new Thread(() => parentHandler(tmp));
            parentHandlerThread.Start();
          }
        }

        static void parentHandler(int id){
          Console.WriteLine(id);
          EventWaitHandle ewh_a = new EventWaitHandle(false, EventResetMode.ManualReset, A_EVENT_NAME+"_"+id);
          EventWaitHandle ewh_b = new EventWaitHandle(false, EventResetMode.ManualReset, B_EVENT_NAME+"_"+id);

          EventWaitHandle ewh_r_a = new EventWaitHandle(true, EventResetMode.ManualReset, A_R_EVENT_NAME+"_"+id);
          EventWaitHandle ewh_r_b = new EventWaitHandle(true, EventResetMode.ManualReset, B_R_EVENT_NAME+"_"+id);

          Mutex mta = new Mutex(false, A_MUTEX_NAME+"_"+id);
          Mutex mtb = new Mutex(false, B_MUTEX_NAME+"_"+id);

          Thread aEventHandlerThread = new Thread(() => fEventHandler(ref ewh_a, ref ewh_r_a, ref mta, id, "A", "parent"));
          aEventHandlerThread.Start();

          Thread bEventHandlerThread = new Thread(() => fEventHandler(ref ewh_b, ref ewh_r_b, ref mtb, id, "B", "parent"));
          bEventHandlerThread.Start();

          Process process_parent = new Process();
          process_parent.StartInfo.FileName = "parent.exe";
          process_parent.StartInfo.Arguments = ""+id;
          process_parent.Start();

          process_parent.WaitForExit();
        }

        static void fEventHandler(ref EventWaitHandle ewh, ref EventWaitHandle rewh, ref Mutex mt, int id, string msg_type, string proc_type){
          int lok = 10;
          Console.WriteLine("lll");
          while(true){
            while(true){
              Console.WriteLine(id);
              receiving_control_mutex.WaitOne();
              if (((proc_type == "child") && (!Array.Exists(childs_receiving, element => element == id))) ||
              ((proc_type == "parent") && (parent_receiving != id))){
                      if ((proc_type == "child") && (childs_receiving[0] == -1)){
                        childs_receiving[0] = id;
                        childs_receiving_quantity[0] = 1;
                        break;
                      } else if ((proc_type == "child") && (childs_receiving[1] == -1)){
                        childs_receiving[1] = id;
                        childs_receiving_quantity[1] = 1;
                        break;
                      } else if ((proc_type == "parent") && (parent_receiving == -1)){
                        parent_receiving = id;
                        parent_receiving_quantity = 1;
                        break;
                      }
                  }
                  if ((proc_type == "child") && (childs_receiving[0] == id)){
                    childs_receiving_quantity[0] = 2;
                    break;
                  } else if ((proc_type == "child") && (childs_receiving[1] == id)){
                    childs_receiving_quantity[1] = 2;
                    break;
                  } else if ((proc_type == "parent") && (parent_receiving == id)){
                    parent_receiving_quantity = 2;
                    break;
                  }
              receiving_control_mutex.ReleaseMutex();
            }
            ewh.WaitOne();
            Console.WriteLine("Got message "+msg_type+" from "+id+" "+proc_type+"!");
            mt.WaitOne();
            ewh.Reset();
            rewh.Set();
            mt.ReleaseMutex();
            msg_quantity_mutex.WaitOne();
            msg_quantity -= 1;
            lok = msg_quantity;
            msg_quantity_mutex.ReleaseMutex();
            Console.WriteLine(msg_quantity);
            if (lok < 1) {
              Console.WriteLine("Maximal number of messages reached. Exiting...");
              Environment.Exit(0);
            }
            receiving_control_mutex.WaitOne();
            if (proc_type == "child"){
              if (childs_receiving[0] == id){
                if (childs_receiving_quantity[0] == 2){
                  childs_receiving_quantity[0] = 1;
                } else if (childs_receiving_quantity[0] == 1){
                  childs_receiving_quantity[0] = 0;
                  childs_receiving[0] = -1;
                }
              }
            } else {
              if (parent_receiving_quantity == 2){
                parent_receiving_quantity = 1;
              } else {
                parent_receiving = -1;
                parent_receiving_quantity = 0;
              }
            }
            receiving_control_mutex.ReleaseMutex();
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

          Thread cEventHandlerThread = new Thread(() => fEventHandler(ref ewh_c, ref ewh_r_c, ref mtc, id, "C", "child"));
          cEventHandlerThread.Start();

          Thread dEventHandlerThread = new Thread(() => fEventHandler(ref ewh_d, ref ewh_r_d, ref mtd, id, "D", "child"));
          dEventHandlerThread.Start();

          Process process_child = new Process();
          process_child.StartInfo.FileName = "child.exe";
          process_child.StartInfo.Arguments = ""+id;
          process_child.Start();
          process_child.WaitForExit();
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
