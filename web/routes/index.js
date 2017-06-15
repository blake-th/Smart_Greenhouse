var express = require('express');
var router = express.Router();

var temperature = 27.0;
var moisture = 700;
var luminance = 60.0;

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index');
});

router.post('/', function(req, res, next) {
    var response = {
        'temperature': temperature,
        'moisture': moisture,
        'luminance': luminance,
    };
    res.json(response);
});

router.get_sensor_value = function(temperature, moisture, luminance) {
    temperature = temperature;
    moisture = moisture;
    luminance = luminance;
};

module.exports = router;
