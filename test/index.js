var latte_fs = require('../lib/index');
console.log(latte_fs.existsSync("./build/Release/addon.node"));
latte_fs.exists("./build/Release/addon.node", function(err, result) {
    console.log(err, result);
});
latte_fs.mkdirSync('./hello/word');
latte_fs.removeFileSync('./t/txt');
