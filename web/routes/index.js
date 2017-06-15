var express = require('express');
var router = express.Router();

router.temperature = 27.0;
router.moisture = 700;
router.luminance = 60.0;

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index');
});

router.post('/', function(req, res, next) {

    var response = {
        'temperature': router.temperature,
        'moisture': router.moisture,
        'luminance': router.luminance,
    };
    console.log(response);
    res.json(response);
});

router.get_sensor_value = function(temperature, moisture, luminance) {
    router.temperature = temperature;
    router.moisture = moisture;
    router.luminance = luminance;
    console.log('GET_SENSOR_VALUE', temperature, moisture, luminance);
};

module.exports = router;
