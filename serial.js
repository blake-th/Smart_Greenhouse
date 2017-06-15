var readline = require('readline');

var rl = readline.createInterface({
      input: process.stdin,
      output: process.stdout,
      terminal: false
});

rl.on('line', function (line) {
    var [T, t, M, m, L, l] = line.split(' ');    
    console.log('T:', parseFloat(t), 'M:', parseFloat(m), 'L:', parseFloat(l));
});