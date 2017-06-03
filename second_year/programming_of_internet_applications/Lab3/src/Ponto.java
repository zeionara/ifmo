/**
 * Created by Zerbs on 08.10.2016.
 */
//Файл Ponto.java
public class Ponto {
    private float x = 0;
    private float y = 0;

    public Ponto(float x, float y){
        this.x = x;
        this.y = y;
    }

    public void setX(float x){
        this.x = x;
    }

    public float getX(){
        return x;
    }

    public void setY(float x){
        this.x = x;
    }

    public float getY(){
        return y;
    }

    public String toString(){
        return ("Ponto { "+x+" ; "+y+" }");
    }
}
