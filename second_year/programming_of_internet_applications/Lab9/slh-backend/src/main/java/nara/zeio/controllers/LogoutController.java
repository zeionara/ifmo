package nara.zeio.controllers;

import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import nara.zeio.authorization.AuthorizationResult;
import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.CrossOrigin;

@RestController
@CrossOrigin
@RequestMapping("/logout")
class LogoutController{
  @RequestMapping(method = RequestMethod.GET)
  AuthorizationResult logOut(HttpServletRequest request){
    System.out.println("LOGGED OUT -----------------------------------------------------------------");
    ((AuthorizationResult)request.getSession().getAttribute("authResult")).setResult(false);
    return (AuthorizationResult)request.getSession().getAttribute("authResult");
  }
}
