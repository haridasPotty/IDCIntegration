load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "udc-sm",
    srcs = [ "src/statemachine.cpp",
	     "inc/statemachine.hpp",
     ],   
    includes = [ 
		"src",
		"inc",
     ],    
    copts = [ "-std=c++14"],    
    deps = [               
        "//Container/JobContainner:jobContainer", 
        #"//Container/TaskContainer:taskContainer",        
        "//UDCdcm:udc-dcm", 
        "//UDCcm:commMngr" , 
        "@my_protos//:point_cc_proto",                   
    ],
    visibility = ["//visibility:public"],
)
