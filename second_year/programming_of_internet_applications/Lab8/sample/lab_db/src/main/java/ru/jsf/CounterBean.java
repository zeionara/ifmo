package ru.jsf;

import java.io.Serializable;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ViewScoped;

@ManagedBean
@ViewScoped
public class CounterBean {
  private int count;
  public void increment() {
    count++;
  }
  public int getCount() {
    return this.count;
  }
  public void setCount(int count) {
    this.count = count;
  }
}
