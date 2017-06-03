package jswing;

//Файл Ponto.java
public class Ponto {
    private double x = 0;
    private double y = 0;

    private boolean checked = false;
    private boolean inside = false;

    private boolean isfirstCorrectShowing = true;

    public Ponto(double x, double y){
        this.x = x;
        this.y = y;
    }

    public boolean isFirstCorrectShowing(){
        return isfirstCorrectShowing;
    }

    public void showed(){
        isfirstCorrectShowing = false;
    }

    public void setX(double x){
        this.x = x;
    }

    public double getX(){
        return x;
    }

    public void setY(double x){
        this.x = x;
    }

    public double getY(){
        return y;
    }

    public double getGraphX(double R){
        return (x*GraphPanel.GRAPHICAL_R)/R+GraphPanel.OFFSET_TO_CENTER;
    }

    public double getGraphY(double R){
        return (-y*GraphPanel.GRAPHICAL_R)/R+GraphPanel.OFFSET_TO_CENTER;
    }

    public boolean equals(Object obj){
        Ponto anotherPonto;
        try{
            anotherPonto = (Ponto)obj;
        } catch (ClassCastException e){
            return false;
        }
        if ((anotherPonto.getX() == x) && (anotherPonto.getY() == y)){
            return true;
        }
        return false;
    }

    public String toString(){
        return (x+" ; "+y);
    }

    //

    public boolean isChecked(){
        return checked;
    }

    public void checkOff(){
        checked = false;
    }

    public void checkOn(boolean inSilhouette){
        inside = inSilhouette;
        checked = true;
    }

    public boolean isInSilhouette(){
        return inside;
    }
}
