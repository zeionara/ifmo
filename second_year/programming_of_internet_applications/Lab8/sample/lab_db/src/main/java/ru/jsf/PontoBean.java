package ru.jsf;

import java.io.Serializable;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import java.util.Date;

import javax.faces.application.FacesMessage;
import javax.faces.context.FacesContext;
import org.primefaces.event.SlideEndEvent;
import silhouette.*;

@ManagedBean
@SessionScoped
public class PontoBean{
  private double actualX;
  private double actualY;
  private double actualR;
  private GeneralSilhouette slh;

  public String getActualX(){
    return String.valueOf(actualX);
  }

  public void setActualX(String actualX){
    this.actualX = Double.parseDouble(actualX);
  }

  public String getActualY(){
    return String.valueOf(actualY);
  }

  public void setActualY(String actualY){
    this.actualY = Double.parseDouble(actualY);
  }

  public String getActualR(){
    return String.valueOf(actualR);
  }

  public void setActualR(String actualR){
    this.actualR = Double.parseDouble(actualR);
    slh = new GeneralSilhouette(this.actualR);
  }

  public String checkPonto() throws SQLException, ClassNotFoundException{
    String query = "INSERT INTO pontos (x, y, r, inside) values('6.6', '5.5', '4.4', 'true')";
    Connection con = getConnection();
    PreparedStatement pst = con.prepareStatement(query);
    pst.execute();

    if(slh.checkPonto(new Ponto(actualX, actualY))) return "successful";
    return "fail";
  }

  public Connection getConnection() throws SQLException, ClassNotFoundException{
      Class.forName("org.postgresql.Driver");
      Connection con = null;
      String url = "jdbc:postgresql://localhost/test";
      String user = "postgres";
      String password = "1234";

      con = DriverManager.getConnection(url, user, password);
      return con;
  }
}
