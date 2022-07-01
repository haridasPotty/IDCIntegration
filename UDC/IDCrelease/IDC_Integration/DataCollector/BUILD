load("@rules_cc//cc:defs.bzl", "cc_binary")

load("@com_google_protobuf//:protobuf.bzl","cc_proto_library")

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")

load("@rules_proto//proto:defs.bzl", "proto_library")

load("@rules_cc//cc:defs.bzl", "cc_library")



cc_binary(
    name = "udcbinary",
    srcs = ["main.cpp"   
    ],
        
    linkopts = [
        "-lpthread", "-lrt",        
    ],
    copts = [ "-std=c++14"],

    deps = [       
        "//UDCsm:udc-sm",        
    ],   
)

cc_library(
    name = "jobx",
    srcs  = [ "Job.cpp" ],
    hdrs = [ "Job.hpp" ,"Parser.hpp"],
    visibility = ["//visibility:public"],
)





#https://chromium.googlesource.com/external/github.com/google/protobuf/+/HEAD/examples

#https://stackoverflow.com/questions/72148865/how-to-reference-bazel-c-protobuf-output-headers-in-a-different-workspace-pack