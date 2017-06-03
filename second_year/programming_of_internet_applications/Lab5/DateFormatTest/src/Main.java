import sun.util.resources.cldr.en.TimeZoneNames_en;

import java.text.DateFormat;
import java.text.DateFormatSymbols;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;

/**
 * Created by Zerbs on 20.11.2016.
 */
public class Main {
    private static Date date = new Date(System.currentTimeMillis());

    public static void main(String[] args) {
        //DateFormat
        DateFormat dateFormat = DateFormat.getDateInstance(DateFormat.FULL, Locale.GERMAN);
        System.out.println(dateFormat.format(date));
        //output : Sonntag, 20. November 2016

        dateFormat = DateFormat.getDateInstance(DateFormat.LONG, Locale.CHINA);
        System.out.println(dateFormat.format(date));
        //output : 2016年11月20日

        dateFormat.setCalendar(Calendar.getInstance(Locale.TAIWAN));
        System.out.println(dateFormat.format(date));
        //output : 2016年11月20日

        //SimpleDateFormat
        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("Эра : GGGG\nГод : YYYY\nМесяц : MMMM\nДень : dd\n"+
                "День от начала года : DD\nЧас : HH\nМинута : mm\nСекунда : ss\nМиллисекунда : SS"+
                "\nНеделя в году : ww\nНеделя в месяце : WW");
        System.out.println(simpleDateFormat.format(date));

        System.out.println(365d/7d);

        //DateFormatSymbols
        DateFormatSymbols dateFormatSymbols = new DateFormatSymbols();
        dateFormatSymbols.setWeekdays(new String[]{"ПН","ВТ","СР","ЧТ","ПТ","СБ","ВС"});
        simpleDateFormat = new SimpleDateFormat("EEEE-YYYY-MMMM",dateFormatSymbols);
        System.out.println(simpleDateFormat.format(date));
    }
}
