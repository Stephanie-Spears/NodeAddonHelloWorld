// hello.cc
#include <node.h>

namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "hello world"));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init)

}  // namespace demo

//1.
//Note that all Node.js Addons must export an initialization function following the pattern:
//
//void Initialize(Local<Object> exports);
//NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
//
//There is no semi-colon after NODE_MODULE as it's not a function (see node.h).
//
//The module_name must match the filename of the final binary (excluding the .node suffix).
//
//In the hello.cc example, then, the initialization function is init and the Addon module name is addon.

//2.Once the source code has been written, it must be compiled into the binary add on.node file.
//  To do so, create a file called binding.gyp in the top-level of the project describing the build
//  configuration of the module using a JSON-like format. This file is used by node-gyp -- a tool written
//  specifically to compile Node.js Addons.
//3.use node-gyp configure to generate the appropriate project build files for the current platform.
//4.Next, invoke the node-gyp build command to generate the compiled addon.node file. This will be put into the build/Release/ directory.
//
//  When using npm install to install a Node.js Addon, npm uses its own bundled version of node-gyp to perform this same set of actions, generating a compiled version of the Addon for the user's platform on demand.
//
//  Once built, the binary Addon can be used from within Node.js by pointing require() to the built addon.node module: