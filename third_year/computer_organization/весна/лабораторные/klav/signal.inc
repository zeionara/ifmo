 SIGNAL void Signa (unsigned int Time) {
twatch (Time);  //задержка Time  мкс при частоте f0=12м√ц
while (1) {
PORT3 = 0x3f;
twatch (Time);
PORT3 = 0;
twatch (2*Time);
} }

Signa(1000) //запуск функции
La PORT3 //вывод сигнала в јнализаторе
