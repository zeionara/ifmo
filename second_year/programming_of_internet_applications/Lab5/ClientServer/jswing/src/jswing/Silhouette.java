package jswing;

//Файл Silhouette
public abstract class Silhouette{
    private double r = 0;

    public Silhouette(double r){
        setR(r);
    }

    public void setR(double r){
        if (r <= 0){
            throw new IllegalArgumentException();
        }
        this.r = r;
    }

    public double getR(){
        return r;
    }
}
