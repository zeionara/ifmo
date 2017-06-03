package ru.jsf;

public class PontoInfo{
  private double x;
  private double y;
  private double r;
  private boolean inside;

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
}
