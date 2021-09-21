"use strict";

var Module = {};

function connectEvents() {
    /*console.log(Module)
    var myStr = "0x2"
    var len = lengthBytesUTF8(myStr)
    console.log(len)
    var buf = Module._malloc(40)
    stringToUTF8(myStr, buf, 40)
    var res = Module.ccall("em_decompose_flags", "number", ["number"], [buf])
    var outStr = UTF8ToString(res)
    console.log("OUT", outStr)*/

    document.getElementById("num_submit").onclick = function(e) {
        e.preventDefault();

        const res = processString(document.getElementById("num_input").value);

        document.getElementById("num_out").innerText = res;
    };
}

function processString(str) {
    // FIXME(colin): Free memory
    const len = lengthBytesUTF8(str);
    const buf = Module._malloc(len + 1);
    stringToUTF8(str, buf, len + 1);

    const res = Module.ccall("em_decompose_flags", "number", ["number"], [buf])

    const outStr = UTF8ToString(res);

    return outStr;
}

Module["onRuntimeInitialized"] = connectEvents;
