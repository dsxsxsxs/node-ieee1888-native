var addon = require('bindings')('ieee1888');

// console.log(addon.hello()); // 'world'
var m_IEEE1888_FROM="http://fiap-sandbox.gutp.ic.i.u-tokyo.ac.jp/axis2/services/FIAPStorage";
var pointIds=[
    "http://gutp.jp/Arduino/test-001/Temperature",
    "http://gutp.jp/Arduino/test-001/Illuminance",
    "http://gutp.jp/Arduino/test-001/DIPSW",
    "http://gutp.jp/Arduino/test-001/TGLSW"
];
setInterval(function () {
    var rs=addon.fetch(pointIds,m_IEEE1888_FROM);
    console.log(new Date().toLocaleString(),rs);

}, 1000);
