var fs = require('fs');
var nowTime = Date.now();
console.log(fs.existsSync('./build/Release/addon.node'));
console.log(Date.now() - nowTime);