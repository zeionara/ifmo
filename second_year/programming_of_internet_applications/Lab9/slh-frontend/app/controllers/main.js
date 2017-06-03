import Ember from 'ember';

export default Ember.Controller.extend({
  init(){
    $(document).ready(function(){
      console.log($(window).width());
      if($(window).width() <= 885) {
        console.log("small");
          $('.emberinputfield').addClass('eif885');
          $('#mainheader').addClass('mh885');
          $('.embersubmitbutton').addClass('esb885');
          $('.embererror').addClass('ee885');
        } else if($(window).width() < 1094) {
          console.log("middle");
            $('.emberinputfield').addClass('eif1094');
            $('#mainheader').addClass('mh1094');
            $('.embersubmitbutton').addClass('esb1094');
            $('.embererror').addClass('ee1094');
          } else {
            $('.emberinputfield').addClass('eiflarge');
          }
    });


    console.log("controller");
    $(window).on('resize', function() {
      console.log("resizing");
      if($(window).width() <= 885) {
          $('.emberinputfield').addClass('eif885');
          $('#mainheader').addClass('mh885');
          $('.embersubmitbutton').addClass('esb885');
          $('.embererror').addClass('ee885');
        } else {
          $('.emberinputfield').removeClass('eif885');
          $('#mainheader').removeClass('mh885');
          $('.embersubmitbutton').removeClass('esb885');
          $('.embererror').removeClass('ee885');
        }
        if(($(window).width() > 885) && ($(window).width() < 1094)) {
            $('.emberinputfield').addClass('eif1094');
            $('#mainheader').addClass('mh1094');
            $('.embersubmitbutton').addClass('esb1094');
            $('.embererror').addClass('ee1094');
          } else {
            $('.emberinputfield').removeClass('eif1094');
            $('#mainheader').removeClass('mh1094');
            $('.embersubmitbutton').removeClass('esb1094');
            $('.embererror').removeClass('ee1094');
          }
          if ($(window).width() >= 1094) {
              $('.emberinputfield').addClass('eiflarge');
            } else {
              $('.emberinputfield').removeClass('eiflarge');
            }
    });
  }
});
