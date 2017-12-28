using System;
using System.Runtime.InteropServices;

namespace ZeroLab
{
  class Program {
      [StructLayout(LayoutKind.Sequential)]
      public class MEMORYSTATUSEX
      {
       public uint dwLength;
       public uint dwMemoryLoad;
       public ulong ullTotalPhys;
       public ulong ullAvailPhys;
       public ulong ullTotalPageFile;
       public ulong ullAvailPageFile;
       public ulong ullTotalVirtual;
       public ulong ullAvailVirtual;
       public ulong ullAvailExtendedVirtual;

       public MEMORYSTATUSEX()
       {
        dwLength = (uint)Marshal.SizeOf(typeof(MEMORYSTATUSEX));
       }
      }

      [return: MarshalAs(UnmanagedType.Bool)]
      [DllImport("Kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
      public static extern bool GlobalMemoryStatusEx(MEMORYSTATUSEX lpBuffer);

      static void Main(string[] args)
      {
       MEMORYSTATUSEX memStatus = new MEMORYSTATUSEX();

       bool success = GlobalMemoryStatusEx(memStatus);

       if (success){
         Console.WriteLine("Available memory : {0} KB", memStatus.ullAvailVirtual/1024);
       } else {
         Console.WriteLine("Error getting available memory");
       }

      }
  }
}
