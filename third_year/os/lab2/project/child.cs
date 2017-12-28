using System;
using System.Threading;

namespace SecondLab
{
    class Child
    {

        const string C_EVENT_NAME = "c_event_name";
        const string D_EVENT_NAME = "d_event_name";

        const string C_R_EVENT_NAME = "c_r_event_name";
        const string D_R_EVENT_NAME = "d_r_event_name";

        const string C_MUTEX_NAME = "c_mutex_name";
        const string D_MUTEX_NAME = "d_mutex_name";

        static void Main(string[] args)
        {
            EventWaitHandle c_ewh = EventWaitHandle.OpenExisting(C_EVENT_NAME+"_"+args[0]);
            EventWaitHandle d_ewh = EventWaitHandle.OpenExisting(D_EVENT_NAME+"_"+args[0]);

            EventWaitHandle c_r_ewh = EventWaitHandle.OpenExisting(C_R_EVENT_NAME+"_"+args[0]);
            EventWaitHandle d_r_ewh = EventWaitHandle.OpenExisting(D_R_EVENT_NAME+"_"+args[0]);

            Mutex mtc = Mutex.OpenExisting(C_MUTEX_NAME+"_"+args[0]);
            Mutex mtd = Mutex.OpenExisting(D_MUTEX_NAME+"_"+args[0]);

            char[] possible_messages = {'C','D'};
            string message_codes_sequence = "";
            do{
              Console.WriteLine("Please, type message codes sequence (only "+possible_messages[0]+" and "+possible_messages[1]+" are available):");
              message_codes_sequence = getMessageCodesSequence(possible_messages);
            }while(message_codes_sequence == "");

            foreach (char c in message_codes_sequence) {
              if (c == 'C'){
                c_r_ewh.WaitOne();
                mtc.WaitOne();
                c_r_ewh.Reset();
                c_ewh.Set();
                mtc.ReleaseMutex();
              } else {
                d_r_ewh.WaitOne();
                mtd.WaitOne();
                d_r_ewh.Reset();
                d_ewh.Set();
                mtd.ReleaseMutex();
              }
            }
        }

        static string getMessageCodesSequence(char[] possible_messages){
          string message_codes_sequence = Console.ReadLine();
          foreach (char c in message_codes_sequence){
            if (!Array.Exists(possible_messages, element => element == c)) return "";
          }
          return message_codes_sequence;
        }
    }
}
