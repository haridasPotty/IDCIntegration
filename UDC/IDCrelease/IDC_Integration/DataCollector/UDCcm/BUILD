load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "commMngr",
    srcs = [ "src/CommManager.cpp",
	     "inc/CommManager.h",
           ],   
    includes = [ 
	"src",
	"inc",
    ],
    #Simulator client code dependancy
    deps = [               
        "@simltrCOMMN//:simcom",              
    ],
    visibility = ["//visibility:public"],
)
