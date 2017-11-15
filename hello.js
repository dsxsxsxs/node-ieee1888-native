var addon = require('bindings')('ieee1888');

// console.log(addon.hello()); // 'world'
var m_IEEE1888_FROM="http://fiap-sandbox.gutp.ic.i.u-tokyo.ac.jp/axis2/services/FIAPStorage";
var pointIds=[
    "http://gutp.jp/Arduino/Labo-a003/Temp",
    "http://gutp.jp/Arduino/Labo-a003/Illuminance"
];
setInterval(function () {
    var rs=addon.fetch(pointIds,m_IEEE1888_FROM);
    console.log(new Date().toLocaleString(),rs);
// console.log(process.memoryUsage());
// gc();
}, 1000);
