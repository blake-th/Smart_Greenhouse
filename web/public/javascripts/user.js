$(function() {
    const UPDATE_INTERVAL = 3000;
    

    setInterval(function() {
        var temperature = $('#t-value');//.val();
        var moisture = $('#m-value');
        var luminance = $('#l-value');

        var request = {};
        $.post(window.location.href, request).done(function(response) {
            console.log(response);
            temperature.html(response.temperature);
            moisture.html(response.moisture);
            luminance.html(response.luminance);
        });
    }, UPDATE_INTERVAL);
});