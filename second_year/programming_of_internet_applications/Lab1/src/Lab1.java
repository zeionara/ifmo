// Файл Lab1.java
public class Lab1 {
    public static void main(String[] args) {
        Hello h;
        int sex = Constants.UNDEFINED_SEX;
        for (String s : args) {

            switch (s){
                case Constants.MR_SCAN:
                    sex = Constants.MAN;
                    break;
                case Constants.MRS_SCAN:
                    sex = Constants.WOMAN;
                    break;
                default:
                    h = new Hello(s,sex);
                    h.say();
                    sex = Constants.UNDEFINED_SEX;
            }

        } // end of for
    } // end of main
}
