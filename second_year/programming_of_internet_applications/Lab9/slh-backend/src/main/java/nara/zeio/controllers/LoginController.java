package nara.zeio.controllers;
import nara.zeio.authentication.PasswordAuthentication;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.CrossOrigin;

import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.beans.factory.annotation.Autowired;

import nara.zeio.authorization.Key;
import nara.zeio.authorization.AuthorizationResult;
import org.springframework.jdbc.core.RowMapper;
import java.util.List;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.http.Cookie;
import org.springframework.context.annotation.Scope;

import org.springframework.web.bind.annotation.ModelAttribute;
import nara.zeio.authorization.AuthorizationDetails;

@RestController
@CrossOrigin
@RequestMapping("/login")
class LoginController{

  @Autowired
  JdbcTemplate jdbcTemplate;

  private String attr;

  @RequestMapping(method = RequestMethod.POST)
  AuthorizationResult isThereUser(@ModelAttribute Key key, HttpServletRequest request, HttpServletResponse res, HttpSession httpSession){
    System.out.println("Current session : ");
    System.out.println(httpSession);
    res.setHeader("Set-Cookie",res.getHeader("Set-Cookie")+";Domain=google.com");
    System.out.println(res.getHeader("Set-Cookie"));
    System.out.println(httpSession.getMaxInactiveInterval());
    httpSession.setAttribute("attr","attr");
    //attr = "attr";
    //System.out.println(attr);
    System.out.println(httpSession.getAttribute("attr"));
    res.addCookie(new Cookie("oop","argument"));
    PasswordAuthentication passwordAuthentication = new PasswordAuthentication();
    System.out.println(request.getSession().getAttribute("authResult"));
    List<Key> keys = jdbcTemplate.query( "select login, password from users", new RowMapper<Key>() {
      public Key mapRow(ResultSet rs, int rowNum) throws SQLException {
        Key key = new Key();
        key.setLogin(rs.getString("login"));
        key.setPassword(rs.getString("password"));
        return key;
      }
    });

    for (Key ikey : keys) if (passwordAuthentication.authenticate(key.getPassword().toCharArray(),ikey.getPassword()) && ikey.getLogin().equals(key.getLogin())){
      System.out.println("YOU MAY PASS");
      if (request.getSession().getAttribute("authResult") == null){
        request.getSession().setAttribute("authResult",new AuthorizationResult(true));
      } else {
        ((AuthorizationResult)request.getSession().getAttribute("authResult")).setResult(true);
      }
      System.out.println(((AuthorizationResult)request.getSession().getAttribute("authResult")).getResult());
      System.out.println(request);
      System.out.println(request.getSession());
      System.out.println(request.getCookies());
      //List<String> strList =
      List<String> strLst = jdbcTemplate.query("select email from users where login='"+ikey.getLogin()+"';", new RowMapper() {
        public String mapRow(ResultSet rs, int rowNum) throws SQLException{
          return rs.getString("email");
        }
      });

      System.out.println("email is "+strLst.get(0));
      request.getSession().setAttribute("authDeatails",new AuthorizationDetails(strLst.get(0), ikey.getLogin()));
      return new AuthorizationResult(true);
    }
    System.out.println("YOU SHALL NOT PASS");
    return new AuthorizationResult(false);
  }

  @RequestMapping(method = RequestMethod.GET)
  AuthorizationResult isThereUser(HttpServletRequest request, HttpServletResponse res, HttpSession httpSession){
    System.out.println("Current session : ");
    System.out.println(httpSession);
    System.out.println(httpSession.getId());
    System.out.println(httpSession.getMaxInactiveInterval());
    //System.out.println(attr);
    System.out.println(httpSession.getAttribute("attr"));
    res.setHeader("Set-Cookie",res.getHeader("Set-Cookie")+";Domain=google.com");
    res.setHeader("Set-Cookie",res.getHeader("Set-Cookie").replaceAll("HttpOnly;",""));
    res.setHeader("Set-Cookie","my=value");
    System.out.println("ok-------------------------");
    System.out.println(request);
    System.out.println(request.getSession());
    System.out.println(request.getSession().getAttribute("authResult"));
    System.out.println(request.isRequestedSessionIdFromCookie());
    System.out.println(request.getCookies());
    //System.out.println(((AuthorizationResult)request.getSession().getAttribute("authResult")).getResult());
    if ((AuthorizationResult)request.getSession().getAttribute("authResult") != null)
    return (AuthorizationResult)request.getSession().getAttribute("authResult");
    return new AuthorizationResult(true);
  }

  /*@RequestMapping(method = RequestMethod.POST)
  AuthorizationResult isThereUser( Key key){
    PasswordAuthentication passwordAuthentication = new PasswordAuthentication();

    List<Key> keys = jdbcTemplate.query( "select login, password from users", new RowMapper<Key>() {
      public Key mapRow(ResultSet rs, int rowNum) throws SQLException {
        Key key = new Key();
        key.setLogin(rs.getString("login"));
        key.setPassword(rs.getString("password"));
        return key;
      }
    });

    for (Key ikey : keys) if (passwordAuthentication.authenticate(key.getPassword().toCharArray(),ikey.getPassword()) && ikey.getLogin().equals(key.getLogin())){
      System.out.println("YOU MAY PASS");
      return new AuthorizationResult(true);
    }
    System.out.println("YOU SHALL NOT PASS");
    return new AuthorizationResult(false);
  }*/
}
