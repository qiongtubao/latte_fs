#include <node.h>
#include <stdint.h>
#include <iostream>
#ifdef WIN32
    #include <io.h>
    #include <direct.h> 
#else
    #include <unistd.h>
    #include <sys/types.h>  
    #include <sys/stat.h> 
#endif


#ifdef WIN32
 
#define ACCESS _access
#define MKDIR(a) _mkdir((a))
 
#else
 
#define ACCESS access
#define MKDIR(a) mkdir((a),0755)
 
#endif

namespace latte_fs
{
    using v8::Exception;
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Number;
    using v8::Object;
    using v8::String;
    using v8::Value;
    using v8::Function;
    using v8::Null;
    //文件是否存在
    void Exists(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        if (args.Length() < 2) {
            // Throw an Error that is passed back to JavaScript
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }

        // Check the argument types
        if (!args[0]->IsString() && !args[1] -> IsFunction()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }
        //args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
        v8::String::Utf8Value param1(args[0]->ToString());
        std::string from = std::string(*param1);
        bool result = access(from.c_str(), 0) != -1;
        Local<Function> cb = Local<Function>::Cast(args[1]);
        const unsigned argc = 2;
        Local<Value> argv[argc] =  {Null(isolate),v8::Boolean::New(isolate, result)} ;
        cb->Call(Null(isolate), argc, argv);
    }
    void ExistsSync(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        if (args.Length() < 1) {
            // Throw an Error that is passed back to JavaScript
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }

        // Check the argument types
        if (!args[0]->IsString()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }
        //args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
        v8::String::Utf8Value param1(args[0]->ToString());
        std::string from = std::string(*param1);
        bool result = access(from.c_str(), 0) != -1;
        args.GetReturnValue().Set(v8::Boolean::New(isolate, result));
    }
    //创建文件夹
    bool createDir(char *pszDir) {
        int i = 0;
        int iRet;
        int iLen = strlen(pszDir);
    
        //在末尾加/
        if (pszDir[iLen - 1] != '\\' && pszDir[iLen - 1] != '/')
        {
            pszDir[iLen] = '/';
            pszDir[iLen + 1] = '\0';
        }
    
        // 创建目录
        for (i = 0;i <= iLen;i ++)
        {
            if (pszDir[i] == '\\' || pszDir[i] == '/')
            { 
                pszDir[i] = '\0';
    
                //如果不存在,创建
                iRet = ACCESS(pszDir,0);
                if (iRet != 0)
                {
                    iRet = MKDIR(pszDir);
                    if (iRet != 0)
                    {
                        return false;
                    } 
                }
                //支持linux,将所有\换成/
                pszDir[i] = '/';
            } 
        }
        return true;

    }


    void Mkdir(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        if (args.Length() < 2) {
            // Throw an Error that is passed back to JavaScript
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }

        // Check the argument types
        if (!args[0]->IsString() && !args[1] -> IsFunction()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }
        v8::String::Utf8Value param1(args[0]->ToString());
        std::string from = std::string(*param1);
        bool result = createDir(*param1);
        Local<Function> cb = Local<Function>::Cast(args[1]);
        const unsigned argc = 2;
        Local<Value> argv[argc] =  {Null(isolate),v8::Boolean::New(isolate, result)} ;
        cb->Call(Null(isolate), argc, argv);
    }
    

    void MkdirSync(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        if (args.Length() < 1) {
            // Throw an Error that is passed back to JavaScript
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }

        // Check the argument types
        if (!args[0]->IsString()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }
        //args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
        v8::String::Utf8Value param1(args[0]->ToString());
        std::string from = std::string(*param1);
        bool result = createDir(*param1);
        args.GetReturnValue().Set(v8::Boolean::New(isolate, result));
    }

    void RemoveFile(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        if (args.Length() < 2) {
            // Throw an Error that is passed back to JavaScript
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }
        // Check the argument types
        if (!args[0]->IsString() && !args[1] -> IsFunction()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }
        v8::String::Utf8Value param1(args[0]->ToString());
        std::string from = std::string(*param1);
        bool result = remove(*param1) == 0;
        Local<Function> cb = Local<Function>::Cast(args[1]);
        const unsigned argc = 2;
        Local<Value> argv[argc] =  {Null(isolate),v8::Boolean::New(isolate, result)} ;
        cb->Call(Null(isolate), argc, argv);
    }

    void RemoveFileSync(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        if (args.Length() < 2) {
            // Throw an Error that is passed back to JavaScript
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }
        // Check the argument types
        if (!args[0]->IsString() && !args[1] -> IsFunction()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }
        v8::String::Utf8Value param1(args[0]->ToString());
        std::string from = std::string(*param1);
        bool result = remove(*param1) == 0;
        args.GetReturnValue().Set(v8::Boolean::New(isolate, result));
    }

    void init(Local<Object> exports) {
        NODE_SET_METHOD(exports, "existsSync", ExistsSync);
        NODE_SET_METHOD(exports, "exists", Exists);
        NODE_SET_METHOD(exports, "mkdirSync", MkdirSync);
        NODE_SET_METHOD(exports, "mkdir", Mkdir);
        NODE_SET_METHOD(exports, "removeSync", RemoveFileSync);
        NODE_SET_METHOD(exports, "remove", RemoveFile);
    }

    NODE_MODULE(addon, init)
} // demo
