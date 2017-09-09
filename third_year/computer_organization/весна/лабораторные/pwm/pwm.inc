
 SIGNAL void pwm (unsigned int Time) { 
 
//twatch(4*Time);  //искусственная задержка для синхронизации  в реальном времени исполнения функции pwm( ) и основной программы
while(1)
{         // формирование диаграммы, соответствующей  биту 
          //  P3.i = 1  ,  i=0..5  , S1=6
P3 = 0;		 
twatch (Time); 
P3 = 0x3f;                 
twatch (2*Time);
         // формирование диаграммы, соответствующей  биту 
         //  P3.i = 0,  S0=3
P3 = 0;		
twatch (2*Time);
P3 = 0x3f;
twatch (Time);
           //S1=6
P3 = 0;
twatch (Time);         
P3 = 0x3f;
twatch (2*Time);

            //S0=3
P3 = 0;
twatch (2*Time);	       
P3 = 0x3f;
twatch (Time);

P3=0;
twatch(10*Time);
 }
}

pwm(100)                // разрешение формирования сигнала

La  PORT3   // ввод значения с виртуального входа порта P3  и вывод в графике        
