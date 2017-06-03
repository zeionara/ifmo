import Ember from 'ember';

export default Ember.Component.extend({
  isLoginFailed:false,
  isProcessing:false,

  tryDisable : function(){
    console.log(this.get("password"));
    if (this.get("login") && this.get("login").length && this.get("password") && this.get("password").length){
      $('.submit').removeAttr("disabled");
    } else {
      $(".submit").attr("disabled","true");
    }
  },
  isLoginValid:Ember.computed("login",function(){

    this.tryDisable();

    return this.get("login") && this.get("login").length;
  }),
  isPasswordValid:Ember.computed("password",function(){
    this.tryDisable();
    return this.get("password") && this.get("password").length;
  }),
  init(){
    $(".cop").click();
    this.tryDisable();
    this._super();
  },
  actions : {
    submit(){
      var external_this = this;
      this.setProperties({
        loginFailed:false,
        isProcessing:true
      })
      $.post("http://localhost:20762/login",{
        login: this.get("login"),
        password: this.get("password")
      }).then(function(data){
        external_this.set("isProcessing", false);
        if (data.result){
          document.location = "app";
        } else {
          external_this.set("loginFailed",true);
        }
      }, function(){
        this.set("isProcessing", false);
        this.set("loginFailed",true);
      }.bind(this));
    },
    loginChanged(login){
      this.set("login", login);
      console.log(this.store);
    },
    passwordChanged(password){
      this.set("password", password);
    }
  }
});
