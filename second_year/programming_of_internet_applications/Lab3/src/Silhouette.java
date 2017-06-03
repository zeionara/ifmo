/**
 * Created by Zerbs on 08.10.2016.
 */
//Файл Silhouette
public class Silhouette {
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

    public boolean checkPonto(Ponto p){
        float x = p.getX();
        float y = p.getY();

        return ((x*x + y*y < r*r) && (x > 0) && (y > 0)) || //part of circle
                (((x > -r) && (x < 0)) && ((y > -r) && (y < 0))) || //square
                ((y > x - r/2) && (x >= 0) && (y <= 0) && !((x == 0) && (y == 0))); //triangle
    }
}
