var mymap = L.map('mapid').setView([30.06570, 31.27832], 17);

let lastLat = 0;
let lastLong = 0;
let connected = 0;
let lastUpdate = 0;

L.tileLayer('https://api.mapbox.com/styles/v1/{id}/tiles/{z}/{x}/{y}?access_token=pk.eyJ1IjoibG9heWVsc2hhbGwiLCJhIjoiY2twdG0wZTdkMGRwdTJ3cXd5Nzg1MnNscyJ9.eLOTtKZhCSbzkWboxjS4cg', {
  maxZoom: 18,
  attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors, ' +
    'Imagery © <a href="https://www.mapbox.com/">Mapbox</a>',
  id: 'mapbox/streets-v11',
  tileSize: 512,
  zoomOffset: -1
}).addTo(mymap);


function drawLine(long1, lat1, long2, lat2){
    var polygon = L.polygon([
        [long1, lat1],
        [long2, lat2]
    ]).addTo(mymap);    
}

function checkConnection(){
    let connection = document.getElementById('connection');
    let lastUpdated = document.getElementById('lastUpdated');
    if(connected){
        connection.innerHTML = `Connection Status:  <b style="color: green;">Connected</b>  <span class="material-icons" style="transform: translateY(5px);">radio_button_checked</span>`;
        lastUpdated.innerHTML = `Last Updated: <b>${lastUpdate} secs ago</b>`;
    } else {
        connection.innerHTML = `Connection Status:  <b style="color: red;">Not Connected</b>  <span class="material-icons" style="transform: translateY(5px);">radio_button_unchecked</span>`;
        lastUpdated.innerHTML = `Last Updated: <b>${lastUpdate} secs ago</b>`;
    } 
    lastUpdate++;  
    if(lastUpdate > 30){
        connected = 0;
    }
}

function updateDistance(newDistance){
    document.getElementById('distance').innerHTML = `Distance Moved : ${newDistance} m`;
}




const updateUI = async ()=>{
    const req = await fetch('/fetch');
    try{
        const allData = await req.json()
        updateDistance(allData.distance);
        connected = 1;
        lastUpdate = 0;
        if(lastLong == 0){
            lastLong = allData.long;
            lastLat = allData.lat;
        }
        drawLine(lastLat, lastLong, allData.lat, allData.long);
        lastLat = allData.lat;
        lastLong = allData.long;
    } catch(error){
        console.log(error);
    }
}



setInterval(checkConnection,1000);
setInterval(updateUI, 1000);