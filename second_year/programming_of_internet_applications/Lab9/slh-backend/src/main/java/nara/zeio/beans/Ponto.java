package nara.zeio.beans;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Column;
import com.fasterxml.jackson.annotation.JsonIgnore;

@Entity
@Table(name = "pontos")
public class Ponto{

  @Id
  @Column(name="id")
  @GeneratedValue(strategy = GenerationType.IDENTITY)
  private long id;

  @Column(name="x")
  private double x;

  @Column(name="y")
  private double y;

  @Column(name="rad")
  private double rad;

  @Column(name="inside")
  private boolean inside;

  public Ponto(){
  }

  public Ponto(double x, double y, double rad, boolean inside){
    this.x = x;
    this.y = y;
    this.rad = rad;
    this.inside = inside;
  }

  public double getX(){
    return x;
  }

  public double getY(){
    return y;
  }

  public void setX(double x){
    this.x = x;
  }

  public void setY(double y){
    this.y = y;
  }

  public long getId(){
    return id;
  }

  public void setId(long id){
    this.id = id;
  }

  public double getRad(){
    return rad;
  }

  public void setRad(double rad){
    this.rad = rad;
  }

  public boolean getInside(){
    return inside;
  }

  public void setInside(boolean inside){
    this.inside = inside;
  }

}
