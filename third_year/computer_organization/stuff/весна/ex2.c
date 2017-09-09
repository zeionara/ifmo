

#include <rtx51tny.h>                 
#include <reg51.h>

char counter0;                        
char counter1;                        
char counter2;                        
char counter3;                        

job0 () _task_ 0  {                  
  os_create_task (1);            
  os_create_task (2);            
  os_create_task (3);            

  while (1)  {                        
     os_wait (K_TMO, 1, 0);      
	 counter0+=0x10;
  }
}

job1 () _task_ 1  {
  while (1)  {                        
     os_wait (K_TMO, 1, 0);           
	 counter1+=0x10;          
  }
}

job2 () _task_ 2  {
  while (1)  {                   
  counter2+=0x10;
    if (counter2 == 0)  {  
      os_send_signal (3);  
      }
  }
}

job3 () _task_ 3  {
  while (1)  {            
    counter3+=0x10; 
	os_wait (K_SIG, 1, 0); 
                          
  }
}
