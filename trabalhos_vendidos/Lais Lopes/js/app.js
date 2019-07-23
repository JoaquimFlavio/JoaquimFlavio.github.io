var app_id = "029f6cfc";
var app_key = "f875bb1e6bc3398b9f464137d97f8f7a";
var where = document.querySelector('#exampleFormControlInput1');

where.value = "palmas";

var botaoPesquisa = document.querySelector('#botaoPesquisa');

botaoPesquisa.addEventListener("click", function(){
    axios.get('https://api.adzuna.com:443/v1/api/jobs/br/search?app_id='+app_id+'&app_key='+app_key+'&where='+where.value).then(dados => {
        console.log(dados.data.results);
        document.querySelector('#corpo_do_site').innerHTML = null;

        var i =0;
        
        for(dado of dados.data.results) {

            let emprego = `
            <div class="col-lg-4 col-md-6 mb-4">
                <div class="card h-100">
                    <!--<a href="#"><img class="card-img-top" src="http://placehold.it/700x400" alt=""></a>-->
                    <div class="card-body">
                        <h4 class="card-title">
                            <a href="#">${dado.category.label}</a>
                        </h4>
                        
                        <h5>Descrição</h5>
                        <p class="card-text">${dado.title}</p>

                    
                        <!-- Button trigger modal -->
                        <a data-toggle="modal" href="#multiCollapseExample" role="button" aria-expanded="false" data-target="#exampleModal${i}">Leia mais</a>

                        <!-- Modal -->
                        <div class="modal fade" id="exampleModal${i}" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel${i}" aria-hidden="true">
                          <div class="modal-dialog" role="document">
                            <div class="modal-content">
                              <div class="modal-header">
                                <h5 class="modal-title" id="exampleModalLabel${i}">Leia mais</h5>
                                <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                                  <span aria-hidden="true">&times;</span>
                                </button>
                              </div>
                              <div class="modal-body">
                                <p>Creado em: ${dado.created}</p>
                                <p>Localização: ${dado.location.display_name}</p>
                                <p>Empresa: ${dado.company.display_name}</p>
                                ${dado.description}
                              </div>
                            </div>
                          </div>
                        </div>

                    </div>
                    <div class="card-footer">
                        <a href=" ${dado.redirect_url}">Saiba mais!</a>                        
                        <!--<small class="text-muted">&#9733; &#9733; &#9733; &#9733; &#9734;</small>-->
                    </div>
                </div>
            </div>`;

            document.querySelector('#corpo_do_site').innerHTML += emprego;
            i++;
        }
    })
    .catch(resposta => {
        document.querySelector('#corpo_do_site').innerHTML += resposta;
    });
});

botaoPesquisa.click();