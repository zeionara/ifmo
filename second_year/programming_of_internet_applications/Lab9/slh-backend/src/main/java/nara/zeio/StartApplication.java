package nara.zeio;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import javax.sql.DataSource;
import org.apache.commons.dbcp.BasicDataSource;

import org.springframework.boot.CommandLineRunner;

import org.springframework.context.annotation.*;

import org.springframework.cloud.netflix.zuul.EnableZuulProxy;

import nara.zeio.mail.Sender;

@EnableZuulProxy
@SpringBootApplication
public class StartApplication implements CommandLineRunner{

  //@Autowired
  //JdbcTemplate jdbcTemplate;

  public static void main(String[] args) throws Exception{

    SpringApplication.run(StartApplication.class, args);
  }

  @Override
  public void run(String... strings) throws Exception {
    //Sender.sendMessage();
    //int total = jdbcTemplate.queryForInt("select r from pontos");
    //System.out.println(total);
  }

  @Bean
    public DataSource dataSource()
    {
        BasicDataSource dataSource = new BasicDataSource();
        dataSource.setUrl("jdbc:postgresql://localhost:5443/test");
        dataSource.setUsername("loremipsum");
        dataSource.setPassword("dolorsitamet");
        return dataSource;
    }

}
