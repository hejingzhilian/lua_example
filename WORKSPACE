workspace(name = "lua_example")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Lua 5.4.6 source
http_archive(
	name = "lua_src",
	urls = ["https://www.lua.org/ftp/lua-5.4.6.tar.gz"],
	strip_prefix = "lua-5.4.6",
)

# Expose a simple cc_library target from the downloaded Lua sources so other
# targets can depend on it as `@lua_src//:lua`.
http_archive(
	name = "lua_src_with_build",
	urls = ["https://www.lua.org/ftp/lua-5.4.6.tar.gz"],
	strip_prefix = "lua-5.4.6",
	build_file_content = """
cc_library(
	name = "lua",
	srcs = glob(["src/*.c"]),
	hdrs = glob(["src/*.h"]),
	includes = ["src"],
	visibility = ["//visibility:public"],
)
""",
)


