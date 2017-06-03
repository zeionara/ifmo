import DS from 'ember-data';

export default DS.Model.extend({
  x : DS.attr(),
  y : DS.attr(),
  inside : DS.attr(),
  rad : DS.attr()
});
