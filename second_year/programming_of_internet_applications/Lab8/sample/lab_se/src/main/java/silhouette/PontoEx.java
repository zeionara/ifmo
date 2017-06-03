package silhouette;

public class PontoEx {
    private double x = 0;
    private double y = 0;
    private double r = 0;
    private boolean inside = false;

    public PontoEx(double x, double y, double r, boolean inside){
        this.x = x;
        this.y = y;
        this.r = r;
        this.inside = inside;
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

    public void setR(double r){
        this.r = r;
    }

    public double getR(){
        return r;
    }

    public void setInside(boolean inside){
        this.inside = inside;
    }

    public boolean getInside(){
        return inside;
    }

    public double getGraphX(double R){
        return 1.0;
    }

    public double getGraphY(double R){
        return 1.0;
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

    public String toHTMLTableRaw(){
      String insideStr = "OUT";
      if (inside == true) insideStr = "IN";
      return("<tr><td>"+x+"</td><td>"+y+"</td><td>"+r+"</td><td>"+insideStr+"</td></tr>");
    }
}
