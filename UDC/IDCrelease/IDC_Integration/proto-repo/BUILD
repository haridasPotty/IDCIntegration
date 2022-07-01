load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
package(default_visibility = ["//visibility:public"])

cc_proto_library(
    name = "point_cc_proto",
    visibility = ["//visibility:public"],
    deps = [":my-proto"],
)


proto_library(
    name = "my-proto",
    srcs = [
        "data_types.proto",
        "logical_expression.proto",
        "signal_source_definition.proto",
        "data_collection_configuration_request.proto",
        "backend_message_format.proto",
        "static_config_udc_civic.proto",
    ],
    visibility = ["//visibility:public"],
)


