var campo_dia = document.querySelector('#campo_dia');
var campo_mes = document.querySelector('#campo_mes');
var campo_ano = document.querySelector('#campo_ano');
var campo_tipo = document.querySelector('#campo_tipo');
var botao_busca = document.querySelector('#botao_busca');

var meses = ["Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"];

botao_busca.addEventListener('click', function(){    
    var parametros = '';
    
    if(campo_dia.value != 0){
        parametros += '&day='+campo_dia.value;
    }
    if(campo_mes.value != 'Desabilitar'){
        for(var i=0; i < 12; i++){
            if(campo_mes.value == meses[i]){
                i++;
                break;
            }
        }
        parametros += '&month='+i;
    }
    if(campo_tipo.value != 'Desabilitar'){
        parametros += '&type='+campo_tipo.value;
    }
    
    axios.get('https://calendarific.com/api/v2/holidays?api_key=55dac0eaf2bed4054ae3f56d90394afdbb9fcd5ef7b9c9ac8b4fa94bc5e5d75f&country=BR&year='+campo_ano.value+parametros)
    .then(dados => {
        
        if(dados.data.response.holidays == ''){
           document.querySelector('#feriados').innerHTML = `
            <div class="alert alert-danger" role="alert">
                Nenhum resultado encontrado para esses filtros!
            </div>`;
        }else{
        
        console.log(dados.data);
        
        document.querySelector('#feriados').innerHTML = '';
        
        for(feriado of dados.data.response.holidays) {

            let caixaDeFeriado = `
                <div class="col-md-4 mb-5">
                    <div class="card h-100">
                        <div class="card-header"><h4 class="card-title">${feriado.name}</h4></div>
                        <div class="card-body">
                            <h4 class="card-title">Descrição</h4>
                            <p class="card-text">${feriado.description}</p>
                            <ul>
                                <li>Data: ${feriado.date.datetime.day}/${feriado.date.datetime.month}/${feriado.date.datetime.year}</li>
                                <li>Tipo: ${feriado.type}</li>
                            </ul>
                        </div>
                    </div>
                </div>`;

            document.querySelector('#feriados').innerHTML += caixaDeFeriado;
        }
        }
    })
    .catch(resposta => {
        document.querySelector('#feriados').innerHTML += resposta;
    });
    
});