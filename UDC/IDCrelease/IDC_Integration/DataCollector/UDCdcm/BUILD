load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "udc-dcm",
    srcs = [ "src/DataCollection.cpp",
	     "inc/DataCollection.hpp",
           ],   
    includes = [ 
	"src",
	"inc",
    ],
    
    deps = [               
        "//Container/JobContainner:jobContainer", 
        "//Container/TaskContainer:taskContainer", 
        
         
                   
    ],
    visibility = ["//visibility:public"],
)
