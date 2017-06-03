import DS from 'ember-data';

export default DS.JSONAPIAdapter.extend({
  host: 'http://localhost:20762',
  headers: {
    'Accept': '*/*'
  }
});
