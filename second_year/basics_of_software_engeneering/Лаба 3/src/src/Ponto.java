
//Файл Ponto.java
public class Ponto {
    private float x = 0;
    private float y = 0;

    public Ponto(float x, float y){
        this.x = x;
        this.y = y;
    }

    public float getX(){
        return x;
    }

    public float getY(){
        return y;
    }

    public String toString(){
        return ("Ponto { "+x+" ; "+y+" }");
    }
}
