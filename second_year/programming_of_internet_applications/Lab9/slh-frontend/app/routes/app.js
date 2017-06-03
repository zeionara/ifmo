import Ember from 'ember';

export default Ember.Route.extend({

  model() {
    //console.log("model returns : ",this.store.findAll("ponto"));
    return this.store.findAll("ponto");
  },
  actions: {
    add(){
       alert(this.controller.get('model.x')); // returns undefined
       // get form values like model.email model.checkbox
    }, reload : function(){
      this.refresh();
    }
  }
});
