$(function() {
    const UPDATE_INTERVAL = 3000;
    var temperature = $('#t-value');//.val();
    var moisture = $('#m-value');
    var luminance = $('#l-value');

    var request = {};

    setInterval(function() {
        $.post(window.location.href, request).done(function(response) {
            console.log(response);
            temperature.html(response.temperature);
            moisture.html(response.moisture);
            luminance.html(response.luminance);
        });
    }, UPDATE_INTERVAL);
});