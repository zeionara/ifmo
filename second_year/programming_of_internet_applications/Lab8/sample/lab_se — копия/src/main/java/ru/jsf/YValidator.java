package ru.jsf;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.faces.application.FacesMessage;
import javax.faces.component.UIComponent;
import javax.faces.context.FacesContext;
import javax.faces.validator.FacesValidator;
import javax.faces.validator.Validator;
import javax.faces.validator.ValidatorException;

@FacesValidator("ru.jsf.YValidator")
public class YValidator implements Validator{
  private void throwError(){
    FacesMessage msg = new FacesMessage("Y validation failed.","Invalid Y value.");
    msg.setSeverity(FacesMessage.SEVERITY_ERROR);
    throw new ValidatorException(msg);
  }

	@Override
	public void validate(FacesContext context, UIComponent component,Object value) throws ValidatorException {
    double validated = 0;
    try{
      validated = Double.parseDouble(value.toString());
    } catch (NumberFormatException e){
      throwError();
    }
    if ((validated < -5) || (validated > 3)) throwError();
  }
}
