package ru.jsf;


import javax.annotation.PostConstruct;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.RequestScoped;

@ManagedBean(name="helloWorldBean")
@RequestScoped
public class HelloWorldBean {
	private String msg;

	public String getMsg() {
		return msg;
	}
	public void setMsg(String msg) {
		this.msg = msg;
	}
	@PostConstruct
	private void init() {

		msg = "Hello World!! JFS example.. ";
	}

}
