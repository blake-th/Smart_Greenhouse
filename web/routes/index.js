var express = require('express');
var router = express.Router();
var child_process = require('child_process');
router.temperature = 27.0;
router.moisture = 700;
router.luminance = 60.0;
router.roof_state = 'c';

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index');
});

router.post('/', function(req, res, next) {
    var {roof_state} = req.body;
    console.log(req.body);
    
    if ((roof_state === 'o' && router.roof_state === 'c') || (roof_state === 'c' && router.roof_state === 'o')) {
        router.roof_state = roof_state;
        child_process.exec('echo "'+router.roof_state+'\n" > /dev/cu.usbmodem1421', function(err, stdout, stderr) {
            if (err) {
                console.log("\n"+stderr);
            } else {
                console.log(stdout);
            }
        });
        /*child_process.exec('echo "'+router.roof_state+'\n" > /dev/cu.usbmodem1411', function(err, stdout, stderr) {
            if (err) {
                console.log("\n"+stderr);
            } else {
                console.log(stdout);
            }
        });*/
    }
    
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
