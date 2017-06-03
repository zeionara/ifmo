package nara.zeio.beans;

public class PontoShort{

  private double x;

  private double y;

  private double rad;

  public PontoShort(){

  }

  public PontoShort(double x, double y, double rad){
    this.x = x;
    this.y = y;
    this.rad = rad;
  }

  public void setX(double x){
    this.x = x;
  }

  public double getX(){
    return x;
  }

  public void setY(double y){
    this.y = y;
  }

  public double getY(){
    return y;
  }

  public double getRad(){
    return rad;
  }

  public void setRad(double rad){
    this.rad = rad;
  }

  @Override
  public String toString(){
    return ("Ponto[ x = "+x+", y = "+y+", rad = "+rad+" ] ");
  }
}
