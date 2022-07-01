load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "jobContainer",
    srcs = [ "src/JobContainer.cpp",
	     "inc/JobContainer.hpp",
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
