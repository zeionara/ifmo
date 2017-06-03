package ru.jsf;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
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
  private Connection con;

  public PontoBean(){
    setActualR("1.0");
  }

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

  public void truncateTable() throws SQLException, ClassNotFoundException{
    String query = "TRUNCATE TABLE pontos";
    Connection con = getConnection();
    PreparedStatement pst = con.prepareStatement(query);
    pst.execute();
    //con.close();
  }

  public List<PontoInfo> getPrevious() throws SQLException, ClassNotFoundException{
    String query = "SELECT * FROM pontos";
    Connection con = getConnection();
    PreparedStatement pst = con.prepareStatement(query);
    ResultSet rs = pst.executeQuery();
    List<PontoInfo> pinfos = new ArrayList<PontoInfo>();

    while(rs.next()) {
      PontoInfo pinfo = new PontoInfo();
      pinfo.setX(rs.getDouble(1));
      pinfo.setY(rs.getDouble(2));
      pinfo.setR(rs.getDouble(3));
      pinfo.setInside(rs.getBoolean(4));
      pinfos.add(pinfo);
    }
    //con.close();
    return pinfos;
  }

  public String updateData() throws SQLException, ClassNotFoundException{
    List<PontoInfo> pinfos = getPrevious();
    truncateTable();
    for(PontoInfo pinfo : pinfos){
      actualX = pinfo.getX();
      actualY = pinfo.getY();
      checkPonto();
    }
    return "successful";
  }

  public String checkPonto() throws SQLException, ClassNotFoundException{
    boolean result = slh.checkPonto(new Ponto(actualX, actualY));
    String query = "INSERT INTO pontos (x, y, r, inside) values('"+getActualX()+"', '"+getActualY()+"', '"+getActualR()+"', '"+result+"')";
    Connection con = getConnection();
    PreparedStatement pst = con.prepareStatement(query);
    pst.execute();

    //con.close();
    if(result) return "successful";
    return "fail";
  }

  public Connection getConnection() throws SQLException, ClassNotFoundException{
    if ((con == null) || con.isClosed()){
      Class.forName("org.postgresql.Driver");

      String url = "jdbc:postgresql://localhost/test";
      String user = "loremipsum";
      String password = "dolorsitamet";

      con = DriverManager.getConnection(url, user, password);
    }
    return con;
  }
}
