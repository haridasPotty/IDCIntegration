load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "taskContainer",
    srcs = [ "src/TaskContainer.cpp",
	     "inc/TaskContainer.hpp",
           ],   
    includes = [ 
	"src",
	"inc",
    ],    
     deps = [               
        "@job//:jobx",             
    ],
    visibility = ["//visibility:public"],
)
