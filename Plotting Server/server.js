// Setup empty JS object to act as endpoint for all routes
projectData = [];

// Require Express to run server and routes
const express = require('express');

// Start up an instance of app
const app = express();

const bodyParser = require('body-parser');

/* Middleware*/
//Here we are configuring express to use body-parser as middle-ware.
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());


// Cors for cross origin allowance
const cors = require('cors');
app.use(cors());

// Initialize the main project folder
app.use(express.static('.'));


// Setup Server
const port = 8000;
const server = app.listen(process.env.PORT || 5000, ()=>{console.log('server running'); console.log(`running on localhost: ${process.env.PORT || 5000}`);});



//Setup a get url and function 
app.get('/',(req, res)=>{
    console.log("Requested Main");
    res.redirect('maps.html');
});


// app.post('/update', (req, res)=>{
//     newEntry = {
//         'lat': req.body.lat,
//         'long' : req.body.long,
//         'distance' : req.body.distance
//     }
//     projectData.push(newEntry);
//     res.status(200);
//     console.log(req);
// });


app.get('/update', (req, res)=>{ 
    let lat = req.query.lat;
    let long = req.query.long;
    newEntry = {
        'lat': lat.replace("^", "."),
        'long' : long.replace("^", "."),
        'distance' : req.query.distance
    }
    projectData.push(newEntry);
    console.log(newEntry);
    res.status(200);
    res.json({"success": true});
    
});

app.get('/fetch', (req, res)=>{
    res.status(200);
    res.send(projectData[projectData.length-1]);
});


app.get('/clear', (req, res)=>{
    projectData = [];
    res.status(200);
    res.redirect('/');
});