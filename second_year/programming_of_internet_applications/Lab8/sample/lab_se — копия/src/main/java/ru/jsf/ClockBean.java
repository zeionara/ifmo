package ru.jsf;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import java.util.Date;

@ManagedBean
@SessionScoped
public class ClockBean{
  private String serverTime = "";

  public void updateServerTime(){
    Date date = new Date();
    serverTime = date.toString();
  }

  public String getServerTime(){
      updateServerTime();
      return serverTime;
  }

  public void setServerTime(String time){
    Date date = new Date();
    serverTime = date.toString();
  }
}
