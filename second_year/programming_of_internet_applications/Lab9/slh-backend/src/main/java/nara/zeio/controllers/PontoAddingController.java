package nara.zeio.controllers;

import org.springframework.data.rest.webmvc.RepositoryRestController;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import nara.zeio.authorization.AuthorizationResult;
import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RequestBody;
import nara.zeio.beans.PontoShort;
import nara.zeio.beans.Ponto;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.ModelAttribute;
import nara.zeio.storages.PontoRepository;
import java.util.List;
import nara.zeio.mail.Sender;
import nara.zeio.authorization.AuthorizationDetails;
import org.springframework.web.bind.annotation.CrossOrigin;

@RepositoryRestController
@CrossOrigin
@RequestMapping("/addponto")
class PontoAddingController{

  private final PontoRepository repository;

  @Autowired
  public PontoAddingController(PontoRepository repository){
    this.repository = repository;
  }

  @RequestMapping(method = RequestMethod.POST)
  public @ResponseBody AuthorizationResult addPonto(@RequestBody PontoShort pontoShort, HttpServletRequest request){
    System.out.println("PONTO -----------------------------------------------------------------");
    System.out.println(pontoShort);
    List<Ponto> matched = repository.findByXAndYAndRad(pontoShort.getX(),pontoShort.getY(),pontoShort.getRad());
    if (matched.size() == 0){
      Ponto newPonto = new Ponto(pontoShort.getX(), pontoShort.getY(), pontoShort.getRad(), isInsideArea(pontoShort.getX(), pontoShort.getY(), pontoShort.getRad()));
      repository.save(newPonto);
      Sender.sendMessage((AuthorizationDetails)request.getSession().getAttribute("authDeatails"),newPonto);
    }
    //((AuthorizationResult)request.getSession().getAttribute("authResult")).setResult(false);
    return new AuthorizationResult(true);
  }

  private boolean isInsideArea(double x, double y, double r){
    return (isInsideRectangle(x,y,r) || isInsideTriangle(x,y,r) || isInsideCircle(x,y,r));
  }

  private boolean isInsideRectangle(double x, double y, double r){
    return ((y > -r/2) && (y < 0) && (x > 0) && (x < r));
  }

  private boolean isInsideTriangle(double x, double y, double r){
    return ((x >= 0) && (y >= 0) && (y < (r/2 - x)));
  }

  private boolean isInsideCircle(double x, double y, double r){
    return ((x < 0) && (y > 0) && (x*x + y*y < r*r));
  }
}
/*package nara.zeio.controllers;

import org.springframework.data.rest.webmvc.RepositoryRestController;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.beans.factory.annotation.Autowired;

import nara.zeio.beans.PontoShort;
import nara.zeio.authorization.AuthorizationResult;
import nara.zeio.storages.PontoRepository;

import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.ModelAttribute;

@RepositoryRestController

class PontoAddingController{

  private final PontoRepository repository;

  @Autowired
  public PontoAddingController(PontoRepository repository){
    this.repository = repository;
  }

  @RequestMapping(method = RequestMethod.GET, value = "/scanners")
  AuthorizationResult addPonto(@ModelAttribute PontoShort pontoShort, HttpServletRequest request){
    System.out.println("GOT SHORT PONTO");
    return new AuthorizationResult(true);
  }

}*/
