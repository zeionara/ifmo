import DS from 'ember-data';
export default DS.RESTSerializer.extend({
  normalizeResponse(store, primaryModelClass, hateoasPayload, id, requestType) {
    let restPayload = {};

    hateoasPayload.meta = {};
    //console.log("jjjjjjjjjj",hateoasPayload);
    if (hateoasPayload._embedded != undefined){
      var pontos = hateoasPayload._embedded.pontos;
      //console.log("hateoas before = ",pontos);
      pontos.forEach(function(item, i, pontos) {
        item.id = i;
        //item.inside = true;
      });
      //console.log("hateoas after = ",hateoasPayload._embedded.pontos);

      hateoasPayload.meta.links = hateoasPayload.links;
      delete hateoasPayload.links;
      restPayload[primaryModelClass.modelName] = pontos;
    } else {
      hateoasPayload.meta.links = hateoasPayload.links;
      delete hateoasPayload.links;
      restPayload[primaryModelClass.modelName] = hateoasPayload;
    }


    //console.log("payload- : ",restPayload);
    restPayload.ponto.id = 1;
    //restPayload.ponto.inside = true;
    //console.log(this._super);
    return this._super(store, primaryModelClass, restPayload, id, requestType);
    //console.log("payload llll: "+hateoasPayload);
  }
});
