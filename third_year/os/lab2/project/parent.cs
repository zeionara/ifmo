using System;
using System.Threading;

namespace SecondLab
{
    class Parent
    {

      const string A_EVENT_NAME = "a_event_name";
      const string B_EVENT_NAME = "b_event_name";

      const string A_R_EVENT_NAME = "a_r_event_name";
      const string B_R_EVENT_NAME = "b_r_event_name";

      const string A_MUTEX_NAME = "a_mutex_name";
      const string B_MUTEX_NAME = "b_mutex_name";

      static void Main(string[] args)
      {
          EventWaitHandle a_ewh = EventWaitHandle.OpenExisting(A_EVENT_NAME+"_"+args[0]);
          EventWaitHandle b_ewh = EventWaitHandle.OpenExisting(B_EVENT_NAME+"_"+args[0]);

          EventWaitHandle a_r_ewh = EventWaitHandle.OpenExisting(A_R_EVENT_NAME+"_"+args[0]);
          EventWaitHandle b_r_ewh = EventWaitHandle.OpenExisting(B_R_EVENT_NAME+"_"+args[0]);

          Mutex mta = Mutex.OpenExisting(A_MUTEX_NAME+"_"+args[0]);
          Mutex mtb = Mutex.OpenExisting(B_MUTEX_NAME+"_"+args[0]);

          char[] possible_messages = {'A','B'};
          string message_codes_sequence = "";
          do{
            Console.WriteLine("Please, type message codes sequence (only "+possible_messages[0]+" and "+possible_messages[1]+" are available):");
            message_codes_sequence = getMessageCodesSequence(possible_messages);
          }while(message_codes_sequence == "");

          foreach (char c in message_codes_sequence) {
            if (c == 'B'){
              //Console.WriteLine("Sending B...");
              b_r_ewh.WaitOne();
              mtb.WaitOne();
              b_r_ewh.Reset();
              b_ewh.Set();
              mtb.ReleaseMutex();
            } else {
              a_r_ewh.WaitOne();
              mta.WaitOne();
              a_r_ewh.Reset();
              a_ewh.Set();
              mta.ReleaseMutex();
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
