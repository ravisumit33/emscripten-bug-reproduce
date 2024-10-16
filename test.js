self.Module = {};
self.Module["locateFile"] = (path, prefix) => {
  return prefix + "build/" + path;
};
Module.mainScriptUrlOrBlob = "http://localhost:8000/" + "build/test.js";
Module.preInit = () => {
  FS.createLazyFile("/", "x.wasm", locateFile("side-module.wasm"), true, false);
};

importScripts("build/test.js");

const collectProfile = () => {
  const wasmExports = Module.asm;
  if (wasmExports.__write_profile) {
    console.log("Collecting profile...");
    const lenProfile = wasmExports.__write_profile(0, 0);
    const bufferPtr = _malloc(lenProfile);
    wasmExports.__write_profile(bufferPtr, lenProfile);
    const m2 = new Uint8Array(wasmMemory.buffer);
    const m3 = m2.slice(bufferPtr, bufferPtr + lenProfile);
    const file = new Blob([m3.buffer], { type: "application/octet-stream" });
    _free(bufferPtr);
    postMessage({ type: "profile", file });
  }
};

onmessage = (e) => {
  console.log("Message recieved on worker: ", e.data);
  const { type } = e.data;
  try {
    switch (type) {
      case "pmodule": {
        console.log(Module._pmodule(1));
        break;
      }
      case "smodule": {
        console.log(Module._smodule(5, 17));
        break;
      }
      case "collectProfile": {
        console.log(Module._pmodule(1));
        collectProfile();
        break;
      }
    }
  } catch (e) {
    console.error(e.message);
    console.log(e.stack);
  }
};
