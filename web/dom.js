"use strict";

var Module = {};

function connectEvents() {
    document.getElementById("num_submit").disabled = false;

    document.getElementById("num_form").onsubmit = function(e) {
        e.preventDefault();

        const res = processString(document.getElementById("num_input").value);

        document.getElementById("num_out").innerText = res;
    };
}

function _decompose_flags(cstr) {
    const res = Module.ccall("em_decompose_flags", "number", ["number"], [cstr])
    if (res === 0) {
        throw "Ran out of memory -- got null from em_decompose_flags";
    }

    try {
        const outStr = UTF8ToString(res);
        return outStr;
    } finally {
        Module.ccall("em_free", null, ["number"], [res]);
    }
}

function processString(str) {
    const len = lengthBytesUTF8(str);
    const buf = Module._malloc(len + 1);

    try {
        stringToUTF8(str, buf, len + 1);
        return _decompose_flags(buf);
    } finally {
        Module._free(buf);
    }
}

Module["onRuntimeInitialized"] = connectEvents;
