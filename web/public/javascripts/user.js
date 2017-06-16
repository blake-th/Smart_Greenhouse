$(function() {
    const UPDATE_INTERVAL = 3000;
    var roof_state = 'c';
    $('#open-btn').on('click', function(event) {
        roof_state = 'o';
    });

    $('#close-btn').on('click', function(event) {
        roof_state = 'c';
    });

    setInterval(function() {
        var temperature = $('#t-value');//.val();
        var moisture = $('#m-value');
        var luminance = $('#l-value');

        var request = {
            roof_state: roof_state
        };
        $.post(window.location.href, request).done(function(response) {
            console.log(response);
            temperature.html(response.temperature);
            moisture.html(response.moisture);
            luminance.html(response.luminance);
        });
    }, UPDATE_INTERVAL);


});