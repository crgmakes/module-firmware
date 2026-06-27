Import("env")
env.Append(CXXFLAGS=["-Wno-register"])
# Import("projenv")
# for e in (env):
#     e.Append(CXXFLAGS=["-Wno-register"])