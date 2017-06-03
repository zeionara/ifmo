package nara.zeio.authorization;

public class AuthorizationResult{

  private boolean result;

  public AuthorizationResult(){
    result = false;
  }

  public AuthorizationResult(boolean result){
    this.result = result;
  }

  public boolean getResult(){
    return result;
  }

  public void setResult(boolean result){
    this.result = result;
  }

}
