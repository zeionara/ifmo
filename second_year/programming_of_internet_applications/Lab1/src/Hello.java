//Файл Hello.java
public class Hello {

    private String name;
    private int sex;

    public Hello() {
        SetName(Constants.DEFAULT_NAME);
        SetSex(Constants.UNDEFINED_SEX);
    }

    public Hello(String name) {
        SetName(name);
        SetSex(Constants.UNDEFINED_SEX);
    }

    public Hello(String name, int sex) {
        SetName(name);
        SetSex(sex);
    }

    public void SetName(String s) {
        for (int i = 0; i < s.length(); i++){
            if ((s.charAt(i) < 65) || ((s.charAt(i) > 90) && (s.charAt(i) < 97)) || (s.charAt(i) > 122)){
                throw new IllegalArgumentException();
            }
        }
        name = s;
    }

    public String GetName (){
        return name;
    }

    public void SetSex(int sex){

        if ((sex != Constants.UNDEFINED_SEX) && (sex != Constants.MAN) && (sex != Constants.WOMAN)){
            throw new IllegalArgumentException();
        }
        this.sex = sex;
    }

    public int GetSex(){
        return sex;
    }

    public void say() {
        String msg = Constants.MORNING_MSG;
        switch (sex){
            case Constants.UNDEFINED_SEX:
                break;
            case Constants.MAN:
                msg += Constants.MR_MSG;
                break;
            case Constants.WOMAN:
                msg += Constants.MRS_MSG;
                break;
            default:
                throw new InternalError();
        }
        msg += name + Constants.EXCL_MSG;
        System.out.println(msg);
    }
}
